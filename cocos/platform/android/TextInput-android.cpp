#include "platform/TextInputBackend.h"

#include "base/ccUTF8.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/TextInputIndex.h"

#include <algorithm>
#include <iterator>
#include <limits>
#include <mutex>
#include <unordered_map>

namespace cc
{
namespace
{
constexpr auto hostClass = "org/cocos/lib/CocosGLSurfaceView";
std::mutex sinksMutex;
std::unordered_map<TextInputSessionId, TextInputEventSink> sinks;

TextInputEventSink lookupSink(TextInputSessionId session, bool remove = false)
{
    const std::lock_guard lock(sinksMutex);
    const auto it = sinks.find(session);
    if (it == sinks.end())
        return {};
    auto sink = it->second;
    if (remove)
        sinks.erase(it);
    return sink;
}

class AndroidTextInputBackend final : public TextInputBackend
{
public:
    ~AndroidTextInputBackend() override { deactivate(); }

    TextInputCapabilities capabilities() const override
    {
        TextInputCapabilities result;
        result.anchor = true;
        result.observePreedit = true;
        result.rangeEdit = true;
        result.requestKeyboard = true;
        result.cancelComposition = true;
        result.keyboardVisibility = JniHelper::callStaticBooleanMethod(hostClass, "hasTextInputKeyboardVisibility");
        result.keyboardOcclusion = result.keyboardVisibility;
        return result;
    }

    TextInputError activate(const TextInputActivation& activation) override
    {
        _session = activation.sink.session();
        {
            const std::lock_guard lock(sinksMutex);
            sinks.emplace(_session, activation.sink);
        }

        const auto& options = activation.options;
        if (!JniHelper::callStaticBooleanMethod(hostClass, "activateTextInput",
                static_cast<jlong>(_session), static_cast<jint>(options.purpose),
                static_cast<jint>(options.capitalization), static_cast<jint>(options.returnAction),
                static_cast<jboolean>(options.multiline),
                static_cast<jint>(options.autocorrect ? (*options.autocorrect ? 1 : 0) : -1),
                static_cast<jboolean>(activation.initial.snapshot.has_value()),
                static_cast<jboolean>(options.observePreedit)))
        {
            lookupSink(_session, true);
            _session = 0;
            return TextInputError::activationFailed;
        }
        if (activation.initial.area)
            setArea(activation.initial.area);
        if (activation.initial.snapshot)
            updateSnapshot(*activation.initial.snapshot);
        return TextInputError::none;
    }

    void setArea(const std::optional<TextInputArea>& area) override
    {
        const auto caret = area ? area->caret : TextInputRect{};
        JniHelper::callStaticVoidMethod(hostClass, "setTextInputArea", static_cast<jlong>(_session),
            static_cast<jboolean>(area.has_value()), static_cast<jfloat>(caret.x),
            static_cast<jfloat>(caret.y), static_cast<jfloat>(caret.height));
    }

    void updateSnapshot(const TextInputSnapshot& snapshot) override
    {
        const TextInputIndex index(snapshot.utf8);
        const auto anchor = index.utf16FromScalar(snapshot.anchor - snapshot.origin);
        const auto focus = index.utf16FromScalar(snapshot.focus - snapshot.origin);
        if (!anchor || !focus || anchor.offset > std::numeric_limits<jint>::max() ||
            focus.offset > std::numeric_limits<jint>::max())
            return;

        JniMethodInfo method;
        if (JniHelper::getStaticMethodInfo(method, hostClass, "setTextInputSnapshot", "(JJJJJLjava/lang/String;II)V"))
        {
            const jstring text = StringUtils::newStringUTFJNI(method.env, snapshot.utf8);
            method.env->CallStaticVoidMethod(method.classID, method.methodID, static_cast<jlong>(_session),
                static_cast<jlong>(lookupSink(_session).snapshotEpoch()), static_cast<jlong>(snapshot.revision),
                static_cast<jlong>(snapshot.acknowledgedTransaction.value_or(0)), static_cast<jlong>(snapshot.origin),
                text, static_cast<jint>(anchor.offset), static_cast<jint>(focus.offset));
            method.env->DeleteLocalRef(text);
            method.env->DeleteLocalRef(method.classID);
        }
    }

    TextInputError requestKeyboard(bool visible) override
    {
        return JniHelper::callStaticBooleanMethod(hostClass, "requestTextInputKeyboard",
            static_cast<jlong>(_session), static_cast<jboolean>(visible))
            ? TextInputError::none : TextInputError::activationFailed;
    }

    TextInputError cancelComposition() override
    {
        return JniHelper::callStaticBooleanMethod(hostClass, "cancelTextInputComposition", static_cast<jlong>(_session))
            ? TextInputError::none : TextInputError::activationFailed;
    }

