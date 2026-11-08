#include "platform/CCAppDirectories.h"

#include <algorithm>
#include <array>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <mutex>
#include <utility>
#include <vector>

#if defined(_WIN32)
#    include <Windows.h>
#    include <ShlObj.h>
#elif defined(__ANDROID__)
#    include <jni.h>
#    include <sys/stat.h>
#elif defined(__APPLE__)
#    include <sys/stat.h>
#else
#    include <pwd.h>
#    include <sys/stat.h>
#    include <unistd.h>
#endif

#ifndef CC_APP_DIRECTORY_DEFAULT_ID
#    define CC_APP_DIRECTORY_DEFAULT_ID "org.cocos2d.application"
#endif

NS_CC_BEGIN

AppDirectoryConfig::AppDirectoryConfig() : appId(CC_APP_DIRECTORY_DEFAULT_ID) {}

#if defined(__APPLE__)
// Foundation is deliberately confined to the Objective-C++ provider.
DirectoryResult queryAppleAppDirectory(AppDirectory kind, const std::string& appId);
#endif

namespace
{
DirectoryResult failure(DirectoryStatus status, const char* domain = "", std::int64_t code = 0)
{
    return {status, {}, domain, code};
}

DirectoryResult success(std::string path)
{
    return {DirectoryStatus::Ok, std::move(path), {}, 0};
}

bool validUtf8(std::string_view value)
{
    for (size_t i = 0; i < value.size();)
    {
        const auto first = static_cast<unsigned char>(value[i++]);
        if (first == 0)
            return false;
        if (first < 0x80)
            continue;
        unsigned count;
        std::uint32_t code;
        if (first >= 0xc2 && first <= 0xdf) { count = 1; code = first & 0x1f; }
        else if (first >= 0xe0 && first <= 0xef) { count = 2; code = first & 0x0f; }
        else if (first >= 0xf0 && first <= 0xf4) { count = 3; code = first & 0x07; }
        else return false;
        if (value.size() - i < count)
            return false;
        for (unsigned n = 0; n < count; ++n)
        {
            const auto next = static_cast<unsigned char>(value[i++]);
            if ((next & 0xc0) != 0x80)
                return false;
            code = (code << 6) | (next & 0x3f);
        }
        if ((count == 1 && code < 0x80) || (count == 2 && code < 0x800) ||
            (count == 3 && code < 0x10000) || code > 0x10ffff || (code >= 0xd800 && code <= 0xdfff))
            return false;
    }
    return true;
}

bool reservedWindowsName(std::string_view component)
{
    std::string stem(component.substr(0, component.find('.')));
    std::transform(stem.begin(), stem.end(), stem.begin(), [](unsigned char c) {
        return c >= 'A' && c <= 'Z' ? static_cast<char>(c + ('a' - 'A')) : static_cast<char>(c);
    });
    while (!stem.empty() && (stem.back() == ' ' || stem.back() == '.'))
        stem.pop_back();
    return stem == "con" || stem == "prn" || stem == "aux" || stem == "nul" ||
           (stem.size() == 4 && (stem.compare(0, 3, "com") == 0 || stem.compare(0, 3, "lpt") == 0) &&
            stem[3] >= '1' && stem[3] <= '9') ||
           (stem.size() == 5 && (stem.compare(0, 3, "com") == 0 || stem.compare(0, 3, "lpt") == 0) &&
            (stem.compare(3, 2, "\xc2\xb9") == 0 || stem.compare(3, 2, "\xc2\xb2") == 0 ||
             stem.compare(3, 2, "\xc2\xb3") == 0)) ||
           stem == "conin$" || stem == "conout$";
}

#if defined(_WIN32)
bool validWindowsComponent(std::string_view component)
{
    if (component.empty() || component.back() == '.' || component.back() == ' ' || reservedWindowsName(component))
        return false;
    return std::none_of(component.begin(), component.end(), [](unsigned char c) {
        return c < 32 || c == '<' || c == '>' || c == ':' || c == '"' || c == '|' || c == '?' || c == '*';
    });
}
#endif

bool validAppId(std::string_view id)
{
    if (id.empty() || id.size() > 200)
        return false;
    size_t start = 0;
    for (size_t end = 0; end <= id.size(); ++end)
    {
        if (end == id.size() || id[end] == '.')
        {
            if (end == start || reservedWindowsName(id.substr(start, end - start)))
                return false;
            start = end + 1;
        }
        else if (!((id[end] >= 'a' && id[end] <= 'z') || (id[end] >= '0' && id[end] <= '9') ||
                   id[end] == '-' || id[end] == '_'))
            return false;
    }
    return true;
}

bool normalizeAbsolute(std::string_view input, std::string& output)
{
    if (input.empty() || !validUtf8(input))
        return false;
    output.assign(input);
#if defined(_WIN32)
    std::replace(output.begin(), output.end(), '\\', '/');
    size_t components;
    if (output.size() >= 3 && ((output[0] >= 'a' && output[0] <= 'z') ||
                              (output[0] >= 'A' && output[0] <= 'Z')) && output[1] == ':' && output[2] == '/')
        components = 3;
    else if (output.size() >= 5 && output.compare(0, 2, "//") == 0 && output[2] != '/' &&
             output[2] != '?' && output[2] != '.')
    {
        const auto serverEnd = output.find('/', 2);
        if (serverEnd == std::string::npos || serverEnd + 1 == output.size())
            return false;
        const auto shareEnd = output.find('/', serverEnd + 1);
        const auto end = shareEnd == std::string::npos ? output.size() : shareEnd;
        if (!validWindowsComponent(std::string_view(output).substr(2, serverEnd - 2)) ||
            !validWindowsComponent(std::string_view(output).substr(serverEnd + 1, end - serverEnd - 1)))
            return false;
        components = end;
        if (components < output.size())
            ++components;
    }
    else
        return false;
#else
    if (output[0] != '/' || output.find('\\') != std::string::npos ||
        (output.size() > 1 && output[1] == '/'))
        return false;
    size_t components = 1;
#endif
    while (output.size() > components && output.back() == '/')
        output.pop_back();
    for (size_t start = components; start < output.size();)
    {
        const auto separator = output.find('/', start);
        const auto end = separator == std::string::npos ? output.size() : separator;
        const auto part = std::string_view(output).substr(start, end - start);
        if (part.empty() || part == "." || part == "..")
            return false;
#if defined(_WIN32)
        if (!validWindowsComponent(part))
            return false;
#endif
        start = end + 1;
    }
    if (output.back() != '/')
        output.push_back('/');
    return true;
}

bool validChild(std::string_view child)
{
    if (!validUtf8(child) || child.find('\\') != std::string_view::npos || child.find(':') != std::string_view::npos)
        return false;
    if (child.empty())
        return true;
    for (size_t start = 0; start <= child.size();)
    {
        const auto separator = child.find('/', start);
        const auto end = separator == std::string_view::npos ? child.size() : separator;
        const auto part = child.substr(start, end - start);
        if (part.empty() || part == "." || part == "..")
            return false;
#if defined(_WIN32)
        if (!validWindowsComponent(part))
            return false;
#endif
        if (separator == std::string_view::npos)
            break;
        start = end + 1;
    }
    return true;
}

bool validKind(AppDirectory kind)
{
    return kind == AppDirectory::PersistentData || kind == AppDirectory::TransientData;
}

#if defined(_WIN32)
bool toWide(std::string_view text, std::wstring& path)
{
    if (text.size() > static_cast<size_t>(INT_MAX))
        return false;
    const int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()), nullptr, 0);
    if (size <= 0)
        return false;
    path.resize(size);
    return MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()), path.data(), size) == size;
}

