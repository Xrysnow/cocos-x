#include "platform/FileDialogInternal.h"

#include "base/ccUTF8.h"
#include "platform/android/jni/JniHelper.h"

#include <algorithm>
#include <atomic>
#include <charconv>
#include <limits>
#include <mutex>

namespace cc::dialog {
namespace {
constexpr char Bridge[] = "org/cocos/lib/CocosFileDialog";
constexpr char DirectoryMime[] = "vnd.android.document/directory";
constexpr jint ReadGrant = 1, WriteGrant = 2;
constexpr jint Open = 0, Folder = 1, Export = 2;
constexpr jint Ok = 0, Cancelled = 1;

FileDialogError androidError(DialogErrorCode code, std::string message = {}, int64_t native = 0)
{
    return {code, std::move(message), "android", native};
}

class LocalFrame {
public:
    explicit LocalFrame(JNIEnv* env) : _env(env), _valid(env->PushLocalFrame(32) == 0) {
        if (!_valid) _env->ExceptionClear();
    }
    ~LocalFrame() { if (_valid) _env->PopLocalFrame(nullptr); }
    explicit operator bool() const { return _valid; }
private:
    JNIEnv* _env;
    bool _valid;
};

std::optional<std::string> fromJava(JNIEnv* env, jstring value)
{
    if (!value) return {};
    std::u16string utf16(env->GetStringLength(value), u'\0');
    env->GetStringRegion(value, 0, static_cast<jsize>(utf16.size()), reinterpret_cast<jchar*>(utf16.data()));
    std::string utf8;
    if (env->ExceptionCheck() || !StringUtils::UTF16ToUTF8(utf16, utf8)) return {};
    return utf8;
}

jstring toJava(JNIEnv* env, const std::string& value)
{
    std::u16string utf16;
    if (!StringUtils::UTF8ToUTF16(value, utf16) || utf16.size() > std::numeric_limits<jsize>::max())
        return nullptr;
    return env->NewString(reinterpret_cast<const jchar*>(utf16.data()), static_cast<jsize>(utf16.size()));
}

FileDialogError takeJavaError(JNIEnv* env)
{
    jthrowable exception = env->ExceptionOccurred();
    if (!exception) return {};
    env->ExceptionClear();
    LocalFrame locals(env);
    DialogErrorCode code = DialogErrorCode::IoError;
    std::string message;
    if (locals) {
        for (const auto& [type, mapped] : {
                 std::pair{"java/lang/SecurityException", DialogErrorCode::PermissionDenied},
                 {"java/io/FileNotFoundException", DialogErrorCode::NotFound},
                 {"java/lang/IllegalArgumentException", DialogErrorCode::InvalidResult},
                 {"java/lang/UnsupportedOperationException", DialogErrorCode::UnsupportedFeature},
                 {"java/lang/OutOfMemoryError", DialogErrorCode::OutOfMemory}}) {
            jclass clazz = env->FindClass(type);
            if (clazz && env->IsInstanceOf(exception, clazz)) {
                code = mapped;
                break;
            }
            env->ExceptionClear();
        }
        jclass throwable = env->FindClass("java/lang/Throwable");
        jmethodID describe = throwable ? env->GetMethodID(throwable, "toString", "()Ljava/lang/String;") : nullptr;
        if (describe) {
            auto result = static_cast<jstring>(env->CallObjectMethod(exception, describe));
            if (!env->ExceptionCheck()) message = fromJava(env, result).value_or("");
        }
        env->ExceptionClear();
    }
    env->DeleteLocalRef(exception);
    return androidError(code, std::move(message));
}

template<class Invoke>
FileDialogError withJava(const char* method, const char* signature, const Invoke& invoke)
{
    if (!JniHelper::getJavaVM() || !JniHelper::classloader)
        return androidError(DialogErrorCode::Unavailable, "Android Java bridge is unavailable");
    JNIEnv* env = JniHelper::getEnv();
    if (!env) return androidError(DialogErrorCode::Unavailable, "Android Java environment is unavailable");
    LocalFrame locals(env);
    if (!locals) return androidError(DialogErrorCode::OutOfMemory);
    JniMethodInfo call{};
    if (!JniHelper::getStaticMethodInfo(call, Bridge, method, signature))
        return androidError(DialogErrorCode::Unavailable, "Android document bridge method is unavailable");
    auto error = invoke(call);
    auto javaError = takeJavaError(env);
    return javaError ? javaError : error;
}

io::StreamError streamError(DialogErrorCode code)
{
    switch (code) {
    case DialogErrorCode::PermissionDenied: return {io::ErrorCode::PermissionDenied};
    case DialogErrorCode::NotFound: return {io::ErrorCode::NotFound};
    case DialogErrorCode::OutOfMemory: return {io::ErrorCode::OutOfMemory};
    default: return {io::ErrorCode::IoError};
    }
}

// The caller owns the JNI frame and closes the stream before leaving it.
// ContentResolver streams can be pipe-backed or have an AssetFileDescriptor offset.
class ProviderStream final : public io::Stream {
public:
    ProviderStream(RefConstructionToken token, JNIEnv* env, jobject stream, jmethodID transfer,
                   jmethodID flush, jmethodID close, jbyteArray bytes, bool writable, std::optional<int64_t> size)
        : Stream(token), _env(env), _stream(stream), _transfer(transfer), _flush(flush), _close(close),
          _bytes(bytes), _writable(writable), _size(size) {}