    void deactivate() override
    {
        if (_session)
        {
            if (!JniHelper::callStaticBooleanMethod(hostClass, "closeTextInput", static_cast<jlong>(_session)))
                lookupSink(_session, true).closed();
            _session = 0;
        }
    }

private:
    TextInputSessionId _session = 0;
};
}

std::unique_ptr<TextInputBackend> createAndroidTextInputBackend()
{
    return std::make_unique<AndroidTextInputBackend>();
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGLSurfaceView_nativeTextInputCommit(
    JNIEnv* env, jclass, jlong session, jstring text)
{
    lookupSink(session).post(TextInputCommit{StringUtils::getStringUTFCharsJNI(env, text)});
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosGLSurfaceView_nativeTextInputEdit(
    JNIEnv* env, jclass, jlong session, jlong epoch, jlong revision, jlong transaction,
    jlong origin, jstring previous, jstring current, jint anchor, jint focus)
{
    const auto sink = lookupSink(session);
    if (!sink || sink.snapshotEpoch() != static_cast<std::uint64_t>(epoch))
        return JNI_FALSE;

    bool validPrevious = false;
    bool validCurrent = false;
    const auto previousText = StringUtils::getStringUTFCharsJNI(env, previous, &validPrevious);
    const auto currentText = StringUtils::getStringUTFCharsJNI(env, current, &validCurrent);
    if (!validPrevious || !validCurrent || anchor < 0 || focus < 0)
        return JNI_FALSE;

    const TextInputIndex index(currentText);
    const auto anchorScalar = index.scalarFromUtf16(anchor);
    const auto focusScalar = index.scalarFromUtf16(focus);
    const auto offset = static_cast<std::size_t>(origin);
    if (!anchorScalar || !focusScalar || offset > std::numeric_limits<std::size_t>::max() - index.scalarCount().offset)
        return JNI_FALSE;

    TextInputEdit edit;
    edit.baseRevision = static_cast<std::uint64_t>(revision);
    edit.transactionId = static_cast<std::uint64_t>(transaction);
    edit.selectionAfter = {offset + anchorScalar.offset, offset + focusScalar.offset};
    if (previousText != currentText)
    {
        std::u32string before;
        std::u32string after;
        if (!StringUtils::UTF8ToUTF32(previousText, before) || !StringUtils::UTF8ToUTF32(currentText, after) ||
            offset > std::numeric_limits<std::size_t>::max() - before.size())
            return JNI_FALSE;

        const auto prefix = std::mismatch(before.begin(), before.end(), after.begin(), after.end());
        const auto start = static_cast<std::size_t>(prefix.first - before.begin());
        const auto suffix = std::mismatch(before.rbegin(), std::make_reverse_iterator(prefix.first),
            after.rbegin(), std::make_reverse_iterator(prefix.second));
        const auto end = static_cast<std::size_t>(suffix.first.base() - before.begin());
        const auto firstByte = index.utf8FromScalar(start).offset;
        const auto lastByte = index.utf8FromScalar(static_cast<std::size_t>(suffix.second.base() - after.begin())).offset;
        edit.operations.push_back({offset + start, offset + end, currentText.substr(firstByte, lastByte - firstByte)});
    }
    return sink.post(std::move(edit), static_cast<std::uint64_t>(epoch)) ? JNI_TRUE : JNI_FALSE;
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGLSurfaceView_nativeTextInputCommand(
    JNIEnv*, jclass, jlong session, jint action)
{
    if (action >= 0 && action <= static_cast<jint>(TextInputCommandAction::cancel))
        lookupSink(session).post(TextInputCommand{static_cast<TextInputCommandAction>(action)});
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGLSurfaceView_nativeTextInputPreedit(
    JNIEnv* env, jclass, jlong session, jstring text, jint phase, jint anchor, jint focus)
{
    if (phase < 0 || phase > static_cast<jint>(TextInputPreeditPhase::ended))
        return;
    const auto sink = lookupSink(session);
    if (!sink)
        return;

    bool valid = false;
    TextInputPreedit preedit;
    preedit.text = StringUtils::getStringUTFCharsJNI(env, text, &valid);
    if (!valid)
        return;
    preedit.phase = static_cast<TextInputPreeditPhase>(phase);
    if (anchor >= 0 && focus >= 0)
    {
        const TextInputIndex index(preedit.text);
        const auto anchorScalar = index.scalarFromUtf16(anchor);
        const auto focusScalar = index.scalarFromUtf16(focus);
        if (anchorScalar && focusScalar)
            preedit.selection = TextInputSelection{anchorScalar.offset, focusScalar.offset};
    }
    sink.post(std::move(preedit));
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGLSurfaceView_nativeTextInputClosed(
    JNIEnv*, jclass, jlong session, jint reason)
{
    if (reason >= 0 && reason <= static_cast<jint>(TextInputCloseReason::nativeEnded))
        lookupSink(session, true).closed(static_cast<TextInputCloseReason>(reason));
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGLSurfaceView_nativeTextInputKeyboardState(
    JNIEnv*, jclass, jlong session, jint composing, jboolean visible, jboolean hasOcclusion,
    jfloat x, jfloat y, jfloat width, jfloat height)
{
    TextInputState state;
    if (composing >= 0 && composing <= static_cast<jint>(TextInputKnowledge::yes))
        state.composing = static_cast<TextInputKnowledge>(composing);
    state.keyboardVisible = visible ? TextInputKnowledge::yes : TextInputKnowledge::no;
    if (hasOcclusion)
        state.occlusion = TextInputRect{x, y, width, height};
    lookupSink(session).post(TextInputStateChanged{state, std::nullopt, std::nullopt});
}
}