DirectoryResult win32Failure(DWORD error)
{
    DirectoryStatus status = DirectoryStatus::IoError;
    if (error == ERROR_ACCESS_DENIED || error == ERROR_PRIVILEGE_NOT_HELD || error == ERROR_WRITE_PROTECT)
        status = DirectoryStatus::PermissionDenied;
    else if (error == ERROR_DIRECTORY)
        status = DirectoryStatus::NotDirectory;
    else if (error == ERROR_FILENAME_EXCED_RANGE)
        status = DirectoryStatus::Unsupported;
    else if (error == ERROR_PATH_NOT_FOUND || error == ERROR_FILE_NOT_FOUND || error == ERROR_INVALID_DRIVE ||
             error == ERROR_NOT_READY || error == ERROR_BAD_NETPATH || error == ERROR_BAD_NET_NAME)
        status = DirectoryStatus::Unavailable;
    return failure(status, "win32", error);
}

DirectoryResult usablePath(std::string path)
{
    std::wstring native;
    if (!toWide(path, native))
        return win32Failure(GetLastError());
    // Existing consumers do not have a complete extended-length open/write chain.
    // CreateDirectoryW's ordinary namespace has the stricter MAX_PATH-12 limit.
    if (native.size() >= MAX_PATH - 12)
        return win32Failure(ERROR_FILENAME_EXCED_RANGE);
    return success(std::move(path));
}

