#include "../../../external/glfw/src/internal.h"
#include "TextInputX11-glfw.h"

#include <stdlib.h>
#include <string.h>

typedef XVaNestedList (*CreateNestedList)(int, ...);
typedef char* (*SetICValues)(XIC, ...);
typedef XFontSet (*CreateFontSet)(Display*, const char*, char***, int*, char**);
typedef void (*FreeFontSet)(Display*, XFontSet);
typedef void (*FreeStringList)(char**);

struct CcGlfwX11TextInput
{
    CcGlfwX11TextInput* nextActive;
    _GLFWwindow* window;
    XIC positioned;
    XIM checkedIM;
    XIMStyle style;
    XFontSet fontSet;
    CreateNestedList createNestedList;
    SetICValues setICValues;
    FreeFontSet freeFontSet;
    GLFWbool active;
    GLFWbool hasSpot;
    XPoint spot;
    unsigned long checkedGeneration;
    Time filteredPressTimes[256];
};

static PFN_XFilterEvent filterEvent;
static CcGlfwX11TextInput* activeInputs;
static Window filteredKeyWindow;
static unsigned long inputMethodGeneration;

static Bool observeFilterEvent(XEvent* event, Window window)
{
    const Window keyWindow = event->type == KeyPress ? event->xkey.window : None;
    const unsigned int keycode = keyWindow ? event->xkey.keycode : 0;
    const Time time = keyWindow ? event->xkey.time : 0;
    const XIM im = _glfw.x11.im;
    const Bool filtered = filterEvent(event, window);
    if (im != _glfw.x11.im)
        ++inputMethodGeneration;
    filteredKeyWindow = None;

    if (keycode && keycode < 256)
    {
        for (CcGlfwX11TextInput* input = activeInputs; input; input = input->nextActive)
        {
            if (input->window->x11.handle != keyWindow)
                continue;
            if (filtered)
            {
                input->filteredPressTimes[keycode] = time;
                filteredKeyWindow = keyWindow;
            }
            else if (time && input->filteredPressTimes[keycode] == time)
            {
                input->filteredPressTimes[keycode] = 0;
                // Back-end XIMs can filter every press and forward the ones they
                // did not use. GLFW normally deduplicates that second event; let
                // it deliver this press since the text path skipped the first.
                if (input->window->x11.keyPressTimes[keycode] == time)
                    input->window->x11.keyPressTimes[keycode] = time - 1;
            }
            break;
        }
    }
    return filtered;
}

static void contextDestroyed(XIM im, XPointer clientData, XPointer callData)
{
    (void) callData;
    CcGlfwX11TextInput* input = (CcGlfwX11TextInput*) clientData;
    const XIC ic = (XIC) im;
    if (input->window->x11.ic == ic)
        input->window->x11.ic = NULL;
    if (input->positioned == ic)
        input->positioned = NULL;
}

static int hasFocus(const CcGlfwX11TextInput* input)
{
    return glfwGetWindowAttrib((GLFWwindow*) input->window, GLFW_FOCUSED);
}

static void releasePositionedContext(CcGlfwX11TextInput* input)
{
    if (!input->positioned)
        return;

    const GLFWbool installed = input->window->x11.ic == input->positioned;
    const int focused = installed && hasFocus(input);
    if (focused && input->positioned)
        XUnsetICFocus(input->positioned);
    if (input->positioned)
    {
        if (installed)
            input->window->x11.ic = NULL;
        XDestroyIC(input->positioned);
        input->positioned = NULL;
    }

    // GLFW owns the ordinary context when the field is inactive or has no usable spot.
    if (installed && _glfw.x11.im && !input->window->x11.ic)
    {
        _glfwCreateInputContextX11(input->window);
        if (focused && input->window->x11.ic)
            XSetICFocus(input->window->x11.ic);
        XFlush(_glfw.x11.display);
    }
}