    io::Capability capabilities() const noexcept override {
        return _writable ? io::Capability::Write : io::Capability::Read;
    }
    bool isOpen() const noexcept override { return _stream != nullptr; }
    io::IoResult read(void* destination, size_t length) override {
        if (!isOpen()) return io::IoResult::failure({io::ErrorCode::Closed});
        if (_writable) return io::IoResult::failure({io::ErrorCode::NotSupported});
        if (length == 0) return io::IoResult::success(0);
        if (!destination) return io::IoResult::failure({io::ErrorCode::InvalidArgument});
        auto count = static_cast<jint>(std::min(length, BufferSize));
        auto received = _env->CallIntMethod(_stream, _transfer, _bytes, 0, count);
        if (_env->ExceptionCheck()) return io::IoResult::failure(streamError(takeJavaError(_env).code));
        if (received == -1) return {0, io::IoStatus::EndOfStream, {}};
        if (received <= 0 || received > count)
            return io::IoResult::failure({received == 0 ? io::ErrorCode::NoProgress : io::ErrorCode::InvalidBackend});
        _env->GetByteArrayRegion(_bytes, 0, received, static_cast<jbyte*>(destination));
        if (_env->ExceptionCheck()) return io::IoResult::failure(streamError(takeJavaError(_env).code));
        _position += received;
        return io::IoResult::success(received);
    }
    io::IoResult write(const void* source, size_t length) override {
        if (!isOpen()) return io::IoResult::failure({io::ErrorCode::Closed});
        if (!_writable) return io::IoResult::failure({io::ErrorCode::NotSupported});
        if (length == 0) return io::IoResult::success(0);
        if (!source) return io::IoResult::failure({io::ErrorCode::InvalidArgument});
        auto count = static_cast<jint>(std::min(length, BufferSize));
        _env->SetByteArrayRegion(_bytes, 0, count, static_cast<const jbyte*>(source));
        if (!_env->ExceptionCheck()) _env->CallVoidMethod(_stream, _transfer, _bytes, 0, count);
        if (_env->ExceptionCheck()) return io::IoResult::failure(streamError(takeJavaError(_env).code));
        _position += count;
        return io::IoResult::success(count);
    }
    io::Result<int64_t> tell() const override {
        if (!isOpen()) return io::Result<int64_t>::failure({io::ErrorCode::Closed});
        return io::Result<int64_t>::success(_position);
    }
    io::Result<std::optional<int64_t>> size() const override {
        using Result = io::Result<std::optional<int64_t>>;
        if (!isOpen()) return Result::failure({io::ErrorCode::Closed});
        if (_writable) return Result::success(_position);
        return Result::success(_size);
    }
    io::Status seek(io::SeekOrigin, int64_t) override {
        return io::Status::failure({isOpen() ? io::ErrorCode::NotSupported : io::ErrorCode::Closed});
    }
    io::Status flush() override {
        if (!isOpen()) return io::Status::failure({io::ErrorCode::Closed});
        if (!_writable) return io::Status::success();
        _env->CallVoidMethod(_stream, _flush);
        auto error = takeJavaError(_env);
        return error ? io::Status::failure(streamError(error.code)) : io::Status::success();
    }
    io::Status close() override {
        auto stream = std::exchange(_stream, nullptr);
        if (!stream) return io::Status::success();
        _env->CallVoidMethod(stream, _close);
        auto error = takeJavaError(_env);
        return error ? io::Status::failure(streamError(error.code)) : io::Status::success();
    }