DirectoryResult platformDirectory(AppDirectory kind, const std::string& appId)
{
    PWSTR folder = nullptr;
    const auto hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DONT_VERIFY, nullptr, &folder);
    if (FAILED(hr))
    {
        CoTaskMemFree(folder);
        return failure(hr == E_ACCESSDENIED ? DirectoryStatus::PermissionDenied : DirectoryStatus::Unavailable,
                       "hresult", static_cast<std::int64_t>(hr));
    }
    std::string base;
    if (folder)
    {
        const auto length = wcslen(folder);
        if (length <= static_cast<size_t>(INT_MAX))
        {
            const int bytes = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, folder, static_cast<int>(length), nullptr, 0, nullptr, nullptr);
            if (bytes > 0)
            {
                base.resize(bytes);
                WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, folder, static_cast<int>(length), base.data(), bytes, nullptr, nullptr);
            }
        }
    }
    const auto conversionError = GetLastError();
    CoTaskMemFree(folder);
    std::string path;
    if (!normalizeAbsolute(base, path))
        return failure(DirectoryStatus::Unavailable, "win32", base.empty() ? conversionError : ERROR_INVALID_NAME);
    path += appId + (kind == AppDirectory::PersistentData ? "/data/" : "/cache/");
    return success(std::move(path));
}

DirectoryResult createDirectory(const std::string& path)
{
    const auto checked = usablePath(path);
    if (checked.status != DirectoryStatus::Ok)
        return checked;
    std::wstring native;
    toWide(path, native);
    std::replace(native.begin(), native.end(), L'/', L'\\');
    const size_t rootEnd = native[1] == L':' ? 3 : native.find(L'\\', native.find(L'\\', 2) + 1) + 1;
    // Validate the drive/share root first; never attempt to create a UNC share.
    const auto root = native.substr(0, rootEnd);
    const auto attributes = GetFileAttributesW(root.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES)
        return win32Failure(GetLastError());
    if (!(attributes & FILE_ATTRIBUTE_DIRECTORY))
        return win32Failure(ERROR_DIRECTORY);
    for (size_t end = rootEnd; end < native.size(); ++end)
    {
        if (native[end] != L'\\')
            continue;
        const auto part = native.substr(0, end);
        if (CreateDirectoryW(part.c_str(), nullptr))
            continue;
        const auto error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS && error != ERROR_FILE_EXISTS)
            return win32Failure(error);
        const auto current = GetFileAttributesW(part.c_str());
        if (current == INVALID_FILE_ATTRIBUTES)
            return win32Failure(GetLastError());
        if (!(current & FILE_ATTRIBUTE_DIRECTORY))
            return win32Failure(ERROR_DIRECTORY);
    }
    return success(path);
}

