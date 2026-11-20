#include "platform/TextInputBackend.h"
#include "platform/linux/TextInputX11-glfw.h"

#define GLFW_INCLUDE_NONE
#include "glfw3.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace cc
{
namespace
{
class X11TextInputBackend;
std::vector<X11TextInputBackend*> activeBackends;

class X11TextInputBackend final : public TextInputBackend
{
public:
    X11TextInputBackend(GLFWwindow* window, CcGlfwX11TextInput* input)
        : _window(window), _input(input)
    {}

    ~X11TextInputBackend() override
    {
        deactivate();
        cc_glfw_x11_text_input_destroy(_input);
    }

    TextInputCapabilities capabilities() const override
    {
        TextInputCapabilities capabilities;
        capabilities.anchor = cc_glfw_x11_text_input_has_anchor(_input);
        return capabilities;
    }

    TextInputError activate(const TextInputActivation& activation) override
    {
        _sink = activation.sink;
        activeBackends.push_back(this);
        cc_glfw_x11_text_input_begin(_input);
        setArea(activation.initial.area);
        return TextInputError::none;
    }

    void setArea(const std::optional<TextInputArea>& area) override
    {
        int width = 0, height = 0;
        if (area)
            glfwGetWindowSize(_window, &width, &height);
        if (!area || width <= 0 || height <= 0)
        {
            cc_glfw_x11_text_input_set_spot(_input, false, 0, 0);
            return;
        }

        double left = 0, top = 0;
        double right = width - 1.0, bottom = height - 1.0;
        if (area->clip)
        {
            left = std::max(left, area->clip->x);
            top = std::max(top, area->clip->y);
            right = std::min(right, area->clip->x + area->clip->width);
            bottom = std::min(bottom, area->clip->y + area->clip->height);
        }
        if (left > right || top > bottom)
        {
            cc_glfw_x11_text_input_set_spot(_input, false, 0, 0);
            return;
        }

        // XIM uses a client-window-local insertion x and baseline y. The lower
        // edge of the caret approximates the baseline when only a rect is known.
        const auto x = std::clamp(std::floor(area->caret.x), left, right);
        const auto y = std::clamp(std::ceil(area->caret.y + area->caret.height), top, bottom);
        constexpr double maxCoordinate = (std::numeric_limits<short>::max)();
        cc_glfw_x11_text_input_set_spot(_input, true, static_cast<short>(std::min(x, maxCoordinate)),
                                        static_cast<short>(std::min(y, maxCoordinate)));
    }

    void updateSnapshot(const TextInputSnapshot&) override {}
    TextInputError requestKeyboard(bool) override { return TextInputError::unsupported; }
    TextInputError cancelComposition() override { return TextInputError::unsupported; }

    void deactivate() override
    {
        std::erase(activeBackends, this);
        cc_glfw_x11_text_input_end(_input);
        _sink.closed();
        _sink = {};
    }

    void refresh() { cc_glfw_x11_text_input_refresh(_input); }

private:
    GLFWwindow* _window;
    CcGlfwX11TextInput* _input;
    TextInputEventSink _sink;
};
}  // namespace

std::unique_ptr<TextInputBackend> createX11TextInputBackend(GLFWwindow* window)
{
    if (auto* input = cc_glfw_x11_text_input_create(window))
        return std::make_unique<X11TextInputBackend>(window, input);
    return nullptr;
}

bool isX11ImeKeyConsumed(GLFWwindow* window)
{
    return cc_glfw_x11_text_input_key_consumed(window);
}

void refreshX11TextInputBackends()
{
    cc_glfw_x11_text_input_finish_poll();
    for (auto* backend : activeBackends)
        backend->refresh();
}
}  // namespace cc