    static constexpr size_t BufferSize = 64 * 1024;
private:
    JNIEnv* _env;
    jobject _stream;
    jmethodID _transfer, _flush, _close;
    jbyteArray _bytes;
    bool _writable;
    std::optional<int64_t> _size;
    int64_t _position = 0;
};

FileDialogError useStream(const std::string& uri, bool writable, std::optional<int64_t> size,
                          const StreamOperation& operation)
{
    return withJava(writable ? "openWrite" : "openRead",
                    writable ? "(Ljava/lang/String;)Ljava/io/OutputStream;" : "(Ljava/lang/String;)Ljava/io/InputStream;",
                    [&](const JniMethodInfo& call) -> FileDialogError {
        JNIEnv* env = call.env;
        jclass type = env->FindClass(writable ? "java/io/OutputStream" : "java/io/InputStream");
        if (!type) return {};
        auto close = env->GetMethodID(type, "close", "()V");
        if (!close) return {};
        auto transfer = env->GetMethodID(type, writable ? "write" : "read", writable ? "([BII)V" : "([BII)I");
        if (!transfer) return {};
        auto flush = writable ? env->GetMethodID(type, "flush", "()V") : nullptr;
        if (writable && !flush) return {};
        auto buffer = env->NewByteArray(ProviderStream::BufferSize);
        if (!buffer) return androidError(DialogErrorCode::OutOfMemory);
        auto path = toJava(env, uri);
        if (!path) return androidError(DialogErrorCode::EncodingError);
        auto stream = env->CallStaticObjectMethod(call.classID, call.methodID, path);
        if (env->ExceptionCheck() || !stream)
            return androidError(DialogErrorCode::IoError, "Android provider did not open the stream");
        ThreadSafeRefPtr<ProviderStream> adapter;
        FileDialogError error;
        try {
            adapter = makeThreadSafeRef<ProviderStream>(env, stream, transfer, flush, close, buffer, writable, size);
            error = operation(*adapter);
            if (!error && writable && !adapter->flush())
                error = androidError(DialogErrorCode::IoError, "Android provider stream flush failed");
        } catch (const std::bad_alloc&) {
            error = androidError(DialogErrorCode::OutOfMemory);
        } catch (...) {
            error = androidError(DialogErrorCode::IoError, "Android document stream operation failed");
        }
        if (!adapter) {
            env->CallVoidMethod(stream, close);
        } else if (!adapter->close() && !error) {
            error = androidError(DialogErrorCode::IoError, "Android provider stream close failed");
        }
        return error;
    });
}

std::atomic<uint64_t> documentSession{1};

void cleanup(const std::string& uri)
{
    withJava("cleanup", "(Ljava/lang/String;)V", [&](const JniMethodInfo& call) -> FileDialogError {
        if (auto path = toJava(call.env, uri))
            call.env->CallStaticVoidMethod(call.classID, call.methodID, path);
        return {};
    });
}

class AndroidDocument final : public DocumentProvider, public std::enable_shared_from_this<AndroidDocument> {
public:
    AndroidDocument() { location = LocationKind::AndroidDocument; }
    DocumentAccessHints hints() const override {
        if (_session != documentSession.load()) return {};
        const bool read = (grants & ReadGrant) != 0;
        const bool directory = kind == DocumentKind::Directory;
        return {read && !directory, read && directory, directory && (grants & WriteGrant) != 0};
    }
    ~AndroidDocument() override {
        if (!unwritten) return;
        try { cleanup(uri); } catch (...) {}
    }
    std::string legacyAndroidUri() const override { return uri; }
    FileDialogError read(const StreamOperation& operation) override {
        if (auto error = checkGrant(ReadGrant)) return error;
        if (kind != DocumentKind::File)
            return androidError(DialogErrorCode::InvalidArgument, "A file document is required");
        return useStream(uri, false, length ? std::optional<int64_t>(*length) : std::nullopt, operation);
    }
    FileDialogError children(size_t maximum, std::vector<DocumentHandle>& out) override;
    FileDialogError write(const std::string& childName, const StreamOperation&, DocumentHandle&, ExternalEffect&) override;