bool pathsOverlap(const std::string& left, const std::string& right)
{
    std::wstring a, b;
    if (!toWide(left, a) || !toWide(right, b))
        return true;
    const auto count = static_cast<int>((std::min)(a.size(), b.size()));
    // Both normalized paths end in '/', so a prefix also has a component boundary.
    return CompareStringOrdinal(a.data(), count, b.data(), count, TRUE) == CSTR_EQUAL;
}
#else
DirectoryResult usablePath(std::string path) { return success(std::move(path)); }

DirectoryResult errnoFailure(int error)
{
    DirectoryStatus status = DirectoryStatus::IoError;
    if (error == EACCES || error == EPERM || error == EROFS)
        status = DirectoryStatus::PermissionDenied;
    else if (error == ENOTDIR)
        status = DirectoryStatus::NotDirectory;
    else if (error == ENOENT)
        status = DirectoryStatus::Unavailable;
    else if (error == ENAMETOOLONG)
        status = DirectoryStatus::Unsupported;
    return failure(status, "errno", error);
}

DirectoryResult createDirectory(const std::string& path)
{
    for (size_t end = 1; end < path.size(); ++end)
    {
        if (path[end] != '/')
            continue;
        const auto part = path.substr(0, end);
        int created;
        do { created = mkdir(part.c_str(), 0700); } while (created != 0 && errno == EINTR);
        if (created == 0)
            continue;
        const int error = errno;
        if (error != EEXIST)
            return errnoFailure(error);
        struct stat info;
        int inspected;
        do { inspected = stat(part.c_str(), &info); } while (inspected != 0 && errno == EINTR);
        if (inspected != 0)
            return errnoFailure(errno);
        if (!S_ISDIR(info.st_mode))
            return errnoFailure(ENOTDIR);
    }
    // The only path with no non-root components is '/', which is already a directory.
    return success(path);
}

bool pathsOverlap(const std::string& left, const std::string& right)
{
    const auto count = std::min(left.size(), right.size());
#if defined(__APPLE__)
    // Conservatively reject ASCII case aliases on the usual case-insensitive volumes.
    for (size_t i = 0; i < count; ++i)
    {
        auto a = left[i], b = right[i];
        if (a >= 'A' && a <= 'Z') a += 'a' - 'A';
        if (b >= 'A' && b <= 'Z') b += 'a' - 'A';
        if (a != b) return false;
    }
    return true;
#else
    return left.compare(0, count, right, 0, count) == 0;
#endif
}
#endif

#if defined(__ANDROID__)
struct AndroidContext
{
    std::mutex mutex;
    JavaVM* vm = nullptr;
    jobject application = nullptr;
    jmethodID files = nullptr;
    jmethodID cache = nullptr;
    jmethodID absolute = nullptr;
    DirectoryResult initialization = failure(DirectoryStatus::NotInitialized, "jni");
};

AndroidContext& androidContext()
{
    static auto* context = new AndroidContext;
    return *context;
}

DirectoryResult javaFailure(JNIEnv* env)
{
    auto exception = env->ExceptionOccurred();
    env->ExceptionClear();
    auto security = env->FindClass("java/lang/SecurityException");
    const bool denied = security && exception && env->IsInstanceOf(exception, security);
    if (env->ExceptionCheck())
        env->ExceptionClear();
    if (security) env->DeleteLocalRef(security);
    if (exception) env->DeleteLocalRef(exception);
    // Java exceptions have no native integer error code; retain their error family.
    return failure(denied ? DirectoryStatus::PermissionDenied : DirectoryStatus::IoError,
                   denied ? "java.lang.SecurityException" : "jni", 0);
}