static XIMStyle findPositionedStyle(CcGlfwX11TextInput* input)
{
    const XIM im = _glfw.x11.im;
    if (input->checkedIM == im && input->checkedGeneration == inputMethodGeneration)
        return input->style;

    input->checkedIM = im;
    input->checkedGeneration = inputMethodGeneration;
    input->style = 0;
    if (!im || !input->createNestedList || !input->setICValues)
        return 0;

    XIMStyles* styles = NULL;
    if (XGetIMValues(im, XNQueryInputStyle, &styles, NULL) == NULL && styles)
    {
        const XIMStyle preferred = XIMPreeditPosition | XIMStatusNothing;
        const XIMStyle alternate = XIMPreeditPosition | XIMStatusNone;
        for (unsigned int i = 0; i < styles->count_styles; ++i)
        {
            const XIMStyle style = styles->supported_styles[i];
            if (style == preferred || (style == alternate && !input->style))
                input->style = style;
        }
    }
    if (styles)
        XFree(styles);
    return input->style;
}

static int updateSpot(CcGlfwX11TextInput* input)
{
    XVaNestedList attributes = input->createNestedList(0, XNSpotLocation, &input->spot, NULL);
    if (!attributes)
        return 0;
    const char* error = input->setICValues(input->positioned, XNPreeditAttributes, attributes, NULL);
    XFree(attributes);
    return !error && input->positioned;
}

static XVaNestedList preeditAttributes(CcGlfwX11TextInput* input)
{
    if (!input->fontSet)
    {
        void* module = _glfw.x11.xlib.handle;
        const CreateFontSet create = (CreateFontSet) _glfwPlatformGetModuleSymbol(module, "XCreateFontSet");
        const FreeStringList freeStrings = (FreeStringList) _glfwPlatformGetModuleSymbol(module, "XFreeStringList");
        if (create && input->freeFontSet && freeStrings)
        {
            char** missing = NULL;
            int missingCount;
            char* defaultString;
            input->fontSet = create(_glfw.x11.display, "-*-*-medium-r-normal--14-*-*-*-*-*-*-*",
                                    &missing, &missingCount, &defaultString);
            if (missing)
                freeStrings(missing);
        }
    }

    if (input->fontSet)
        return input->createNestedList(0, XNSpotLocation, &input->spot, XNFontSet, input->fontSet, NULL);
    return input->createNestedList(0, XNSpotLocation, &input->spot, NULL);
}

static int acquirePositionedContext(CcGlfwX11TextInput* input, XIMStyle style)
{
    const XIM im = _glfw.x11.im;
    const Window xid = input->window->x11.handle;
    XVaNestedList attributes = preeditAttributes(input);
    if (!attributes || _glfw.x11.im != im)
    {
        if (attributes)
            XFree(attributes);
        return 0;
    }

    XIMCallback destroyed = {(XPointer) input, contextDestroyed};
    input->positioned = XCreateIC(im, XNInputStyle, style, XNClientWindow, xid,
                                  XNFocusWindow, xid, XNDestroyCallback, &destroyed,
                                  XNPreeditAttributes, attributes, NULL);
    XFree(attributes);
    if (!input->positioned)
        return 0;

    if (!updateSpot(input))
    {
        releasePositionedContext(input);
        return 0;
    }

    // Some XIM servers accept this style and its spot setter but reject readback
    // of other IC attributes. Preserve GLFW's existing mask when it cannot be read.
    unsigned long filter = 0;
    XWindowAttributes windowAttributes;
    if (XGetICValues(input->positioned, XNFilterEvents, &filter, NULL) == NULL && filter &&
        XGetWindowAttributes(_glfw.x11.display, xid, &windowAttributes))
        XSelectInput(_glfw.x11.display, xid, windowAttributes.your_event_mask | filter);
    if (!input->positioned)
        return 0;

    // Keep exactly one context for GLFW's XFilterEvent and UTF-8 lookup. The candidate
    // is prepared first so a rejected style keeps the working default context intact.
    if (input->window->x11.ic)
        XDestroyIC(input->window->x11.ic);
    input->window->x11.ic = input->positioned;
    if (!input->positioned)
        return 0;

    if (hasFocus(input))
    {
        if (input->positioned)
            XSetICFocus(input->positioned);
    }
    XFlush(_glfw.x11.display);
    return input->positioned != NULL;
}