    std::string uri;
    jint grants = 0;
    bool unwritten = false;

private:
    FileDialogError checkGrant(jint needed) const {
        if (_session != documentSession.load())
            return androidError(DialogErrorCode::PermissionDenied, "Android document session has ended");
        if ((grants & needed) == 0)
            return androidError(DialogErrorCode::PermissionDenied, "The selected document did not grant this access");
        return {};
    }
    uint64_t _session = documentSession.load();
};

std::shared_ptr<AndroidDocument> documentFromRow(JNIEnv* env, jobjectArray row)
{
    if (!row || env->GetArrayLength(row) != 5) return {};
    LocalFrame locals(env);
    if (!locals) throw std::bad_alloc();
    std::string fields[5];
    for (jsize index = 0; index < 5; ++index) {
        auto value = static_cast<jstring>(env->GetObjectArrayElement(row, index));
        if (env->ExceptionCheck()) return {};
        auto field = fromJava(env, value);
        if (!field || field->find('\0') != std::string::npos) return {};
        fields[index] = std::move(*field);
    }
    if (!fields[0].starts_with("content://")) return {};

    auto result = std::make_shared<AndroidDocument>();
    result->uri = std::move(fields[0]);
    result->name = std::move(fields[1]);
    result->mime = std::move(fields[2]);
    if (result->mime == DirectoryMime) result->kind = DocumentKind::Directory;
    int64_t length = -1;
    const auto endLength = fields[3].data() + fields[3].size();
    auto parsedLength = std::from_chars(fields[3].data(), endLength, length);
    if (parsedLength.ec == std::errc{} && parsedLength.ptr == endLength && length >= 0) result->length = length;
    const auto endGrants = fields[4].data() + fields[4].size();
    auto parsedGrants = std::from_chars(fields[4].data(), endGrants, result->grants);
    if (parsedGrants.ec != std::errc{} || parsedGrants.ptr != endGrants) return {};
    return result;
}

FileDialogError AndroidDocument::children(size_t maximum, std::vector<DocumentHandle>& out)
{
    if (auto error = checkGrant(ReadGrant)) return error;
    if (kind != DocumentKind::Directory)
        return androidError(DialogErrorCode::InvalidArgument, "A directory document is required");
    if (maximum > std::numeric_limits<jint>::max())
        return androidError(DialogErrorCode::LimitExceeded, "Android document enumeration limit is too large");
    return withJava("children", "(Ljava/lang/String;II)[[Ljava/lang/String;",
                    [&](const JniMethodInfo& call) -> FileDialogError {
        auto path = toJava(call.env, uri);
        if (!path) return androidError(DialogErrorCode::EncodingError);
        auto rows = static_cast<jobjectArray>(call.env->CallStaticObjectMethod(
                call.classID, call.methodID, path, static_cast<jint>(maximum), grants));
        if (call.env->ExceptionCheck()) return {};
        if (!rows) return androidError(DialogErrorCode::LimitExceeded, "Android directory exceeds the entry limit");
        jsize count = call.env->GetArrayLength(rows);
        for (jsize index = 0; index < count; ++index) {
            LocalFrame item(call.env);
            if (!item) return androidError(DialogErrorCode::OutOfMemory);
            auto row = static_cast<jobjectArray>(call.env->GetObjectArrayElement(rows, index));
            if (call.env->ExceptionCheck()) return {};
            auto provider = documentFromRow(call.env, row);
            if (!provider) return androidError(DialogErrorCode::InvalidResult, "Invalid Android child document");
            out.push_back(Documents::wrap(std::move(provider)));
        }
        return {};
    });
}

FileDialogError AndroidDocument::write(const std::string& childName, const StreamOperation& operation,
                                      DocumentHandle& actual, ExternalEffect& effect)
{
    if (auto error = checkGrant(WriteGrant)) return error;
    auto target = shared_from_this();
    if (!childName.empty()) {
        if (kind != DocumentKind::Directory)
            return androidError(DialogErrorCode::InvalidArgument, "A directory document is required");
        // The caller supplies only a filename. SAF applies the provider's create and naming rules.
        effect = ExternalEffect::PartialPossible;
        auto error = withJava("create", "(Ljava/lang/String;Ljava/lang/String;I)[Ljava/lang/String;",
                              [&](const JniMethodInfo& call) -> FileDialogError {
            auto path = toJava(call.env, uri);
            if (!path) return androidError(DialogErrorCode::EncodingError);
            auto name = toJava(call.env, childName);
            if (!name) return androidError(DialogErrorCode::EncodingError);
            auto row = static_cast<jobjectArray>(call.env->CallStaticObjectMethod(
                    call.classID, call.methodID, path, name, grants));
            if (call.env->ExceptionCheck()) return {};
            target = documentFromRow(call.env, row);
            if (!target) return androidError(DialogErrorCode::InvalidResult, "Invalid Android export document");
            target->unwritten = true;
            return {};
        });
        if (error) return error;
    }
    if (!target->unwritten)
        return androidError(DialogErrorCode::UnsupportedFeature, "Android writes require a newly created document");

    effect = ExternalEffect::PartialPossible;
    auto error = useStream(target->uri, true, {}, operation);
    target->unwritten = false;
    if (error) {
        bool removed = false;
        auto removeError = withJava("remove", "(Ljava/lang/String;)Z", [&](const JniMethodInfo& call) -> FileDialogError {
            auto path = toJava(call.env, target->uri);
            if (path) removed = call.env->CallStaticBooleanMethod(call.classID, call.methodID, path) == JNI_TRUE;
            return {};
        });
        if (!removed) {
            actual = Documents::wrap(target);
            error.message += removeError ? "; cleanup failed: " + removeError.message
                                         : "; provider declined to remove the incomplete export";
        }
        return error;
    }

    // The post-close provider size is optional and can differ from the creation-time size.
    target->length.reset();
    actual = Documents::wrap(target);
    effect = ExternalEffect::Committed;
    return {};
}

struct Pending {
    uint64_t id = 0;
    uint64_t session = 0;
    Operation operation = Operation::Open;
    NativeCallback callback;
};

std::mutex pendingMutex;
Pending pending;

Pending takePending(uint64_t id)
{
    std::lock_guard guard(pendingMutex);
    return pending.id == id ? std::exchange(pending, {}) : Pending{};
}

void failPending(uint64_t id, FileDialogError error)
{
    auto request = takePending(id);
    if (request.callback) {
        NativeResult result;
        result.error = std::move(error);
        request.callback(std::move(result));
    }
}

bool finishNative(JNIEnv* env, uint64_t id, jint status, jstring message, jobjectArray rows, bool created)
{
    auto request = takePending(id);
    if (!request.callback || request.session != documentSession.load()) return false;
    NativeResult result;
    bool owned = false;
    try {
        if (status == Ok) {
            LocalFrame locals(env);
            if (!locals) throw std::bad_alloc();
            jsize count = rows ? env->GetArrayLength(rows) : 0;
            if (count == 0 || (request.operation != Operation::Open && count != 1))
                result.error = androidError(DialogErrorCode::InvalidResult, "Invalid Android selection count");
            for (jsize index = 0; index < count && !result.error; ++index) {
                auto row = static_cast<jobjectArray>(env->GetObjectArrayElement(rows, index));
                auto document = documentFromRow(env, row);
                env->DeleteLocalRef(row);
                if (!document) {
                    result.error = androidError(DialogErrorCode::InvalidResult, "Invalid Android document metadata");
                } else if (request.operation == Operation::Export) {
                    result.displayName = document->name;
                    document->unwritten = true;
                    result.target = Documents::wrap(std::move(document));
                    owned = true;
                } else {
                    result.documents.push_back(Documents::wrap(std::move(document)));
                }
            }
            if (!result.error) result.status = DialogStatus::Ok;
            else result.documents.clear();
        } else if (status == Cancelled) {
            result.status = DialogStatus::Cancelled;
            result.cancelReason = CancelReason::User;
        } else {
            constexpr DialogErrorCode errors[] = {
                DialogErrorCode::None, DialogErrorCode::None, DialogErrorCode::Unavailable, DialogErrorCode::Busy,
                DialogErrorCode::ParentClosed, DialogErrorCode::PermissionDenied, DialogErrorCode::InvalidResult,
                DialogErrorCode::LimitExceeded, DialogErrorCode::BackendError, DialogErrorCode::NotFound,
                DialogErrorCode::IoError, DialogErrorCode::OutOfMemory, DialogErrorCode::Timeout
            };
            auto error = status > Cancelled && status < static_cast<jint>(std::size(errors))
                    ? errors[status] : DialogErrorCode::BackendError;
            result.error = androidError(error, fromJava(env, message).value_or(""), status);
        }
        if (auto error = takeJavaError(env)) {
            result = {};
            result.error = std::move(error);
        }
    } catch (const std::bad_alloc&) {
        result = {};
        result.error.code = DialogErrorCode::OutOfMemory;
        env->ExceptionClear();
    } catch (...) {
        result = {};
        result.error.code = DialogErrorCode::BackendError;
        env->ExceptionClear();
    }
    if (created) result.effect = ExternalEffect::PartialPossible;
    request.callback(std::move(result));
    return owned || request.operation != Operation::Export;
}
}

DialogCapabilities nativeCapabilities()
{
    DialogCapabilities capabilities;
    capabilities.backend = "android-saf";
    jint sdk = 0;
    withJava("availability", "()I", [&](const JniMethodInfo& call) -> FileDialogError {
        sdk = call.env->CallStaticIntMethod(call.classID, call.methodID);
        return {};
    });
    if (sdk == 0) capabilities.unavailableReason = "Android Activity is unavailable";
    capabilities.available = sdk > 0;
    capabilities.openFiles = capabilities.multipleFiles = capabilities.pickFolder = capabilities.exportFile = true;
    capabilities.initialDirectoryHint = sdk >= 26;
    return capabilities;
}

void presentNative(NativeRequest request, NativeCallback callback)
{
    if (request.operation == Operation::SaveTarget) {
        NativeResult result;
        result.error = androidError(DialogErrorCode::UnsupportedFeature, "SAF creates the selected export document");
        callback(std::move(result));
        return;
    }
    bool accepted;
    {
        std::lock_guard guard(pendingMutex);
        accepted = !pending.callback;
        if (accepted) pending = {request.id, documentSession.load(), request.operation, std::move(callback)};
    }
    if (!accepted) {
        NativeResult result;
        result.error = androidError(DialogErrorCode::Busy, "An Android document selection is active");
        callback(std::move(result));
        return;
    }
    try {
        auto error = withJava("present", "(JILjava/lang/String;Ljava/lang/String;[Ljava/lang/String;ZZI)Z",
                              [&](const JniMethodInfo& call) -> FileDialogError {
            auto* env = call.env;
            jstring initial = nullptr;
            if (request.options.initialDirectory) {
                auto provider = std::dynamic_pointer_cast<AndroidDocument>(Documents::get(*request.options.initialDirectory));
                if (provider) {
                    initial = toJava(env, provider->uri);
                    if (!initial) return androidError(DialogErrorCode::EncodingError);
                }
            }
            auto name = toJava(env, request.suggestedName);
            if (!name) return androidError(DialogErrorCode::EncodingError);
            std::vector<std::string> types;
            for (const auto& filter : request.options.filters) {
                if (!filter.mimeTypes.empty()) {
                    types.insert(types.end(), filter.mimeTypes.begin(), filter.mimeTypes.end());
                } else {
                    for (const auto& extension : filter.extensions) types.push_back("." + extension);
                }
            }
            if (types.size() > std::numeric_limits<jsize>::max())
                return androidError(DialogErrorCode::LimitExceeded, "Android MIME filter count exceeds the limit");
            jclass javaString = env->FindClass("java/lang/String");
            if (!javaString) return {};
            auto array = env->NewObjectArray(static_cast<jsize>(types.size()), javaString, nullptr);
            if (!array) return androidError(DialogErrorCode::OutOfMemory);
            for (size_t index = 0; index < types.size(); ++index) {
                auto value = toJava(env, types[index]);
                if (!value) return androidError(DialogErrorCode::EncodingError);
                env->SetObjectArrayElement(array, static_cast<jsize>(index), value);
                env->DeleteLocalRef(value);
                if (env->ExceptionCheck()) return {};
            }
            jint operation = request.operation == Operation::Folder ? Folder
                    : request.operation == Operation::Export ? Export : Open;
            auto posted = env->CallStaticBooleanMethod(call.classID, call.methodID, static_cast<jlong>(request.id),
                    operation, initial, name, array, static_cast<jboolean>(request.options.allowAllFiles),
                    static_cast<jboolean>(request.options.allowMultiple),
                    static_cast<jint>(std::min(request.options.maxSelectionCount,
                                              static_cast<uint32_t>(std::numeric_limits<jint>::max()))));
            return posted ? FileDialogError{} : androidError(DialogErrorCode::Unavailable, "Android UI queue is unavailable");
        });
        if (error) failPending(request.id, std::move(error));
    } catch (const std::bad_alloc&) {
        failPending(request.id, {DialogErrorCode::OutOfMemory, {}, {}, 0});
    } catch (...) {
        failPending(request.id, {DialogErrorCode::BackendError, {}, {}, 0});
    }
}

void cancelNative(uint64_t id)
{
    withJava("cancel", "(J)V", [&](const JniMethodInfo& call) -> FileDialogError {
        call.env->CallStaticVoidMethod(call.classID, call.methodID, static_cast<jlong>(id));
        return {};
    });
}

void shutdownNative()
{
    uint64_t id;
    {
        std::lock_guard guard(pendingMutex);
        ++documentSession;
        id = std::exchange(pending, {}).id;
    }
    if (id) cancelNative(id);
}
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosFileDialog_nativeResult(
        JNIEnv* env, jclass, jlong request, jint status, jstring message, jobjectArray documents, jboolean created)
{
    try {
        return cc::dialog::finishNative(env, request, status, message, documents, created == JNI_TRUE) ? JNI_TRUE : JNI_FALSE;
    } catch (...) {
        env->ExceptionClear();
        return JNI_FALSE;
    }
}