DirectoryResult platformDirectory(AppDirectory kind, const std::string&)
{
    auto& context = androidContext();
    std::lock_guard<std::mutex> lock(context.mutex);
    if (context.initialization.status != DirectoryStatus::Ok)
        return context.initialization;
    JNIEnv* env = nullptr;
    const auto attached = context.vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    bool detach = false;
    if (attached == JNI_EDETACHED)
    {
        const auto result = context.vm->AttachCurrentThread(&env, nullptr);
        if (result != JNI_OK)
            return failure(DirectoryStatus::NotInitialized, "jni", result);
        detach = true;
    }
    else if (attached != JNI_OK)
        return failure(DirectoryStatus::NotInitialized, "jni", attached);
    struct Detach
    {
        JavaVM* vm;
        bool active;
        ~Detach() { if (active) vm->DetachCurrentThread(); }
    } guard{context.vm, detach};
    if (env->PushLocalFrame(8) != JNI_OK)
        return javaFailure(env);
    struct Frame { JNIEnv* env; ~Frame() { env->PopLocalFrame(nullptr); } } frame{env};
    auto directory = env->CallObjectMethod(context.application,
        kind == AppDirectory::PersistentData ? context.files : context.cache);
    if (env->ExceptionCheck())
        return javaFailure(env);
    if (!directory)
        return failure(DirectoryStatus::Unavailable, "jni");
    auto text = static_cast<jstring>(env->CallObjectMethod(directory, context.absolute));
    if (env->ExceptionCheck())
        return javaFailure(env);
    if (!text)
        return failure(DirectoryStatus::Unavailable, "jni");
    const jchar* chars = env->GetStringChars(text, nullptr);
    if (!chars)
        return env->ExceptionCheck() ? javaFailure(env) : failure(DirectoryStatus::IoError, "jni");
    struct Characters
    {
        JNIEnv* env;
        jstring text;
        const jchar* chars;
        ~Characters() { env->ReleaseStringChars(text, chars); }
    } characters{env, text, chars};
    const auto size = env->GetStringLength(text);
    // JNI's modified UTF-8 is not the physical UTF-8 contract (notably for supplementary characters).
    std::string path;
    bool valid = true;
    for (jsize i = 0; i < size; ++i)
    {
        std::uint32_t code = chars[i];
        if (code >= 0xd800 && code <= 0xdbff)
        {
            if (i + 1 >= size || chars[i + 1] < 0xdc00 || chars[i + 1] > 0xdfff) { valid = false; break; }
            code = 0x10000 + ((code - 0xd800) << 10) + (chars[++i] - 0xdc00);
        }
        else if (code >= 0xdc00 && code <= 0xdfff) { valid = false; break; }
        if (code < 0x80) path.push_back(static_cast<char>(code));
        else if (code < 0x800)
        {
            path.push_back(static_cast<char>(0xc0 | (code >> 6)));
            path.push_back(static_cast<char>(0x80 | (code & 0x3f)));
        }
        else
        {
            if (code >= 0x10000) path.push_back(static_cast<char>(0xf0 | (code >> 18)));
            path.push_back(static_cast<char>((code >= 0x10000 ? 0x80 : 0xe0) | ((code >> 12) & (code >= 0x10000 ? 0x3f : 0x0f))));
            path.push_back(static_cast<char>(0x80 | ((code >> 6) & 0x3f)));
            path.push_back(static_cast<char>(0x80 | (code & 0x3f)));
        }
    }
    if (!valid)
        return failure(DirectoryStatus::Unsupported, "jni");
    return success(std::move(path));
}
#elif defined(__APPLE__)
DirectoryResult platformDirectory(AppDirectory kind, const std::string& appId)
{
    return queryAppleAppDirectory(kind, appId);
}
#elif !defined(_WIN32)
DirectoryResult platformDirectory(AppDirectory kind, const std::string& appId)
{
    const bool persistent = kind == AppDirectory::PersistentData;
    const char* xdg = std::getenv(persistent ? "XDG_DATA_HOME" : "XDG_CACHE_HOME");
    std::string base;
    if (xdg && xdg[0] == '/')
    {
        if (!normalizeAbsolute(xdg, base))
            return failure(DirectoryStatus::Unavailable, "errno", EINVAL);
    }
    else
    {
        const char* home = std::getenv("HOME");
        if (!home || !normalizeAbsolute(home, base))
        {
            long hint = sysconf(_SC_GETPW_R_SIZE_MAX);
            std::vector<char> buffer(hint > 0 && hint < 1024 * 1024 ? static_cast<size_t>(hint) : 16384);
            struct passwd user;
            struct passwd* found = nullptr;
            int error;
            for (;;)
            {
                error = getpwuid_r(geteuid(), &user, buffer.data(), buffer.size(), &found);
                if (error != ERANGE || buffer.size() >= 1024 * 1024)
                    break;
                buffer.resize(buffer.size() * 2);
            }
            if (error || !found || !user.pw_dir || !normalizeAbsolute(user.pw_dir, base))
                return failure(DirectoryStatus::Unavailable, "errno", error ? error : ENOENT);
        }
        base += persistent ? ".local/share/" : ".cache/";
    }
    return success(base + appId + '/');
}
#endif