GLFWAPI CcGlfwX11TextInput* cc_glfw_x11_text_input_create(GLFWwindow* window)
{
    if (glfwGetPlatform() != GLFW_PLATFORM_X11)
        return NULL;
    CcGlfwX11TextInput* input = calloc(1, sizeof(*input));
    if (!input)
        return NULL;

    void* module = _glfw.x11.xlib.handle;
    input->window = (_GLFWwindow*) window;
    input->createNestedList = (CreateNestedList) _glfwPlatformGetModuleSymbol(module, "XVaCreateNestedList");
    input->setICValues = (SetICValues) _glfwPlatformGetModuleSymbol(module, "XSetICValues");
    input->freeFontSet = (FreeFontSet) _glfwPlatformGetModuleSymbol(module, "XFreeFontSet");
    return input;
}

GLFWAPI void cc_glfw_x11_text_input_begin(CcGlfwX11TextInput* input)
{
    if (input->active)
        return;
    input->active = GLFW_TRUE;
    input->checkedIM = NULL;
    input->style = 0;
    if (!activeInputs)
    {
        filterEvent = XFilterEvent;
        XFilterEvent = observeFilterEvent;
    }
    input->nextActive = activeInputs;
    activeInputs = input;
}

GLFWAPI void cc_glfw_x11_text_input_end(CcGlfwX11TextInput* input)
{
    if (!input->active)
        return;
    releasePositionedContext(input);
    if (input->fontSet)
    {
        input->freeFontSet(_glfw.x11.display, input->fontSet);
        input->fontSet = NULL;
    }
    input->active = GLFW_FALSE;
    input->hasSpot = GLFW_FALSE;
    memset(input->filteredPressTimes, 0, sizeof(input->filteredPressTimes));
    CcGlfwX11TextInput** link = &activeInputs;
    while (*link != input)
        link = &(*link)->nextActive;
    *link = input->nextActive;
    input->nextActive = NULL;
    if (!activeInputs)
    {
        XFilterEvent = filterEvent;
        filterEvent = NULL;
        filteredKeyWindow = None;
    }
}

GLFWAPI void cc_glfw_x11_text_input_destroy(CcGlfwX11TextInput* input)
{
    if (input)
    {
        cc_glfw_x11_text_input_end(input);
        free(input);
    }
}

GLFWAPI int cc_glfw_x11_text_input_has_anchor(CcGlfwX11TextInput* input)
{
    const XIMStyle style = findPositionedStyle(input);
    return style && (!input->active || !input->hasSpot || input->positioned);
}

GLFWAPI void cc_glfw_x11_text_input_set_spot(CcGlfwX11TextInput* input, int hasSpot, short x, short y)
{
    if (!input->active)
        return;
    if (!hasSpot)
    {
        input->hasSpot = GLFW_FALSE;
        releasePositionedContext(input);
        return;
    }

    const int changed = !input->hasSpot || input->spot.x != x || input->spot.y != y;
    input->hasSpot = GLFW_TRUE;
    input->spot = (XPoint) {x, y};
    if (!input->positioned)
        cc_glfw_x11_text_input_refresh(input);
    else if (changed)
    {
        if (updateSpot(input))
            XFlush(_glfw.x11.display);
        else
        {
            releasePositionedContext(input);
            input->style = 0;
        }
    }
}

GLFWAPI void cc_glfw_x11_text_input_refresh(CcGlfwX11TextInput* input)
{
    if (input->active && input->hasSpot && !input->positioned)
    {
        const XIMStyle style = findPositionedStyle(input);
        if (style && !acquirePositionedContext(input, style))
            input->style = 0;
    }
}

GLFWAPI int cc_glfw_x11_text_input_key_consumed(GLFWwindow* window)
{
    return filteredKeyWindow != None && ((_GLFWwindow*) window)->x11.handle == filteredKeyWindow;
}

GLFWAPI void cc_glfw_x11_text_input_finish_poll(void)
{
    filteredKeyWindow = None;
}