DirectoryResult resolveDirectory(const AppDirectoryConfig& config, AppDirectory kind)
{
    const auto& overridePath = kind == AppDirectory::PersistentData ? config.persistentDataOverride : config.transientDataOverride;
    DirectoryResult result = overridePath.empty() ? platformDirectory(kind, config.appId) : success(overridePath);
    if (result.status != DirectoryStatus::Ok)
        return result;
    std::string path;
    if (!normalizeAbsolute(result.path, path))
        return failure(DirectoryStatus::Unavailable);
    // Length support is checked after comparing roots, so unsupported roots can still
    // participate in detectable overlap validation.
    return success(std::move(path));
}

struct AppDirectoriesService
{
    std::mutex mutex;
    AppDirectoryConfig config;
    bool frozen = false;
    std::array<DirectoryResult, 2> locations;
};

AppDirectoriesService& service()
{
    static auto* value = new AppDirectoriesService;
    return *value;
}

bool equalConfig(const AppDirectoryConfig& a, const AppDirectoryConfig& b)
{
    return a.appId == b.appId && a.persistentDataOverride == b.persistentDataOverride &&
           a.transientDataOverride == b.transientDataOverride;
}
} // namespace

namespace detail
{
DirectoryStatus configureAppDirectories(const AppDirectoryConfig& config)
{
    if (!validAppId(config.appId))
        return DirectoryStatus::InvalidArgument;
    AppDirectoryConfig normalized = config;
    if ((!config.persistentDataOverride.empty() && !normalizeAbsolute(config.persistentDataOverride, normalized.persistentDataOverride)) ||
        (!config.transientDataOverride.empty() && !normalizeAbsolute(config.transientDataOverride, normalized.transientDataOverride)))
        return DirectoryStatus::InvalidArgument;
    auto& state = service();
    std::lock_guard<std::mutex> lock(state.mutex);
    if (state.frozen)
        return equalConfig(state.config, normalized) ? DirectoryStatus::Ok : DirectoryStatus::InUse;
    const auto persistent = resolveDirectory(normalized, AppDirectory::PersistentData);
    const auto transient = resolveDirectory(normalized, AppDirectory::TransientData);
    if (persistent.status == DirectoryStatus::Ok && transient.status == DirectoryStatus::Ok &&
        pathsOverlap(persistent.path, transient.path))
        return DirectoryStatus::InvalidArgument;
    state.config = std::move(normalized);
    state.locations = {};
    return DirectoryStatus::Ok;
}

DirectoryResult queryAppDirectory(AppDirectory kind)
{
    if (!validKind(kind))
        return failure(DirectoryStatus::InvalidArgument);
    auto& state = service();
    std::lock_guard<std::mutex> lock(state.mutex);
    if (!validAppId(state.config.appId))
        return failure(DirectoryStatus::InvalidArgument);
    state.frozen = true;
    for (size_t index = 0; index < state.locations.size(); ++index)
    {
        if (state.locations[index].status != DirectoryStatus::Ok)
            state.locations[index] = resolveDirectory(state.config, index == 0 ? AppDirectory::PersistentData : AppDirectory::TransientData);
    }
    if (state.locations[0].status == DirectoryStatus::Ok && state.locations[1].status == DirectoryStatus::Ok &&
        pathsOverlap(state.locations[0].path, state.locations[1].path))
        return failure(DirectoryStatus::InvalidArgument);
    auto result = state.locations[kind == AppDirectory::PersistentData ? 0 : 1];
    return result.status == DirectoryStatus::Ok ? usablePath(std::move(result.path)) : result;
}

DirectoryResult ensureAppDirectory(AppDirectory kind, std::string_view relativeSubdirectory)
{
    if (!validKind(kind) || !validChild(relativeSubdirectory))
        return failure(DirectoryStatus::InvalidArgument);
    auto result = queryAppDirectory(kind);
    if (result.status != DirectoryStatus::Ok)
        return result;
    if (!relativeSubdirectory.empty())
    {
        result.path.append(relativeSubdirectory);
        result.path.push_back('/');
    }
    return createDirectory(result.path);
}
} // namespace detail

#if defined(__ANDROID__)
extern "C" JNIEXPORT void JNICALL
Java_org_cocos_lib_CocosEngine_nativeSetAppDirectoryContext(JNIEnv* env, jclass, jobject application)
{
    auto& context = androidContext();
    std::lock_guard<std::mutex> lock(context.mutex);
    if (!application)
        return;
    // The Java caller supplies Application Context, never a transient Activity.
    if (env->PushLocalFrame(8) != JNI_OK)
    {
        context.initialization = javaFailure(env);
        return;
    }
    struct Frame { JNIEnv* env; ~Frame() { env->PopLocalFrame(nullptr); } } frame{env};
    auto type = env->GetObjectClass(application);
    if (env->ExceptionCheck())
    {
        context.initialization = javaFailure(env);
        return;
    }
    auto fileType = env->FindClass("java/io/File");
    if (env->ExceptionCheck())
    {
        context.initialization = javaFailure(env);
        return;
    }
    auto files = type ? env->GetMethodID(type, "getFilesDir", "()Ljava/io/File;") : nullptr;
    if (env->ExceptionCheck())
    {
        context.initialization = javaFailure(env);
        return;
    }
    auto cache = type ? env->GetMethodID(type, "getCacheDir", "()Ljava/io/File;") : nullptr;
    if (env->ExceptionCheck())
    {
        context.initialization = javaFailure(env);
        return;
    }
    auto absolute = fileType ? env->GetMethodID(fileType, "getAbsolutePath", "()Ljava/lang/String;") : nullptr;
    if (env->ExceptionCheck())
    {
        context.initialization = javaFailure(env);
        return;
    }
    auto retained = env->NewGlobalRef(application);
    if (env->ExceptionCheck())
    {
        context.initialization = javaFailure(env);
        if (retained) env->DeleteGlobalRef(retained);
        return;
    }
    JavaVM* vm = nullptr;
    const auto vmResult = env->GetJavaVM(&vm);
    if (!files || !cache || !absolute || !retained || vmResult != JNI_OK)
    {
        if (retained) env->DeleteGlobalRef(retained);
        context.initialization = failure(DirectoryStatus::NotInitialized, "jni", vmResult);
        return;
    }
    if (context.application)
        env->DeleteGlobalRef(context.application);
    context.vm = vm;
    context.application = retained;
    context.files = files;
    context.cache = cache;
    context.absolute = absolute;
    context.initialization = success({});
}
#endif

NS_CC_END
