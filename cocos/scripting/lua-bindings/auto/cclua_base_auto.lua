------------------------------
--- Tag: Core
------------------------------

---
--- Ref is used for reference count management. If a class inherits from Ref,
--- then it is easy to be shared in different places.
--- @js NA
---@class cc.Ref
local Ref = {}
cc.Ref = Ref

---
--- Returns the Ref's current reference count.
--- For Atomic objects this is a snapshot, not an exclusivity or lifetime test.
---
--- @returns The Ref's reference count.
--- @js NA
---@return number @(unsigned int)
function Ref:getReferenceCount()
end

---
--- Releases the ownership immediately.
---
--- This decrements the Ref's reference count.
---
--- If the reference count reaches 0 after the decrement, this Ref is
--- destructed.
---
--- @see retain, autorelease
--- @js NA
---@return self @(void)
function Ref:release()
end

---
--- Retains the ownership.
---
--- This increases the Ref's reference count.
--- The caller must already have a live reference; this cannot revive an object.
--- Concurrent calls are supported only for the Atomic policy.
---
--- @see release, autorelease
--- @js NA
---@return self @(void)
function Ref:retain()
end

--- Console is helper class that lets the developer control the game from TCP connection.
---  Console will spawn a new thread that will listen to a specified TCP port.
---  Console has a basic token parser. Each token is associated with an std::function<void(int)>.
---  If the std::function<> needs to use the cocos2d API, it needs to call
---
---  ```
---  scheduler->performFunctionInCocosThread( ... );
---  ```
---@class cc.Console:cc.Ref
local Console = {}
cc.Console = Console

--- delete custom command
---@param cmdName string @(std::string_view)
---@return self @(void)
function Console:delCommand(cmdName)
end

--- Checks whether the server for console is bound with ipv6 address
---@return boolean @(bool)
function Console:isIpv6Server()
end

--- starts listening to specified file descriptor
---@param fd number @(int)
---@return boolean @(bool)
function Console:listenOnFileDescriptor(fd)
end

--- starts listening to specified TCP port
---@param port number @(int)
---@return boolean @(bool)
function Console:listenOnTCP(port)
end

--- print something in the console
---@param buf string @(const char*)
---@return self @(void)
function Console:print(buf)
end

---
--- set bind address
---
--- @address : 127.0.0.1
---@param address string @(std::string_view)
---@return self @(void)
function Console:setBindAddress(address)
end

--- The command separator
---@param var number @(char)
---@return self @(void)
function Console:setCommandSeparator(var)
end

--- stops the Console. 'stop' will be called at destruction time as well
---@return self @(void)
function Console:stop()
end

--- @class EventListener
---  @brief The base class of event listener.
---  If you need custom listener which with different callback, you need to inherit this class.
---  For instance, you could refer to EventListenerAcceleration, EventListenerKeyboard, EventListenerTouchOneByOne,
--- EventListenerCustom.
---@class cc.EventListener:cc.Ref
local EventListener = {}
cc.EventListener = EventListener

--- Checks whether the listener is available.
---
---@return boolean @(bool) True if the listener is available.
function EventListener:checkAvailable()
end

--- Clones the listener, its subclasses have to override this method.
---@return cc.EventListener @(cocos2d::EventListener*)
function EventListener:clone()
end

--- Checks whether the listener is enabled.
---
---@return boolean @(bool) True if the listener is enabled.
function EventListener:isEnabled()
end

--- Enables or disables the listener.
--- @note Only listeners with `enabled` state will be able to receive events.
--- When an listener was initialized, it's enabled by default.
--- An event listener can receive events when it is enabled and is not paused.
--- paused state is always false when it is a fixed priority listener.
---
---@param enabled boolean @(bool) True if enables the listener.
---@return self @(void)
function EventListener:setEnabled(enabled)
end

--- @class EventListenerCustom
--- @brief Custom event listener.
--- @code Usage:
---        auto dispatcher = Director::getInstance()->getEventDispatcher();
---     Adds a listener:
---
---        auto callback = [](EventCustom* event){ do_some_thing(); };
---        auto listener = EventListenerCustom::create(callback);
---        dispatcher->addEventListenerWithSceneGraphPriority(listener, one_node);
---
---     Dispatches a custom event:
---
---        EventCustom event("your_event_type");
---        dispatcher->dispatchEvent(&event);
---
---     Removes a listener
---
---        dispatcher->removeEventListener(listener);
--- \endcode
--- @js cc._EventListenerCustom
---@class cc.EventListenerCustom:cc.EventListener
local EventListenerCustom = {}
cc.EventListenerCustom = EventListenerCustom

--- Creates an event listener with type and callback.
--- (static)
---@param eventName string @(std::string_view) The type of the event.
---@param callback function @(std::function<void(cocos2d::EventCustom*)>) The callback function when the specified event was emitted. Required callback; nil is rejected.
---@return cc.EventListenerCustom @(cocos2d::EventListenerCustom*) An autoreleased EventListenerCustom object.
function EventListenerCustom:create(eventName, callback)
end

---
--- Create and reuse shader module.
---@class cc.ShaderCache:cc.Ref
local ShaderCache = {}
cc.ShaderCache = ShaderCache

---
--- Remove all unused shaders.
---@return self @(void)
function ShaderCache:removeUnusedShader()
end

--- returns the shared instance
--- (static)
---@return cc.ShaderCache @(cocos2d::backend::ShaderCache*)
function ShaderCache:getInstance()
end

---
--- Create a fragment shader module.
--- If it is created before, then just return the cached shader module.
--- (static)
---@param shaderSource string @(std::string_view) The source code of the shader.
---@return ccb.ShaderModule @(cocos2d::backend::ShaderModule*)
function ShaderCache:newFragmentShaderModule(shaderSource)
end

---
--- Create a vertex shader module and add it to cache.
--- If it is created before, then just return the cached shader module.
--- (static)
---@param shaderSource string @(std::string_view) The source code of the shader.
---@return ccb.ShaderModule @(cocos2d::backend::ShaderModule*)
function ShaderCache:newVertexShaderModule(shaderSource)
end

---
--- @brief Texture2D class. This class allows to easily create OpenGL 2D textures from images, text or raw data.
--- The created Texture2D object will always have power-of-two dimensions.
--- Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the
--- texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0). Be aware that the
--- content of the generated textures will be upside-down!
---@class cc.Texture2D:cc.Ref
local Texture2D = {}
cc.Texture2D = Texture2D

---
--- Drawing extensions to make it easy to draw basic quads using a Texture2D object.
--- These functions require GL_TEXTURE_2D and both GL_VERTEX_ARRAY and GL_TEXTURE_COORD_ARRAY client states to be
--- enabled.
---
--- Draws a texture at a given point.
---@param point vec2_table @(cocos2d::Vec2)
---@param globalZOrder number @(float)
---@return self @(void)
function Texture2D:drawAtPoint(point, globalZOrder)
end

--- Draws a texture inside a rect.
---@param rect rect_table @(cocos2d::Rect)
---@param globalZOrder number @(float)
---@return self @(void)
function Texture2D:drawInRect(rect, globalZOrder)
end

--- Generates mipmap images for the texture.
--- It only works if the texture size is POT (power of 2).
--- @since v0.99.0
---@return self @(void)
function Texture2D:generateMipmap()
end

---@return ccb.TextureBackend @(cocos2d::backend::TextureBackend*)
function Texture2D:getBackendTexture()
end

--- Helper functions that returns bits per pixels for a given format.
--- @since v2.0
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat)
---@return number @(unsigned int)
function Texture2D:getBitsPerPixelForFormat(format)
end

--- Returns the bits-per-pixel of the in-memory OpenGL texture
--- @since v1.0
---@return number @(unsigned int)
function Texture2D:getBitsPerPixelForFormat()
end

--- Get the texture content size.
---@return vec2_table @(cocos2d::Vec2)
function Texture2D:getContentSize()
end

--- Get content size.
---@return vec2_table @(const cocos2d::Vec2&)
function Texture2D:getContentSizeInPixels()
end

--- Gets max S.
---@return number @(float)
function Texture2D:getMaxS()
end

--- Gets max T.
---@return number @(float)
function Texture2D:getMaxT()
end

---@return string @(std::string)
function Texture2D:getPath()
end

--- Gets the pixel format of the texture.
---@return ccb.PixelFormat @(cocos2d::backend::PixelFormat)
function Texture2D:getPixelFormat()
end

--- Gets the height of the texture in pixels.
---@return number @(int)
function Texture2D:getPixelsHigh()
end

--- Gets the width of the texture in pixels.
---@return number @(int)
function Texture2D:getPixelsWide()
end

---@return number @(int)
function Texture2D:getSamplerFlags()
end

--- Returns the pixel format.
--- @since v2.0
---@return string @(const char*)
function Texture2D:getStringForFormat()
end

--- Whether or not the texture has mip maps.
---@return boolean @(bool)
function Texture2D:hasMipmaps()
end

--- Whether or not the texture has their Alpha premultiplied.
---@return boolean @(bool)
function Texture2D:hasPremultipliedAlpha()
end

---
--- Initializes a texture from a UIImage object.
---
--- We will use the format you passed to the function to convert the image format to the texture format.
--- If you pass PixelFormat::NONE, we will auto detect the image render type and use that type for texture to render.
--- @param image An UIImage object.
--- @param format Texture pixel formats.
---
---@param image cc.Image @(cocos2d::Image*)
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat)
---@return boolean @(bool)
function Texture2D:initWithImage(image, format)
end

---
--- Extensions to make it easy to create a Texture2D object from an image file.
---
---
--- Initializes a texture from a UIImage object.
---
--- We will use the format you specified with setDefaultAlphaPixelFormat to convert the image for texture.
--- NOTE: It will not convert the pvr image file.
--- @param image An UIImage object.
---@param image cc.Image @(cocos2d::Image*)
---@return boolean @(bool)
function Texture2D:initWithImage(image)
end

--- Initializes a texture from a string with dimensions, alignment, font name and font size.
---
--- @param text A null terminated string.
--- @param fontName The font name.
--- @param fontSize The font size.
--- @param dimensions The font dimension.
--- @param hAlignment The font horizontal text alignment type.
--- @param vAlignment The font vertical text alignment type.
--- @param enableWrap Whether enable text wrap or not.
--- @param overflow Whether shrink font size when content larger than the dimensions.
---@param text string @(const char*)
---@param fontName string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment)
---@param enableWrap boolean @(bool)
---@param overflow number @(int)
---@return boolean @(bool)
function Texture2D:initWithString(text, fontName, fontSize, dimensions, hAlignment, vAlignment, enableWrap, overflow)
end

--- Initializes a texture from a string with dimensions, alignment, font name and font size.
---
--- @param text A null terminated string.
--- @param fontName The font name.
--- @param fontSize The font size.
--- @param dimensions The font dimension.
--- @param hAlignment The font horizontal text alignment type.
--- @param vAlignment The font vertical text alignment type.
--- @param enableWrap Whether enable text wrap or not.
--- @param overflow Whether shrink font size when content larger than the dimensions.
---@param text string @(const char*)
---@param fontName string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment)
---@param enableWrap boolean @(bool)
---@return boolean @(bool)
function Texture2D:initWithString(text, fontName, fontSize, dimensions, hAlignment, vAlignment, enableWrap)
end

--- Initializes a texture from a string with dimensions, alignment, font name and font size.
---
--- @param text A null terminated string.
--- @param fontName The font name.
--- @param fontSize The font size.
--- @param dimensions The font dimension.
--- @param hAlignment The font horizontal text alignment type.
--- @param vAlignment The font vertical text alignment type.
--- @param enableWrap Whether enable text wrap or not.
--- @param overflow Whether shrink font size when content larger than the dimensions.
---@param text string @(const char*)
---@param fontName string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment)
---@return boolean @(bool)
function Texture2D:initWithString(text, fontName, fontSize, dimensions, hAlignment, vAlignment)
end

--- Initializes a texture from a string with dimensions, alignment, font name and font size.
---
--- @param text A null terminated string.
--- @param fontName The font name.
--- @param fontSize The font size.
--- @param dimensions The font dimension.
--- @param hAlignment The font horizontal text alignment type.
--- @param vAlignment The font vertical text alignment type.
--- @param enableWrap Whether enable text wrap or not.
--- @param overflow Whether shrink font size when content larger than the dimensions.
---@param text string @(const char*)
---@param fontName string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@return boolean @(bool)
function Texture2D:initWithString(text, fontName, fontSize, dimensions, hAlignment)
end

--- Initializes a texture from a string with dimensions, alignment, font name and font size.
---
--- @param text A null terminated string.
--- @param fontName The font name.
--- @param fontSize The font size.
--- @param dimensions The font dimension.
--- @param hAlignment The font horizontal text alignment type.
--- @param vAlignment The font vertical text alignment type.
--- @param enableWrap Whether enable text wrap or not.
--- @param overflow Whether shrink font size when content larger than the dimensions.
---@param text string @(const char*)
---@param fontName string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function Texture2D:initWithString(text, fontName, fontSize, dimensions)
end

--- Initializes a texture from a string with dimensions, alignment, font name and font size.
---
--- @param text A null terminated string.
--- @param fontName The font name.
--- @param fontSize The font size.
--- @param dimensions The font dimension.
--- @param hAlignment The font horizontal text alignment type.
--- @param vAlignment The font vertical text alignment type.
--- @param enableWrap Whether enable text wrap or not.
--- @param overflow Whether shrink font size when content larger than the dimensions.
---@param text string @(const char*)
---@param fontName string @(std::string_view)
---@param fontSize number @(float)
---@return boolean @(bool)
function Texture2D:initWithString(text, fontName, fontSize)
end

--- Initializes a texture from a string using a text definition.
---
--- @param text A null terminated string.
--- @param textDefinition A FontDefinition object contains font attributes.
---@param text string @(const char*)
---@param textDefinition cc.FontDefinition @(cocos2d::FontDefinition)
---@return boolean @(bool)
function Texture2D:initWithString(text, textDefinition)
end

---@return boolean @(bool)
function Texture2D:isRenderTarget()
end

--- Sets alias texture parameters:
--- - GL_TEXTURE_MIN_FILTER = GL_NEAREST
--- - GL_TEXTURE_MAG_FILTER = GL_NEAREST
---
--- @warning Calling this method could allocate additional texture memory.
---
--- @since v0.8
---@return self @(void)
function Texture2D:setAliasTexParameters()
end

--- Sets antialias texture parameters:
--- - GL_TEXTURE_MIN_FILTER = GL_LINEAR
--- - GL_TEXTURE_MAG_FILTER = GL_LINEAR
---
--- @warning Calling this method could allocate additional texture memory.
---
--- @since v0.8
---@return self @(void)
function Texture2D:setAntiAliasTexParameters()
end

--- Sets max S.
---@param maxS number @(float)
---@return self @(void)
function Texture2D:setMaxS(maxS)
end

--- Sets max T.
---@param maxT number @(float)
---@return self @(void)
function Texture2D:setMaxT(maxT)
end

---@param premultipliedAlpha boolean @(bool)
---@return self @(void)
function Texture2D:setPremultipliedAlpha(premultipliedAlpha)
end

---@param renderTarget boolean @(bool)
---@return self @(void)
function Texture2D:setRenderTarget(renderTarget)
end

--- Update with image.
---
--- @param data Specifies a pointer to the image data in memory.
--- @param offsetX Specifies a texel offset in the x direction within the texture array.
--- @param offsetY Specifies a texel offset in the y direction within the texture array.
--- @param width Specifies the width of the texture subimage.
--- @param height Specifies the height of the texture subimage.
---@param image cc.Image @(cocos2d::Image*)
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat)
---@param index number @(int)
---@return boolean @(bool)
function Texture2D:updateWithImage(image, format, index)
end

--- Update with image.
---
--- @param data Specifies a pointer to the image data in memory.
--- @param offsetX Specifies a texel offset in the x direction within the texture array.
--- @param offsetY Specifies a texel offset in the y direction within the texture array.
--- @param width Specifies the width of the texture subimage.
--- @param height Specifies the height of the texture subimage.
---@param image cc.Image @(cocos2d::Image*)
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat)
---@return boolean @(bool)
function Texture2D:updateWithImage(image, format)
end

--- Returns the alpha pixel format.
--- @since v0.8
--- (static)
---@return ccb.PixelFormat @(cocos2d::backend::PixelFormat)
function Texture2D:getDefaultAlphaPixelFormat()
end

--- sets the default pixel format for UIImagescontains alpha channel.
---
--- @param format
--- If the UIImage contains alpha channel, then the options are:
--- - generate 32-bit textures: backend::PixelFormat::RGBA8 (default one)
--- - generate 24-bit textures: backend::PixelFormat::RGB8
--- - generate 16-bit textures: backend::PixelFormat::RGBA4
--- - generate 16-bit textures: backend::PixelFormat::RGB5A1
--- - generate 16-bit textures: backend::PixelFormat::RGB565
--- - generate 8-bit textures: backend::PixelFormat::A8 (only use it if you use just 1 color)
---
--- How does it work ?
--- - If the image is an RGBA (with Alpha) then the default pixel format will be used (it can be a 8-bit, 16-bit or
--- 32-bit texture)
--- - If the image is an RGB (without Alpha) then: If the default pixel format is RGBA8888 then a RGBA8888 (32-bit)
--- will be used. Otherwise a RGB565 (16-bit texture) will be used.
---
--- This parameter is not valid for PVR PVR.CCZ images.
---
--- @since v0.8
--- (static)
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat)
---@return self @(void)
function Texture2D:setDefaultAlphaPixelFormat(format)
end

--- @class Touch
--- @brief Encapsulates the Touch information, such as touch point, id and so on,
---  and provides the methods that commonly used.
---@class cc.Touch:cc.Ref
local Touch = {}
cc.Touch = Touch

--- Returns the current touch force for 3d touch.
---
---@return number @(float) The current touch force for 3d touch.
function Touch:getCurrentForce()
end

--- Returns the delta of 2 current touches locations in screen coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The delta of 2 current touches locations in screen coordinates.
function Touch:getDelta()
end

--- Get touch id.
--- @js getId
--- @lua getId
---
---@return number @(int) The id of touch.
function Touch:getId()
end

--- Returns the current touch location in OpenGL coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The current touch location in OpenGL coordinates.
function Touch:getLocation()
end

--- Returns the current touch location in screen coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The current touch location in screen coordinates.
function Touch:getLocationInView()
end

--- Returns the maximum touch force for 3d touch.
---
---@return number @(float) The maximum touch force for 3d touch.
function Touch:getMaxForce()
end

--- Returns the previous touch location in OpenGL coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The previous touch location in OpenGL coordinates.
function Touch:getPreviousLocation()
end

--- Returns the previous touch location in screen coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The previous touch location in screen coordinates.
function Touch:getPreviousLocationInView()
end

--- Returns the start touch location in OpenGL coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The start touch location in OpenGL coordinates.
function Touch:getStartLocation()
end

--- Returns the start touch location in screen coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The start touch location in screen coordinates.
function Touch:getStartLocationInView()
end

--- Set the touch information. It always used to monitor touch event.
---
---@param id number @(int) A given id
---@param x number @(float) A given x coordinate.
---@param y number @(float) A given y coordinate.
---@param force number @(float) Current force for 3d touch.
---@param maxForce number @(float) maximum possible force for 3d touch.
---@return self @(void)
function Touch:setTouchInfo(id, x, y, force, maxForce)
end

--- Set the touch information. It always used to monitor touch event.
---
---@param id number @(int) A given id
---@param x number @(float) A given x coordinate.
---@param y number @(float) A given y coordinate.
---@return self @(void)
function Touch:setTouchInfo(id, x, y)
end

--- @class Event
--- @brief Base class of all kinds of events.
---@class cc.Event:cc.Ref
local Event = {}
cc.Event = Event

--- Gets current target of the event.
--- @note It's only available when the event listener is associated with node.
--- It returns 0 when the listener is associated with fixed priority.
---@return cc.Node @(cocos2d::Node*) The target with which the event associates.
function Event:getCurrentTarget()
end

--- Gets the event type.
---
---@return cc.Event.Type @(cocos2d::Event::Type) The event type.
function Event:getType()
end

--- Checks whether the event has been stopped.
---
---@return boolean @(bool) True if the event has been stopped.
function Event:isStopped()
end

--- Stops propagation for current event.
---@return self @(void)
function Event:stopPropagation()
end

--- @class EventTouch
--- @brief Touch event.
---@class cc.EventTouch:cc.Event
local EventTouch = {}
cc.EventTouch = EventTouch

--- Get event code.
---
---@return cc.EventTouch.EventCode @(cocos2d::EventTouch::EventCode) The code of the event.
function EventTouch:getEventCode()
end

--- Set the event code.
---
---@param eventCode cc.EventTouch.EventCode @(cocos2d::EventTouch::EventCode) A given EventCode.
---@return self @(void)
function EventTouch:setEventCode(eventCode)
end

--- @class EventKeyboard
--- @brief Keyboard event.
---@class cc.EventKeyboard:cc.Event
local EventKeyboard = {}
cc.EventKeyboard = EventKeyboard




---@class cc.Component:cc.Ref
local Component = {}
cc.Component = Component

---@return string @(std::string_view)
function Component:getName()
end

---@return cc.Node @(cocos2d::Node*)
function Component:getOwner()
end

---@return boolean @(bool)
function Component:init()
end

---@return boolean @(bool)
function Component:isEnabled()
end

---@return self @(void)
function Component:onAdd()
end

---@return self @(void)
function Component:onRemove()
end

---@param enabled boolean @(bool)
---@return self @(void)
function Component:setEnabled(enabled)
end

---@param name string @(std::string_view)
---@return self @(void)
function Component:setName(name)
end

---@param owner cc.Node @(cocos2d::Node*)
---@return self @(void)
function Component:setOwner(owner)
end

---@param delta number @(float)
---@return self @(void)
function Component:update(delta)
end

--- (static)
---@return cc.Component @(cocos2d::Component*)
function Component:create()
end

--- @class Node
--- @brief Node is the base element of the Scene Graph. Elements of the Scene Graph must be Node objects or subclasses of
--- it. The most common Node objects are: Scene, Layer, Sprite, Menu, Label.
---
---  The main features of a Node are:
---  - They can contain other Node objects (`addChild`, `getChildByTag`, `removeChild`, etc)
---  - They can schedule periodic callback (`schedule`, `unschedule`, etc)
---  - They can execute actions (`runAction`, `stopAction`, etc)
---
---  Subclassing a Node usually means (oneall) of:
---  - overriding init to initialize resources and schedule callbacks
---  - create callbacks to handle the advancement of time
---  - overriding `draw` to render the node
---
---  Properties of Node:
---  - position (default: x=0, y=0)
---  - scale (default: x=1, y=1)
---  - rotation (in degrees, clockwise) (default: 0)
---  - anchor point (default: x=0, y=0)
---  - contentSize (default: width=0, height=0)
---  - visible (default: true)
---
---  Limitations:
---  - A Node is a "void" object. If you want to draw something on the screen, you should use a Sprite instead. Or subclass
--- Node and override `draw`.
---
---@class cc.Node:cc.Ref
local Node = {}
cc.Node = Node

---@param z std.int32_t @(std::int32_t)
---@return self @(void)
function Node:_setLocalZOrder(z)
end

---
--- Adds a child to the container with z order and tag
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---
---@param child cc.Node @(cocos2d::Node*)     A child node.
---@param localZOrder number @(int)    Z order for drawing priority. Please refer to `setLocalZOrder(int)`.
---@param name string @(std::string_view)      A string to identify the node easily. Please refer to `setName(int)`.
---@return self @(void)
function Node:addChild(child, localZOrder, name)
end

---
--- Adds a child to the container with z order and tag.
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---
--- Please use `addChild(Node* child, int localZOrder, const std::string &name)` instead.
---@param child cc.Node @(cocos2d::Node*)         A child node.
---@param localZOrder number @(int)   Z order for drawing priority. Please refer to `setLocalZOrder(int)`.
---@param tag number @(int)           An integer to identify the node easily. Please refer to `setTag(int)`.
---@return self @(void)
function Node:addChild(child, localZOrder, tag)
end

---
--- Adds a child to the container with a local z-order.
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---@param child cc.Node @(cocos2d::Node*)     A child node.
---@param localZOrder number @(int)    Z order for drawing priority. Please refer to `setLocalZOrder(int)`.
---@return self @(void)
function Node:addChild(child, localZOrder)
end

---
--- Adds a child to the container with z-order as 0.
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---@param child cc.Node @(cocos2d::Node*) A child node.
---@return self @(void)
function Node:addChild(child)
end

---
--- Adds a component.
---
---@param component cc.Component @(cocos2d::Component*) A given component.
---@return boolean @(bool) True if added success.
function Node:addComponent(component)
end

---
--- Should addChild() make the child follow it's parent's mask?
--- If applyChildren is true, then it will modify the camera mask of its children recursively when a child is added.
---@param applyChildren boolean @(bool) A boolean value to determine whether the mask bit should apply to its children or not.
---@return self @(void)
function Node:applyMaskOnEnter(applyChildren)
end

---
--- Stops all running actions and schedulers
---@return self @(void)
function Node:cleanup()
end

---
--- Converts a Vec2 to node (local) space coordinates. The result is in Points.
---
---@param worldPoint vec2_table @(cocos2d::Vec2) A given coordinate.
---@return vec2_table @(cocos2d::Vec2) A point in node (local) space coordinates.
function Node:convertToNodeSpace(worldPoint)
end

---
--- Converts a Vec2 to node (local) space coordinates. The result is in Points.
--- treating the returnedreceived node point as anchor relative.
---
---@param worldPoint vec2_table @(cocos2d::Vec2) A given coordinate.
---@return vec2_table @(cocos2d::Vec2) A point in node (local) space coordinates, anchor relative.
function Node:convertToNodeSpaceAR(worldPoint)
end

---
--- Converts a Vec2 to world space coordinates. The result is in Points.
---
---@param nodePoint vec2_table @(cocos2d::Vec2) A given coordinate.
---@return vec2_table @(cocos2d::Vec2) A point in world space coordinates.
function Node:convertToWorldSpace(nodePoint)
end

---
--- Converts a local Vec2 to world space coordinates.The result is in Points.
--- treating the returnedreceived node point as anchor relative.
---
---@param nodePoint vec2_table @(cocos2d::Vec2) A given coordinate.
---@return vec2_table @(cocos2d::Vec2) A point in world space coordinates, anchor relative.
function Node:convertToWorldSpaceAR(nodePoint)
end

---
--- convenience methods which take a Touch instead of Vec2.
---
---@param touch cc.Touch @(cocos2d::Touch*) A given touch.
---@return vec2_table @(cocos2d::Vec2) A point in world space coordinates.
function Node:convertTouchToNodeSpace(touch)
end

---
--- converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
---
---@param touch cc.Touch @(cocos2d::Touch*) A given touch.
---@return vec2_table @(cocos2d::Vec2) A point in world space coordinates, anchor relative.
function Node:convertTouchToNodeSpaceAR(touch)
end

---
--- Override this method to draw your own node.
--- The following GL states will be enabled by default:
--- - `glEnableClientState(GL_VERTEX_ARRAY);`
--- - `glEnableClientState(GL_COLOR_ARRAY);`
--- - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
--- - `glEnable(GL_TEXTURE_2D);`
--- AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
--- But if you enable any other GL state, you should disable it after drawing your node.
---
---@param renderer cc.Renderer @(cocos2d::Renderer*) A given renderer.
---@param transform mat4_table @(cocos2d::Mat4) A transform matrix.
---@param flags number @(uint32_t) Renderer flag.
---@return self @(void)
function Node:draw(renderer, transform, flags)
end

---@return self @(void)
function Node:draw()
end

--- Search the children of the receiving node to perform processing for nodes which share a name.
---
--- Search syntax options:
--- ``: Can only be placed at the begin of the search string. This indicates that it will search recursively.
--- `..`: The search should move up to the node's parent. Can only be placed at the end of string.
--- `` : When placed anywhere but the start of the search string, this indicates that the search should move to the
--- node's children.
---
--- @code
--- enumerateChildren("MyName", ...): This searches the children recursively and matches any node with the name
--- `MyName`. enumerateChildren("[[:alnum:]]+", ...): This search string matches every node of its children.
--- enumerateChildren("A[[:digit:]]", ...): This searches the node's children and returns any child named `A0`, `A1`,
--- ..., `A9`. enumerateChildren("AbbyNormal", ...): This searches the node's grandchildren and returns any node
--- whose name is `Normal` and whose parent is named `Abby`. enumerateChildren("AbbyNormal", ...): This searches
--- recursively and returns any node whose name is `Normal` and whose parent is named `Abby`.
--- @endcode
---
--- @warning Only support alpha or number for name, and not support unicode.
---
--- following arguments: `node` A node that matches the name And returns a boolean result. Your callback can return
--- `true` to terminate the enumeration.
---
--- @since v3.2
---@param name string @(std::string_view) The name to search for, supports c++11 regular expression.
---@param callback function @(std::function<bool(cocos2d::Node*)>) A callback function to execute on nodes that match the `name` parameter. The function takes the Required callback; nil is rejected.
---@return self @(void)
function Node:enumerateChildren(name, callback)
end

---
--- Gets an action from the running action list by its tag.
---
--- @see `setTag(int)`, `getTag()`.
---
---@param tag number @(int)
---@return cc.Action @(cocos2d::Action*) The action object with the given tag.
function Node:getActionByTag(tag)
end

---@return cc.ActionManager @(const cocos2d::ActionManager*)
function Node:getActionManager()
end

---
--- Gets the ActionManager object that is used by all actions.
--- @see setActionManager(ActionManager*)
---@return cc.ActionManager @(cocos2d::ActionManager*) A ActionManager object.
function Node:getActionManager()
end

---
--- Returns the anchor point in percent.
---
--- @see `setAnchorPoint(const Vec2&)`
---
---@return vec2_table @(const cocos2d::Vec2&) The anchor point of node.
function Node:getAnchorPoint()
end

---
--- Returns the anchorPoint in absolute pixels.
---
--- @warning You can only read it. If you wish to modify it, use anchorPoint instead.
--- @see `getAnchorPoint()`
---
---@return vec2_table @(const cocos2d::Vec2&) The anchor point in absolute pixels.
function Node:getAnchorPointInPoints()
end

---
--- Returns an AABB (axis-aligned bounding-box) in its parent's coordinate system.
---
---@return rect_table @(cocos2d::Rect) An AABB (axis-aligned bounding-box) in its parent's coordinate system
function Node:getBoundingBox()
end

---
--- get & set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true
---@return number @(unsigned short)
function Node:getCameraMask()
end

---
--- Gets a child from the container with its name.
---
---
---
--- @since v3.2
---@param name string @(std::string_view)   An identifier to find the child node.
---@return cc.Node @(cocos2d::Node*) a Node object whose name equals to the input parameter.
function Node:getChildByName(name)
end

---
--- Gets a child from the container with its tag.
---
---
---
--- Please use `getChildByName()` instead.
---@param tag number @(int)   An identifier to find the child node.
---@return cc.Node @(cocos2d::Node*) a Node object whose tag equals to the input parameter.
function Node:getChildByTag(tag)
end

---@return cc.Node [] @(const cocos2d::Vector<cocos2d::Node *>&)
function Node:getChildren()
end

---
--- Returns the array of the node's children.
---
---@return cc.Node [] @(cocos2d::Vector<cocos2d::Node *>&) the array the node's children.
function Node:getChildren()
end

---
--- Returns the amount of children.
---
---@return number @(ssize_t) The amount of children.
function Node:getChildrenCount()
end

---
--- Query node's color value.
---@return color3b_table @(const cocos2d::Color3B&) A Color3B color value.
function Node:getColor()
end

--- @{
--- @name component functions
---
--- Gets a component by its name.
---
---@param name string @(std::string_view) A given name of component.
---@return cc.Component @(cocos2d::Component*) The Component by name.
function Node:getComponent(name)
end

---
--- Returns the untransformed size of the node.
---
--- @see `setContentSize(const Vec2&)`
---
---@return vec2_table @(const cocos2d::Vec2&) The untransformed size of the node.
function Node:getContentSize()
end

---
--- Gets the description string. It makes debugging easier.
--- @js NA
--- @lua NA
---@return string @(std::string) A string
function Node:getDescription()
end

---
--- Query node's displayed color.
---@return color3b_table @(const cocos2d::Color3B&) A Color3B color value.
function Node:getDisplayedColor()
end

---
--- Return the node's display opacity.
--- The difference between opacity and displayedOpacity is:
--- The displayedOpacity is what's the final rendering opacity of node.
---@return number @(uint8_t) A GLubyte value.
function Node:getDisplayedOpacity()
end

--- Get the event dispatcher of scene.
---
---@return cc.EventDispatcher @(cocos2d::EventDispatcher*) The event dispatcher of scene.
function Node:getEventDispatcher()
end

---
--- Returns the Node's Global Z Order.
---
--- @see `setGlobalZOrder(int)`
---
---@return number @(float) The node's global Z order
function Node:getGlobalZOrder()
end

---
--- Gets the local Z order of this node.
---
--- @see `setLocalZOrder(int)`
---
---@return std.int32_t @(std::int32_t) The local (relative to its siblings) Z order.
function Node:getLocalZOrder()
end

--- Returns a string that is used to identify the node.
---
--- @since v3.2
---@return string @(std::string_view) A string that identifies the node.
function Node:getName()
end

---
--- Returns the affine transform matrix that transform the node's (local) space coordinates into the parent's space
--- coordinates. The matrix is in Pixels.
---
--- Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see
--- getNodeToWorldAffineTransform
---
--- @since v3.7
---@param ancestor cc.Node @(cocos2d::Node*) The parent's node pointer.
---@return cc.AffineTransform @(cocos2d::AffineTransform) The affine transformation matrix.
function Node:getNodeToParentAffineTransform(ancestor)
end

---@return cc.AffineTransform @(cocos2d::AffineTransform)
function Node:getNodeToParentAffineTransform()
end

---
--- Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
--- The matrix is in Pixels.
--- Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see
--- getNodeToWorldTransform
---
--- @since v3.7
---@param ancestor cc.Node @(cocos2d::Node*) The parent's node pointer.
---@return mat4_table @(cocos2d::Mat4) The transformation matrix.
function Node:getNodeToParentTransform(ancestor)
end

---
--- Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
--- The matrix is in Pixels.
---
---@return mat4_table @(const cocos2d::Mat4&) The transformation matrix.
function Node:getNodeToParentTransform()
end

---@return cc.AffineTransform @(cocos2d::AffineTransform)
function Node:getNodeToWorldAffineTransform()
end

---
--- Returns the world affine transform matrix. The matrix is in Pixels.
---
---@return mat4_table @(cocos2d::Mat4) transformation matrix, in pixels.
function Node:getNodeToWorldTransform()
end

---@return vec2_table @(const cocos2d::Vec2&)
function Node:getNormalizedPosition()
end

---
--- Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd
--- and actions arrays).
---
--- Composable actions are counted as 1 action. Example:
--- If you are running 1 Sequence of 7 actions, it will return 1.
--- If you are running 7 Sequences of 2 actions, it will return 7.
---
---@return number @(ssize_t) The number of actions that are running plus the ones that are schedule to run.
function Node:getNumberOfRunningActions()
end

---
--- Returns the numbers of actions that are running plus the ones that are
--- schedule to run (actions in actionsToAdd and actions arrays) with a
--- specific tag.
---
--- Composable actions are counted as 1 action. Example:
--- If you are running 1 Sequence of 7 actions, it will return 1.
--- If you are running 7 Sequences of 2 actions, it will return 7.
---
---
--- ones that are schedule to run with specific tag.
---@param tag number @(int)
---@return number @(ssize_t) The number of actions that are running plus the
function Node:getNumberOfRunningActionsByTag(tag)
end

---
--- Get the callback of event EnterTransitionDidFinish.
---@return function @(const std::function<void ()>&) std::function<void()>
function Node:getOnEnterTransitionDidFinishCallback()
end

---
--- Get the callback of event ExitTransitionDidStart.
---@return function @(const std::function<void ()>&) std::function<void()>
function Node:getOnExitTransitionDidStartCallback()
end

---
--- Return the node's opacity.
---@return number @(uint8_t) A GLubyte value.
function Node:getOpacity()
end

---@return cc.Node @(const cocos2d::Node*)
function Node:getParent()
end

---
--- Returns a pointer to the parent node.
---
--- @see `setParent(Node*)`
---
--- @returns A pointer to the parent node.
---@return cc.Node @(cocos2d::Node*)
function Node:getParent()
end

---@return cc.AffineTransform @(cocos2d::AffineTransform)
function Node:getParentToNodeAffineTransform()
end

---
--- Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
--- The matrix is in Pixels.
---
---@return mat4_table @(const cocos2d::Mat4&) The transformation matrix.
function Node:getParentToNodeTransform()
end

---
--- Gets the position (x,y) of the node in its parent's coordinate system.
---
--- @see setPosition(const Vec2&)
---
--- @code
--- In js and lua return value is table which contains x,y.
--- @endcode
---@return vec2_table @(const cocos2d::Vec2&) The position (x,y) of the node in OpenGL coordinates.
function Node:getPosition()
end

---
--- Returns the position (X,Y,Z) in its parent's coordinate system.
---
--- @js NA
---@return vec3_table @(cocos2d::Vec3) The position (X, Y, and Z) in its parent's coordinate system.
function Node:getPosition3D()
end

--- Returns the normalized position.
---
---@return vec2_table @(const cocos2d::Vec2&) The normalized position.
function Node:getPositionNormalized()
end

--- Gets the x coordinate of the node in its parent's coordinate system.
---
---@return number @(float) The x coordinate of the node.
function Node:getPositionX()
end

--- Gets the y coordinate of the node in its parent's coordinate system.
---
---@return number @(float) The y coordinate of the node.
function Node:getPositionY()
end

---
--- Gets position Z coordinate of this node.
---
--- @see setPositionZ(float)
---
--- @js getVertexZ
---@return number @(float) The position Z coordinate of this node.
function Node:getPositionZ()
end

---@return ccb.ProgramState @(cocos2d::backend::ProgramState*)
function Node:getProgramState()
end

---
--- Returns the rotation of the node in degrees.
---
--- @see `setRotation(float)`
---
---@return number @(float) The rotation of the node in degrees.
function Node:getRotation()
end

---
--- Returns the rotation (X,Y,Z) in degrees.
---
--- @js NA
---@return vec3_table @(cocos2d::Vec3) The rotation of the node in 3d.
function Node:getRotation3D()
end

---
--- Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.
---
--- @see `setRotationSkewX(float)`
---
--- @js getRotationX
---@return number @(float) The X rotation in degrees.
function Node:getRotationSkewX()
end

---
--- Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
---
--- @see `setRotationSkewY(float)`
---
--- @js getRotationY
---@return number @(float) The Y rotation in degrees.
function Node:getRotationSkewY()
end

---
--- Gets the scale factor of the node,  when X and Y have the same scale factor.
---
--- @warning Assert when `_scaleX != _scaleY`
--- @see setScale(float)
---
---@return number @(float) The scale factor of the node.
function Node:getScale()
end

---
--- Returns the scale factor on X axis of this node
---
--- @see setScaleX(float)
---
---@return number @(float) The scale factor on X axis.
function Node:getScaleX()
end

---
--- Returns the scale factor on Y axis of this node
---
--- @see `setScaleY(float)`
---
---@return number @(float) The scale factor on Y axis.
function Node:getScaleY()
end

---
--- Returns the scale factor on Z axis of this node
---
--- @see `setScaleZ(float)`
---
---@return number @(float) The scale factor on Z axis.
function Node:getScaleZ()
end

--- Returns the Scene that contains the Node.
--- It returns `nullptr` if the node doesn't belong to any Scene.
--- This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It
--- is that the user caches the results in case this functions is being used inside a loop.
---
---@return cc.Scene @(cocos2d::Scene*) The Scene that contains the node.
function Node:getScene()
end

---@return cc.Scheduler @(const cocos2d::Scheduler*)
function Node:getScheduler()
end

---
--- Gets a Scheduler object.
---
--- @see setScheduler(Scheduler*)
---@return cc.Scheduler @(cocos2d::Scheduler*) A Scheduler object.
function Node:getScheduler()
end

---
--- Returns the X skew angle of the node in degrees.
---
--- @see `setSkewX(float)`
---
---@return number @(float) The X skew angle of the node in degrees.
function Node:getSkewX()
end

---
--- Returns the Y skew angle of the node in degrees.
---
--- @see `setSkewY(float)`
---
---@return number @(float) The Y skew angle of the node in degrees.
function Node:getSkewY()
end

---
--- Returns a tag that is used to identify the node easily.
---
---
--- Please use `getTag()` instead.
---@return number @(int) An integer that identifies the node.
function Node:getTag()
end

---
--- Gets position of widget in world space.
---
---@return vec2_table @(cocos2d::Vec2) Position of widget in world space.
function Node:getWorldPosition()
end

---@return cc.AffineTransform @(cocos2d::AffineTransform)
function Node:getWorldToNodeAffineTransform()
end

---
--- Returns the inverse world affine transform matrix. The matrix is in Pixels.
---
---@return mat4_table @(cocos2d::Mat4) The transformation matrix.
function Node:getWorldToNodeTransform()
end

---
--- The basic node hit test, since axmol-1.0
---
---
---
---@param worldPoint vec2_table @(cocos2d::Vec2)   The coord in GL world space.
---@return boolean @(bool) Whether the worldPoint is inside this node
function Node:hitTest(worldPoint)
end

---@return boolean @(bool)
function Node:init()
end

---@return boolean @(bool)
function Node:initLayer()
end

---
--- Query whether cascadeColor is enabled or not.
---@return boolean @(bool) Whether cascadeColor is enabled or not.
function Node:isCascadeColorEnabled()
end

---
--- Whether cascadeOpacity is enabled or not.
---@return boolean @(bool) A boolean value.
function Node:isCascadeOpacityEnabled()
end

---
--- Gets whether the anchor point will be (0,0) when you position this node.
---
--- @see `setIgnoreAnchorPointForPosition(bool)`
---
---@return boolean @(bool) true if the anchor point will be (0,0) when you position this node.
function Node:isIgnoreAnchorPointForPosition()
end

---
--- If node opacity will modify the RGB color value, then you should override this method and return true.
---@return boolean @(bool) A boolean value, true indicates that opacity will modify color; false otherwise.
function Node:isOpacityModifyRGB()
end

---
--- Returns whether or not the node is "running".
---
--- If the node is running it will accept event callbacks like onEnter(), onExit(), update().
---
---@return boolean @(bool) Whether or not the node is running.
function Node:isRunning()
end

---
--- Checks whether a lambda function is scheduled.
---
--- @js NA
--- @lua NA
---@param key string @(std::string_view)      key of the callback
---@return boolean @(bool) Whether the lambda function selector is scheduled.
function Node:isScheduled(key)
end

---
--- Determines if the node is visible.
---
--- @see `setVisible(bool)`
---
---@return boolean @(bool) true if the node is visible, false if the node is hidden.
function Node:isVisible()
end

---
--- Pauses all scheduled selectors, actions and event listeners.
--- This method is called internally by onExit.
---@return self @(void)
function Node:pause()
end

---
--- Removes all components
---@return self @(void)
function Node:removeAllComponents()
end

---
--- Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
---
---@param child cc.Node @(cocos2d::Node*)     The child node which will be removed.
---@param cleanup boolean @(bool)   True if all running actions and callbacks on the child node will be cleanup, false otherwise.
---@return self @(void)
function Node:removeChild(child, cleanup)
end

---
--- Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
---
---@param child cc.Node @(cocos2d::Node*)     The child node which will be removed.
---@return self @(void)
function Node:removeChild(child)
end

---
--- Removes a child from the container by tag value. It will also cleanup all running actions depending on the
--- cleanup parameter.
---
---@param name string @(std::string_view)       A string that identifies a child node.
---@param cleanup boolean @(bool)   True if all running actions and callbacks on the child node will be cleanup, false otherwise.
---@return self @(void)
function Node:removeChildByName(name, cleanup)
end

---
--- Removes a child from the container by tag value. It will also cleanup all running actions depending on the
--- cleanup parameter.
---
---@param name string @(std::string_view)       A string that identifies a child node.
---@return self @(void)
function Node:removeChildByName(name)
end

---
--- Removes a child from the container by tag value. It will also cleanup all running actions depending on the
--- cleanup parameter.
---
---
--- Please use `removeChildByName` instead.
---@param tag number @(int)       An integer number that identifies a child node.
---@param cleanup boolean @(bool)   True if all running actions and callbacks on the child node will be cleanup, false otherwise.
---@return self @(void)
function Node:removeChildByTag(tag, cleanup)
end

---
--- Removes a child from the container by tag value. It will also cleanup all running actions depending on the
--- cleanup parameter.
---
---
--- Please use `removeChildByName` instead.
---@param tag number @(int)       An integer number that identifies a child node.
---@return self @(void)
function Node:removeChildByTag(tag)
end

---
--- Removes a component by its pointer.
---
---@param component cc.Component @(cocos2d::Component*) A given component.
---@return boolean @(bool) True if removed success.
function Node:removeComponent(component)
end

---
--- Removes a component by its name.
---
---@param name string @(std::string_view) A given name of component.
---@return boolean @(bool) True if removed success.
function Node:removeComponent(name)
end

---
--- Reorders a child according to a new z value.
---
---@param child cc.Node @(cocos2d::Node*)     An already added child node. It MUST be already added.
---@param localZOrder number @(int) Z order for drawing priority. Please refer to setLocalZOrder(int).
---@return self @(void)
function Node:reorderChild(child, localZOrder)
end

---@param child cc.Node @(cocos2d::Node*)
---@param cleanup boolean @(bool)
---@return self @(void)
function Node:resetChild(child, cleanup)
end

---
--- Resumes all scheduled selectors, actions and event listeners.
--- This method is called internally by onEnter.
---@return self @(void)
function Node:resume()
end

---
--- Executes an action, and returns the action that is executed.
---
--- This node becomes the action's target. Refer to Action::getTarget().
--- @warning Actions don't retain their target.
---
---@param action cc.Action @(cocos2d::Action*) An Action pointer.
---@return cc.Action @(cocos2d::Action*)
function Node:runAction(action)
end

---
--- Sets the ActionManager object that is used by all actions.
---
--- @warning If you set a new ActionManager, then previously created actions will be removed.
---
---@param actionManager cc.ActionManager @(cocos2d::ActionManager*)     A ActionManager object that is used by all actions.
---@return self @(void)
function Node:setActionManager(actionManager)
end

---@param additionalTransform cc.AffineTransform @(cocos2d::AffineTransform)
---@return self @(void)
function Node:setAdditionalTransform(additionalTransform)
end

---@param additionalTransform mat4_table @(cocos2d::Mat4)
---@return self @(void)
function Node:setAdditionalTransform(additionalTransform)
end

---
--- Sets the anchor point in percent.
---
--- anchorPoint is the point around which all transformations and positioning manipulations take place.
--- It's like a pin in the node where it is "attached" to its parent.
--- The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the
--- top-right corner. But you can use values higher than (1,1) and lower than (0,0) too. The default anchorPoint is
--- (0,0), so it starts in the lower left corner of the node.
--- @note If node has a physics body, the anchor must be in the middle, you can't change this to other value.
---
---@param anchorPoint vec2_table @(cocos2d::Vec2)   The anchor point of node.
---@return self @(void)
function Node:setAnchorPoint(anchorPoint)
end

---
--- Modify the camera mask for current node.
--- If applyChildren is true, then it will modify the camera mask of its children recursively.
---@param mask number @(unsigned short) A unsigned short bit for mask.
---@param applyChildren boolean @(bool) A boolean value to determine whether the mask bit should apply to its children or not.
---@return self @(void)
function Node:setCameraMask(mask, applyChildren)
end

---
--- Modify the camera mask for current node.
--- If applyChildren is true, then it will modify the camera mask of its children recursively.
---@param mask number @(unsigned short) A unsigned short bit for mask.
---@return self @(void)
function Node:setCameraMask(mask)
end

---
--- If you want node's color affect the children node's color, then set it to true.
--- Otherwise, set it to false.
---@param cascadeColorEnabled boolean @(bool) A boolean value.
---@return self @(void)
function Node:setCascadeColorEnabled(cascadeColorEnabled)
end

---
--- Change node's cascadeOpacity property.
---@param cascadeOpacityEnabled boolean @(bool) True to enable cascadeOpacity, false otherwise.
---@return self @(void)
function Node:setCascadeOpacityEnabled(cascadeOpacityEnabled)
end

---
--- Change the color of node.
---@param color color3b_table @(cocos2d::Color3B) A Color3B color value.
---@return self @(void)
function Node:setColor(color)
end

---
--- Sets the untransformed size of the node.
---
--- The contentSize remains the same no matter the node is scaled or rotated.
--- All nodes has a size. Layer and Scene has the same size of the screen.
---
---@param contentSize vec2_table @(cocos2d::Vec2)   The untransformed size of the node.
---@return self @(void)
function Node:setContentSize(contentSize)
end

--- Set event dispatcher for scene.
---
---@param dispatcher cc.EventDispatcher @(cocos2d::EventDispatcher*) The event dispatcher of scene.
---@return self @(void)
function Node:setEventDispatcher(dispatcher)
end

---
--- Defines the order in which the nodes are renderer.
--- Nodes that have a Global Z Order lower, are renderer first.
---
--- In case two or more nodes have the same Global Z Order, the order is not guaranteed.
--- The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.
---
--- By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to
--- render the nodes.
---
--- Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.
---
--- Limitations: Global Z Order can't be used by Nodes that have SpriteBatchNode as one of their ancestors.
--- And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.
---
--- @see `setLocalZOrder()`
--- @see `setVertexZ()`
---
--- @since v3.0
---
---@param globalZOrder number @(float) The global Z order value.
---@return self @(void)
function Node:setGlobalZOrder(globalZOrder)
end

---
--- Sets whether the anchor point will be (0,0) when you position this node.
---
--- This is an internal method, only used by Layer and Scene. Don't call it outside framework.
--- The default value is false, while in Layer and Scene are true.
---
---@param ignore boolean @(bool)    true if anchor point will be (0,0) when you position this node.
---@return self @(void)
function Node:setIgnoreAnchorPointForPosition(ignore)
end

---
--- LocalZOrder is the 'key' used to sort the node relative to its siblings.
---
--- The Node's parent will sort all its children based on the LocalZOrder value.
--- If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front
--- of the other node in the array.
---
--- Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm (
--- http:en.wikipedia.orgwikiTree_traversal#In-order ) And Nodes that have LocalZOrder values < 0 are the "left"
--- subtree While Nodes with LocalZOrder >=0 are the "right" subtree.
---
--- @see `setGlobalZOrder`
--- @see `setVertexZ`
---
---@param localZOrder std.int32_t @(std::int32_t) The local Z order value.
---@return self @(void)
function Node:setLocalZOrder(localZOrder)
end

--- Changes the name that is used to identify the node easily.
---
--- @since v3.2
---@param name string @(std::string_view) A string that identifies the node.
---@return self @(void)
function Node:setName(name)
end

---
--- Sets the transformation matrix manually.
---
---@param transform mat4_table @(cocos2d::Mat4) A given transformation matrix.
---@return self @(void)
function Node:setNodeToParentTransform(transform)
end

---@param position vec2_table @(cocos2d::Vec2)
---@return self @(void)
function Node:setNormalizedPosition(position)
end

---
--- Set the callback of event onEnter.
---@param callback function @(std::function<void()>) A std::function<void()> callback.
---@return self @(void)
function Node:setOnEnterCallback(callback)
end

---
--- Set the callback of event EnterTransitionDidFinish.
---@param callback function @(std::function<void()>) A std::function<void()> callback.
---@return self @(void)
function Node:setOnEnterTransitionDidFinishCallback(callback)
end

---
--- Set the callback of event onExit.
---@param callback function @(std::function<void()>) A std::function<void()> callback.
---@return self @(void)
function Node:setOnExitCallback(callback)
end

---
--- Set the callback of event ExitTransitionDidStart.
---@param callback function @(std::function<void()>) A std::function<void()> callback.
---@return self @(void)
function Node:setOnExitTransitionDidStartCallback(callback)
end

---
--- Change node opacity.
---@param opacity number @(uint8_t) A GLubyte opacity value.
---@return self @(void)
function Node:setOpacity(opacity)
end

---
--- If you want the opacity affect the color property, then set to true.
---@param value boolean @(bool) A boolean value.
---@return self @(void)
function Node:setOpacityModifyRGB(value)
end

---
--- Sets the parent node.
---
---@param parent cc.Node @(cocos2d::Node*)    A pointer to the parent node.
---@return self @(void)
function Node:setParent(parent)
end

---
--- Sets the position (x,y) of the node in its parent's coordinate system.
---
--- Passing two numbers (x,y) is much efficient than passing Vec2 object.
--- This method is bound to Lua and JavaScript.
--- Passing a number is 10 times faster than passing a object from Lua to c++.
---
--- @code
--- sample code in Lua
--- local pos  = node::getPosition()  -- returns Vec2 object from C++.
--- node:setPosition(x, y)            -- pass x, y coordinate to C++.
--- @endcode
---
---@param x number @(float)     X coordinate for position.
---@param y number @(float)     Y coordinate for position.
---@return self @(void)
function Node:setPosition(x, y)
end

---
--- Sets the position (x,y) of the node in its parent's coordinate system.
---
--- Usually we use `Vec2(x,y)` to compose Vec2 object.
--- This code snippet sets the node in the center of screen.
--- @code
--- Vec2 size = Director::getInstance()->getWinSize();
--- node->setPosition(size.width2, size.height2);
--- @endcode
---
---@param position vec2_table @(cocos2d::Vec2)  The position (x,y) of the node in OpenGL coordinates.
---@return self @(void)
function Node:setPosition(position)
end

---
--- Sets the position (X, Y, and Z) in its parent's coordinate system.
---
--- @js NA
---@param position vec3_table @(cocos2d::Vec3) The position (X, Y, and Z) in its parent's coordinate system.
---@return self @(void)
function Node:setPosition3D(position)
end

--- Sets the position (x,y) using values between 0 and 1.
--- The positions in pixels is calculated like the following:
--- @code
--- pseudo code
--- void setNormalizedPosition(Vec2 pos) {
--- Vec2 s = getParent()->getContentSize();
--- _position = pos * s;
--- }
--- @endcode
---
---@param position vec2_table @(cocos2d::Vec2) The normalized position (x,y) of the node, using value between 0 and 1.
---@return self @(void)
function Node:setPositionNormalized(position)
end

---
--- GetsSets x or y coordinate individually for position.
--- These methods are used in Lua and Javascript Bindings
---
--- Sets the x coordinate of the node in its parent's coordinate system.
---
---@param x number @(float) The x coordinate of the node.
---@return self @(void)
function Node:setPositionX(x)
end

--- Sets the y coordinate of the node in its parent's coordinate system.
---
---@param y number @(float) The y coordinate of the node.
---@return self @(void)
function Node:setPositionY(y)
end

---
--- Sets the 'z' coordinate in the position. It is the OpenGL Z vertex value.
---
--- The OpenGL depth buffer and depth testing are disabled by default. You need to turn them on.
--- In order to use this property correctly.
---
--- `setPositionZ()` also sets the `setGlobalZValue()` with the positionZ as value.
---
--- @see `setGlobalZValue()`
---
--- @js setVertexZ
---@param positionZ number @(float)  OpenGL Z vertex of this node.
---@return self @(void)
function Node:setPositionZ(positionZ)
end

---
--- Sets ProgramState with retain
---@param programState ccb.ProgramState @(cocos2d::backend::ProgramState*)
---@param needsRetain boolean @(bool)
---@return boolean @(bool)
function Node:setProgramState(programState, needsRetain)
end

---
--- Sets ProgramState with retain
---@param programState ccb.ProgramState @(cocos2d::backend::ProgramState*)
---@return boolean @(bool)
function Node:setProgramState(programState)
end

---@param programType number @(uint32_t)
---@return self @(void)
function Node:setProgramState(programType)
end

---@param programType number @(uint32_t)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function Node:setProgramStateWithRegistry(programType, texture)
end

---
--- Sets the rotation (angle) of the node in degrees.
---
--- 0 is the default rotation angle.
--- Positive values rotate node clockwise, and negative values for anti-clockwise.
---
---@param rotation number @(float)     The rotation of the node in degrees.
---@return self @(void)
function Node:setRotation(rotation)
end

---
--- Sets the rotation (X,Y,Z) in degrees.
--- Useful for 3d rotations.
---
--- @warning The physics body doesn't support this.
---
--- @js NA
---@param rotation vec3_table @(cocos2d::Vec3) The rotation of the node in 3d.
---@return self @(void)
function Node:setRotation3D(rotation)
end

---
--- Set rotation by quaternion. You should make sure the quaternion is normalized.
---
--- @js NA
---@param quat cc.Quaternion @(cocos2d::Quaternion) The rotation in quaternion, note that the quat must be normalized.
---@return self @(void)
function Node:setRotationQuat(quat)
end

---
--- Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
---
--- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew
--- functionality, while the second one uses the real skew function.
---
--- 0 is the default rotation angle.
--- Positive values rotate node clockwise, and negative values for anti-clockwise.
---
---
--- @warning The physics body doesn't support this.
--- @js setRotationX
---@param rotationX number @(float)    The X rotation in degrees which performs a horizontal rotational skew.
---@return self @(void)
function Node:setRotationSkewX(rotationX)
end

---
--- Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
---
--- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew
--- functionality, while the second one uses the real skew function.
---
--- 0 is the default rotation angle.
--- Positive values rotate node clockwise, and negative values for anti-clockwise.
---
---
--- @warning The physics body doesn't support this.
--- @js setRotationY
---@param rotationY number @(float)    The Y rotation in degrees.
---@return self @(void)
function Node:setRotationSkewY(rotationY)
end

---
--- Sets the scale (x,y) of the node.
---
--- It is a scaling factor that multiplies the width and height of the node and its children.
---
---
--- @warning The physics body doesn't support this.
---@param scaleX number @(float)     The scale factor on X axis.
---@param scaleY number @(float)     The scale factor on Y axis.
---@return self @(void)
function Node:setScale(scaleX, scaleY)
end

---
--- Sets the scale (x,y,z) of the node.
---
--- It is a scaling factor that multiplies the width, height and depth of the node and its children.
---
---
--- @warning The physics body doesn't support this.
---@param scale number @(float)     The scale factor for both X and Y axis.
---@return self @(void)
function Node:setScale(scale)
end

---
--- Sets the scale (x) of the node.
---
--- It is a scaling factor that multiplies the width of the node and its children.
---
---
--- @warning The physics body doesn't support this.
---@param scaleX number @(float)   The scale factor on X axis.
---@return self @(void)
function Node:setScaleX(scaleX)
end

---
--- Sets the scale (y) of the node.
---
--- It is a scaling factor that multiplies the height of the node and its children.
---
---
--- @warning The physics body doesn't support this.
---@param scaleY number @(float)   The scale factor on Y axis.
---@return self @(void)
function Node:setScaleY(scaleY)
end

---
--- Changes the scale factor on Z axis of this node
---
--- The Default value is 1.0 if you haven't changed it before.
---
---
--- @warning The physics body doesn't support this.
---@param scaleZ number @(float)   The scale factor on Z axis.
---@return self @(void)
function Node:setScaleZ(scaleZ)
end

---
--- Sets a Scheduler object that is used to schedule all "updates" and timers.
---
--- @warning If you set a new Scheduler, then previously created timersupdate are going to be removed.
---@param scheduler cc.Scheduler @(cocos2d::Scheduler*)     A Scheduler object that is used to schedule all "update" and timers.
---@return self @(void)
function Node:setScheduler(scheduler)
end

---
--- Changes the X skew angle of the node in degrees.
---
--- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew
--- functionality while the second one uses the real skew function.
---
--- This angle describes the shear distortion in the X direction.
--- Thus, it is the angle between the Y coordinate and the left edge of the shape
--- The default skewX angle is 0. Positive values distort the node in a CW direction.
---
---
--- @warning The physics body doesn't support this.
---@param skewX number @(float) The X skew angle of the node in degrees.
---@return self @(void)
function Node:setSkewX(skewX)
end

---
--- Changes the Y skew angle of the node in degrees.
---
--- The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew
--- functionality while the second one uses the real skew function.
---
--- This angle describes the shear distortion in the Y direction.
--- Thus, it is the angle between the X coordinate and the bottom edge of the shape.
--- The default skewY angle is 0. Positive values distort the node in a CCW direction.
---
---
--- @warning The physics body doesn't support this.
---@param skewY number @(float)    The Y skew angle of the node in degrees.
---@return self @(void)
function Node:setSkewY(skewY)
end

---
--- Changes the tag that is used to identify the node easily.
---
--- Please refer to getTag for the sample code.
---
---
--- Please use `setName()` instead.
---@param tag number @(int)   A integer that identifies the node.
---@return self @(void)
function Node:setTag(tag)
end

---
--- Returns a user assigned Object.
---
--- Similar to UserData, but instead of holding a void* it holds an object.
--- The UserObject will be retained once in this method,
--- and the previous UserObject (if existed) will be released.
--- The UserObject will be released in Node's destructor.
---
---@param userObject cc.Ref @(cocos2d::Ref*)    A user assigned Object.
---@return self @(void)
function Node:setUserObject(userObject)
end

---
--- Sets whether the node is visible.
---
--- The default value is true, a node is default to visible.
---
---@param visible boolean @(bool)   true if the node is visible, false if the node is hidden.
---@return self @(void)
function Node:setVisible(visible)
end

---
--- Sorts the children array once before drawing, instead of every time when a child is added or reordered.
--- This approach can improve the performance massively.
--- @note Don't call this manually unless a child added needs to be removed in the same frame.
---@return self @(void)
function Node:sortAllChildren()
end

---
--- Stops and removes an action from the running action list.
---
---@param action cc.Action @(cocos2d::Action*)    The action object to be removed.
---@return self @(void)
function Node:stopAction(action)
end

---
--- Removes an action from the running action list by its tag.
---
---@param tag number @(int)   A tag that indicates the action to be removed.
---@return self @(void)
function Node:stopActionByTag(tag)
end

---
--- Removes all actions from the running action list by its flags.
---
---@param flags number @(unsigned int)   A flag field that removes actions based on bitwise AND.
---@return self @(void)
function Node:stopActionsByFlags(flags)
end

---
--- Stops and removes all actions from the running action list .
---@return self @(void)
function Node:stopAllActions()
end

---
--- Removes all actions from the running action list by its tag.
---
---@param tag number @(int)   A tag that indicates the action to be removed.
---@return self @(void)
function Node:stopAllActionsByTag(tag)
end

---
--- Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".
---@param delta number @(float) In seconds.
---@return self @(void)
function Node:update(delta)
end

---
--- Update node's displayed color with its parent color.
---@param parentColor color3b_table @(cocos2d::Color3B) A Color3B color value.
---@return self @(void)
function Node:updateDisplayedColor(parentColor)
end

---
--- Update the displayed opacity of node with it's parent opacity;
---@param parentOpacity number @(uint8_t) The opacity of parent node.
---@return self @(void)
function Node:updateDisplayedOpacity(parentOpacity)
end

--- !!! ONLY FOR INTERNAL USE
--- Sets the arrival order when this node has a same ZOrder with other children.
---
--- A node which called addChild subsequently will take a larger arrival order,
--- If two children have the same Z order, the child with larger arrival order will be
--- n later.
---
--- @warning This method is used internally for localZOrder sorting, don't change this manually
---
---@return self @(void)
function Node:updateOrderOfArrival()
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function Node:updateProgramStateTexture(texture)
end

---
--- Calls children's updateTransform() method recursively.
---
--- This method is moved from Sprite, so it's no longer specific to Sprite.
--- As the result, you apply SpriteBatchNode's optimization on your customed Node.
--- e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
---@return self @(void)
function Node:updateTransform()
end

---
--- Visits this node's children and draw them recursively.
---
---@param renderer cc.Renderer @(cocos2d::Renderer*) A given renderer.
---@param parentTransform mat4_table @(cocos2d::Mat4) A transform matrix.
---@param parentFlags number @(uint32_t) Renderer flag.
---@return self @(void)
function Node:visit(renderer, parentTransform, parentFlags)
end

---@return self @(void)
function Node:visit()
end

---
--- Allocates and initializes a node.
--- (static)
---@return cc.Node @(cocos2d::Node*) A initialized node which is marked as "autorelease".
function Node:create()
end

---
--- Gets count of nodes those are attached to scene graph.
--- (static)
---@return number @(int)
function Node:getAttachedNodeCount()
end

--- @class Scene
--- @brief Scene is a subclass of Node that is used only as an abstract concept.
---
--- Scene and Node are almost identical with the difference that Scene has its
--- anchor point (by default) at the center of the screen.
---
--- For the moment Scene has no other logic than that, but in future releases it might have
--- additional logic.
---
--- It is a good practice to use a Scene as the parent of all your nodes.
---
--- Scene will create a default camera for you.
---@class cc.Scene:cc.Node
local Scene = {}
cc.Scene = Scene

--- Get the default camera.
--- @js NA
---@return cc.Camera @(cocos2d::Camera*) The default camera of scene.
function Scene:getDefaultCamera()
end

---@param size vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function Scene:initWithSize(size)
end

---@param event cc.EventCustom @(cocos2d::EventCustom*)
---@return self @(void)
function Scene:onProjectionChanged(event)
end

---@return self @(void)
function Scene:setCameraOrderDirty()
end

--- Creates a new Scene object.
---
--- (static)
---@return cc.Scene @(cocos2d::Scene*) An autoreleased Scene object.
function Scene:create()
end

--- Creates a new Scene object with a predefined size.
---
--- @js NA
--- (static)
---@param size vec2_table @(cocos2d::Vec2) The predefined size of scene.
---@return cc.Scene @(cocos2d::Scene*) An autoreleased Scene object.
function Scene:createWithSize(size)
end

---
--- @addtogroup platform
--- @{
---
---
--- @brief By GLView you can operate the frame information of EGL view through some function.
---@class cc.GLView:cc.Ref
local GLView = {}
cc.GLView = GLView

--- Force destroying EGL view, subclass must implement this method.
---
--- @lua endToLua
---@return self @(void)
function GLView:endToLua()
end

---
--- Get list of all active touches.
---
---@return cc.Touch [] @(std::vector<cocos2d::Touch *>) A list of all active touches.
function GLView:getAllTouches()
end

--- Only works on ios platform. Get Content Scale of the Factor.
---@return number @(float)
function GLView:getContentScaleFactor()
end

--- Get design resolution size.
--- Default resolution size is the same as 'getFrameSize'.
---
---@return vec2_table @(const cocos2d::Vec2&) The design resolution size.
function GLView:getDesignResolutionSize()
end

---
--- Get the frame size of EGL view.
--- In general, it returns the screen size since the EGL view is a fullscreen view.
---
---@return vec2_table @(cocos2d::Vec2) The frame size of EGL view.
function GLView:getFrameSize()
end

--- Get zoom factor for frame. This methods are for
--- debugging big resolution (e.g.new ipad) app on desktop.
---
---@return number @(float) The zoom factor for frame.
function GLView:getFrameZoomFactor()
end

--- Returns the current Resolution policy.
---
---@return ResolutionPolicy @(ResolutionPolicy) The current Resolution policy.
function GLView:getResolutionPolicy()
end

--- Get retina factor.
---
---@return number @(int) The retina factor.
function GLView:getRetinaFactor()
end

---
--- Gets safe area rectangle
---@return rect_table @(cocos2d::Rect)
function GLView:getSafeAreaRect()
end

---
--- Get scale factor of the horizontal direction.
---
---@return number @(float) Scale factor of the horizontal direction.
function GLView:getScaleX()
end

---
--- Get scale factor of the vertical direction.
---
---@return number @(float) Scale factor of the vertical direction.
function GLView:getScaleY()
end

---
--- Get the current scissor rectangle.
---
---@return rect_table @(cocos2d::Rect) The current scissor rectangle.
function GLView:getScissorRect()
end

--- Get the view name.
---
---@return string @(std::string_view) The view name.
function GLView:getViewName()
end

---
--- Get the opengl view port rectangle.
---
---@return rect_table @(const cocos2d::Rect&) Return the opengl view port rectangle.
function GLView:getViewPortRect()
end

---
--- Get the visible origin point of opengl viewport.
---
---@return vec2_table @(cocos2d::Vec2) The visible origin point of opengl viewport.
function GLView:getVisibleOrigin()
end

---
--- Get the visible rectangle of opengl viewport.
---
---@return rect_table @(cocos2d::Rect) The visible rectangle of opengl viewport.
function GLView:getVisibleRect()
end

---
--- Get the visible area size of opengl viewport.
---
---@return vec2_table @(cocos2d::Vec2) The visible area size of opengl viewport.
function GLView:getVisibleSize()
end

--- Get whether opengl render system is ready, subclass must implement this method.
---@return boolean @(bool)
function GLView:isOpenGLReady()
end

--- Returns whether or not the view is in Retina Display mode.
---
---@return boolean @(bool) Returns whether or not the view is in Retina Display mode.
function GLView:isRetinaDisplay()
end

---
--- Get whether GL_SCISSOR_TEST is enable.
---
---@return boolean @(bool) Whether GL_SCISSOR_TEST is enable.
function GLView:isScissorEnabled()
end

--- Polls the events.
---@return self @(void)
function GLView:pollEvents()
end

---
--- Renders a Scene with a Renderer
--- This method is called directly by the Director
---@param scene cc.Scene @(cocos2d::Scene*)
---@param renderer cc.Renderer @(cocos2d::Renderer*)
---@return self @(void)
function GLView:renderScene(scene, renderer)
end

--- Only works on ios platform. Set Content Scale of the Factor.
---@param param1 number @(float)
---@return boolean @(bool)
function GLView:setContentScaleFactor(param1)
end

---
--- Hide or Show the mouse cursor if there is one.
---
---@param param1 boolean @(bool)
---@return self @(void)
function GLView:setCursorVisible(param1)
end

--- Set default window icon (implemented for windows and linux).
--- On windows it will use icon from .exe file (if included).
--- On linux it will use default window icon.
---@return self @(void)
function GLView:setDefaultIcon()
end

---
--- Set the design resolution size.
--- [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to
--- height is different from the screen resolution ratio, your game view will be stretched. [2] NO_BORDER Full screen
--- without black border: if the design resolution ratio of width to height is different from the screen resolution
--- ratio, two areas of your game view will be cut. [3] SHOW_ALL  Full screen with black border: if the design
--- resolution ratio of width to height is different from the screen resolution ratio, two black borders will be
--- shown.
---@param width number @(float) Design resolution width.
---@param height number @(float) Design resolution height.
---@param resolutionPolicy ResolutionPolicy @(ResolutionPolicy) The resolution policy desired, you may choose:
---@return self @(void)
function GLView:setDesignResolutionSize(width, height, resolutionPolicy)
end

---
--- Set the frame size of EGL view.
---
---@param width number @(float) The width of the fram size.
---@param height number @(float) The height of the fram size.
---@return self @(void)
function GLView:setFrameSize(width, height)
end

--- Set zoom factor for frame. This methods are for
--- debugging big resolution (e.g.new ipad) app on desktop.
---
---@param param1 number @(float)
---@return self @(void)
function GLView:setFrameZoomFactor(param1)
end

--- Open or close IME keyboard , subclass must implement this method.
---
---@param open boolean @(bool) Open or close IME keyboard.
---@return self @(void)
function GLView:setIMEKeyboardState(open)
end

--- Set window icon (implemented for windows and linux).
--- Best icon (based on size) will be auto selected.
---
---@param filelist string[] @(std::vector<std::string_view>) The array contains icons.
---@return self @(void)
function GLView:setIcon(filelist)
end

--- Set window icon (implemented for windows and linux).
---
---@param filename string @(std::string_view) A path to image file, e.g., "iconscusom.png".
---@return self @(void)
function GLView:setIcon(filename)
end

---
--- Set Scissor rectangle with points.
---
---@param x number @(float) Set the points of x.
---@param y number @(float) Set the points of y.
---@param w number @(float) Set the width of  the view port
---@param h number @(float) Set the Height of the view port.
---@return self @(void)
function GLView:setScissorInPoints(x, y, w, h)
end

--- Set the view name.
---
---@param viewname string @(std::string_view) A string will be set to the view as name.
---@return self @(void)
function GLView:setViewName(viewname)
end

---
--- Set opengl view port rectangle with points.
---
---@param x number @(float) Set the points of x.
---@param y number @(float) Set the points of y.
---@param w number @(float) Set the width of  the view port
---@param h number @(float) Set the Height of the view port.
---@return self @(void)
function GLView:setViewPortInPoints(x, y, w, h)
end

--- Exchanges the front and back buffers, subclass must implement this method.
---@return self @(void)
function GLView:swapBuffers()
end

--- When the window is closed, it will return false if the platforms is Ios or Android.
--- If the platforms is windows or Mac,it will return true.
---
---@return boolean @(bool) In ios and android it will return false,if in windows or Mac it will return true.
function GLView:windowShouldClose()
end

---
---  @brief Class that creates and handles the main Window and manages how
---  and when to execute the Scenes.
---
---  The Director is also responsible for:
---  - initializing the OpenGL context
---  - setting the OpenGL buffer depth (default one is 0-bit)
---  - setting the projection (default one is 3D)
---
---  Since the Director is a singleton, the standard way to use it is by calling:
---  _ Director::getInstance()->methodName();
---@class cc.Director
local Director = {}
cc.Director = Director

---
--- Converts a screen coordinate to an OpenGL coordinate.
--- Useful to convert (multi) touch coordinates to the current layout (portrait or landscape).
---@param point vec2_table @(cocos2d::Vec2)
---@return vec2_table @(cocos2d::Vec2)
function Director:convertToGL(point)
end

---
--- Converts an OpenGL coordinate to a screen coordinate.
--- Useful to convert node points to window points for calls such as glScissor.
---@param point vec2_table @(cocos2d::Vec2)
---@return vec2_table @(cocos2d::Vec2)
function Director:convertToUI(point)
end

--- Draw the scene.
--- This method is called every frame. Don't call it manually.
---@return self @(void)
function Director:drawScene()
end

--- Ends the execution, releases the running scene.
--- @lua endToLua
---@return self @(void)
function Director:endToLua()
end

--- Gets the ActionManager associated with this director.
--- @since v2.0
---@return cc.ActionManager @(cocos2d::ActionManager*)
function Director:getActionManager()
end

--- Gets the FPS value.
---@return number @(float)
function Director:getAnimationInterval()
end

---
--- returns the cocos2d thread id.
--- Useful to know if certain code is already running on the cocos2d thread
---@return std.__thread_id @(const std::thread::id&)
function Director:getAxmolThreadId()
end

--- Returns the Console associated with this director.
--- @since v3.0
--- @js NA
---@return cc.Console @(cocos2d::Console*)
function Director:getConsole()
end

---
--- Gets content scale factor.
--- @see Director::setContentScaleFactor()
---@return number @(float)
function Director:getContentScaleFactor()
end

---@return number @(float)
function Director:getDeltaTime()
end

--- Gets the EventDispatcher associated with this director.
--- @since v3.0
--- @js NA
---@return cc.EventDispatcher @(cocos2d::EventDispatcher*)
function Director:getEventDispatcher()
end

---
--- Gets Frame Rate.
--- @js NA
---@return number @(float)
function Director:getFrameRate()
end

---
--- Gets the top matrix of specified type of matrix stack.
--- @js NA
---@param type cc.MATRIX_STACK_TYPE @(cocos2d::MATRIX_STACK_TYPE)
---@return mat4_table @(const cocos2d::Mat4&)
function Director:getMatrix(type)
end

--- This object will be visited after the main scene is visited.
--- This object MUST implement the "visit" function.
--- Useful to hook a notification object, like Notifications (http:github.commanucorporatCCNotifications)
--- @since v0.99.5
---@return cc.Node @(cocos2d::Node*)
function Director:getNotificationNode()
end

---
--- Get the GLView.
--- @lua NA
---@return cc.GLView @(cocos2d::GLView*)
function Director:getOpenGLView()
end

--- Returns the Renderer associated with this director.
--- @since v3.0
---@return cc.Renderer @(cocos2d::Renderer*)
function Director:getRenderer()
end

--- Gets the current running Scene. Director can only run one Scene at a time.
---@return cc.Scene @(cocos2d::Scene*)
function Director:getRunningScene()
end

---
--- Returns safe area rectangle of the OpenGL view in points.
---@return rect_table @(cocos2d::Rect)
function Director:getSafeAreaRect()
end

--- Gets the Scheduler associated with this director.
--- @since v2.0
---@return cc.Scheduler @(cocos2d::Scheduler*)
function Director:getScheduler()
end

--- Gets the seconds per frame.
---@return number @(float)
function Director:getSecondsPerFrame()
end

---@return cc.TextureCache @(cocos2d::TextureCache*)
function Director:getTextureCache()
end

--- How many frames were called since the director started
---@return number @(unsigned int)
function Director:getTotalFrames()
end

--- Returns visible origin coordinate of the OpenGL view in points.
---@return vec2_table @(cocos2d::Vec2)
function Director:getVisibleOrigin()
end

---
--- Returns visible size of the OpenGL view in points.
--- The value is equal to `Director::getWinSize()` if don't invoke `GLView::setDesignResolutionSize()`.
---@return vec2_table @(cocos2d::Vec2)
function Director:getVisibleSize()
end

--- Returns the size of the OpenGL view in points.
---@return vec2_table @(const cocos2d::Vec2&)
function Director:getWinSize()
end

--- Returns the size of the OpenGL view in pixels.
---@return vec2_table @(cocos2d::Vec2)
function Director:getWinSizeInPixels()
end

---
--- Gets the distance between camera and near clipping frame.
--- It is correct for default camera that near clipping frame is same as the screen.
---@return number @(float)
function Director:getZEye()
end

---@return boolean @(bool)
function Director:init()
end

---
--- returns whether or not node tree children indexer map enabled
---@return boolean @(bool)
function Director:isChildrenIndexerEnabled()
end

--- Whether or not `_nextDeltaTimeZero` is set to 0.
---@return boolean @(bool)
function Director:isNextDeltaTimeZero()
end

--- Whether or not the Director is paused.
---@return boolean @(bool)
function Director:isPaused()
end

--- Whether or not the replaced scene will receive the cleanup message.
--- If the new scene is pushed, then the old scene won't receive the "cleanup" message.
--- If the new scene replaces the old one, the it will receive the "cleanup" message.
--- @since v0.99.0
---@return boolean @(bool)
function Director:isSendCleanupToScene()
end

--- Whether the FPS on the bottom-left corner of the screen is displayed or not.
---@return boolean @(bool)
function Director:isStatsDisplay()
end

---
--- returns whether or not the Director is in a valid state
---@return boolean @(bool)
function Director:isValid()
end

--- Adds an identity matrix to the top of specified type of matrix stack.
--- @js NA
---@param type cc.MATRIX_STACK_TYPE @(cocos2d::MATRIX_STACK_TYPE)
---@return self @(void)
function Director:loadIdentityMatrix(type)
end

---
--- Adds a matrix to the top of specified type of matrix stack.
---
--- @js NA
---@param type cc.MATRIX_STACK_TYPE @(cocos2d::MATRIX_STACK_TYPE) Matrix type.
---@param mat mat4_table @(cocos2d::Mat4) The matrix that to be added.
---@return self @(void)
function Director:loadMatrix(type, mat)
end

--- Invoke main loop with delta time. Then `calculateDeltaTime` can just use the delta time directly.
--- The delta time paseed may include vsync time. See issue #17806
--- @since 3.16
---@param dt number @(float)
---@return self @(void)
function Director:mainLoop(dt)
end

---@return self @(void)
function Director:mainLoop()
end

---
--- Multiplies a matrix to the top of specified type of matrix stack.
---
--- @js NA
---@param type cc.MATRIX_STACK_TYPE @(cocos2d::MATRIX_STACK_TYPE) Matrix type.
---@param mat mat4_table @(cocos2d::Mat4) The matrix that to be multiplied.
---@return self @(void)
function Director:multiplyMatrix(type, mat)
end

--- Pauses the running scene.
--- The running scene will be _drawed_ but all scheduled timers will be paused.
--- While paused, the draw rate will be 4 FPS to reduce CPU consumption.
---@return self @(void)
function Director:pause()
end

--- Pops the top matrix of the specified type of matrix stack.
--- @js NA
---@param type cc.MATRIX_STACK_TYPE @(cocos2d::MATRIX_STACK_TYPE)
---@return self @(void)
function Director:popMatrix(type)
end

---
--- Pops out a scene from the stack.
--- This scene will replace the running one.
--- The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
--- ONLY call it if there is a running scene.
---@return self @(void)
function Director:popScene()
end

---
--- Pops out all scenes from the stack until the root scene in the queue.
--- This scene will replace the running one.
--- Internally it will call `popToSceneStackLevel(1)`.
---@return self @(void)
function Director:popToRootScene()
end

--- Pops out all scenes from the stack until it reaches `level`.
--- If level is 0, it will end the director.
--- If level is 1, it will pop all scenes until it reaches to root scene.
--- If level is <= than the current stack level, it won't do anything.
---@param level number @(int)
---@return self @(void)
function Director:popToSceneStackLevel(level)
end

--- Removes all cocos2d cached data.
--- It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache
--- @since v0.99.3
---@return self @(void)
function Director:purgeCachedData()
end

---
--- Clones a specified type matrix and put it to the top of specified type of matrix stack.
--- @js NA
---@param type cc.MATRIX_STACK_TYPE @(cocos2d::MATRIX_STACK_TYPE)
---@return self @(void)
function Director:pushMatrix(type)
end

---
--- Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
--- The new scene will be executed.
--- Try to avoid big stacks of pushed scenes to reduce memory allocation.
--- ONLY call it if there is a running scene.
---@param scene cc.Scene @(cocos2d::Scene*)
---@return self @(void)
function Director:pushScene(scene)
end

--- Replaces the running scene with a new one. The running scene is terminated.
--- ONLY call it if there is a running scene.
--- @js NA
---@param scene cc.Scene @(cocos2d::Scene*)
---@return self @(void)
function Director:replaceScene(scene)
end

---
--- Clear all types of matrix stack, and add identity matrix to these matrix stacks.
--- @js NA
---@return self @(void)
function Director:resetMatrixStack()
end

---@return self @(void)
function Director:restart()
end

--- Resumes the paused scene.
--- The scheduled timers will be activated again.
--- The "delta time" will be 0 (as if the game wasn't paused).
---@return self @(void)
function Director:resume()
end

---
--- Enters the Director's main loop with the given Scene.
--- Call it to run only your FIRST scene.
--- Don't call it if there is already a running scene.
---
--- It will call pushScene: and then it will call startAnimation
--- @js NA
---@param scene cc.Scene @(cocos2d::Scene*)
---@return self @(void)
function Director:runWithScene(scene)
end

--- Sets the ActionManager associated with this director.
--- @since v2.0
---@param actionManager cc.ActionManager @(cocos2d::ActionManager*)
---@return self @(void)
function Director:setActionManager(actionManager)
end

--- Sets the FPS value. FPS = 1interval.
---@param interval number @(float)
---@return self @(void)
function Director:setAnimationInterval(interval)
end

--- Enable node tree children indexer map, the concept is like database INDEX
--- Notes:
--- If enable is true: will cost more memory to speed up getChildByTag & getChildByName
---@param enable boolean @(bool)
---@return self @(void)
function Director:setChildrenIndexerEnabled(enable)
end

--- Sets clear values for the color buffers,
--- value range of each element is [0.0, 1.0].
--- @js NA
---@param clearColor color4f_table @(cocos2d::Color4F)
---@return self @(void)
function Director:setClearColor(clearColor)
end

--- The size in pixels of the surface. It could be different than the screen size.
--- High-res devices might have a higher surface size than the screen size.
--- Only available when compiled using SDK >= 4.0.
--- @since v0.99.4
---@param scaleFactor number @(float)
---@return self @(void)
function Director:setContentScaleFactor(scaleFactor)
end

--- Sets the default values based on the Configuration info.
---@return self @(void)
function Director:setDefaultValues()
end

--- Sets the EventDispatcher associated with this director.
--- @since v3.0
--- @js NA
---@param dispatcher cc.EventDispatcher @(cocos2d::EventDispatcher*)
---@return self @(void)
function Director:setEventDispatcher(dispatcher)
end

--- Sets the OpenGL default values.
--- It will enable alpha blending, disable depth test.
--- @js NA
---@return self @(void)
function Director:setGLDefaultValues()
end

---
--- Sets the delta time between current frame and next frame is 0.
--- This value will be used in Schedule, and will affect all functions that are using frame delta time, such as
--- Actions. This value will take effect only one time.
---@param nextDeltaTimeZero boolean @(bool)
---@return self @(void)
function Director:setNextDeltaTimeZero(nextDeltaTimeZero)
end

---
--- Sets the notification node.
--- @see Director::getNotificationNode()
---@param node cc.Node @(cocos2d::Node*)
---@return self @(void)
function Director:setNotificationNode(node)
end

---
--- Sets the GLView.
--- @lua NA
---@param openGLView cc.GLView @(cocos2d::GLView*)
---@return self @(void)
function Director:setOpenGLView(openGLView)
end

--- Sets OpenGL projection.
---@param projection cc.Director.Projection @(cocos2d::Director::Projection)
---@return self @(void)
function Director:setProjection(projection)
end

--- Sets the Scheduler associated with this director.
--- @since v2.0
---@param scheduler cc.Scheduler @(cocos2d::Scheduler*)
---@return self @(void)
function Director:setScheduler(scheduler)
end

--- Sets the stats corner displayed on screen if display stats is enabled.
---@param anchor cc.AnchorPreset @(cocos2d::AnchorPreset)
---@return self @(void)
function Director:setStatsAnchor(anchor)
end

--- Sets the stats corner displayed on screen if display stats is enabled.
---@return self @(void)
function Director:setStatsAnchor()
end

--- Display the FPS on the bottom-left corner of the screen.
---@param displayStats boolean @(bool)
---@return self @(void)
function Director:setStatsDisplay(displayStats)
end

--- Sets the glViewport.
---@return self @(void)
function Director:setViewport()
end

--- The main loop is triggered again.
--- Call this function only if [stopAnimation] was called earlier.
--- @warning Don't call this function to start the main loop. To run the main loop call runWithScene.
---@return self @(void)
function Director:startAnimation()
end

--- Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
--- If you don't want to pause your animation call [pause] instead.
---@return self @(void)
function Director:stopAnimation()
end

---
--- Returns a shared instance of the director.
--- @js _getInstance
--- (static)
---@return cc.Director @(cocos2d::Director*)
function Director:getInstance()
end

---
--- @cond
---@class cc.Timer:cc.Ref
local Timer = {}
cc.Timer = Timer

---@return self @(void)
function Timer:cancel()
end

---@return boolean @(bool)
function Timer:isAborted()
end

---@return boolean @(bool)
function Timer:isExhausted()
end

---@return self @(void)
function Timer:setAborted()
end

---@param seconds number @(float)
---@param repeat_ number @(unsigned int)
---@param delay number @(float)
---@return self @(void)
function Timer:setupTimerWithInterval(seconds, repeat_, delay)
end

---@param dt number @(float)
---@return self @(void)
function Timer:trigger(dt)
end

--- triggers the timer
---@param dt number @(float)
---@return self @(void)
function Timer:update(dt)
end

--- @brief Scheduler is responsible for triggering the scheduled callbacks.
--- You should not use system timer for your game logic. Instead, use this class.
---
--- There are 2 different types of callbacks (selectors):
---
--- - update selector: the 'update' selector will be called every frame. You can customize the priority.
--- - custom selector: A custom selector will be called every frame, or with a custom interval of time
---
--- The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update
--- selector'.
---
---@class cc.Scheduler:cc.Ref
local Scheduler = {}
cc.Scheduler = Scheduler

---
--- Gets the time scale of schedule callbacks.
--- @see Scheduler::setTimeScale()
---@return number @(float)
function Scheduler:getTimeScale()
end

--- Calls a function on the cocos2d thread. Useful when you need to call a cocos2d function from another thread.
--- This function is thread safe.
--- @param function The function to be run in cocos2d thread.
--- @since v3.0
--- @js NA
---@param action function @(std::function<void()>) Required callback; nil is rejected.
---@return self @(void)
function Scheduler:performFunctionInCocosThread(action)
end

---
--- Remove all pending functions queued to be performed with Scheduler::performFunctionInCocosThread
--- Functions unscheduled in this manner will not be executed
--- This function is thread safe
--- @since v3.14
--- @js NA
---@return self @(void)
function Scheduler:removeAllPendingActions()
end

--- Modifies the time of all scheduled callbacks.
--- You can use this property to create a 'slow motion' or 'fast forward' effect.
--- Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
--- To create a 'fast forward' effect, use values higher than 1.0.
--- @since v0.8
--- @warning It will affect EVERY scheduled selector action.
---@param timeScale number @(float)
---@return self @(void)
function Scheduler:setTimeScale(timeScale)
end

---
--- @class AsyncTaskPool
--- @brief This class allows to perform background operations without having to manipulate threads.
--- @js NA
---@class cc.AsyncTaskPool
local AsyncTaskPool = {}
cc.AsyncTaskPool = AsyncTaskPool

---
--- Stop tasks.
---
---@param type cc.AsyncTaskPool.TaskType @(cocos2d::AsyncTaskPool::TaskType) Task type you want to stop.
---@return self @(void)
function AsyncTaskPool:stopTasks(type)
end

---
--- Returns the shared instance of the async task pool.
--- (static)
---@return cc.AsyncTaskPool @(cocos2d::AsyncTaskPool*)
function AsyncTaskPool:getInstance()
end

---
--- @brief Base class for Action objects.
---@class cc.Action:cc.Ref
local Action = {}
cc.Action = Action

--- Returns a clone of action.
---
---@return cc.Action @(cocos2d::Action*) A clone action.
function Action:clone()
end

--- Returns a flag field that is used to group the actions easily.
---
---@return number @(unsigned int) A tag.
function Action:getFlags()
end

--- Return a original Target.
---
---@return cc.Node @(cocos2d::Node*) A original Target.
function Action:getOriginalTarget()
end

--- Returns a tag that is used to identify the action easily.
---
---@return number @(int) A tag.
function Action:getTag()
end

--- Return certain target.
---
---@return cc.Node @(cocos2d::Node*) A certain target.
function Action:getTarget()
end

--- Return true if the action has finished.
---
---@return boolean @(bool) Is true if the action has finished.
function Action:isDone()
end

--- Returns a new action that performs the exact reverse of the action.
---
--- @js NA
---@return cc.Action @(cocos2d::Action*) A new action that performs the exact reverse of the action.
function Action:reverse()
end

--- Changes the flag field that is used to group the actions easily.
---
---@param flags number @(unsigned int) Used to group the actions easily.
---@return self @(void)
function Action:setFlags(flags)
end

---
--- Set the original target, since target can be nil.
--- Is the target that were used to run the action. Unless you are doing something complex, like ActionManager, you
--- should NOT call this method. The target is 'assigned', it is not 'retained'.
--- @since v0.8.2
---
---@param originalTarget cc.Node @(cocos2d::Node*) Is 'assigned', it is not 'retained'.
---@return self @(void)
function Action:setOriginalTarget(originalTarget)
end

--- Changes the tag that is used to identify the action easily.
---
---@param tag number @(int) Used to identify the action easily.
---@return self @(void)
function Action:setTag(tag)
end

--- The action will modify the target properties.
---
---@param target cc.Node @(cocos2d::Node*) A certain target.
---@return self @(void)
function Action:setTarget(target)
end

--- Called before the action start. It will also set the target.
---
---@param target cc.Node @(cocos2d::Node*) A certain target.
---@return self @(void)
function Action:startWithTarget(target)
end

--- Called every frame with it's delta time, dt in seconds. DON'T override unless you know what you are doing.
---
---@param dt number @(float) In seconds.
---@return self @(void)
function Action:step(dt)
end

---
--- Called after the action has finished. It will set the 'target' to nil.
--- IMPORTANT: You should never call "Action::stop()" manually. Instead, use: "target->stopAction(action);".
---@return self @(void)
function Action:stop()
end

---
--- Called once per frame. time a value between 0 and 1.
---
--- For example:
--- - 0 Means that the action just started.
--- - 0.5 Means that the action is in the middle.
--- - 1 Means that the action is over.
---
---@param time number @(float) A value between 0 and 1.
---@return self @(void)
function Action:update(time)
end

--- @class FiniteTimeAction
--- @brief
--- Base class actions that do have a finite time duration.
--- Possible actions:
--- - An action with a duration of 0 seconds.
--- - An action with a duration of 35.5 seconds.
--- Infinite time actions are valid.
---@class cc.FiniteTimeAction:cc.Action
local FiniteTimeAction = {}
cc.FiniteTimeAction = FiniteTimeAction

--- Get duration in seconds of the action.
---
---@return number @(float) The duration in seconds of the action.
function FiniteTimeAction:getDuration()
end

--- Set duration in seconds of the action.
---
---@param duration number @(float) In seconds of the action.
---@return self @(void)
function FiniteTimeAction:setDuration(duration)
end

--- @class Speed
--- @brief Changes the speed of an action, making it take longer (speed>1)
--- or shorter (speed<1) time.
--- Useful to simulate 'slow motion' or 'fast forward' effect.
--- @warning This action can't be Sequenceable because it is not an IntervalAction.
---@class cc.Speed:cc.Action
local Speed = {}
cc.Speed = Speed

--- Return the interior action.
---
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The interior action.
function Speed:getInnerAction()
end

--- Return the speed.
---
---@return number @(float) The action speed.
function Speed:getSpeed()
end

--- Initializes the action.
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param speed number @(float)
---@return boolean @(bool)
function Speed:initWithAction(action, speed)
end

--- Replace the interior action.
---
---@param action cc.ActionInterval @(cocos2d::ActionInterval*) The new action, it will replace the running action.
---@return self @(void)
function Speed:setInnerAction(action)
end

--- Alter the speed of the inner function in runtime.
---
---@param speed number @(float) Alter the speed of the inner function in runtime.
---@return self @(void)
function Speed:setSpeed(speed)
end

--- Create the action and set the speed.
---
--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*) An action.
---@param speed number @(float) The action speed.
---@return cc.Speed @(cocos2d::Speed*)
function Speed:create(action, speed)
end

--- @class Follow
--- @brief Follow is an action that "follows" a node.
--- Eg:
--- @code
--- layer->runAction(Follow::create(hero));
--- @endcode
--- Instead of using Camera as a "follower", use this action instead.
--- @since v0.99.2
---@class cc.Follow:cc.Action
local Follow = {}
cc.Follow = Follow

---
--- Initializes the action with a set boundary or with no boundary.
---
--- with no boundary.
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@param rect rect_table @(cocos2d::Rect)  The boundary. If \p rect is equal to Rect::ZERO, it'll work
---@return boolean @(bool)
function Follow:initWithTarget(followedNode, rect)
end

---
--- Initializes the action with a set boundary or with no boundary.
---
--- with no boundary.
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@return boolean @(bool)
function Follow:initWithTarget(followedNode)
end

---
--- Initializes the action with a set boundary or with no boundary with offsets.
---
--- with no boundary.
--- node  is to be followed.It can be positive,negative or zero.If
--- set to zero the node will be horizontally centered followed.
--- node is to be followed.It can be positive,negative or zero.
--- If set to zero the node will be vertically centered followed.
--- If both xOffset and yOffset are set to zero,then the node will be horizontally and vertically centered
--- followed.
---
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@param xOffset number @(float) The horizontal offset from the center of the screen from which the
---@param yOffset number @(float) The vertical offset from the center of the screen from which the
---@param rect rect_table @(cocos2d::Rect)  The boundary. If \p rect is equal to Rect::ZERO, it'll work
---@return boolean @(bool)
function Follow:initWithTargetAndOffset(followedNode, xOffset, yOffset, rect)
end

---
--- Initializes the action with a set boundary or with no boundary with offsets.
---
--- with no boundary.
--- node  is to be followed.It can be positive,negative or zero.If
--- set to zero the node will be horizontally centered followed.
--- node is to be followed.It can be positive,negative or zero.
--- If set to zero the node will be vertically centered followed.
--- If both xOffset and yOffset are set to zero,then the node will be horizontally and vertically centered
--- followed.
---
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@param xOffset number @(float) The horizontal offset from the center of the screen from which the
---@param yOffset number @(float) The vertical offset from the center of the screen from which the
---@return boolean @(bool)
function Follow:initWithTargetAndOffset(followedNode, xOffset, yOffset)
end

--- Return boundarySet.
---
---@return boolean @(bool) Return boundarySet.
function Follow:isBoundarySet()
end

--- Alter behavior - turn onoff boundary.
---
---@param value boolean @(bool) Turn onoff boundary.
---@return self @(void)
function Follow:setBoundarySet(value)
end

---
--- Creates the action with a set boundary or with no boundary.
---
--- with no boundary.
--- (static)
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@param rect rect_table @(cocos2d::Rect)  The boundary. If \p rect is equal to Rect::ZERO, it'll work
---@return cc.Follow @(cocos2d::Follow*)
function Follow:create(followedNode, rect)
end

---
--- Creates the action with a set boundary or with no boundary.
---
--- with no boundary.
--- (static)
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@return cc.Follow @(cocos2d::Follow*)
function Follow:create(followedNode)
end

---
--- Creates the action with a set boundary or with no boundary with offsets.
---
--- with no boundary.
--- node  is to be followed.It can be positive,negative or zero.If
--- set to zero the node will be horizontally centered followed.
--- @param yOffset The vertical offset from the center of the screen from which the
--- node is to be followed.It can be positive,negative or zero.
--- If set to zero the node will be vertically centered followed.
--- If both xOffset and yOffset are set to zero,then the node will be horizontally and vertically centered
--- followed.
--- (static)
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@param xOffset number @(float) The horizontal offset from the center of the screen from which the
---@param yOffset number @(float)
---@param rect rect_table @(cocos2d::Rect)  The boundary. If \p rect is equal to Rect::ZERO, it'll work
---@return cc.Follow @(cocos2d::Follow*)
function Follow:createWithOffset(followedNode, xOffset, yOffset, rect)
end

---
--- Creates the action with a set boundary or with no boundary with offsets.
---
--- with no boundary.
--- node  is to be followed.It can be positive,negative or zero.If
--- set to zero the node will be horizontally centered followed.
--- @param yOffset The vertical offset from the center of the screen from which the
--- node is to be followed.It can be positive,negative or zero.
--- If set to zero the node will be vertically centered followed.
--- If both xOffset and yOffset are set to zero,then the node will be horizontally and vertically centered
--- followed.
--- (static)
---@param followedNode cc.Node @(cocos2d::Node*)  The node to be followed.
---@param xOffset number @(float) The horizontal offset from the center of the screen from which the
---@param yOffset number @(float)
---@return cc.Follow @(cocos2d::Follow*)
function Follow:createWithOffset(followedNode, xOffset, yOffset)
end

--- The Image class for loading all images supported by axmol .
---@class cc.Image:cc.Ref
local Image = {}
cc.Image = Image

---@return number @(int)
function Image:getBitPerPixel()
end

---@return string @(std::string)
function Image:getFilePath()
end

---@return cc.Image.Format @(cocos2d::Image::Format)
function Image:getFileType()
end

---@return number @(int)
function Image:getHeight()
end

---@return number @(int)
function Image:getNumberOfMipmaps()
end

---@return ccb.PixelFormat @(cocos2d::backend::PixelFormat)
function Image:getPixelFormat()
end

---@return number @(int)
function Image:getWidth()
end

---@return boolean @(bool)
function Image:hasAlpha()
end

---@return boolean @(bool)
function Image:hasPremultipliedAlpha()
end

---
--- @brief Load the image from the specified path.
--- @param path   the absolute file path.
--- @return true if loaded correctly.
---@param path string @(std::string_view)
---@return boolean @(bool)
function Image:initWithImageFile(path)
end

---@return boolean @(bool)
function Image:isCompressed()
end

---@return self @(void)
function Image:premultiplyAlpha()
end

---@return self @(void)
function Image:reversePremultipliedAlpha()
end

---
--- @brief    Save Image data to the specified file, with specified format.
--- @param    filePath        the file's absolute path, including file suffix.
--- @param    isToRGB        whether the image is saved as RGB format.
---@param filename string @(std::string_view)
---@param isToRGB boolean @(bool)
---@return boolean @(bool)
function Image:saveToFile(filename, isToRGB)
end

---
--- @brief    Save Image data to the specified file, with specified format.
--- @param    filePath        the file's absolute path, including file suffix.
--- @param    isToRGB        whether the image is saved as RGB format.
---@param filename string @(std::string_view)
---@return boolean @(bool)
function Image:saveToFile(filename)
end

--- (static)
---@param target number @(uint32_t)
---@return boolean @(bool)
function Image:isCompressedImageHavePMA(target)
end

--- The new APIs to treats (or not) compressed image files as if they have alpha premultiplied.
---
--- By default, ETC1 + ETC1_ALPHA is enabled, because we do PMA at shader etc1.frag
--- !!!IMPORTANT:
--- The spine-runtimes official always regard texture has PMA, so you needs
--- do compressed images PMA at texture convert tools or GPU fragment shader, such as
--- positionTexture.frag, positionTextureColor.frag and others which have texture sampler,
--- otherwise, the spine animations can't be render properly
--- (static)
---@param targets number @(uint32_t)
---@param havePMA boolean @(bool)
---@return self @(void)
function Image:setCompressedImagesHavePMA(targets, havePMA)
end

---
--- Enables or disables premultiplied alpha for PNG files.
---
--- @param enabled (default: true)
--- (static)
---@param enabled boolean @(bool)
---@return self @(void)
function Image:setPNGPremultipliedAlphaEnabled(enabled)
end

--- @class SpriteFrame
--- @brief A SpriteFrame has:
---     - texture: A Texture2D that will be used by the Sprite
---     - rectangle: A rectangle of the texture
---
---
---  You can modify the frame of a Sprite by doing:
---
---  @code
---     SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
---     sprite->setSpriteFrame(frame);
---  @endcode
---@class cc.SpriteFrame:cc.Ref
local SpriteFrame = {}
cc.SpriteFrame = SpriteFrame

---@return cc.SpriteFrame @(cocos2d::SpriteFrame*)
function SpriteFrame:clone()
end

--- Get anchor point of the frame.
---
---@return vec2_table @(const cocos2d::Vec2&) The anchor point of the sprite frame.
function SpriteFrame:getAnchorPoint()
end

--- Get center rect of the frame.
---
--- Useful to create 9-slice sprites
---
---@return rect_table @(const cocos2d::Rect&) The center rect of the sprite frame in points
function SpriteFrame:getCenterRect()
end

--- Get offset of the frame.
---
---@return vec2_table @(const cocos2d::Vec2&) The offset of the sprite frame.
function SpriteFrame:getOffset()
end

--- Get offset of the frame.
---
---@return vec2_table @(const cocos2d::Vec2&) The offset of the sprite frame, in pixels.
function SpriteFrame:getOffsetInPixels()
end

--- Get original size of the trimmed image.
---
---@return vec2_table @(const cocos2d::Vec2&) The original size of the trimmed image.
function SpriteFrame:getOriginalSize()
end

--- Get original size of the trimmed image.
---
---@return vec2_table @(const cocos2d::Vec2&) The original size of the trimmed image, in pixels.
function SpriteFrame:getOriginalSizeInPixels()
end

--- Get rect of the frame.
---
---@return rect_table @(const cocos2d::Rect&) The rect of the sprite frame.
function SpriteFrame:getRect()
end

--- Get rect of the sprite frame.
---
---@return rect_table @(const cocos2d::Rect&) The rect of the sprite frame, in pixels.
function SpriteFrame:getRectInPixels()
end

--- Get texture of the frame.
---
---@return cc.Texture2D @(cocos2d::Texture2D*) The texture of the sprite frame.
function SpriteFrame:getTexture()
end

--- Check if anchor point is defined for the frame.
---
---@return boolean @(bool) true if anchor point is available.
function SpriteFrame:hasAnchorPoint()
end

--- hasCenterRect
--- @return Whether or not it has a centerRect
---@return boolean @(bool)
function SpriteFrame:hasCenterRect()
end

--- Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
--- The originalSize is the size in points of the frame before being trimmed.
---@param pobTexture cc.Texture2D @(cocos2d::Texture2D*)
---@param rect rect_table @(cocos2d::Rect)
---@param rotated boolean @(bool)
---@param offset vec2_table @(cocos2d::Vec2)
---@param originalSize vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function SpriteFrame:initWithTexture(pobTexture, rect, rotated, offset, originalSize)
end

--- Initializes a SpriteFrame with a texture, rect in points.
--- It is assumed that the frame was not trimmed.
---@param pobTexture cc.Texture2D @(cocos2d::Texture2D*)
---@param rect rect_table @(cocos2d::Rect)
---@return boolean @(bool)
function SpriteFrame:initWithTexture(pobTexture, rect)
end

--- Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
--- The originalSize is the size in pixels of the frame before being trimmed.
---
--- @since v1.1
---@param filename string @(std::string_view)
---@param rect rect_table @(cocos2d::Rect)
---@param rotated boolean @(bool)
---@param offset vec2_table @(cocos2d::Vec2)
---@param originalSize vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function SpriteFrame:initWithTextureFilename(filename, rect, rotated, offset, originalSize)
end

--- Initializes a SpriteFrame with a texture filename, rect in points;
--- It is assumed that the frame was not trimmed.
---@param filename string @(std::string_view)
---@param rect rect_table @(cocos2d::Rect)
---@return boolean @(bool)
function SpriteFrame:initWithTextureFilename(filename, rect)
end

--- Is the sprite frame rotated or not.
---
---@return boolean @(bool) Is rotated if true.
function SpriteFrame:isRotated()
end

--- Set anchor point of the frame.
---
---@param anchorPoint vec2_table @(cocos2d::Vec2) The anchor point of the sprite frame.
---@return self @(void)
function SpriteFrame:setAnchorPoint(anchorPoint)
end

---
--- setCenterRect
---
--- Useful to implement "9 sliced" sprites.
--- The sprite will be sliced into a 3 x 3 grid. The four corners of this grid are applied without
--- performing any scaling. The upper- and lower-middle parts are scaled horizontally, and the left- and right-middle
--- parts are scaled vertically. The center is scaled in both directions. Important: The scaling is based the
--- Sprite's trimmed size.
---
--- Limitations: Does not work when the sprite is part of `SpriteBatchNode`.
---@param centerRect rect_table @(cocos2d::Rect) the Rect in points
---@return self @(void)
function SpriteFrame:setCenterRectInPixels(centerRect)
end

--- Set offset of the frame.
---
---@param offsets vec2_table @(cocos2d::Vec2) The offset of the sprite frame.
---@return self @(void)
function SpriteFrame:setOffset(offsets)
end

--- Set offset of the frame.
---
---@param offsetInPixels vec2_table @(cocos2d::Vec2) The offset of the sprite frame, in pixels.
---@return self @(void)
function SpriteFrame:setOffsetInPixels(offsetInPixels)
end

--- Set original size of the trimmed image.
---
---@param sizeInPixels vec2_table @(cocos2d::Vec2) The original size of the trimmed image.
---@return self @(void)
function SpriteFrame:setOriginalSize(sizeInPixels)
end

--- Set original size of the trimmed image.
---
---@param sizeInPixels vec2_table @(cocos2d::Vec2) The original size of the trimmed image, in pixels.
---@return self @(void)
function SpriteFrame:setOriginalSizeInPixels(sizeInPixels)
end

--- Set rect of the frame.
---
---@param rect rect_table @(cocos2d::Rect) The rect of the sprite.
---@return self @(void)
function SpriteFrame:setRect(rect)
end

--- Set rect of the sprite frame.
---
---@param rectInPixels rect_table @(cocos2d::Rect) The rect of the sprite frame, in pixels.
---@return self @(void)
function SpriteFrame:setRectInPixels(rectInPixels)
end

--- Set rotated of the sprite frame.
---
---@param rotated boolean @(bool) Rotated the sprite frame if true.
---@return self @(void)
function SpriteFrame:setRotated(rotated)
end

--- Set texture of the frame, the texture is retained.
---
---@param pobTexture cc.Texture2D @(cocos2d::Texture2D*) The texture of the sprite frame.
---@return self @(void)
function SpriteFrame:setTexture(pobTexture)
end

--- Create a SpriteFrame with a texture filename, rect, rotated, offset and originalSize in pixels.
--- The originalSize is the size in pixels of the frame before being trimmed.
---
--- (static)
---@param filename string @(std::string_view) Texture filename
---@param rect rect_table @(cocos2d::Rect) A specified rect.
---@param rotated boolean @(bool) Is rotated if true.
---@param offset vec2_table @(cocos2d::Vec2) A specified offset.
---@param originalSize vec2_table @(cocos2d::Vec2) A specified original size.
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*) An autoreleased SpriteFrame object.
function SpriteFrame:create(filename, rect, rotated, offset, originalSize)
end

--- Create a SpriteFrame with a texture filename, rect in points.
--- It is assumed that the frame was not trimmed.
---
--- (static)
---@param filename string @(std::string_view) Texture file name.
---@param rect rect_table @(cocos2d::Rect) A specified rect.
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*) An autoreleased SpriteFrame object.
function SpriteFrame:create(filename, rect)
end

--- Create a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
--- The originalSize is the size in points of the frame before being trimmed.
--- (static)
---@param pobTexture cc.Texture2D @(cocos2d::Texture2D*) The texture pointer.
---@param rect rect_table @(cocos2d::Rect) A specified rect.
---@param rotated boolean @(bool) Is rotated if true.
---@param offset vec2_table @(cocos2d::Vec2) A specified offset.
---@param originalSize vec2_table @(cocos2d::Vec2) A specified original size.
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*) An autoreleased SpriteFrame object.
function SpriteFrame:createWithTexture(pobTexture, rect, rotated, offset, originalSize)
end

--- Create a SpriteFrame with a texture, rect in points.
--- It is assumed that the frame was not trimmed.
--- (static)
---@param pobTexture cc.Texture2D @(cocos2d::Texture2D*) The texture pointer.
---@param rect rect_table @(cocos2d::Rect) A specified rect.
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*) An autoreleased SpriteFrame object.
function SpriteFrame:createWithTexture(pobTexture, rect)
end

--- @class AnimationFrame
---
--- A frame of the animation. It contains information like:
--- - sprite frame name.
--- - # of delay units.
--- - offset
---
---  @since v2.0
---@class cc.AnimationFrame:cc.Ref
local AnimationFrame = {}
cc.AnimationFrame = AnimationFrame

---@return cc.AnimationFrame @(cocos2d::AnimationFrame*)
function AnimationFrame:clone()
end

--- Gets the units of time the frame takes.
---
---@return number @(float) The units of time the frame takes.
function AnimationFrame:getDelayUnits()
end

--- Return a SpriteFrameName to be used.
---
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*) a SpriteFrameName to be used.
function AnimationFrame:getSpriteFrame()
end

---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap&)
function AnimationFrame:getUserInfo()
end

--- @brief Gets user information
--- A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this
--- dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast.
---
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(const cocos2d::ValueMap&) A dictionary as UserInfo
function AnimationFrame:getUserInfo()
end

--- initializes the animation frame with a spriteframe, number of delay units and a notification user info
---@param spriteFrame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@param delayUnits number @(float)
---@param userInfo tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@return boolean @(bool)
function AnimationFrame:initWithSpriteFrame(spriteFrame, delayUnits, userInfo)
end

--- Sets the units of time the frame takes.
---
---@param delayUnits number @(float) The units of time the frame takes.
---@return self @(void)
function AnimationFrame:setDelayUnits(delayUnits)
end

--- Set the SpriteFrame.
---
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*) A SpriteFrame will be used.
---@return self @(void)
function AnimationFrame:setSpriteFrame(frame)
end

--- Sets user information.
---@param userInfo tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) A dictionary as UserInfo.
---@return self @(void)
function AnimationFrame:setUserInfo(userInfo)
end

---
--- Creates the animation frame with a spriteframe, number of delay units and a notification user info.
---
--- @since 3.0
--- (static)
---@param spriteFrame cc.SpriteFrame @(cocos2d::SpriteFrame*) The animation frame with a spriteframe.
---@param delayUnits number @(float) Number of delay units.
---@param userInfo tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) A notification user info.
---@return cc.AnimationFrame @(cocos2d::AnimationFrame*)
function AnimationFrame:create(spriteFrame, delayUnits, userInfo)
end

--- @class Animation
--- A Animation object is used to perform animations on the Sprite objects.
--- The Animation object contains AnimationFrame objects, and a possible delay between the frames.
--- You can animate a Animation object by using the Animate action. Example:
--- @code
--- sprite->runAction(Animate::create(animation));
--- @endcode
---@class cc.Animation:cc.Ref
local Animation = {}
cc.Animation = Animation

--- Adds a SpriteFrame to a Animation.
---
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*) The frame will be added with one "delay unit".
---@return self @(void)
function Animation:addSpriteFrame(frame)
end

--- Adds a frame with an image filename. Internally it will create a SpriteFrame and it will add it.
--- The frame will be added with one "delay unit".
--- Added to facilitate the migration from v0.8 to v0.9.
---@param filename string @(std::string_view) The path of SpriteFrame.
---@return self @(void)
function Animation:addSpriteFrameWithFile(filename)
end

--- Adds a frame with a texture and a rect. Internally it will create a SpriteFrame and it will add it.
--- The frame will be added with one "delay unit".
--- Added to facilitate the migration from v0.8 to v0.9.
---@param pobTexture cc.Texture2D @(cocos2d::Texture2D*) A frame with a texture.
---@param rect rect_table @(cocos2d::Rect) The Texture of rect.
---@return self @(void)
function Animation:addSpriteFrameWithTexture(pobTexture, rect)
end

---@return cc.Animation @(cocos2d::Animation*)
function Animation:clone()
end

--- Gets the delay in seconds of the "delay unit".
---
---@return number @(float) The delay in seconds of the "delay unit".
function Animation:getDelayPerUnit()
end

--- Gets the duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit.
---
---@return number @(float) Result of totalDelayUnits * delayPerUnit.
function Animation:getDuration()
end

--- Gets the array of AnimationFrames.
---
---@return cc.AnimationFrame [] @(const cocos2d::Vector<cocos2d::AnimationFrame *>&) The array of AnimationFrames.
function Animation:getFrames()
end

--- Gets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one
--- time, ...
---
---@return number @(unsigned int) The times the animation is going to loop.
function Animation:getLoops()
end

--- Checks whether to restore the original frame when animation finishes.
---
---@return boolean @(bool) Restore the original frame when animation finishes.
function Animation:getRestoreOriginalFrame()
end

--- Gets the total Delay units of the Animation.
---
---@return number @(float) The total Delay units of the Animation.
function Animation:getTotalDelayUnits()
end

--- Initializes a Animation.
---@return boolean @(bool)
function Animation:init()
end

--- Initializes a Animation with AnimationFrame.
--- @since v2.0
---@param arrayOfAnimationFrameNames cc.AnimationFrame [] @(cocos2d::Vector<cocos2d::AnimationFrame *>)
---@param delayPerUnit number @(float)
---@param loops number @(unsigned int)
---@return boolean @(bool)
function Animation:initWithAnimationFrames(arrayOfAnimationFrameNames, delayPerUnit, loops)
end

--- Initializes a Animation with frames and a delay between frames.
--- @since v0.99.5
---@param arrayOfSpriteFrameNames cc.SpriteFrame [] @(cocos2d::Vector<cocos2d::SpriteFrame *>)
---@param delay number @(float)
---@param loops number @(unsigned int)
---@return boolean @(bool)
function Animation:initWithSpriteFrames(arrayOfSpriteFrameNames, delay, loops)
end

--- Initializes a Animation with frames and a delay between frames.
--- @since v0.99.5
---@param arrayOfSpriteFrameNames cc.SpriteFrame [] @(cocos2d::Vector<cocos2d::SpriteFrame *>)
---@param delay number @(float)
---@return boolean @(bool)
function Animation:initWithSpriteFrames(arrayOfSpriteFrameNames, delay)
end

--- Initializes a Animation with frames and a delay between frames.
--- @since v0.99.5
---@param arrayOfSpriteFrameNames cc.SpriteFrame [] @(cocos2d::Vector<cocos2d::SpriteFrame *>)
---@return boolean @(bool)
function Animation:initWithSpriteFrames(arrayOfSpriteFrameNames)
end

--- Sets the delay in seconds of the "delay unit".
---
---@param delayPerUnit number @(float) The delay in seconds of the "delay unit".
---@return self @(void)
function Animation:setDelayPerUnit(delayPerUnit)
end

--- Sets the array of AnimationFrames.
---
---@param frames cc.AnimationFrame [] @(cocos2d::Vector<cocos2d::AnimationFrame *>) The array of AnimationFrames.
---@return self @(void)
function Animation:setFrames(frames)
end

--- Sets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one
--- time, ...
---
---@param loops number @(unsigned int) The times the animation is going to loop.
---@return self @(void)
function Animation:setLoops(loops)
end

--- Sets whether to restore the original frame when animation finishes.
---
---@param restoreOriginalFrame boolean @(bool) Whether to restore the original frame when animation finishes.
---@return self @(void)
function Animation:setRestoreOriginalFrame(restoreOriginalFrame)
end

--- (static)
---@param arrayOfAnimationFrameNames cc.AnimationFrame [] @(cocos2d::Vector<cocos2d::AnimationFrame *>)
---@param delayPerUnit number @(float)
---@param loops number @(unsigned int)
---@return cc.Animation @(cocos2d::Animation*)
function Animation:create(arrayOfAnimationFrameNames, delayPerUnit, loops)
end

--- (static)
---@param arrayOfAnimationFrameNames cc.AnimationFrame [] @(cocos2d::Vector<cocos2d::AnimationFrame *>)
---@param delayPerUnit number @(float)
---@return cc.Animation @(cocos2d::Animation*)
function Animation:create(arrayOfAnimationFrameNames, delayPerUnit)
end

--- Creates an animation.
--- @since v0.99.5
--- (static)
---@return cc.Animation @(cocos2d::Animation*)
function Animation:create()
end

--- (static)
---@param arrayOfSpriteFrameNames cc.SpriteFrame [] @(cocos2d::Vector<cocos2d::SpriteFrame *>)
---@param delay number @(float)
---@param loops number @(unsigned int)
---@return cc.Animation @(cocos2d::Animation*)
function Animation:createWithSpriteFrames(arrayOfSpriteFrameNames, delay, loops)
end

--- (static)
---@param arrayOfSpriteFrameNames cc.SpriteFrame [] @(cocos2d::Vector<cocos2d::SpriteFrame *>)
---@param delay number @(float)
---@return cc.Animation @(cocos2d::Animation*)
function Animation:createWithSpriteFrames(arrayOfSpriteFrameNames, delay)
end

--- (static)
---@param arrayOfSpriteFrameNames cc.SpriteFrame [] @(cocos2d::Vector<cocos2d::SpriteFrame *>)
---@return cc.Animation @(cocos2d::Animation*)
function Animation:createWithSpriteFrames(arrayOfSpriteFrameNames)
end

--- @class ActionInterval
--- @brief An interval action is an action that takes place within a certain period of time.
--- It has an start time, and a finish time. The finish time is the parameter
--- duration plus the start time.
---
--- These ActionInterval actions have some interesting properties, like:
--- - They can run normally (default)
--- - They can run reversed with the reverse method
--- - They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.
---
--- For example, you can simulate a Ping Pong effect running the action normally and
--- then running it again in Reverse mode.
---
--- Example:
---
--- @code
--- auto action = MoveBy::create(1.0f, Vec2::ONE);
--- auto pingPongAction = Sequence::create(action, action->reverse(), nullptr);
--- @endcode
---@class cc.ActionInterval:cc.FiniteTimeAction
local ActionInterval = {}
cc.ActionInterval = ActionInterval

--- Gets the amplitude rate, extension in GridAction
---
---@return number @(float)  The amplitude rate.
function ActionInterval:getAmplitudeRate()
end

--- How many seconds had elapsed since the actions started to run.
---
---@return number @(float) The seconds had elapsed since the actions started to run.
function ActionInterval:getElapsed()
end

--- initializes the action
---@param d number @(float)
---@return boolean @(bool)
function ActionInterval:initWithDuration(d)
end

--- Sets the amplitude rate, extension in GridAction
---
---@param amp number @(float)   The amplitude rate.
---@return self @(void)
function ActionInterval:setAmplitudeRate(amp)
end

--- @class Sequence
--- @brief Runs actions sequentially, one after another.
---@class cc.Sequence:cc.ActionInterval
local Sequence = {}
cc.Sequence = Sequence

---@param arrayOfActions cc.FiniteTimeAction [] @(cocos2d::Vector<cocos2d::FiniteTimeAction *>)
---@return boolean @(bool)
function Sequence:init(arrayOfActions)
end

--- initializes the action
---@param pActionOne cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*)
---@param pActionTwo cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*)
---@return boolean @(bool)
function Sequence:initWithTwoActions(pActionOne, pActionTwo)
end

--- @class Repeat
--- @brief Repeats an action a number of times.
--- To repeat an action forever use the RepeatForever action.
---@class cc.Repeat:cc.ActionInterval
local Repeat = {}
cc.Repeat = Repeat

--- Gets the inner action.
---
---@return cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*) The inner action.
function Repeat:getInnerAction()
end

--- initializes a Repeat action. Times is an unsigned integer between 1 and pow(2,30)
---@param pAction cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*)
---@param times number @(unsigned int)
---@return boolean @(bool)
function Repeat:initWithAction(pAction, times)
end

--- Sets the inner action.
---
---@param action cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*) The inner action.
---@return self @(void)
function Repeat:setInnerAction(action)
end

--- Creates a Repeat action. Times is an unsigned integer between 1 and pow(2,30).
---
--- (static)
---@param action cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*) The action needs to repeat.
---@param times number @(unsigned int) The repeat times.
---@return cc.Repeat @(cocos2d::Repeat*) An autoreleased Repeat object.
function Repeat:create(action, times)
end

--- @class RepeatForever
--- @brief Repeats an action for ever.
---  To repeat the an action for a limited number of times use the Repeat action.
--- @warning This action can't be Sequenceable because it is not an IntervalAction.
---@class cc.RepeatForever:cc.ActionInterval
local RepeatForever = {}
cc.RepeatForever = RepeatForever

--- Gets the inner action.
---
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The inner action.
function RepeatForever:getInnerAction()
end

--- initializes the action
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return boolean @(bool)
function RepeatForever:initWithAction(action)
end

--- Sets the inner action.
---
---@param action cc.ActionInterval @(cocos2d::ActionInterval*) The inner action.
---@return self @(void)
function RepeatForever:setInnerAction(action)
end

--- Creates the action.
---
--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*) The action need to repeat forever.
---@return cc.RepeatForever @(cocos2d::RepeatForever*) An autoreleased RepeatForever object.
function RepeatForever:create(action)
end

--- @class Spawn
--- @brief Spawn a new action immediately
---@class cc.Spawn:cc.ActionInterval
local Spawn = {}
cc.Spawn = Spawn

---@param arrayOfActions cc.FiniteTimeAction [] @(cocos2d::Vector<cocos2d::FiniteTimeAction *>)
---@return boolean @(bool)
function Spawn:init(arrayOfActions)
end

--- initializes the Spawn action with the 2 actions to spawn
---@param action1 cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*)
---@param action2 cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*)
---@return boolean @(bool)
function Spawn:initWithTwoActions(action1, action2)
end

--- @class RotateTo
--- @brief Rotates a Node object to a certain angle by modifying it's rotation attribute.
---  The direction will be decided by the shortest angle.
---@class cc.RotateTo:cc.ActionInterval
local RotateTo = {}
cc.RotateTo = RotateTo

---
--- initializes the action
---@param duration number @(float) in seconds
---@param dstAngleX number @(float) in degreesCW
---@param dstAngleY number @(float) in degreesCW
---@return boolean @(bool)
function RotateTo:initWithDuration(duration, dstAngleX, dstAngleY)
end

---
--- initializes the action
---@param duration number @(float) in seconds
---@param dstAngle3D vec3_table @(cocos2d::Vec3)
---@return boolean @(bool)
function RotateTo:initWithDuration(duration, dstAngle3D)
end

---
--- Creates the action with separate rotation angles.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param dstAngleX number @(float) In degreesCW.
---@param dstAngleY number @(float) In degreesCW.
---@return cc.RotateTo @(cocos2d::RotateTo*) An autoreleased RotateTo object.
function RotateTo:create(duration, dstAngleX, dstAngleY)
end

---
--- Creates the action with 3D rotation angles.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param dstAngle3D vec3_table @(cocos2d::Vec3) A Vec3 angle.
---@return cc.RotateTo @(cocos2d::RotateTo*) An autoreleased RotateTo object.
function RotateTo:create(duration, dstAngle3D)
end

---
--- Creates the action.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param dstAngle number @(float) In degreesCW.
---@return cc.RotateTo @(cocos2d::RotateTo*) An autoreleased RotateTo object.
function RotateTo:create(duration, dstAngle)
end

--- @class RotateBy
--- @brief Rotates a Node object clockwise a number of degrees by modifying it's rotation attribute.
---@class cc.RotateBy:cc.ActionInterval
local RotateBy = {}
cc.RotateBy = RotateBy

---
--- @warning The physics body contained in Node doesn't support rotate with different x and y angle.
---@param duration number @(float)
---@param deltaAngleZ_X number @(float) in degreesCW
---@param deltaAngleZ_Y number @(float) in degreesCW
---@return boolean @(bool)
function RotateBy:initWithDuration(duration, deltaAngleZ_X, deltaAngleZ_Y)
end

---@param duration number @(float)
---@param deltaAngle3D vec3_table @(cocos2d::Vec3)
---@return boolean @(bool)
function RotateBy:initWithDuration(duration, deltaAngle3D)
end

--- initializes the action
---@param duration number @(float)
---@param deltaAngle number @(float)
---@return boolean @(bool)
function RotateBy:initWithDuration(duration, deltaAngle)
end

---
--- Creates the action with separate rotation angles.
---
--- @warning The physics body contained in Node doesn't support rotate with different x and y angle.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param deltaAngleZ_X number @(float) In degreesCW.
---@param deltaAngleZ_Y number @(float) In degreesCW.
---@return cc.RotateBy @(cocos2d::RotateBy*) An autoreleased RotateBy object.
function RotateBy:create(duration, deltaAngleZ_X, deltaAngleZ_Y)
end

--- Creates the action with 3D rotation angles.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param deltaAngle3D vec3_table @(cocos2d::Vec3) A Vec3 angle.
---@return cc.RotateBy @(cocos2d::RotateBy*) An autoreleased RotateBy object.
function RotateBy:create(duration, deltaAngle3D)
end

---
--- Creates the action.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param deltaAngle number @(float) In degreesCW.
---@return cc.RotateBy @(cocos2d::RotateBy*) An autoreleased RotateBy object.
function RotateBy:create(duration, deltaAngle)
end

--- @class MoveBy
--- @brief Moves a Node object x,y pixels by modifying it's position attribute.
---  x and y are relative to the position of the object.
---  Several MoveBy actions can be concurrently called, and the resulting
---  movement will be the sum of individual movements.
---  @since v2.1beta2-custom
---@class cc.MoveBy:cc.ActionInterval
local MoveBy = {}
cc.MoveBy = MoveBy

---@param duration number @(float)
---@param deltaPosition vec3_table @(cocos2d::Vec3)
---@return boolean @(bool)
function MoveBy:initWithDuration(duration, deltaPosition)
end

--- initializes the action
---@param duration number @(float)
---@param deltaPosition vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function MoveBy:initWithDuration(duration, deltaPosition)
end

---
--- Creates the action.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param deltaPosition vec3_table @(cocos2d::Vec3) The delta distance in 3d, it's a Vec3 type.
---@return cc.MoveBy @(cocos2d::MoveBy*) An autoreleased MoveBy object.
function MoveBy:create(duration, deltaPosition)
end

---
--- Creates the action.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param deltaPosition vec2_table @(cocos2d::Vec2) The delta distance in 2d, it's a Vec2 type.
---@return cc.MoveBy @(cocos2d::MoveBy*) An autoreleased MoveBy object.
function MoveBy:create(duration, deltaPosition)
end

--- @class MoveTo
--- @brief Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position
---  attribute. Several MoveTo actions can be concurrently called, and the resulting movement will be the sum of individual
---  movements.
---  @since v2.1beta2-custom
---@class cc.MoveTo:cc.MoveBy
local MoveTo = {}
cc.MoveTo = MoveTo

---
--- initializes the action
---@param duration number @(float) in seconds
---@param position vec3_table @(cocos2d::Vec3)
---@return boolean @(bool)
function MoveTo:initWithDuration(duration, position)
end

---
--- initializes the action
---@param duration number @(float) in seconds
---@param position vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function MoveTo:initWithDuration(duration, position)
end

---
--- Creates the action.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param position vec3_table @(cocos2d::Vec3) The destination position in 3d.
---@return cc.MoveTo @(cocos2d::MoveTo*) An autoreleased MoveTo object.
function MoveTo:create(duration, position)
end

---
--- Creates the action.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param position vec2_table @(cocos2d::Vec2) The destination position in 2d.
---@return cc.MoveTo @(cocos2d::MoveTo*) An autoreleased MoveTo object.
function MoveTo:create(duration, position)
end

--- @class SkewTo
--- @brief Skews a Node object to given angles by modifying it's skewX and skewY attributes
--- @since v1.0
---@class cc.SkewTo:cc.ActionInterval
local SkewTo = {}
cc.SkewTo = SkewTo

---
---@param t number @(float) In seconds.
---@param sx number @(float)
---@param sy number @(float)
---@return boolean @(bool)
function SkewTo:initWithDuration(t, sx, sy)
end

---
--- Creates the action.
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param sx number @(float) Skew x angle.
---@param sy number @(float) Skew y angle.
---@return cc.SkewTo @(cocos2d::SkewTo*) An autoreleased SkewTo object.
function SkewTo:create(t, sx, sy)
end

--- @class SkewBy
--- @brief Skews a Node object by skewX and skewY degrees.
--- @since v1.0
---@class cc.SkewBy:cc.SkewTo
local SkewBy = {}
cc.SkewBy = SkewBy

---
---@param t number @(float) In seconds.
---@param sx number @(float)
---@param sy number @(float)
---@return boolean @(bool)
function SkewBy:initWithDuration(t, sx, sy)
end

---
--- Creates the action.
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param deltaSkewX number @(float) Skew x delta angle.
---@param deltaSkewY number @(float) Skew y delta angle.
---@return cc.SkewBy @(cocos2d::SkewBy*) An autoreleased SkewBy object.
function SkewBy:create(t, deltaSkewX, deltaSkewY)
end

--- @class JumpBy
--- @brief Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
---@class cc.JumpBy:cc.ActionInterval
local JumpBy = {}
cc.JumpBy = JumpBy

---
--- initializes the action
---@param duration number @(float) in seconds
---@param position vec2_table @(cocos2d::Vec2)
---@param height number @(float)
---@param jumps number @(int)
---@return boolean @(bool)
function JumpBy:initWithDuration(duration, position, height, jumps)
end

---
--- Creates the action.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param position vec2_table @(cocos2d::Vec2) The jumping distance.
---@param height number @(float) The jumping height.
---@param jumps number @(int) The jumping times.
---@return cc.JumpBy @(cocos2d::JumpBy*) An autoreleased JumpBy object.
function JumpBy:create(duration, position, height, jumps)
end

--- @class JumpTo
--- @brief Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
---@class cc.JumpTo:cc.JumpBy
local JumpTo = {}
cc.JumpTo = JumpTo

---
--- initializes the action
---@param duration number @(float) In seconds.
---@param position vec2_table @(cocos2d::Vec2)
---@param height number @(float)
---@param jumps number @(int)
---@return boolean @(bool)
function JumpTo:initWithDuration(duration, position, height, jumps)
end

---
--- Creates the action.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param position vec2_table @(cocos2d::Vec2) The jumping destination position.
---@param height number @(float) The jumping height.
---@param jumps number @(int) The jumping times.
---@return cc.JumpTo @(cocos2d::JumpTo*) An autoreleased JumpTo object.
function JumpTo:create(duration, position, height, jumps)
end

--- @class BezierBy
--- @brief An action that moves the target with a cubic Bezier curve by a certain distance.
---@class cc.BezierBy:cc.ActionInterval
local BezierBy = {}
cc.BezierBy = BezierBy



--- @class BezierTo
--- @brief An action that moves the target with a cubic Bezier curve to a destination point.
---  @since v0.8.2
---@class cc.BezierTo:cc.BezierBy
local BezierTo = {}
cc.BezierTo = BezierTo



--- @class ScaleTo
---  @brief Scales a Node object to a zoom factor by modifying it's scale attribute.
---  @warning This action doesn't support "reverse".
---  @warning The physics body contained in Node doesn't support this action.
---@class cc.ScaleTo:cc.ActionInterval
local ScaleTo = {}
cc.ScaleTo = ScaleTo

---
--- initializes the action with X Y Z factor
---@param duration number @(float) in seconds
---@param sx number @(float)
---@param sy number @(float)
---@param sz number @(float)
---@return boolean @(bool)
function ScaleTo:initWithDuration(duration, sx, sy, sz)
end

---
--- initializes the action with and X factor and a Y factor
---@param duration number @(float) in seconds
---@param sx number @(float)
---@param sy number @(float)
---@return boolean @(bool)
function ScaleTo:initWithDuration(duration, sx, sy)
end

---
--- initializes the action with the same scale factor for X and Y
---@param duration number @(float) in seconds
---@param s number @(float)
---@return boolean @(bool)
function ScaleTo:initWithDuration(duration, s)
end

---
--- Creates the action with X Y Z factor.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param sx number @(float) Scale factor of x.
---@param sy number @(float) Scale factor of y.
---@param sz number @(float) Scale factor of z.
---@return cc.ScaleTo @(cocos2d::ScaleTo*) An autoreleased ScaleTo object.
function ScaleTo:create(duration, sx, sy, sz)
end

---
--- Creates the action with and X factor and a Y factor.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param sx number @(float) Scale factor of x.
---@param sy number @(float) Scale factor of y.
---@return cc.ScaleTo @(cocos2d::ScaleTo*) An autoreleased ScaleTo object.
function ScaleTo:create(duration, sx, sy)
end

---
--- Creates the action with the same scale factor for X and Y.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param s number @(float) Scale factor of x and y.
---@return cc.ScaleTo @(cocos2d::ScaleTo*) An autoreleased ScaleTo object.
function ScaleTo:create(duration, s)
end

--- @class ScaleBy
--- @brief Scales a Node object a zoom factor by modifying it's scale attribute.
---  @warning The physics body contained in Node doesn't support this action.
---@class cc.ScaleBy:cc.ScaleTo
local ScaleBy = {}
cc.ScaleBy = ScaleBy

---
--- Creates the action with X Y Z factor.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param sx number @(float) Scale factor of x.
---@param sy number @(float) Scale factor of y.
---@param sz number @(float) Scale factor of z.
---@return cc.ScaleBy @(cocos2d::ScaleBy*) An autoreleased ScaleBy object.
function ScaleBy:create(duration, sx, sy, sz)
end

---
--- Creates the action with and X factor and a Y factor.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param sx number @(float) Scale factor of x.
---@param sy number @(float) Scale factor of y.
---@return cc.ScaleBy @(cocos2d::ScaleBy*) An autoreleased ScaleBy object.
function ScaleBy:create(duration, sx, sy)
end

---
--- Creates the action with the same scale factor for X and Y.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param s number @(float) Scale factor of x and y.
---@return cc.ScaleBy @(cocos2d::ScaleBy*) An autoreleased ScaleBy object.
function ScaleBy:create(duration, s)
end

--- @class Blink
--- @brief Blinks a Node object by modifying it's visible attribute.
---@class cc.Blink:cc.ActionInterval
local Blink = {}
cc.Blink = Blink

---
--- initializes the action
---@param duration number @(float) in seconds
---@param blinks number @(int)
---@return boolean @(bool)
function Blink:initWithDuration(duration, blinks)
end

---
--- Creates the action.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param blinks number @(int) Blink times.
---@return cc.Blink @(cocos2d::Blink*) An autoreleased Blink object.
function Blink:create(duration, blinks)
end

--- @class FadeTo
--- @brief Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a
---  custom one.
---  @warning This action doesn't support "reverse"
---@class cc.FadeTo:cc.ActionInterval
local FadeTo = {}
cc.FadeTo = FadeTo

---
--- initializes the action with duration and opacity
---@param duration number @(float) in seconds
---@param opacity number @(uint8_t)
---@return boolean @(bool)
function FadeTo:initWithDuration(duration, opacity)
end

---
--- Creates an action with duration and opacity.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param opacity number @(uint8_t) A certain opacity, the range is from 0 to 255.
---@return cc.FadeTo @(cocos2d::FadeTo*) An autoreleased FadeTo object.
function FadeTo:create(duration, opacity)
end

--- @class FadeIn
--- @brief Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
---  The "reverse" of this action is FadeOut
---@class cc.FadeIn:cc.FadeTo
local FadeIn = {}
cc.FadeIn = FadeIn

---
--- @js NA
---@param ac cc.FadeTo @(cocos2d::FadeTo*)
---@return self @(void)
function FadeIn:setReverseAction(ac)
end

---
--- Creates the action.
--- (static)
---@param d number @(float) Duration time, in seconds.
---@return cc.FadeIn @(cocos2d::FadeIn*) An autoreleased FadeIn object.
function FadeIn:create(d)
end

--- @class FadeOut
--- @brief Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
---  The "reverse" of this action is FadeIn
---@class cc.FadeOut:cc.FadeTo
local FadeOut = {}
cc.FadeOut = FadeOut

---
--- @js NA
---@param ac cc.FadeTo @(cocos2d::FadeTo*)
---@return self @(void)
function FadeOut:setReverseAction(ac)
end

---
--- Creates the action.
--- (static)
---@param d number @(float) Duration time, in seconds.
---@return cc.FadeOut @(cocos2d::FadeOut*)
function FadeOut:create(d)
end

--- @class TintTo
--- @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
---  @warning This action doesn't support "reverse"
---  @since v0.7.2
---@class cc.TintTo:cc.ActionInterval
local TintTo = {}
cc.TintTo = TintTo

--- initializes the action with duration and color
---@param duration number @(float)
---@param red number @(uint8_t)
---@param green number @(uint8_t)
---@param blue number @(uint8_t)
---@return boolean @(bool)
function TintTo:initWithDuration(duration, red, green, blue)
end

---
--- Creates an action with duration and color.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param red number @(uint8_t) Red Color, from 0 to 255.
---@param green number @(uint8_t) Green Color, from 0 to 255.
---@param blue number @(uint8_t) Blue Color, from 0 to 255.
---@return cc.TintTo @(cocos2d::TintTo*) An autoreleased TintTo object.
function TintTo:create(duration, red, green, blue)
end

---
--- Creates an action with duration and color.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param color color3b_table @(cocos2d::Color3B) It's a Color3B type.
---@return cc.TintTo @(cocos2d::TintTo*) An autoreleased TintTo object.
function TintTo:create(duration, color)
end

--- @class TintBy
---  @brief Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
---  @since v0.7.2
---@class cc.TintBy:cc.ActionInterval
local TintBy = {}
cc.TintBy = TintBy

--- initializes the action with duration and color
---@param duration number @(float)
---@param deltaRed number @(int16_t)
---@param deltaGreen number @(int16_t)
---@param deltaBlue number @(int16_t)
---@return boolean @(bool)
function TintBy:initWithDuration(duration, deltaRed, deltaGreen, deltaBlue)
end

---
--- Creates an action with duration and color.
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param deltaRed number @(int16_t) Delta red color.
---@param deltaGreen number @(int16_t) Delta green color.
---@param deltaBlue number @(int16_t) Delta blue color.
---@return cc.TintBy @(cocos2d::TintBy*) An autoreleased TintBy object.
function TintBy:create(duration, deltaRed, deltaGreen, deltaBlue)
end

--- @class DelayTime
--- @brief Delays the action a certain amount of seconds.
---@class cc.DelayTime:cc.ActionInterval
local DelayTime = {}
cc.DelayTime = DelayTime

---
--- Creates the action.
--- (static)
---@param d number @(float) Duration time, in seconds.
---@return cc.DelayTime @(cocos2d::DelayTime*) An autoreleased DelayTime object.
function DelayTime:create(d)
end

--- @class Animate
--- @brief Animates a sprite given the name of an Animation.
---@class cc.Animate:cc.ActionInterval
local Animate = {}
cc.Animate = Animate

---@return cc.Animation @(const cocos2d::Animation*)
function Animate:getAnimation()
end

--- returns the Animation object that is being animated
---
---@return cc.Animation @(cocos2d::Animation*) Gets the animation object that is being animated.
function Animate:getAnimation()
end

---
--- Gets the index of sprite frame currently displayed.
---@return number @(int) int  the index of sprite frame currently displayed.
function Animate:getCurrentFrameIndex()
end

--- initializes the action with an Animation and will restore the original frame when the animation is over
---@param animation cc.Animation @(cocos2d::Animation*)
---@return boolean @(bool)
function Animate:initWithAnimation(animation)
end

--- Sets the Animation object to be animated
---
---@param animation cc.Animation @(cocos2d::Animation*) certain animation.
---@return self @(void)
function Animate:setAnimation(animation)
end

--- Creates the action with an Animation and will restore the original frame when the animation is over.
---
--- (static)
---@param animation cc.Animation @(cocos2d::Animation*) A certain animation.
---@return cc.Animate @(cocos2d::Animate*) An autoreleased Animate object.
function Animate:create(animation)
end

--- @class TargetedAction
--- @brief Overrides the target of an action so that it always runs on the target
--- specified at action creation rather than the one specified by runAction.
---@class cc.TargetedAction:cc.ActionInterval
local TargetedAction = {}
cc.TargetedAction = TargetedAction

---@return cc.Node @(const cocos2d::Node*)
function TargetedAction:getForcedTarget()
end

--- returns the target that the action is forced to run with.
---
---@return cc.Node @(cocos2d::Node*) The target that the action is forced to run with.
function TargetedAction:getForcedTarget()
end

--- Init an action with the specified action and forced target
---@param target cc.Node @(cocos2d::Node*)
---@param action cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*)
---@return boolean @(bool)
function TargetedAction:initWithTarget(target, action)
end

--- Sets the target that the action will be forced to run with.
---
---@param forcedTarget cc.Node @(cocos2d::Node*) The target that the action will be forced to run with.
---@return self @(void)
function TargetedAction:setForcedTarget(forcedTarget)
end

--- Create an action with the specified action and forced target.
---
--- (static)
---@param target cc.Node @(cocos2d::Node*) The target needs to override.
---@param action cc.FiniteTimeAction @(cocos2d::FiniteTimeAction*) The action needs to override.
---@return cc.TargetedAction @(cocos2d::TargetedAction*) An autoreleased TargetedAction object.
function TargetedAction:create(target, action)
end

---
--- @class ActionFloat
--- @brief Action used to animate any value in range [from,to] over specified time interval
---@class cc.ActionFloat:cc.ActionInterval
local ActionFloat = {}
cc.ActionFloat = ActionFloat

---@param duration number @(float)
---@param from number @(float)
---@param to number @(float)
---@param callback function @(cocos2d::ActionFloat::ActionFloatCallback) Required callback; nil is rejected.
---@return boolean @(bool)
function ActionFloat:initWithDuration(duration, from, to, callback)
end

---
--- Creates FloatAction with specified duration, from value, to value and callback to report back
--- results
---
--- (static)
---@param duration number @(float) of the action
---@param from number @(float) value to start from
---@param to number @(float) value to be at the end of the action
---@param callback function @(cocos2d::ActionFloat::ActionFloatCallback) to report back result Required callback; nil is rejected.
---@return cc.ActionFloat @(cocos2d::ActionFloat*) An autoreleased ActionFloat object
function ActionFloat:create(duration, from, to, callback)
end

---
--- UserDefault acts as a tiny database. You can save and get base type values by it.
--- For example, setBoolForKey("played", true) will add a bool value true into the database.
--- Its key is "played". You can get the value of the key by getBoolForKey("played").
---
--- It supports the following base types:
--- bool, int, float, double, string
---
--- @warning: On windows, linux, use XML to store data, which means there are some limitations of
--- the key string, for example, `` is not valid.
---@class cc.UserDefault
local UserDefault = {}
cc.UserDefault = UserDefault

---
--- delete any value by key,
--- @js NA
---@param key string @(const char*) The key to delete value.
---@return self @(void)
function UserDefault:deleteValueForKey(key)
end

---
--- Since we reimplement UserDefault with file mapping io,
--- you don't needs call this function manually
--- @js NA
---@return self @(void)
function UserDefault:flush()
end

---
--- Get bool value by key, if the key doesn't exist, will return passed default value.
--- @js NA
---@param key string @(const char*) The key to get value.
---@param defaultValue boolean @(bool) The default value to return if the key doesn't exist.
---@return boolean @(bool)
function UserDefault:getBoolForKey(key, defaultValue)
end

---
--- Get bool value by key, if the key doesn't exist, will return false.
--- You can set the default value, or it is false.
--- @js NA
---@param key string @(const char*) The key to get value.
---@return boolean @(bool) Bool value by `key`.
function UserDefault:getBoolForKey(key)
end

---
--- Get double value by key, if the key doesn't exist, will return passed default value.
--- @js NA
---@param key string @(const char*) The key to get value.
---@param defaultValue number @(double) The default value to return if the key doesn't exist.
---@return number @(double) Double value of the key.
function UserDefault:getDoubleForKey(key, defaultValue)
end

---
--- Get double value by key, if the key doesn't exist, will return 0.0.
--- @js NA
---@param key string @(const char*) The key to get value.
---@return number @(double) Double value of the key.
function UserDefault:getDoubleForKey(key)
end

---
--- Get float value by key, if the key doesn't exist, will return passed default value.
--- @js NA
---@param key string @(const char*) The key to get value.
---@param defaultValue number @(float) The default value to return if the key doesn't exist.
---@return number @(float) Float value of the key.
function UserDefault:getFloatForKey(key, defaultValue)
end

---
--- Get float value by key, if the key doesn't exist, will return 0.0.
--- @js NA
---@param key string @(const char*) The key to get value.
---@return number @(float) Float value of the key.
function UserDefault:getFloatForKey(key)
end

---
--- Get integer value by key, if the key doesn't exist, will return passed default value.
--- @js NA
---@param key string @(const char*) The key to get value.
---@param defaultValue number @(int) The default value to return if the key doesn't exist.
---@return number @(int) Integer value of the key.
function UserDefault:getIntegerForKey(key, defaultValue)
end

---
--- Get integer value by key, if the key doesn't exist, will return 0.
--- You can set the default value, or it is 0.
--- @js NA
---@param key string @(const char*) The key to get value.
---@return number @(int) Integer value of the key.
function UserDefault:getIntegerForKey(key)
end

---
--- Get large integer value by key, if the key doesn't exist, will return passed default value.
--- @js NA
---@param key string @(const char*) The key to get value.
---@param defaultValue number @(int64_t) The default value to return if the key doesn't exist.
---@return number @(int64_t) Integer value of the key.
function UserDefault:getLargeIntForKey(key, defaultValue)
end

---
--- Get large integer value by key, if the key doesn't exist, will return 0.
--- You can set the default value, or it is 0.
--- @js NA
---@param key string @(const char*) The key to get value.
---@return number @(int64_t) Integer value of the key.
function UserDefault:getLargeIntForKey(key)
end

---
--- Get string value by key, if the key doesn't exist, will return passed default value.
--- @js NA
---@param key string @(const char*) The key to get value.
---@param defaultValue string @(std::string_view) The default value to return if the key doesn't exist.
---@return string @(std::string_view) String value of the key.
function UserDefault:getStringForKey(key, defaultValue)
end

---
--- Get string value by key, if the key doesn't exist, will return an empty string.
--- @js NA
---@param key string @(const char*) The key to get value.
---@return string @(std::string_view) String value of the key.
function UserDefault:getStringForKey(key)
end

---
--- Set bool value by key.
--- @js NA
---@param key string @(const char*) The key to set.
---@param value boolean @(bool) A bool value to set to the key.
---@return self @(void)
function UserDefault:setBoolForKey(key, value)
end

---
--- Set double value by key.
--- @js NA
---@param key string @(const char*) The key to set.
---@param value number @(double) A double value to set to the key.
---@return self @(void)
function UserDefault:setDoubleForKey(key, value)
end

---@param enabled boolean @(bool)
---@param key string @(std::string_view)
---@param iv string @(std::string_view)
---@return self @(void)
function UserDefault:setEncryptEnabled(enabled, key, iv)
end

---
--- Set float value by key.
--- @js NA
---@param key string @(const char*) The key to set.
---@param value number @(float) A float value to set to the key.
---@return self @(void)
function UserDefault:setFloatForKey(key, value)
end

---
--- Set integer value by key.
--- @js NA
---@param key string @(const char*) The key to set.
---@param value number @(int) A integer value to set to the key.
---@return self @(void)
function UserDefault:setIntegerForKey(key, value)
end

---
--- Set large integer value by key.
--- @js NA
---@param key string @(const char*) The key to set.
---@param value number @(int64_t) A integer value to set to the key.
---@return self @(void)
function UserDefault:setLargeIntForKey(key, value)
end

---
--- Set string value by key.
--- @js NA
---@param key string @(const char*) The key to set.
---@param value string @(std::string_view) A string value to set to the key.
---@return self @(void)
function UserDefault:setStringForKey(key, value)
end

--- Returns the singleton.
--- @js NA
--- @lua NA
--- (static)
---@return cc.UserDefault @(cocos2d::UserDefault*)
function UserDefault:getInstance()
end

local AppDirectory = {
	PersistentData = 0,
	TransientData = 1,
}
--- Retention requirements for application-owned physical directories.
---@class cc.AppDirectory
cc.AppDirectory = AppDirectory

local DirectoryStatus = {
	Ok = 0,
	NotInitialized = 1,
	InvalidArgument = 2,
	InUse = 3,
	Unavailable = 4,
	PermissionDenied = 5,
	NotDirectory = 6,
	IoError = 7,
	Unsupported = 8,
}
---
---@class cc.DirectoryStatus
cc.DirectoryStatus = DirectoryStatus

--- Helper class to handle file operations.
---@class cc.FileUtils
local FileUtils = {}
cc.FileUtils = FileUtils

---
--- Add search path.
---
--- @since v2.1
---@param path string @(std::string_view)
---@param front boolean @(const bool)
---@return self @(void)
function FileUtils:addSearchPath(path, front)
end

---
--- Add search path.
---
--- @since v2.1
---@param path string @(std::string_view)
---@return self @(void)
function FileUtils:addSearchPath(path)
end

---
--- Create a directory, async off the main cocos thread.
---
--- argument, true if the physical target is a directory, false otherwise (including emptyNUL input).
---@param dirPath string @(std::string_view) Native path; relative paths use the worker's process CWD when it executes.
---@param callback function @(std::function<void(bool)>) The function that will be called when the operation is complete. Will have one boolean
---@return self @(void)
function FileUtils:createDirectory(dirPath, callback)
end

---
--- Creates a physical directory and any missing parent directories without resource lookup.
---
--- @param dirPath Native path; relative paths use the process CWD when the operation executes.
--- @return True if the target is a directory after the operation (including an existing one).
--- Empty or NUL-containing paths, file occupants and creation failures return false.
---@param dirPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:createDirectory(dirPath)
end

---
--- Recursively create and verify a root or relative child using native filesystem IO.
--- Child components must be nonempty, without '.', '..', NUL, backslash or drive syntax;
--- empty input means the root. This is not a sandbox against hostile symlinks.
--- Success does not promise that subsequent writes will succeed.
---@param kind cc.AppDirectory @(cocos2d::AppDirectory)
---@param relativeSubdirectory string @(std::string_view)
---@return cc.DirectoryResult @(cocos2d::DirectoryResult)
function FileUtils:ensureAppDirectory(kind, relativeSubdirectory)
end

---
--- Recursively create and verify a root or relative child using native filesystem IO.
--- Child components must be nonempty, without '.', '..', NUL, backslash or drive syntax;
--- empty input means the root. This is not a sandbox against hostile symlinks.
--- Success does not promise that subsequent writes will succeed.
---@param kind cc.AppDirectory @(cocos2d::AppDirectory)
---@return cc.DirectoryResult @(cocos2d::DirectoryResult)
function FileUtils:ensureAppDirectory(kind)
end

--- Returns the fullpath for a given filename.
---
--- First it will try to get a new filename from the "filenameLookup" dictionary.
--- If a new filename can't be found on the dictionary, it will use the original filename.
--- Then it will try to obtain the full path of the filename using the FileUtils search rules: resolutions, and search
--- paths. The file search is based on the array element order of search paths and resolution directories.
---
--- For instance:
---
--- We set two elements("mntsdcard", "internal_dir") to search paths vector by setSearchPaths,
---
--- If we have a file named 'sprite.png', the mapping in fileLookup dictionary contains `key: sprite.png -> value:
--- sprite.pvr.gz`. Firstly, it will replace 'sprite.png' with 'sprite.pvr.gz', then searching the file sprite.pvr.gz
--- as follows:
---
--- mntsdcardresources-ipadhdsprite.pvr.gz      (if not found, search next)
--- mntsdcardresources-ipadsprite.pvr.gz        (if not found, search next)
--- mntsdcardresources-iphonehdsprite.pvr.gz    (if not found, search next)
--- mntsdcardsprite.pvr.gz                       (if not found, search next)
--- internal_dirresources-ipadhdsprite.pvr.gz     (if not found, search next)
--- internal_dirresources-ipadsprite.pvr.gz       (if not found, search next)
--- internal_dirresources-iphonehdsprite.pvr.gz   (if not found, search next)
--- internal_dirsprite.pvr.gz                      (if not found, return "sprite.png")
---
--- If the filename contains relative path like "gamesceneuilayersprite.png",
--- and the mapping in fileLookup dictionary contains `key: gamesceneuilayersprite.png -> value:
--- gamesceneuilayersprite.pvr.gz`. The file search order will be:
---
--- mntsdcardgamesceneuilayerresources-ipadhdsprite.pvr.gz      (if not found, search next)
--- mntsdcardgamesceneuilayerresources-ipadsprite.pvr.gz        (if not found, search next)
--- mntsdcardgamesceneuilayerresources-iphonehdsprite.pvr.gz    (if not found, search next)
--- mntsdcardgamesceneuilayersprite.pvr.gz                       (if not found, search next)
--- internal_dirgamesceneuilayerresources-ipadhdsprite.pvr.gz     (if not found, search next)
--- internal_dirgamesceneuilayerresources-ipadsprite.pvr.gz       (if not found, search next)
--- internal_dirgamesceneuilayerresources-iphonehdsprite.pvr.gz   (if not found, search next)
--- internal_dirgamesceneuilayersprite.pvr.gz                      (if not found, return
--- "gamesceneuilayersprite.png")
---
--- If the new file can't be found on the file system, it will return the parameter filename directly.
---
--- This method was added to simplify multiplatform support. Whether you are using cocos2d-js or any cross-compilation
--- toolchain like StellaSDK or Apportable, you might need to load different resources for a given file in the
--- different platforms.
---
--- @since v2.1
---@param filename string @(std::string_view)
---@return string @(std::string)
function FileUtils:fullPathForFilename(filename)
end

---
--- Gets full path from a file name and the path of the relative file.
--- @param filename The file name.
--- @param relativeFile The path of the relative file.
--- @return The full path.
--- e.g. filename: hello.png, pszRelativeFile:Userpath1path2hello.plist
--- Return:Userpath1path2hello.pvr (If there a a key(hello.png)-value(hello.pvr) in FilenameLookup
--- dictionary. )
---
---@param filename string @(std::string_view)
---@param relativeFile string @(std::string_view)
---@return string @(std::string)
function FileUtils:fullPathFromRelativeFile(filename, relativeFile)
end

---
--- Get default resource root path.
---@return string @(const std::string)
function FileUtils:getDefaultResourceRootPath()
end

---
--- Gets filename extension is a suffix (separated from the base filename by a dot) in lower case.
--- Examples of filename extensions are .png, .jpeg, .exe, .dmg and .txt.
--- @param filePath The path of the file, it could be a relative or absolute path.
--- @return suffix for filename in lower case or empty if a dot not found.
---@param filePath string @(std::string_view)
---@return string @(std::string)
function FileUtils:getFileExtension(filePath)
end

---
--- Retrieve the file size, async off the main cocos thread.
---
--- @note If a relative path was passed in, it will be inserted a default root path at the beginning.
--- @param filepath The path of the file, it could be a relative or absolute path.
--- @param callback The function that will be called when the operation is complete. Will have one long
--- argument, the file size.
---@param filepath string @(std::string_view)
---@param callback function @(std::function<void(int64_t)>)
---@return self @(void)
function FileUtils:getFileSize(filepath, callback)
end

---
--- Retrieve the file size.
---
--- @note If a relative path was passed in, it will be inserted a default root path at the beginning.
--- @param filepath The path of the file, it could be a relative or absolute path.
--- @return The file size.
---@param filepath string @(std::string_view)
---@return number @(int64_t)
function FileUtils:getFileSize(filepath)
end

---
--- Gets the same physical UTF-8 directory snapshot as getWritablePath().
--- Native means the physical file system, not a resource name or an ANSI-encoded path.
---@return string @(std::string)
function FileUtils:getNativeWritableAbsolutePath()
end

---
--- Gets the original search path array set by 'setSearchPaths' or 'addSearchPath'.
--- @return The array of the original search paths
---@return string[] @(const std::vector<std::string>)
function FileUtils:getOriginalSearchPaths()
end

--- Query-only convenience getters; failure returns an empty string. Check before concatenating.
---@return string @(std::string)
function FileUtils:getPersistentDataPath()
end

---
--- Gets the array of search paths.
---
--- @return The array of search paths which may contain the prefix of default resource root path.
--- @note In best practise, getter function should return the value of setter function passes in.
--- But since we should not break the compatibility, we keep using the old logic.
--- Therefore, If you want to get the original search paths, please call 'getOriginalSearchPaths()' instead.
--- @see fullPathForFilename(const char*).
--- @lua NA
---@return string[] @(const std::vector<std::string>)
function FileUtils:getSearchPaths()
end

---
--- Gets string from a file.
---@param filename string @(std::string_view)
---@return string @(std::string)
function FileUtils:getStringFromFile(filename)
end

---
--- Only for compatibility.
---@param path string @(std::string_view)
---@return string @(std::string)
function FileUtils:getSuitableFOpen(path)
end

---@return string @(std::string)
function FileUtils:getTransientDataPath()
end

--- Converts the contents of a file to a ValueMap.
--- This method is used internally.
---@param filedata string @(const char*)
---@param filesize number @(int)
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
function FileUtils:getValueMapFromData(filedata, filesize)
end

---
--- Converts the contents of a file to a ValueMap.
--- @param filename The filename of the file to gets content.
--- @return ValueMap of the file contents.
--- @note This method is used internally.
---@param filename string @(std::string_view)
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
function FileUtils:getValueMapFromFile(filename)
end

---@param filename string @(std::string_view)
---@return cc.Value[] @(cocos2d::ValueVector)
function FileUtils:getValueVectorFromFile(filename)
end

---
--- Gets the configured physical directory as a fully qualified UTF-8 path ending in ''.
--- This query does not check, create or repair the directory. An empty result means that
--- no platform default is available and no override has been configured.
---@return string @(std::string)
function FileUtils:getWritablePath()
end

---
--- Checks whether the path is an absolute path.
---
--- @note On Android, if the parameter passed in is relative to "assets", this method will treat it as an absolute
--- path. Also on Blackberry, path starts with "appnativeResources" is treated as an absolute path.
---
--- @param path The path that needs to be checked.
--- @return True if it's an absolute path, false if not.
---@param path string @(std::string_view)
---@return boolean @(bool)
function FileUtils:isAbsolutePath(path)
end

---
--- Checks whether the absoulate path is a directory, async off of the main cocos thread.
---
--- Callback will happen on the main cocos thread.
---@param fullPath string @(std::string_view)
---@param callback function @(std::function<void(bool)>) that will accept a boolean, true if the file exists, false otherwise.
---@return self @(void)
function FileUtils:isDirectoryExist(fullPath, callback)
end

---
--- Checks whether the path is a directory.
---
--- @param dirPath The path of the directory, it could be a relative or an absolute path.
--- @return True if the directory exists, false if not.
---@param dirPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:isDirectoryExist(dirPath)
end

---
--- Checks whether a directory exists without considering search paths and resolution orders.
--- @param dirPath The directory (with absolute path) to look up for
--- @return Returns true if the directory found at the given absolute path, otherwise returns false
---@param dirPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:isDirectoryExistInternal(dirPath)
end

---
--- Checks if a file exists, done async off the main cocos thread.
---
--- Use this function if you need to check if a file exists while not blocking the main cocos thread.
---
--- @note If a relative path was passed in, it will be inserted a default root path at the beginning.
--- @param filename The path of the file, it could be a relative or absolute path.
--- @param callback The function that will be called when the operation is complete. Will have one boolean
--- argument, true if the file exists, false otherwise.
---@param filename string @(std::string_view)
---@param callback function @(std::function<void(bool)>)
---@return self @(void)
function FileUtils:isFileExist(filename, callback)
end

---
--- Checks whether a file exists.
---
--- @note If a relative path was passed in, it will be inserted a default root path at the beginning.
--- @param filename The path of the file, it could be a relative or absolute path.
--- @return True if the file exists, false if not.
---@param filename string @(std::string_view)
---@return boolean @(bool)
function FileUtils:isFileExist(filename)
end

---
--- Checks whether a file exists without considering search paths and resolution orders.
--- @param filename The file (with absolute path) to look up for
--- @return Returns true if the file found at the given absolute path, otherwise returns false
---@param filename string @(std::string_view)
---@return boolean @(bool)
function FileUtils:isFileExistInternal(filename)
end

--- Checks whether to pop up a message box when failed to load an image.
--- @return True if pop up a message box when failed to load an image, false if not.
---@return boolean @(bool)
function FileUtils:isPopupNotify()
end

---
--- List all files in a directory.
---
--- @param dirPath The path of the directory, it could be a relative or an absolute path.
--- @return File paths in a string vector
---@param dirPath string @(std::string_view)
---@return string[] @(std::vector<std::string>)
function FileUtils:listFiles(dirPath)
end

---
--- List all files in a directory async, off of the main cocos thread.
---
--- thread.
--- @js NA
--- @lua NA
---@param dirPath string @(std::string_view) The path of the directory, it could be a relative or an absolute path.
---@param callback function @(std::function<void(std::vector<std::string>)>) The callback to be called once the list operation is complete. Will be called on the main cocos
---@return self @(void)
function FileUtils:listFilesAsync(dirPath, callback)
end

---
--- List all files recursively in a directory, async off the main cocos thread.
---
--- @param dirPath The path of the directory, it could be a relative or an absolute path.
--- @param callback The callback to be called once the list operation is complete.
--- Will be called on the main cocos thread.
--- @js NA
--- @lua NA
---@param dirPath string @(std::string_view)
---@param callback function @(std::function<void(std::vector<std::string>)>)
---@return self @(void)
function FileUtils:listFilesRecursivelyAsync(dirPath, callback)
end

---
--- Purges full path caches.
---@return self @(void)
function FileUtils:purgeCachedEntries()
end

---
--- Resolve a physical application root without explicitly creating or inspecting it.
--- Native platform APIs may prepare directories themselves (notably Android Context).
--- Success gives a fully qualified UTF-8 path with '' separators and a trailing ''.
--- Errors carry no path; no fallback to CWD, installation or another root occurs.
--- TransientData may be lost at any time and is not automatically cleared on exit.
---@param kind cc.AppDirectory @(cocos2d::AppDirectory)
---@return cc.DirectoryResult @(cocos2d::DirectoryResult)
function FileUtils:queryAppDirectory(kind)
end

---
--- Removes a directory, async off the main cocos thread.
---
--- argument, true if the directory was successfully removed, false otherwise.
---@param dirPath string @(std::string_view) the path of the directory, it must be an absolute path
---@param callback function @(std::function<void(bool)>) The function that will be called when the operation is complete. Will have one boolean
---@return self @(void)
function FileUtils:removeDirectory(dirPath, callback)
end

---
--- Removes a directory.
---
--- @param dirPath  The full path of the directory, it must be an absolute path.
--- @return True if the directory have been removed successfully, false if not.
---@param dirPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:removeDirectory(dirPath)
end

---
--- Removes a file, async off the main cocos thread.
---
--- argument, true if the file was successfully removed, false otherwise.
---@param filepath string @(std::string_view) the path of the file to remove, it must be an absolute path
---@param callback function @(std::function<void(bool)>) The function that will be called when the operation is complete. Will have one boolean
---@return self @(void)
function FileUtils:removeFile(filepath, callback)
end

---
--- Removes a file.
---
--- @param filepath The full path of the file, it must be an absolute path.
--- @return True if the file have been removed successfully, false if not.
---@param filepath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:removeFile(filepath)
end

---
--- Renames a file under the given directory, async off the main cocos thread.
---
--- @param path     The parent directory path of the file, it must be an absolute path.
--- @param oldname  The current name of the file.
--- @param name     The new name of the file.
--- @param callback The function that will be called when the operation is complete. Will have one boolean
--- argument, true if the file was successfully renamed, false otherwise.
---@param path string @(std::string_view)
---@param oldname string @(std::string_view)
---@param name string @(std::string_view)
---@param callback function @(std::function<void(bool)>)
---@return self @(void)
function FileUtils:renameFile(path, oldname, name, callback)
end

---
--- Renames a file under the given directory, async off the main cocos thread.
---
--- @param oldfullpath  The current fullpath of the file. Includes path and name.
--- @param newfullpath  The new fullpath of the file. Includes path and name.
--- @param callback The function that will be called when the operation is complete. Will have one boolean
--- argument, true if the file was successfully renamed, false otherwise.
---@param oldfullpath string @(std::string_view)
---@param newfullpath string @(std::string_view)
---@param callback function @(std::function<void(bool)>)
---@return self @(void)
function FileUtils:renameFile(oldfullpath, newfullpath, callback)
end

---
--- Renames a file under the given directory.
---
--- @param path     The parent directory path of the file, it must be an absolute path.
--- @param oldname  The current name of the file.
--- @param name     The new name of the file.
--- @return True if the file have been renamed successfully, false if not.
---@param path string @(std::string_view)
---@param oldname string @(std::string_view)
---@param name string @(std::string_view)
---@return boolean @(bool)
function FileUtils:renameFile(path, oldname, name)
end

---
--- Renames a file under the given directory.
---
--- @param oldfullpath  The current fullpath of the file. Includes path and name.
--- @param newfullpath  The new fullpath of the file. Includes path and name.
--- @return True if the file have been renamed successfully, false if not.
---@param oldfullpath string @(std::string_view)
---@param newfullpath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:renameFile(oldfullpath, newfullpath)
end

---
--- Set default resource root path.
---@param path string @(std::string_view)
---@return self @(void)
function FileUtils:setDefaultResourceRootPath(path)
end

---
--- Sets whether to pop-up a message box when failed to load an image.
---@param notify boolean @(bool)
---@return self @(void)
function FileUtils:setPopupNotify(notify)
end

---
--- Sets the array of search paths.
---
--- You can use this array to modify the search path of the resources.
--- If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in
--- this array.
---
--- @note This method could access relative path and absolute path.
--- If the relative path was passed to the vector, FileUtils will add the default resource directory before
--- the relative path. For instance: On Android, the default resource root path is "assets". If "mntsdcard" and
--- "resources-large" were set to the search paths vector, "resources-large" will be converted to
--- "assetsresources-large" since it was a relative path.
---
--- @param searchPaths The array contains search paths.
--- @see fullPathForFilename(const char*)
--- @since v2.1
--- In js:var setSearchPaths(var jsval);
--- @lua NA
---@param searchPaths string[] @(std::vector<std::string>)
---@return self @(void)
function FileUtils:setSearchPaths(searchPaths)
end

---
--- Configures a physical directory without testing its existence or writability.
--- Ordinary relative paths are resolved once against this call's process CWD snapshot.
--- Empty input reloads the platform default and removes the override. Invalid UTF-8,
--- embedded NUL, invalid native syntax, or unavailable required path information fails
--- without changing the previous state. Windows drive-relative, root-relative, device
--- and extended namespace paths are rejected. No shellURI expansion is performed.
--- Normalization is lexical and does not resolve symlinks. Callers must synchronize
--- concurrent process-CWD changes and explicitly prepare directories before writing.
--- @return True if the configuration was accepted; this does not guarantee successful IO.
---@param writablePath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:setWritablePath(writablePath)
end

---
--- Write a string to a file, done async off the main cocos thread
--- Use this function if you need file access without blocking the main thread.
---
--- This function takes a std::string by value on purpose, to leverage move sematics.
--- If you want to avoid a copy of your datastr, use std::movestd::forward if appropriate
---
--- function will be executed on the main cocos thread. It will have on boolean argument
--- signifying if the write was successful.
---@param dataStr string @(std::string) the string want to save
---@param fullPath string @(std::string_view) The full path to the file you want to save a string
---@param callback function @(std::function<void(bool)>) The function called once the string has been written to a file. This
---@return self @(void)
function FileUtils:writeStringToFile(dataStr, fullPath, callback)
end

---
--- write a string into a file
---
---@param dataStr string @(std::string_view) the string want to save
---@param fullPath string @(std::string_view) The full path to the file you want to save a string
---@return boolean @(bool) bool True if write success
function FileUtils:writeStringToFile(dataStr, fullPath)
end

---
--- write a ValueMap into a plist file
---
--- *@param dict the ValueMap want to save
--- *@param fullPath The full path to the file you want to save a string
--- *@return bool
---@param dict tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@param fullPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:writeToFile(dict, fullPath)
end

---
--- Write a ValueMap into a file, done async off the main cocos thread.
---
--- Use this function if you need to write a ValueMap while not blocking the main cocos thread.
---
--- This function takes ValueMap by value on purpose, to leverage move sematics.
--- If you want to avoid a copy of your dict, use std::movestd::forward if appropriate
---
--- *@param dict The ValueMap that will be written to disk
--- *@param fullPath The absolute file path that the data will be written to
--- *@param callback The function that will be called when dict is written to disk. This
--- function will be executed on the main cocos thread. It will have on boolean argument
--- signifying if the write was successful.
---@param dict tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@param fullPath string @(std::string_view)
---@param callback function @(std::function<void(bool)>)
---@return self @(void)
function FileUtils:writeValueMapToFile(dict, fullPath, callback)
end

---
--- write ValueMap into a plist file
---
--- *@param dict the ValueMap want to save
--- *@param fullPath The full path to the file you want to save a string
--- *@return bool
---@param dict tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@param fullPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:writeValueMapToFile(dict, fullPath)
end

---
--- Write a ValueVector into a file, done async off the main cocos thread.
---
--- Use this function if you need to write a ValueVector while not blocking the main cocos thread.
---
--- This function takes ValueVector by value on purpose, to leverage move sematics.
--- If you want to avoid a copy of your dict, use std::movestd::forward if appropriate
---
--- *@param vecData The ValueVector that will be written to disk
--- *@param fullPath The absolute file path that the data will be written to
--- *@param callback The function that will be called when vecData is written to disk. This
--- function will be executed on the main cocos thread. It will have on boolean argument
--- signifying if the write was successful.
---@param vecData cc.Value[] @(cocos2d::ValueVector)
---@param fullPath string @(std::string_view)
---@param callback function @(std::function<void(bool)>)
---@return self @(void)
function FileUtils:writeValueVectorToFile(vecData, fullPath, callback)
end

---
--- write ValueVector into a plist file
---
--- *@param vecData the ValueVector want to save
--- *@param fullPath The full path to the file you want to save a string
--- *@return bool
---@param vecData cc.Value[] @(cocos2d::ValueVector)
---@param fullPath string @(std::string_view)
---@return boolean @(bool)
function FileUtils:writeValueVectorToFile(vecData, fullPath)
end

---
--- Gets filename shotName
--- @param filePath The path of the file, it could be a relative or absolute path.
--- @return fileName.Extension without path
--- (static)
---@param filePath string @(std::string_view)
---@return string @(std::string)
function FileUtils:getFileShortName(filePath)
end

---
--- Gets the instance of FileUtils.
--- (static)
---@return cc.FileUtils @(cocos2d::FileUtils*)
function FileUtils:getInstance()
end

--- (static)
---@param path string @(std::string_view)
---@return boolean @(bool)
function FileUtils:isAbsolutePathInternal(path)
end

--- @class EventAcceleration
--- @brief Accelerometer event.
---@class cc.EventAcceleration:cc.Event
local EventAcceleration = {}
cc.EventAcceleration = EventAcceleration



--- @class EventCustom
--- @brief Custom event.
---@class cc.EventCustom:cc.Event
local EventCustom = {}
cc.EventCustom = EventCustom

--- Gets event name.
---
---@return string @(std::string_view) The name of the event.
function EventCustom:getEventName()
end

--- @class EventDispatcher
--- @brief This class manages event listener subscriptions
--- and event dispatching.
---
--- The EventListener list is managed in such a way that
--- event listeners can be added and removed even
--- from within an EventListener, while events are being
--- dispatched.
--- @js NA
---@class cc.EventDispatcher:cc.Ref
local EventDispatcher = {}
cc.EventDispatcher = EventDispatcher

--- Adds a Custom event listener.
--- It will use a fixed priority of 1.
---@param eventName string @(std::string_view) A given name of the event.
---@param callback function @(std::function<void(cocos2d::EventCustom*)>) A given callback method that associated the event name. Required callback; nil is rejected.
---@return cc.EventListenerCustom @(cocos2d::EventListenerCustom*) the generated event. Needed in order to remove the event from the dispatcher
function EventDispatcher:addCustomEventListener(eventName, callback)
end

--- Adds a event listener for a specified event with the fixed priority.
--- @param listener The listener of a specified event.
--- @param fixedPriority The fixed priority of the listener.
--- @note A lower priority will be called before the ones that have a higher value.
--- 0 priority is forbidden for fixed priority since it's used for scene graph based priority.
---@param listener cc.EventListener @(cocos2d::EventListener*)
---@param fixedPriority number @(int)
---@return self @(void)
function EventDispatcher:addEventListenerWithFixedPriority(listener, fixedPriority)
end

--- Adds a event listener for a specified event with the priority of scene graph.
--- @param listener The listener of a specified event.
--- @param node The priority of the listener is based on the draw order of this node.
--- @note  The priority of scene graph will be fixed value 0. So the order of listener item
--- in the vector will be ' <0, scene graph (0 priority), >0'.
---@param listener cc.EventListener @(cocos2d::EventListener*)
---@param node cc.Node @(cocos2d::Node*)
---@return self @(void)
function EventDispatcher:addEventListenerWithSceneGraphPriority(listener, node)
end

--- Dispatches the event.
--- Also removes all EventListeners marked for deletion from the
--- event dispatcher list.
---
---@param event cc.Event @(cocos2d::Event*) The event needs to be dispatched.
---@return self @(void)
function EventDispatcher:dispatchEvent(event)
end

--- Query whether the specified event listener id has been added.
---
---
---@param listenerID string @(std::string_view) The listenerID of the event listener id.
---@return boolean @(bool) True if dispatching events is exist
function EventDispatcher:hasEventListener(listenerID)
end

--- Checks whether dispatching events is enabled.
---
---@return boolean @(bool) True if dispatching events is enabled.
function EventDispatcher:isEnabled()
end

--- Pauses all listeners which are associated the specified target.
---
---@param target cc.Node @(cocos2d::Node*) A given target node.
---@param recursive boolean @(bool) True if pause recursively, the default value is false.
---@return self @(void)
function EventDispatcher:pauseEventListenersForTarget(target, recursive)
end

--- Pauses all listeners which are associated the specified target.
---
---@param target cc.Node @(cocos2d::Node*) A given target node.
---@return self @(void)
function EventDispatcher:pauseEventListenersForTarget(target)
end

--- Removes all listeners.
---@return self @(void)
function EventDispatcher:removeAllEventListeners()
end

--- Removes all custom listeners with the same event name.
---
---@param customEventName string @(std::string_view) A given event listener name which needs to be removed.
---@return self @(void)
function EventDispatcher:removeCustomEventListeners(customEventName)
end

--- Remove a listener.
---
--- @param listener The specified event listener which needs to be removed.
---@param listener cc.EventListener @(cocos2d::EventListener*)
---@return self @(void)
function EventDispatcher:removeEventListener(listener)
end

--- Removes all listeners which are associated with the specified target.
---
---@param target cc.Node @(cocos2d::Node*) A given target node.
---@param recursive boolean @(bool) True if remove recursively, the default value is false.
---@return self @(void)
function EventDispatcher:removeEventListenersForTarget(target, recursive)
end

--- Removes all listeners which are associated with the specified target.
---
---@param target cc.Node @(cocos2d::Node*) A given target node.
---@return self @(void)
function EventDispatcher:removeEventListenersForTarget(target)
end

--- Removes all listeners with the same event listener type.
---
---@param listenerType cc.EventListener.Type @(cocos2d::EventListener::Type) A given event listener type which needs to be removed.
---@return self @(void)
function EventDispatcher:removeEventListenersForType(listenerType)
end

--- Resumes all listeners which are associated the specified target.
---
---@param target cc.Node @(cocos2d::Node*) A given target node.
---@param recursive boolean @(bool) True if resume recursively, the default value is false.
---@return self @(void)
function EventDispatcher:resumeEventListenersForTarget(target, recursive)
end

--- Resumes all listeners which are associated the specified target.
---
---@param target cc.Node @(cocos2d::Node*) A given target node.
---@return self @(void)
function EventDispatcher:resumeEventListenersForTarget(target)
end

--- Whether to enable dispatching events.
---
---@param isEnabled boolean @(bool)  True if enable dispatching events.
---@return self @(void)
function EventDispatcher:setEnabled(isEnabled)
end

--- Sets listener's priority with fixed value.
---
---@param listener cc.EventListener @(cocos2d::EventListener*) A given listener.
---@param fixedPriority number @(int) The fixed priority value.
---@return self @(void)
function EventDispatcher:setPriority(listener, fixedPriority)
end

--- @class EventFocus
--- @brief Focus event.
---@class cc.EventFocus:cc.Event
local EventFocus = {}
cc.EventFocus = EventFocus



--- @class EventListenerAcceleration
--- @brief Acceleration event listener.
--- @js NA
---@class cc.EventListenerAcceleration:cc.EventListener
local EventListenerAcceleration = {}
cc.EventListenerAcceleration = EventListenerAcceleration

---@param callback function @(std::function<void(cocos2d::Acceleration*, cocos2d::Event*)>)
---@return boolean @(bool)
function EventListenerAcceleration:init(callback)
end

--- @class EventListenerFocus
--- @brief Focus event listener.
---@class cc.EventListenerFocus:cc.EventListener
local EventListenerFocus = {}
cc.EventListenerFocus = EventListenerFocus

---@return boolean @(bool)
function EventListenerFocus:init()
end

--- @class EventListenerKeyboard
--- @brief Keyboard event listener.
--- @js cc._EventListenerKeyboard
---@class cc.EventListenerKeyboard:cc.EventListener
local EventListenerKeyboard = {}
cc.EventListenerKeyboard = EventListenerKeyboard

---@return boolean @(bool)
function EventListenerKeyboard:init()
end

--- @class EventMouse
--- @brief The mouse event.
---@class cc.EventMouse:cc.Event
local EventMouse = {}
cc.EventMouse = EventMouse

--- Get the cursor position of x axis.
---
--- @js getLocationX
---@return number @(float) The x coordinate of cursor position.
function EventMouse:getCursorX()
end

--- Get the cursor position of y axis.
---
--- @js getLocationY
---@return number @(float) The y coordinate of cursor position.
function EventMouse:getCursorY()
end

--- Returns the delta of 2 current touches locations in screen coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The delta of 2 current touches locations in screen coordinates.
function EventMouse:getDelta()
end

--- Returns the current touch location in OpenGL coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The current touch location in OpenGL coordinates.
function EventMouse:getLocation()
end

--- Returns the current touch location in screen coordinates.
---
---@return vec2_table @(cocos2d::Vec2) The current touch location in screen coordinates.
function EventMouse:getLocationInView()
end

--- Get mouse button.
---
--- @js getButton
---@return cc.EventMouse.MouseButton @(cocos2d::EventMouse::MouseButton) The mouse button.
function EventMouse:getMouseButton()
end

--- Returns the previous touch location in OpenGL coordinates.
---
--- @js NA
---@return vec2_table @(cocos2d::Vec2) The previous touch location in OpenGL coordinates.
function EventMouse:getPreviousLocation()
end

--- Returns the previous touch location in screen coordinates.
---
--- @js NA
---@return vec2_table @(cocos2d::Vec2) The previous touch location in screen coordinates.
function EventMouse:getPreviousLocationInView()
end

--- Get mouse scroll data of x axis.
---
---@return number @(float) The scroll data of x axis.
function EventMouse:getScrollX()
end

--- Get mouse scroll data of y axis.
---
---@return number @(float) The scroll data of y axis.
function EventMouse:getScrollY()
end

--- Returns the start touch location in OpenGL coordinates.
---
--- @js NA
---@return vec2_table @(cocos2d::Vec2) The start touch location in OpenGL coordinates.
function EventMouse:getStartLocation()
end

--- Returns the start touch location in screen coordinates.
---
--- @js NA
---@return vec2_table @(cocos2d::Vec2) The start touch location in screen coordinates.
function EventMouse:getStartLocationInView()
end

--- Set the cursor position.
---
--- @js setLocation
---@param x number @(float) The x coordinate of cursor position.
---@param y number @(float) The y coordinate of cursor position.
---@return self @(void)
function EventMouse:setCursorPosition(x, y)
end

--- Set mouse button.
---
--- @js setButton
---@param button cc.EventMouse.MouseButton @(cocos2d::EventMouse::MouseButton) a given mouse button.
---@return self @(void)
function EventMouse:setMouseButton(button)
end

--- Set mouse scroll data.
---
---@param scrollX number @(float) The scroll data of x axis.
---@param scrollY number @(float) The scroll data of y axis.
---@return self @(void)
function EventMouse:setScrollData(scrollX, scrollY)
end

--- @class EventListenerMouse
--- @brief Mouse event listener.
--- @js cc._EventListenerMouse
---@class cc.EventListenerMouse:cc.EventListener
local EventListenerMouse = {}
cc.EventListenerMouse = EventListenerMouse

---@return boolean @(bool)
function EventListenerMouse:init()
end

--- @class EventListenerTouchOneByOne
--- @brief Single touch event listener.
--- @js cc._EventListenerTouchOneByOne
---@class cc.EventListenerTouchOneByOne:cc.EventListener
local EventListenerTouchOneByOne = {}
cc.EventListenerTouchOneByOne = EventListenerTouchOneByOne

---@return boolean @(bool)
function EventListenerTouchOneByOne:init()
end

--- Is swall touches or not.
---
---@return boolean @(bool) True if needs to swall touches.
function EventListenerTouchOneByOne:isSwallowTouches()
end

--- Whether or not to swall touches.
---
---@param needSwallow boolean @(bool) True if needs to swall touches.
---@return self @(void)
function EventListenerTouchOneByOne:setSwallowTouches(needSwallow)
end

--- @class EventListenerTouchAllAtOnce
--- @brief Multiple touches event listener.
---@class cc.EventListenerTouchAllAtOnce:cc.EventListener
local EventListenerTouchAllAtOnce = {}
cc.EventListenerTouchAllAtOnce = EventListenerTouchAllAtOnce

---@return boolean @(bool)
function EventListenerTouchAllAtOnce:init()
end

---
---  *@brief Base class for Camera actions.
---  *@ingroup Actions
---@class cc.ActionCamera:cc.ActionInterval
local ActionCamera = {}
cc.ActionCamera = ActionCamera

---@return vec3_table @(const cocos2d::Vec3&)
function ActionCamera:getCenter()
end

---@return vec3_table @(const cocos2d::Vec3&)
function ActionCamera:getEye()
end

---@return vec3_table @(const cocos2d::Vec3&)
function ActionCamera:getUp()
end

---@param center vec3_table @(cocos2d::Vec3)
---@return self @(void)
function ActionCamera:setCenter(center)
end

---@param x number @(float)
---@param y number @(float)
---@param z number @(float)
---@return self @(void)
function ActionCamera:setEye(x, y, z)
end

---@param eye vec3_table @(cocos2d::Vec3)
---@return self @(void)
function ActionCamera:setEye(eye)
end

---@param up vec3_table @(cocos2d::Vec3)
---@return self @(void)
function ActionCamera:setUp(up)
end

--- @class OrbitCamera
---
--- @brief OrbitCamera action.
--- Orbits the camera around the center of the screen using spherical coordinates.
--- @ingroup Actions
---@class cc.OrbitCamera:cc.ActionCamera
local OrbitCamera = {}
cc.OrbitCamera = OrbitCamera

--- Initializes a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX.
---@param t number @(float)
---@param radius number @(float)
---@param deltaRadius number @(float)
---@param angleZ number @(float)
---@param deltaAngleZ number @(float)
---@param angleX number @(float)
---@param deltaAngleX number @(float)
---@return boolean @(bool)
function OrbitCamera:initWithDuration(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX)
end

--- Creates a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX.
---
--- (static)
---@param t number @(float) Duration in seconds.
---@param radius number @(float) The start radius.
---@param deltaRadius number @(float) The delta radius.
---@param angleZ number @(float) The start angle in Z.
---@param deltaAngleZ number @(float) The delta angle in Z.
---@param angleX number @(float) The start angle in X.
---@param deltaAngleX number @(float) The delta angle in X.
---@return cc.OrbitCamera @(cocos2d::OrbitCamera*) An OrbitCamera.
function OrbitCamera:create(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX)
end

--- @class CardinalSplineTo
--- Cardinal Spline path.
--- http:en.wikipedia.orgwikiCubic_Hermite_spline#Cardinal_spline
--- @ingroup Actions
---@class cc.CardinalSplineTo:cc.ActionInterval
local CardinalSplineTo = {}
cc.CardinalSplineTo = CardinalSplineTo

--- Return a PointArray.
---
---@return cc.PointArray @(cocos2d::PointArray*) A PointArray.
function CardinalSplineTo:getPoints()
end

---
--- Initializes the action with a duration and an array of points.
---
---@param duration number @(float) In seconds.
---@param points cc.PointArray @(cocos2d::PointArray*) An PointArray.
---@param tension number @(float) Goodness of fit.
---@return boolean @(bool)
function CardinalSplineTo:initWithDuration(duration, points, tension)
end

--- It will update the target position and change the _previousPosition to newPos
---
---@param newPos vec2_table @(cocos2d::Vec2) The new position.
---@return self @(void)
function CardinalSplineTo:updatePosition(newPos)
end

--- @class CardinalSplineBy
--- Cardinal Spline path.
--- http:en.wikipedia.orgwikiCubic_Hermite_spline#Cardinal_spline
--- @ingroup Actions
---@class cc.CardinalSplineBy:cc.CardinalSplineTo
local CardinalSplineBy = {}
cc.CardinalSplineBy = CardinalSplineBy



--- @class CatmullRomTo
--- An action that moves the target with a CatmullRom curve to a destination point.
--- A Catmull Rom is a Cardinal Spline with a tension of 0.5.
--- http:en.wikipedia.orgwikiCubic_Hermite_spline#Catmull.E2.80.93Rom_spline
--- @ingroup Actions
---@class cc.CatmullRomTo:cc.CardinalSplineTo
local CatmullRomTo = {}
cc.CatmullRomTo = CatmullRomTo

---
--- Initializes the action with a duration and an array of points.
---
---@param dt number @(float) In seconds.
---@param points cc.PointArray @(cocos2d::PointArray*) An PointArray.
---@return boolean @(bool)
function CatmullRomTo:initWithDuration(dt, points)
end

--- @class CatmullRomBy
--- An action that moves the target with a CatmullRom curve by a certain distance.
--- A Catmull Rom is a Cardinal Spline with a tension of 0.5.
--- http:en.wikipedia.orgwikiCubic_Hermite_spline#Catmull.E2.80.93Rom_spline
--- @ingroup Actions
---@class cc.CatmullRomBy:cc.CardinalSplineBy
local CatmullRomBy = {}
cc.CatmullRomBy = CatmullRomBy

--- Initializes the action with a duration and an array of points.
---
---@param dt number @(float) In seconds.
---@param points cc.PointArray @(cocos2d::PointArray*) An PointArray.
---@return boolean @(bool)
function CatmullRomBy:initWithDuration(dt, points)
end

---
---  @class ActionEase
---  @brief Base class for Easing actions.
---  @details Ease actions are created from other interval actions.
---  The ease action will change the timeline of the inner action.
---  @ingroup Actions
---@class cc.ActionEase:cc.ActionInterval
local ActionEase = {}
cc.ActionEase = ActionEase

---
--- @brief Get the pointer of the inner action.
--- @return The pointer of the inner action.
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function ActionEase:getInnerAction()
end

---
--- @brief Initializes the action.
--- @return Return true when the initialization success, otherwise return false.
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return boolean @(bool)
function ActionEase:initWithAction(action)
end

---
---  @class EaseRateAction
---  @brief Base class for Easing actions with rate parameters
---  @details Ease the inner action with specified rate.
---  @ingroup Actions
---@class cc.EaseRateAction:cc.ActionEase
local EaseRateAction = {}
cc.EaseRateAction = EaseRateAction

---
--- @brief Get the rate value of the ease rate action.
--- @return Return the rate value of the ease rate action.
---@return number @(float)
function EaseRateAction:getRate()
end

---
--- @brief Initializes the action with the inner action and the rate parameter.
--- @param pAction The pointer of the inner action.
--- @param fRate The value of the rate parameter.
--- @return Return true when the initialization success, otherwise return false.
---@param pAction cc.ActionInterval @(cocos2d::ActionInterval*)
---@param fRate number @(float)
---@return boolean @(bool)
function EaseRateAction:initWithAction(pAction, fRate)
end

---
--- @brief Set the rate value for the ease rate action.
--- @param rate The value will be set.
---@param rate number @(float)
---@return self @(void)
function EaseRateAction:setRate(rate)
end

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseRateAction @(cocos2d::EaseRateAction*)
function EaseRateAction:create(action, rate)
end


---@class cc.EaseExponentialIn:cc.ActionEase
local EaseExponentialIn = {}
cc.EaseExponentialIn = EaseExponentialIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseExponentialIn @(cocos2d::EaseExponentialIn*)
function EaseExponentialIn:create(action)
end


---@class cc.EaseExponentialOut:cc.ActionEase
local EaseExponentialOut = {}
cc.EaseExponentialOut = EaseExponentialOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseExponentialOut @(cocos2d::EaseExponentialOut*)
function EaseExponentialOut:create(action)
end


---@class cc.EaseExponentialInOut:cc.ActionEase
local EaseExponentialInOut = {}
cc.EaseExponentialInOut = EaseExponentialInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseExponentialInOut @(cocos2d::EaseExponentialInOut*)
function EaseExponentialInOut:create(action)
end


---@class cc.EaseSineIn:cc.ActionEase
local EaseSineIn = {}
cc.EaseSineIn = EaseSineIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseSineIn @(cocos2d::EaseSineIn*)
function EaseSineIn:create(action)
end


---@class cc.EaseSineOut:cc.ActionEase
local EaseSineOut = {}
cc.EaseSineOut = EaseSineOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseSineOut @(cocos2d::EaseSineOut*)
function EaseSineOut:create(action)
end


---@class cc.EaseSineInOut:cc.ActionEase
local EaseSineInOut = {}
cc.EaseSineInOut = EaseSineInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseSineInOut @(cocos2d::EaseSineInOut*)
function EaseSineInOut:create(action)
end

---
---  @class EaseBounce
---  @brief EaseBounce abstract class.
---  @since v0.8.2
---  @ingroup Actions
---@class cc.EaseBounce:cc.ActionEase
local EaseBounce = {}
cc.EaseBounce = EaseBounce




---@class cc.EaseBounceIn:cc.ActionEase
local EaseBounceIn = {}
cc.EaseBounceIn = EaseBounceIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBounceIn @(cocos2d::EaseBounceIn*)
function EaseBounceIn:create(action)
end


---@class cc.EaseBounceOut:cc.ActionEase
local EaseBounceOut = {}
cc.EaseBounceOut = EaseBounceOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBounceOut @(cocos2d::EaseBounceOut*)
function EaseBounceOut:create(action)
end


---@class cc.EaseBounceInOut:cc.ActionEase
local EaseBounceInOut = {}
cc.EaseBounceInOut = EaseBounceInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBounceInOut @(cocos2d::EaseBounceInOut*)
function EaseBounceInOut:create(action)
end


---@class cc.EaseBackIn:cc.ActionEase
local EaseBackIn = {}
cc.EaseBackIn = EaseBackIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBackIn @(cocos2d::EaseBackIn*)
function EaseBackIn:create(action)
end


---@class cc.EaseBackOut:cc.ActionEase
local EaseBackOut = {}
cc.EaseBackOut = EaseBackOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBackOut @(cocos2d::EaseBackOut*)
function EaseBackOut:create(action)
end


---@class cc.EaseBackInOut:cc.ActionEase
local EaseBackInOut = {}
cc.EaseBackInOut = EaseBackInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBackInOut @(cocos2d::EaseBackInOut*)
function EaseBackInOut:create(action)
end


---@class cc.EaseQuadraticActionIn:cc.ActionEase
local EaseQuadraticActionIn = {}
cc.EaseQuadraticActionIn = EaseQuadraticActionIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuadraticActionIn @(cocos2d::EaseQuadraticActionIn*)
function EaseQuadraticActionIn:create(action)
end


---@class cc.EaseQuadraticActionOut:cc.ActionEase
local EaseQuadraticActionOut = {}
cc.EaseQuadraticActionOut = EaseQuadraticActionOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuadraticActionOut @(cocos2d::EaseQuadraticActionOut*)
function EaseQuadraticActionOut:create(action)
end


---@class cc.EaseQuadraticActionInOut:cc.ActionEase
local EaseQuadraticActionInOut = {}
cc.EaseQuadraticActionInOut = EaseQuadraticActionInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuadraticActionInOut @(cocos2d::EaseQuadraticActionInOut*)
function EaseQuadraticActionInOut:create(action)
end


---@class cc.EaseQuarticActionIn:cc.ActionEase
local EaseQuarticActionIn = {}
cc.EaseQuarticActionIn = EaseQuarticActionIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuarticActionIn @(cocos2d::EaseQuarticActionIn*)
function EaseQuarticActionIn:create(action)
end


---@class cc.EaseQuarticActionOut:cc.ActionEase
local EaseQuarticActionOut = {}
cc.EaseQuarticActionOut = EaseQuarticActionOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuarticActionOut @(cocos2d::EaseQuarticActionOut*)
function EaseQuarticActionOut:create(action)
end


---@class cc.EaseQuarticActionInOut:cc.ActionEase
local EaseQuarticActionInOut = {}
cc.EaseQuarticActionInOut = EaseQuarticActionInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuarticActionInOut @(cocos2d::EaseQuarticActionInOut*)
function EaseQuarticActionInOut:create(action)
end


---@class cc.EaseQuinticActionIn:cc.ActionEase
local EaseQuinticActionIn = {}
cc.EaseQuinticActionIn = EaseQuinticActionIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuinticActionIn @(cocos2d::EaseQuinticActionIn*)
function EaseQuinticActionIn:create(action)
end


---@class cc.EaseQuinticActionOut:cc.ActionEase
local EaseQuinticActionOut = {}
cc.EaseQuinticActionOut = EaseQuinticActionOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuinticActionOut @(cocos2d::EaseQuinticActionOut*)
function EaseQuinticActionOut:create(action)
end


---@class cc.EaseQuinticActionInOut:cc.ActionEase
local EaseQuinticActionInOut = {}
cc.EaseQuinticActionInOut = EaseQuinticActionInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseQuinticActionInOut @(cocos2d::EaseQuinticActionInOut*)
function EaseQuinticActionInOut:create(action)
end


---@class cc.EaseCircleActionIn:cc.ActionEase
local EaseCircleActionIn = {}
cc.EaseCircleActionIn = EaseCircleActionIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseCircleActionIn @(cocos2d::EaseCircleActionIn*)
function EaseCircleActionIn:create(action)
end


---@class cc.EaseCircleActionOut:cc.ActionEase
local EaseCircleActionOut = {}
cc.EaseCircleActionOut = EaseCircleActionOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseCircleActionOut @(cocos2d::EaseCircleActionOut*)
function EaseCircleActionOut:create(action)
end


---@class cc.EaseCircleActionInOut:cc.ActionEase
local EaseCircleActionInOut = {}
cc.EaseCircleActionInOut = EaseCircleActionInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseCircleActionInOut @(cocos2d::EaseCircleActionInOut*)
function EaseCircleActionInOut:create(action)
end


---@class cc.EaseCubicActionIn:cc.ActionEase
local EaseCubicActionIn = {}
cc.EaseCubicActionIn = EaseCubicActionIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseCubicActionIn @(cocos2d::EaseCubicActionIn*)
function EaseCubicActionIn:create(action)
end


---@class cc.EaseCubicActionOut:cc.ActionEase
local EaseCubicActionOut = {}
cc.EaseCubicActionOut = EaseCubicActionOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseCubicActionOut @(cocos2d::EaseCubicActionOut*)
function EaseCubicActionOut:create(action)
end


---@class cc.EaseCubicActionInOut:cc.ActionEase
local EaseCubicActionInOut = {}
cc.EaseCubicActionInOut = EaseCubicActionInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseCubicActionInOut @(cocos2d::EaseCubicActionInOut*)
function EaseCubicActionInOut:create(action)
end


---@class cc.EaseIn:cc.EaseRateAction
local EaseIn = {}
cc.EaseIn = EaseIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseIn @(cocos2d::EaseIn*)
function EaseIn:create(action, rate)
end


---@class cc.EaseOut:cc.EaseRateAction
local EaseOut = {}
cc.EaseOut = EaseOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseOut @(cocos2d::EaseOut*)
function EaseOut:create(action, rate)
end


---@class cc.EaseInOut:cc.EaseRateAction
local EaseInOut = {}
cc.EaseInOut = EaseInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseInOut @(cocos2d::EaseInOut*)
function EaseInOut:create(action, rate)
end

---
---  @class EaseElastic
---  @brief Ease Elastic abstract class
---  @since v0.8.2
---  @ingroup Actions
---@class cc.EaseElastic:cc.ActionEase
local EaseElastic = {}
cc.EaseElastic = EaseElastic

---
--- @brief Get period of the wave in radians. Default value is 0.3.
--- @return Return the period of the wave in radians.
---@return number @(float)
function EaseElastic:getPeriod()
end

---
--- @brief Initializes the action with the inner action and the period in radians.
--- @param action The pointer of the inner action.
--- @param period Period of the wave in radians. Default is 0.3.
--- @return Return true when the initialization success, otherwise return false.
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param period number @(float)
---@return boolean @(bool)
function EaseElastic:initWithAction(action, period)
end

---
--- @brief Initializes the action with the inner action and the period in radians.
--- @param action The pointer of the inner action.
--- @param period Period of the wave in radians. Default is 0.3.
--- @return Return true when the initialization success, otherwise return false.
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return boolean @(bool)
function EaseElastic:initWithAction(action)
end

---
--- @brief Set period of the wave in radians.
--- @param fPeriod The value will be set.
---@param fPeriod number @(float)
---@return self @(void)
function EaseElastic:setPeriod(fPeriod)
end


---@class cc.EaseElasticIn:cc.EaseElastic
local EaseElasticIn = {}
cc.EaseElasticIn = EaseElasticIn

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseElasticIn @(cocos2d::EaseElasticIn*)
function EaseElasticIn:create(action, rate)
end

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseElasticIn @(cocos2d::EaseElasticIn*)
function EaseElasticIn:create(action)
end


---@class cc.EaseElasticOut:cc.EaseElastic
local EaseElasticOut = {}
cc.EaseElasticOut = EaseElasticOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseElasticOut @(cocos2d::EaseElasticOut*)
function EaseElasticOut:create(action, rate)
end

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseElasticOut @(cocos2d::EaseElasticOut*)
function EaseElasticOut:create(action)
end


---@class cc.EaseElasticInOut:cc.EaseElastic
local EaseElasticInOut = {}
cc.EaseElasticInOut = EaseElasticInOut

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@param rate number @(float)
---@return cc.EaseElasticInOut @(cocos2d::EaseElasticInOut*)
function EaseElasticInOut:create(action, rate)
end

--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseElasticInOut @(cocos2d::EaseElasticInOut*)
function EaseElasticInOut:create(action)
end

---
---  @class EaseBezierAction
---  @brief Ease Bezier
---  @ingroup Actions
---@class cc.EaseBezierAction:cc.ActionEase
local EaseBezierAction = {}
cc.EaseBezierAction = EaseBezierAction

---
--- @brief Set the bezier parameters.
---@param p0 number @(float)
---@param p1 number @(float)
---@param p2 number @(float)
---@param p3 number @(float)
---@return self @(void)
function EaseBezierAction:setBezierParamer(p0, p1, p2, p3)
end

---
--- @brief Create the action with the inner action.
--- @param action The pointer of the inner action.
--- @return A pointer of EaseBezierAction action. If creation failed, return nil.
--- (static)
---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.EaseBezierAction @(cocos2d::EaseBezierAction*)
function EaseBezierAction:create(action)
end

--- @class ActionInstant
--- @brief Instant actions are immediate actions. They don't have a duration like the IntervalAction actions.
---
---@class cc.ActionInstant:cc.FiniteTimeAction
local ActionInstant = {}
cc.ActionInstant = ActionInstant



--- @class Show
--- @brief Show the node.
---
---@class cc.Show:cc.ActionInstant
local Show = {}
cc.Show = Show

--- Allocates and initializes the action.
---
--- (static)
---@return cc.Show @(cocos2d::Show*)  An autoreleased Show object.
function Show:create()
end

--- @class Hide
--- @brief Hide the node.
---@class cc.Hide:cc.ActionInstant
local Hide = {}
cc.Hide = Hide

--- Allocates and initializes the action.
---
--- (static)
---@return cc.Hide @(cocos2d::Hide*) An autoreleased Hide object.
function Hide:create()
end

--- @class ToggleVisibility
--- @brief Toggles the visibility of a node.
---@class cc.ToggleVisibility:cc.ActionInstant
local ToggleVisibility = {}
cc.ToggleVisibility = ToggleVisibility

--- Allocates and initializes the action.
---
--- (static)
---@return cc.ToggleVisibility @(cocos2d::ToggleVisibility*) An autoreleased ToggleVisibility object.
function ToggleVisibility:create()
end

--- @class RemoveSelf
--- @brief Remove the node.
---@class cc.RemoveSelf:cc.ActionInstant
local RemoveSelf = {}
cc.RemoveSelf = RemoveSelf

--- init the action
---@param isNeedCleanUp boolean @(bool)
---@return boolean @(bool)
function RemoveSelf:init(isNeedCleanUp)
end

--- Create the action.
---
--- (static)
---@param isNeedCleanUp boolean @(bool) Is need to clean up, the default value is true.
---@return cc.RemoveSelf @(cocos2d::RemoveSelf*) An autoreleased RemoveSelf object.
function RemoveSelf:create(isNeedCleanUp)
end

--- Create the action.
---
--- (static)
---@return cc.RemoveSelf @(cocos2d::RemoveSelf*) An autoreleased RemoveSelf object.
function RemoveSelf:create()
end

--- @class FlipX
--- @brief Flips the sprite horizontally.
--- @since v0.99.0
---@class cc.FlipX:cc.ActionInstant
local FlipX = {}
cc.FlipX = FlipX

--- init the action
---@param x boolean @(bool)
---@return boolean @(bool)
function FlipX:initWithFlipX(x)
end

--- Create the action.
---
--- (static)
---@param x boolean @(bool) Flips the sprite horizontally if true.
---@return cc.FlipX @(cocos2d::FlipX*)  An autoreleased FlipX object.
function FlipX:create(x)
end

--- @class FlipY
--- @brief Flips the sprite vertically.
--- @since v0.99.0
---@class cc.FlipY:cc.ActionInstant
local FlipY = {}
cc.FlipY = FlipY

--- init the action
---@param y boolean @(bool)
---@return boolean @(bool)
function FlipY:initWithFlipY(y)
end

--- Create the action.
---
--- (static)
---@param y boolean @(bool) Flips the sprite vertically if true.
---@return cc.FlipY @(cocos2d::FlipY*) An autoreleased FlipY object.
function FlipY:create(y)
end

--- @class Place
--- @brief Places the node in a certain position.
---@class cc.Place:cc.ActionInstant
local Place = {}
cc.Place = Place

--- Initializes a Place action with a position
---@param pos vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function Place:initWithPosition(pos)
end

--- Creates a Place action with a position.
---
--- (static)
---@param pos vec2_table @(cocos2d::Vec2)  A certain position.
---@return cc.Place @(cocos2d::Place*)  An autoreleased Place object.
function Place:create(pos)
end

--- @class CallFunc
--- @brief Calls a 'callback'.
---@class cc.CallFunc:cc.ActionInstant
local CallFunc = {}
cc.CallFunc = CallFunc

--- Executes the callback.
---@return self @(void)
function CallFunc:execute()
end

---
--- @class GridAction
--- @brief Base class for Grid actions.
--- @details Grid actions are the actions take effect on GridBase.
---@class cc.GridAction:cc.ActionInterval
local GridAction = {}
cc.GridAction = GridAction

---
--- @brief Get the pointer of GridBase.
--- @return The pointer of GridBase.
---@return cc.GridBase @(cocos2d::GridBase*)
function GridAction:getGrid()
end

---
--- @brief Initializes the action with size and duration.
---@param duration number @(float) The duration of the GridAction. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) The size of the GridAction should be.
---@return boolean @(bool) Return true when the initialization success, otherwise return false.
function GridAction:initWithDuration(duration, gridSize)
end

---
---  @brief Base class for Grid3D actions.
---  @details Grid3D actions can modify a non-tiled grid.
---@class cc.Grid3DAction:cc.GridAction
local Grid3DAction = {}
cc.Grid3DAction = Grid3DAction

---
--- @brief Get the effect grid rect.
---@return rect_table @(cocos2d::Rect) Return the effect grid rect.
function Grid3DAction:getGridRect()
end

---
--- @brief Base class for TiledGrid3D actions.
---@class cc.TiledGrid3DAction:cc.GridAction
local TiledGrid3DAction = {}
cc.TiledGrid3DAction = TiledGrid3DAction



---
---  @brief StopGrid action.
---  @warning Don't call this action if another grid action is active.
---  Call if you want to remove the grid effect. Example:
---  @code
---  Sequence::create(Lens3D::create(...), StopGrid::create(), nullptr);
---  @endcode
---@class cc.StopGrid:cc.ActionInstant
local StopGrid = {}
cc.StopGrid = StopGrid

---
--- @brief Create a StopGrid Action.
--- @return Return a pointer of StopGrid. When the creation failed, return nil.
--- (static)
---@return cc.StopGrid @(cocos2d::StopGrid*)
function StopGrid:create()
end

---
--- @brief ReuseGrid action.
---@class cc.ReuseGrid:cc.ActionInstant
local ReuseGrid = {}
cc.ReuseGrid = ReuseGrid

---
--- @brief Initializes an action with the number of times that the current grid will be reused.
--- @param times Specify times the grid will be reused.
--- @return If the initialization success, return true; otherwise, return false.
---@param times number @(int)
---@return boolean @(bool)
function ReuseGrid:initWithTimes(times)
end

---
--- @brief Create an action with the number of times that the current grid will be reused.
--- @param times Specify times the grid will be reused.
--- @return Return a pointer of ReuseGrid. When the creation failed, return nil.
--- (static)
---@param times number @(int)
---@return cc.ReuseGrid @(cocos2d::ReuseGrid*)
function ReuseGrid:create(times)
end

---
--- @brief Waves3D action.
--- @details This action is used for take effect on the target node as 3D waves.
---         You can control the effect by these parameters:
---         duration, grid size, waves count, amplitude.
---@class cc.Waves3D:cc.Grid3DAction
local Waves3D = {}
cc.Waves3D = Waves3D

---
--- @brief Get the amplitude of the effect.
--- @return Return the amplitude of the effect.
---@return number @(float)
function Waves3D:getAmplitude()
end

---
--- @brief Get the amplitude rate of the effect.
--- @return Return the amplitude rate of the effect.
---@return number @(float)
function Waves3D:getAmplitudeRate()
end

---
--- @brief Initializes an action with duration, grid size, waves and amplitude.
--- @param duration Specify the duration of the Waves3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the Waves3D action.
--- @param amplitude Specify the amplitude of the Waves3D action.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return boolean @(bool)
function Waves3D:initWithDuration(duration, gridSize, waves, amplitude)
end

---
--- @brief Set the amplitude to the effect.
--- @param amplitude The value of amplitude will be set.
---@param amplitude number @(float)
---@return self @(void)
function Waves3D:setAmplitude(amplitude)
end

---
--- @brief Set the amplitude rate of the effect.
--- @param amplitudeRate The value of amplitude rate will be set.
---@param amplitudeRate number @(float)
---@return self @(void)
function Waves3D:setAmplitudeRate(amplitudeRate)
end

---
--- @brief Create an action with duration, grid size, waves and amplitude.
--- @param duration Specify the duration of the Waves3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the Waves3D action.
--- @param amplitude Specify the amplitude of the Waves3D action.
--- @return If the creation success, return a pointer of Waves3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return cc.Waves3D @(cocos2d::Waves3D*)
function Waves3D:create(duration, gridSize, waves, amplitude)
end

---
--- @brief FlipX3D action.
--- @details This action is used for flipping the target node on the x axis.
---@class cc.FlipX3D:cc.Grid3DAction
local FlipX3D = {}
cc.FlipX3D = FlipX3D

---
--- @brief Initializes an action with duration.
--- @param duration Specify the duration of the FlipX3D action. It's a value in seconds.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@return boolean @(bool)
function FlipX3D:initWithDuration(duration)
end

---
--- @brief Initializes an action with duration and grid size.
--- @param gridSize Specify the grid size of the FlipX3D action.
--- @param duration Specify the duration of the FlipX3D action. It's a value in seconds.
--- @return If the initialization success, return true; otherwise, return false.
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param duration number @(float)
---@return boolean @(bool)
function FlipX3D:initWithSize(gridSize, duration)
end

---
--- @brief Create the action with duration.
--- @param duration Specify the duration of the FilpX3D action. It's a value in seconds.
--- @return If the creation success, return a pointer of FilpX3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@return cc.FlipX3D @(cocos2d::FlipX3D*)
function FlipX3D:create(duration)
end

---
--- @brief FlipY3D action.
--- @details This action is used for flipping the target node on the y axis.
---@class cc.FlipY3D:cc.FlipX3D
local FlipY3D = {}
cc.FlipY3D = FlipY3D

---
--- @brief Create the action with duration.
--- @param duration Specify the duration of the FlipY3D action. It's a value in seconds.
--- @return If the creation success, return a pointer of FlipY3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@return cc.FlipY3D @(cocos2d::FlipY3D*)
function FlipY3D:create(duration)
end

---
--- @brief Lens3D action.
--- @details This action is used for take effect on the target node as lens.
---         You can create the action by these parameters:
---         duration, grid size, center position of lens, radius of lens.
---         Also you can change the lens effect value & whether effect is concave by the setter methods.
---@class cc.Lens3D:cc.Grid3DAction
local Lens3D = {}
cc.Lens3D = Lens3D

---
--- @brief Get the value of lens effect. Default value is 0.7.
--- @return The value of lens effect.
---@return number @(float)
function Lens3D:getLensEffect()
end

---
--- @brief Get the center position of lens effect.
--- @return The center position of lens effect.
---@return vec2_table @(const cocos2d::Vec2&)
function Lens3D:getPosition()
end

---
--- @brief Initializes the action with center position, radius, grid size and duration.
--- @param duration Specify the duration of the Lens3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param position Specify the center position of the lens effect.
--- @param radius Specify the radius of the lens effect.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param position vec2_table @(cocos2d::Vec2)
---@param radius number @(float)
---@return boolean @(bool)
function Lens3D:initWithDuration(duration, gridSize, position, radius)
end

---
--- @brief Set whether lens is concave.
--- @param concave Whether lens is concave.
---@param concave boolean @(bool)
---@return self @(void)
function Lens3D:setConcave(concave)
end

---
--- @brief Set the value of lens effect.
--- @param lensEffect The value of lens effect will be set.
---@param lensEffect number @(float)
---@return self @(void)
function Lens3D:setLensEffect(lensEffect)
end

---
--- @brief Set the center position of lens effect.
--- @param position The center position will be set.
---@param position vec2_table @(cocos2d::Vec2)
---@return self @(void)
function Lens3D:setPosition(position)
end

---
--- @brief Create the action with center position, radius, a grid size and duration.
--- @param duration Specify the duration of the Lens3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param position Specify the center position of the lens.
--- @param radius Specify the radius of the lens.
--- @return If the creation success, return a pointer of Lens3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param position vec2_table @(cocos2d::Vec2)
---@param radius number @(float)
---@return cc.Lens3D @(cocos2d::Lens3D*)
function Lens3D:create(duration, gridSize, position, radius)
end

---
--- @brief Ripple3D action.
--- @details This action is used for take effect on the target node as ripple.
---         You can create the action by these parameters:
---         duration, grid size, center position of ripple,
---         radius of ripple, waves count, amplitude.
---@class cc.Ripple3D:cc.Grid3DAction
local Ripple3D = {}
cc.Ripple3D = Ripple3D

---
--- @brief Get the amplitude of ripple effect.
--- @return The amplitude of ripple effect.
---@return number @(float)
function Ripple3D:getAmplitude()
end

---
--- @brief Get the amplitude rate of ripple effect.
--- @return The amplitude rate of ripple effect.
---@return number @(float)
function Ripple3D:getAmplitudeRate()
end

---
--- @brief Get the center position of ripple effect.
--- @return The center position of ripple effect.
---@return vec2_table @(const cocos2d::Vec2&)
function Ripple3D:getPosition()
end

---
--- @brief Initializes the action with center position, radius, number of waves, amplitude, a grid size and duration.
--- @param duration Specify the duration of the Ripple3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param position Specify the center position of the ripple effect.
--- @param radius Specify the radius of the ripple effect.
--- @param waves Specify the waves count of the ripple effect.
--- @param amplitude Specify the amplitude of the ripple effect.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param position vec2_table @(cocos2d::Vec2)
---@param radius number @(float)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return boolean @(bool)
function Ripple3D:initWithDuration(duration, gridSize, position, radius, waves, amplitude)
end

---
--- @brief Set the amplitude of ripple effect.
--- @param fAmplitude The amplitude of ripple effect.
---@param fAmplitude number @(float)
---@return self @(void)
function Ripple3D:setAmplitude(fAmplitude)
end

---
--- @brief Set the amplitude rate of ripple effect.
--- @param fAmplitudeRate The amplitude rate of ripple effect.
---@param fAmplitudeRate number @(float)
---@return self @(void)
function Ripple3D:setAmplitudeRate(fAmplitudeRate)
end

---
--- @brief Set the center position of ripple effect.
--- @param position The center position of ripple effect will be set.
---@param position vec2_table @(cocos2d::Vec2)
---@return self @(void)
function Ripple3D:setPosition(position)
end

---
--- @brief Create the action with center position, radius, number of waves, amplitude, a grid size and duration.
--- @param duration Specify the duration of the Ripple3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param position Specify the center position of the ripple effect.
--- @param radius Specify the radius of the ripple effect.
--- @param waves Specify the waves count of the ripple effect.
--- @param amplitude Specify the amplitude of the ripple effect.
--- @return If the creation success, return a pointer of Ripple3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param position vec2_table @(cocos2d::Vec2)
---@param radius number @(float)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return cc.Ripple3D @(cocos2d::Ripple3D*)
function Ripple3D:create(duration, gridSize, position, radius, waves, amplitude)
end

---
--- @brief Shaky3D action.
--- @details This action is used for take effect on the target node as shaky.
---         You can create the action by these parameters:
---         duration, grid size, range, whether shake on the z axis.
---@class cc.Shaky3D:cc.Grid3DAction
local Shaky3D = {}
cc.Shaky3D = Shaky3D

---
--- @brief Initializes the action with a range, shake Z vertices, grid size and duration.
--- @param duration Specify the duration of the Shaky3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param range Specify the range of the shaky effect.
--- @param shakeZ Specify whether shake on the z axis.
--- @return If the Initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param range number @(int)
---@param shakeZ boolean @(bool)
---@return boolean @(bool)
function Shaky3D:initWithDuration(duration, gridSize, range, shakeZ)
end

---
--- @brief Create the action with a range, shake Z vertices, a grid and duration.
--- @param initWithDuration Specify the duration of the Shaky3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param range Specify the range of the shaky effect.
--- @param shakeZ Specify whether shake on the z axis.
--- @return If the creation success, return a pointer of Shaky3D action; otherwise, return nil.
--- (static)
---@param initWithDuration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param range number @(int)
---@param shakeZ boolean @(bool)
---@return cc.Shaky3D @(cocos2d::Shaky3D*)
function Shaky3D:create(initWithDuration, gridSize, range, shakeZ)
end

---
--- @brief Liquid action.
--- @details This action is used for take effect on the target node as liquid.
---         You can create the action by these parameters:
---         duration, grid size, waves count, amplitude of the liquid effect.
---@class cc.Liquid:cc.Grid3DAction
local Liquid = {}
cc.Liquid = Liquid

---
--- @brief Get the amplitude of the effect.
--- @return Return the amplitude of the effect.
---@return number @(float)
function Liquid:getAmplitude()
end

---
--- @brief Get the amplitude rate of the effect.
--- @return Return the amplitude rate of the effect.
---@return number @(float)
function Liquid:getAmplitudeRate()
end

---
--- @brief Initializes the action with amplitude, grid size, waves count and duration.
--- @param duration Specify the duration of the Liquid action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the Liquid action.
--- @param amplitude Specify the amplitude of the Liquid action.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return boolean @(bool)
function Liquid:initWithDuration(duration, gridSize, waves, amplitude)
end

---
--- @brief Set the amplitude to the effect.
--- @param amplitude The value of amplitude will be set.
---@param amplitude number @(float)
---@return self @(void)
function Liquid:setAmplitude(amplitude)
end

---
--- @brief Set the amplitude rate of the effect.
--- @param amplitudeRate The value of amplitude rate will be set.
---@param amplitudeRate number @(float)
---@return self @(void)
function Liquid:setAmplitudeRate(amplitudeRate)
end

---
--- @brief Create the action with amplitude, grid size, waves count and duration.
--- @param duration Specify the duration of the Liquid action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the Liquid action.
--- @param amplitude Specify the amplitude of the Liquid action.
--- @return If the creation success, return a pointer of Liquid action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return cc.Liquid @(cocos2d::Liquid*)
function Liquid:create(duration, gridSize, waves, amplitude)
end

---
--- @brief Waves action.
--- @details This action is used for take effect on the target node as waves.
---         You can control the effect by these parameters:
---         duration, grid size, waves count, amplitude,
---         whether waves on horizontal and whether waves on vertical.
---@class cc.Waves:cc.Grid3DAction
local Waves = {}
cc.Waves = Waves

---
--- @brief Get the amplitude of the effect.
--- @return Return the amplitude of the effect.
---@return number @(float)
function Waves:getAmplitude()
end

---
--- @brief Get the amplitude rate of the effect.
--- @return Return the amplitude rate of the effect.
---@return number @(float)
function Waves:getAmplitudeRate()
end

---
--- @brief Initializes the action with amplitude, horizontal sin, vertical sin, grid size, waves count and duration.
--- @param duration Specify the duration of the Waves action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the Waves action.
--- @param amplitude Specify the amplitude of the Waves action.
--- @param horizontal Specify whether waves on horizontal.
--- @param vertical Specify whether waves on vertical.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@param horizontal boolean @(bool)
---@param vertical boolean @(bool)
---@return boolean @(bool)
function Waves:initWithDuration(duration, gridSize, waves, amplitude, horizontal, vertical)
end

---
--- @brief Set the amplitude to the effect.
--- @param amplitude The value of amplitude will be set.
---@param amplitude number @(float)
---@return self @(void)
function Waves:setAmplitude(amplitude)
end

---
--- @brief Set the amplitude rate of the effect.
--- @param amplitudeRate The value of amplitude rate will be set.
---@param amplitudeRate number @(float)
---@return self @(void)
function Waves:setAmplitudeRate(amplitudeRate)
end

---
--- @brief Create the action with amplitude, horizontal sin, vertical sin, grid size, waves count and duration.
--- @param duration Specify the duration of the Waves action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the Waves action.
--- @param amplitude Specify the amplitude of the Waves action.
--- @param horizontal Specify whether waves on horizontal.
--- @param vertical Specify whether waves on vertical.
--- @return If the creation success, return a pointer of Waves action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@param horizontal boolean @(bool)
---@param vertical boolean @(bool)
---@return cc.Waves @(cocos2d::Waves*)
function Waves:create(duration, gridSize, waves, amplitude, horizontal, vertical)
end

---
--- @brief Twirl action.
--- @details This action is used for take effect on the target node as twirl.
---         You can control the effect by these parameters:
---         duration, grid size, center position, twirls count, amplitude.
---@class cc.Twirl:cc.Grid3DAction
local Twirl = {}
cc.Twirl = Twirl

---
--- @brief Get the amplitude of the effect.
--- @return Return the amplitude of the effect.
---@return number @(float)
function Twirl:getAmplitude()
end

---
--- @brief Get the amplitude rate of the effect.
--- @return Return the amplitude rate of the effect.
---@return number @(float)
function Twirl:getAmplitudeRate()
end

---
--- @brief Get the center position of twirl action.
--- @return The center position of twirl action.
---@return vec2_table @(const cocos2d::Vec2&)
function Twirl:getPosition()
end

---
--- @brief Initializes the action with center position, number of twirls, amplitude, a grid size and duration.
--- @param duration Specify the duration of the Twirl action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param position Specify the center position of the twirl action.
--- @param twirls Specify the twirls count of the Twirl action.
--- @param amplitude Specify the amplitude of the Twirl action.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param position vec2_table @(cocos2d::Vec2)
---@param twirls number @(unsigned int)
---@param amplitude number @(float)
---@return boolean @(bool)
function Twirl:initWithDuration(duration, gridSize, position, twirls, amplitude)
end

---
--- @brief Set the amplitude to the effect.
--- @param amplitude The value of amplitude will be set.
---@param amplitude number @(float)
---@return self @(void)
function Twirl:setAmplitude(amplitude)
end

---
--- @brief Set the amplitude rate of the effect.
--- @param amplitudeRate The value of amplitude rate will be set.
---@param amplitudeRate number @(float)
---@return self @(void)
function Twirl:setAmplitudeRate(amplitudeRate)
end

---
--- @brief Set the center position of twirl action.
--- @param position The center position of twirl action will be set.
---@param position vec2_table @(cocos2d::Vec2)
---@return self @(void)
function Twirl:setPosition(position)
end

---
--- @brief Create the action with center position, number of twirls, amplitude, a grid size and duration.
--- @param duration Specify the duration of the Twirl action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param position Specify the center position of the twirl action.
--- @param twirls Specify the twirls count of the Twirl action.
--- @param amplitude Specify the amplitude of the Twirl action.
--- @return If the creation success, return a pointer of Twirl action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param position vec2_table @(cocos2d::Vec2)
---@param twirls number @(unsigned int)
---@param amplitude number @(float)
---@return cc.Twirl @(cocos2d::Twirl*)
function Twirl:create(duration, gridSize, position, twirls, amplitude)
end

--- @class ActionManager
---  @brief ActionManager is a singleton that manages all the actions.
---  Normally you won't need to use this singleton directly. 99% of the cases you will use the Node interface,
---  which uses this singleton.
---  But there are some cases where you might need to use this singleton.
---  Examples:
---     - When you want to run an action where the target is different from a Node.
---     - When you want to pause resume the actions.
---
---  @since v0.8
---@class cc.ActionManager:cc.Ref
local ActionManager = {}
cc.ActionManager = ActionManager

--- Adds an action with a target.
--- If the target is already present, then the action will be added to the existing target.
--- If the target is not present, a new instance of this target will be created either paused or not, and the action
--- will be added to the newly created target. When the target is paused, the queued actions won't be 'ticked'.
---
---@param action cc.Action @(cocos2d::Action*)    A certain action.
---@param target cc.Node @(cocos2d::Node*)    The target which need to be added an action.
---@param paused boolean @(bool)    Is the target paused or not.
---@return self @(void)
function ActionManager:addAction(action, target, paused)
end

--- Gets an action given its tag an a target.
---
---@param tag number @(int)       The action's tag.
---@param target cc.Node @(const cocos2d::Node*)    A certain target.
---@return cc.Action @(cocos2d::Action*)  The Action the with the given tag.
function ActionManager:getActionByTag(tag, target)
end

--- Returns the numbers of actions that are running in all targets.
--- @js NA
---@return number @(ssize_t)  The numbers of actions that are running in all target.
function ActionManager:getNumberOfRunningActions()
end

--- Returns the numbers of actions that are running in a certain target.
--- Composable actions are counted as 1 action. Example:
--- - If you are running 1 Sequence of 7 actions, it will return 1.
--- - If you are running 7 Sequences of 2 actions, it will return 7.
---
--- @js NA
---@param target cc.Node @(const cocos2d::Node*)    A certain target.
---@return number @(ssize_t)  The numbers of actions that are running in a certain target.
function ActionManager:getNumberOfRunningActionsInTarget(target)
end

--- Returns the numbers of actions that are running in a
--- certain target with a specific tag.
--- Like getNumberOfRunningActionsInTarget Composable actions
--- are counted as 1 action. Example:
--- - If you are running 1 Sequence of 7 actions, it will return 1.
--- - If you are running 7 Sequences of 2 actions, it will return 7.
---
--- with a specific tag.
--- @see getNumberOfRunningActionsInTarget
--- @js NA
---@param target cc.Node @(const cocos2d::Node*)    A certain target.
---@param tag number @(int)       Tag that will be searched.
---@return number @(size_t)  The numbers of actions that are running in a certain target
function ActionManager:getNumberOfRunningActionsInTargetByTag(target, tag)
end

--- Pauses all running actions, returning a list of targets whose actions were paused.
---
---@return cc.Node [] @(cocos2d::Vector<cocos2d::Node *>)  A list of targets whose actions were paused.
function ActionManager:pauseAllRunningActions()
end

--- Pauses the target: all running actions and newly added actions will be paused.
---
---@param target cc.Node @(cocos2d::Node*)    A certain target.
---@return self @(void)
function ActionManager:pauseTarget(target)
end

--- Removes an action given an action reference.
---
---@param action cc.Action @(cocos2d::Action*)    A certain target.
---@return self @(void)
function ActionManager:removeAction(action)
end

--- Removes an action given its tag and the target.
---
---@param tag number @(int)       The action's tag.
---@param target cc.Node @(cocos2d::Node*)    A certain target.
---@return self @(void)
function ActionManager:removeActionByTag(tag, target)
end

--- Removes all actions matching at least one bit in flags and the target.
---
--- @js NA
---@param flags number @(unsigned int)     The flag field to match the actions' flags based on bitwise AND.
---@param target cc.Node @(cocos2d::Node*)    A certain target.
---@return self @(void)
function ActionManager:removeActionsByFlags(flags, target)
end

--- Removes all actions from all the targets.
---@return self @(void)
function ActionManager:removeAllActions()
end

--- Removes all actions given its tag and the target.
---
--- @js NA
---@param tag number @(int)       The actions' tag.
---@param target cc.Node @(cocos2d::Node*)    A certain target.
---@return self @(void)
function ActionManager:removeAllActionsByTag(tag, target)
end

--- Removes all actions from a certain target.
--- All the actions that belongs to the target will be removed.
---
---@param target cc.Node @(cocos2d::Node*)    A certain target.
---@return self @(void)
function ActionManager:removeAllActionsFromTarget(target)
end

--- Resumes the target. All queued actions will be resumed.
---
---@param target cc.Node @(cocos2d::Node*)    A certain target.
---@return self @(void)
function ActionManager:resumeTarget(target)
end

--- Resume a set of targets (convenience function to reverse a pauseAllRunningActions call).
---
---@param targetsToResume cc.Node [] @(cocos2d::Vector<cocos2d::Node *>)   A set of targets need to be resumed.
---@return self @(void)
function ActionManager:resumeTargets(targetsToResume)
end

--- Main loop of ActionManager.
---@param dt number @(float)    In seconds.
---@return self @(void)
function ActionManager:update(dt)
end

---
---  @brief This action simulates a page turn from the bottom right hand corner of the screen.
---
---  @details It's not much use by itself but is used by the PageTurnTransition.
---          Based on an original paper by L Hong et al.
---          http:www.parc.compublication1638turning-pages-of-3d-electronic-books.html
---
---  @since v0.8.2
---@class cc.PageTurn3D:cc.Grid3DAction
local PageTurn3D = {}
cc.PageTurn3D = PageTurn3D

---
--- @brief Create an action with duration, grid size.
--- @param duration Specify the duration of the PageTurn3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @return If the creation success, return a pointer of PageTurn3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@return cc.PageTurn3D @(cocos2d::PageTurn3D*)
function PageTurn3D:create(duration, gridSize)
end

---
--- @brief Progress to percentage.
--- @details This action show the target node from current percentage to the specified percentage.
---         You should specify the destination percentage when creating the action.
--- @since v0.99.1
---@class cc.ProgressTo:cc.ActionInterval
local ProgressTo = {}
cc.ProgressTo = ProgressTo

---
--- @brief Initializes with a duration and destination percentage.
---@param duration number @(float) Specify the duration of the ProgressTo action. It's a value in seconds.
---@param percent number @(float) Specify the destination percentage.
---@return boolean @(bool) If the creation success, return true; otherwise, return false.
function ProgressTo:initWithDuration(duration, percent)
end

---
--- @brief Create and initializes with a duration and a destination percentage.
--- (static)
---@param duration number @(float) Specify the duration of the ProgressTo action. It's a value in seconds.
---@param percent number @(float) Specify the destination percentage.
---@return cc.ProgressTo @(cocos2d::ProgressTo*) If the creation success, return a pointer of ProgressTo action; otherwise, return nil.
function ProgressTo:create(duration, percent)
end

---
--- @brief Progress from a percentage to another percentage.
--- @since v0.99.1
---@class cc.ProgressFromTo:cc.ActionInterval
local ProgressFromTo = {}
cc.ProgressFromTo = ProgressFromTo

---
--- @brief Initializes the action with a duration, a "from" percentage and a "to" percentage.
---@param duration number @(float) Specify the duration of the ProgressFromTo action. It's a value in seconds.
---@param fromPercentage number @(float) Specify the source percentage.
---@param toPercentage number @(float) Specify the destination percentage.
---@return boolean @(bool) If the creation success, return true; otherwise, return false.
function ProgressFromTo:initWithDuration(duration, fromPercentage, toPercentage)
end

---
--- @brief Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
--- (static)
---@param duration number @(float) Specify the duration of the ProgressFromTo action. It's a value in seconds.
---@param fromPercentage number @(float) Specify the source percentage.
---@param toPercentage number @(float) Specify the destination percentage.
---@return cc.ProgressFromTo @(cocos2d::ProgressFromTo*) If the creation success, return a pointer of ProgressFromTo action; otherwise, return nil.
function ProgressFromTo:create(duration, fromPercentage, toPercentage)
end

---
--- @brief ShakyTiles3D action.
--- @details This action is make the target node shake with many tiles.
---         You can create the action by these parameters:
---         duration, grid size, range, whether shake on the z axis.
---@class cc.ShakyTiles3D:cc.TiledGrid3DAction
local ShakyTiles3D = {}
cc.ShakyTiles3D = ShakyTiles3D

---
--- @brief Initializes the action with a range, shake Z vertices, grid size and duration.
--- @param duration Specify the duration of the ShakyTiles3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param range Specify the range of the shaky effect.
--- @param shakeZ Specify whether shake on the z axis.
--- @return If the Initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param range number @(int)
---@param shakeZ boolean @(bool)
---@return boolean @(bool)
function ShakyTiles3D:initWithDuration(duration, gridSize, range, shakeZ)
end

---
--- @brief Create the action with a range, shake Z vertices, a grid and duration.
--- @param duration Specify the duration of the ShakyTiles3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param range Specify the range of the shaky effect.
--- @param shakeZ Specify whether shake on the z axis.
--- @return If the creation success, return a pointer of ShakyTiles3D action; otherwise, return nil.
--- (static)
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param range number @(int)
---@param shakeZ boolean @(bool)
---@return cc.ShakyTiles3D @(cocos2d::ShakyTiles3D*)
function ShakyTiles3D:create(duration, gridSize, range, shakeZ)
end

---
--- @brief ShatteredTiles3D action.
--- @details This action make the target node shattered with many tiles.
---         You can create the action by these parameters:
---         duration, grid size, range, whether shatter on the z axis.
---@class cc.ShatteredTiles3D:cc.TiledGrid3DAction
local ShatteredTiles3D = {}
cc.ShatteredTiles3D = ShatteredTiles3D

---
--- @brief Initializes the action with a range, shatter Z vertices, grid size and duration.
--- @param duration Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param range Specify the range of the shatter effect.
--- @param shatterZ Specify whether shake on the z axis.
--- @return If the Initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param range number @(int)
---@param shatterZ boolean @(bool)
---@return boolean @(bool)
function ShatteredTiles3D:initWithDuration(duration, gridSize, range, shatterZ)
end

---
--- @brief Create the action with a range, whether of not to shatter Z vertices, grid size and duration.
--- (static)
---@param duration number @(float) Specify the duration of the ShatteredTiles3D action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param range number @(int) Specify the range of the shatter effect.
---@param shatterZ boolean @(bool) Specify whether shatter on the z axis.
---@return cc.ShatteredTiles3D @(cocos2d::ShatteredTiles3D*) If the creation success, return a pointer of ShatteredTiles3D action; otherwise, return nil.
function ShatteredTiles3D:create(duration, gridSize, range, shatterZ)
end

---
--- @brief ShuffleTiles action.
--- @details This action make the target node shuffle with many tiles in random order.
---         You can create the action by these parameters:
---         duration, grid size, the random seed.
---@class cc.ShuffleTiles:cc.TiledGrid3DAction
local ShuffleTiles = {}
cc.ShuffleTiles = ShuffleTiles

---@param pos vec2_table @(cocos2d::Vec2)
---@return vec2_table @(cocos2d::Vec2)
function ShuffleTiles:getDelta(pos)
end

---
--- @brief Initializes the action with grid size, random seed and duration.
---@param duration number @(float) Specify the duration of the ShuffleTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param seed number @(unsigned int) Specify the random seed.
---@return boolean @(bool) If the Initialization success, return true; otherwise, return false.
function ShuffleTiles:initWithDuration(duration, gridSize, seed)
end

---
--- @brief Create the action with grid size, random seed and duration.
--- (static)
---@param duration number @(float) Specify the duration of the ShuffleTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param seed number @(unsigned int) Specify the random seed.
---@return cc.ShuffleTiles @(cocos2d::ShuffleTiles*) If the creation success, return a pointer of ShuffleTiles action; otherwise, return nil.
function ShuffleTiles:create(duration, gridSize, seed)
end

---
--- @brief FadeOutTRTiles action.
--- @details Fades out the target node with many tiles from Bottom-Left to Top-Right.
---@class cc.FadeOutTRTiles:cc.TiledGrid3DAction
local FadeOutTRTiles = {}
cc.FadeOutTRTiles = FadeOutTRTiles

---
--- @brief Calculate the percentage a tile should be shown.
--- @param pos The position index of the tile.
--- @param time The current percentage of the action.
--- @return Return the percentage the tile should be shown.
---@param pos vec2_table @(cocos2d::Vec2)
---@param time number @(float)
---@return number @(float)
function FadeOutTRTiles:testFunc(pos, time)
end

---
--- @brief Show part of the tile.
--- @param pos The position index of the tile should be shown.
--- @param distance The percentage that the tile should be shown.
---@param pos vec2_table @(cocos2d::Vec2)
---@param distance number @(float)
---@return self @(void)
function FadeOutTRTiles:transformTile(pos, distance)
end

---
--- @brief Hide the tile at specified position.
--- @param pos The position index of the tile should be hide.
---@param pos vec2_table @(cocos2d::Vec2)
---@return self @(void)
function FadeOutTRTiles:turnOffTile(pos)
end

---
--- @brief Show the tile at specified position.
--- @param pos The position index of the tile should be shown.
---@param pos vec2_table @(cocos2d::Vec2)
---@return self @(void)
function FadeOutTRTiles:turnOnTile(pos)
end

---
--- @brief Create the action with the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the FadeOutTRTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@return cc.FadeOutTRTiles @(cocos2d::FadeOutTRTiles*) If the creation success, return a pointer of FadeOutTRTiles action; otherwise, return nil.
function FadeOutTRTiles:create(duration, gridSize)
end

---
--- @brief FadeOutBLTiles action.
--- @details Fades out the target node with many tiles from Top-Right to Bottom-Left.
---@class cc.FadeOutBLTiles:cc.FadeOutTRTiles
local FadeOutBLTiles = {}
cc.FadeOutBLTiles = FadeOutBLTiles

---
--- @brief Create the action with the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the FadeOutBLTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@return cc.FadeOutBLTiles @(cocos2d::FadeOutBLTiles*) If the creation success, return a pointer of FadeOutBLTiles action; otherwise, return nil.
function FadeOutBLTiles:create(duration, gridSize)
end

---
--- @brief FadeOutUpTiles action.
--- @details Fades out the target node with many tiles from bottom to top.
---@class cc.FadeOutUpTiles:cc.FadeOutTRTiles
local FadeOutUpTiles = {}
cc.FadeOutUpTiles = FadeOutUpTiles

---
--- @brief Create the action with the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the FadeOutUpTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@return cc.FadeOutUpTiles @(cocos2d::FadeOutUpTiles*) If the creation success, return a pointer of FadeOutUpTiles action; otherwise, return nil.
function FadeOutUpTiles:create(duration, gridSize)
end

---
--- @brief FadeOutDownTiles action.
--- @details Fades out the target node with many tiles from top to bottom.
---@class cc.FadeOutDownTiles:cc.FadeOutUpTiles
local FadeOutDownTiles = {}
cc.FadeOutDownTiles = FadeOutDownTiles

---
--- @brief Create the action with the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the FadeOutDownTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@return cc.FadeOutDownTiles @(cocos2d::FadeOutDownTiles*) If the creation success, return a pointer of FadeOutDownTiles action; otherwise, return nil.
function FadeOutDownTiles:create(duration, gridSize)
end

---
--- @brief TurnOffTiles action.
--- @details Turn off the target node with many tiles in random order.
---@class cc.TurnOffTiles:cc.TiledGrid3DAction
local TurnOffTiles = {}
cc.TurnOffTiles = TurnOffTiles

---
--- @brief Initializes the action with grid size, random seed and duration.
---@param duration number @(float) Specify the duration of the TurnOffTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param seed number @(unsigned int) Specify the random seed.
---@return boolean @(bool) If the Initialization success, return true; otherwise, return false.
function TurnOffTiles:initWithDuration(duration, gridSize, seed)
end

---
--- @brief Hide the tile at specified position.
--- @param pos The position index of the tile should be hide.
---@param pos vec2_table @(cocos2d::Vec2)
---@return self @(void)
function TurnOffTiles:turnOffTile(pos)
end

---
--- @brief Show the tile at specified position.
--- @param pos The position index of the tile should be shown.
---@param pos vec2_table @(cocos2d::Vec2)
---@return self @(void)
function TurnOffTiles:turnOnTile(pos)
end

---
--- @brief Create the action with the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the TurnOffTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param seed number @(unsigned int) Specify the random seed.
---@return cc.TurnOffTiles @(cocos2d::TurnOffTiles*) If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
function TurnOffTiles:create(duration, gridSize, seed)
end

---
--- @brief Create the action with the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the TurnOffTiles action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@return cc.TurnOffTiles @(cocos2d::TurnOffTiles*) If the creation success, return a pointer of TurnOffTiles action; otherwise, return nil.
function TurnOffTiles:create(duration, gridSize)
end

---
--- @brief WavesTiles3D action.
--- @details This action wave the target node with many tiles.
---@class cc.WavesTiles3D:cc.TiledGrid3DAction
local WavesTiles3D = {}
cc.WavesTiles3D = WavesTiles3D

---
--- @brief Get the amplitude of the effect.
--- @return Return the amplitude of the effect.
---@return number @(float)
function WavesTiles3D:getAmplitude()
end

---
--- @brief Get the amplitude rate of the effect.
--- @return Return the amplitude rate of the effect.
---@return number @(float)
function WavesTiles3D:getAmplitudeRate()
end

---
--- @brief Initializes an action with duration, grid size, waves count and amplitude.
--- @param duration Specify the duration of the WavesTiles3D action. It's a value in seconds.
--- @param gridSize Specify the size of the grid.
--- @param waves Specify the waves count of the WavesTiles3D action.
--- @param amplitude Specify the amplitude of the WavesTiles3D action.
--- @return If the initialization success, return true; otherwise, return false.
---@param duration number @(float)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param waves number @(unsigned int)
---@param amplitude number @(float)
---@return boolean @(bool)
function WavesTiles3D:initWithDuration(duration, gridSize, waves, amplitude)
end

---
--- @brief Set the amplitude to the effect.
--- @param amplitude The value of amplitude will be set.
---@param amplitude number @(float)
---@return self @(void)
function WavesTiles3D:setAmplitude(amplitude)
end

---
--- @brief Set the amplitude rate of the effect.
--- @param amplitudeRate The value of amplitude rate will be set.
---@param amplitudeRate number @(float)
---@return self @(void)
function WavesTiles3D:setAmplitudeRate(amplitudeRate)
end

---
--- @brief Create the action with a number of waves, the waves amplitude, the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the WavesTiles3D action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param waves number @(unsigned int) Specify the waves count of the WavesTiles3D action.
---@param amplitude number @(float) Specify the amplitude of the WavesTiles3D action.
---@return cc.WavesTiles3D @(cocos2d::WavesTiles3D*) If the creation success, return a pointer of WavesTiles3D action; otherwise, return nil.
function WavesTiles3D:create(duration, gridSize, waves, amplitude)
end

---
--- @brief JumpTiles3D action.
--- @details Move the tiles of a target node across the Z axis.
---@class cc.JumpTiles3D:cc.TiledGrid3DAction
local JumpTiles3D = {}
cc.JumpTiles3D = JumpTiles3D

---
--- @brief Get the amplitude of the effect.
--- @return Return the amplitude of the effect.
---@return number @(float)
function JumpTiles3D:getAmplitude()
end

---
--- @brief Get the amplitude rate of the effect.
--- @return Return the amplitude rate of the effect.
---@return number @(float)
function JumpTiles3D:getAmplitudeRate()
end

---
--- @brief Initializes the action with the number of jumps, the sin amplitude, the grid size and the duration.
---@param duration number @(float) Specify the duration of the JumpTiles3D action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param numberOfJumps number @(unsigned int) Specify the jump tiles count.
---@param amplitude number @(float) Specify the amplitude of the JumpTiles3D action.
---@return boolean @(bool) If the initialization success, return true; otherwise, return false.
function JumpTiles3D:initWithDuration(duration, gridSize, numberOfJumps, amplitude)
end

---
--- @brief Set the amplitude to the effect.
--- @param amplitude The value of amplitude will be set.
---@param amplitude number @(float)
---@return self @(void)
function JumpTiles3D:setAmplitude(amplitude)
end

---
--- @brief Set the amplitude rate of the effect.
--- @param amplitudeRate The value of amplitude rate will be set.
---@param amplitudeRate number @(float)
---@return self @(void)
function JumpTiles3D:setAmplitudeRate(amplitudeRate)
end

---
--- @brief Create the action with the number of jumps, the sin amplitude, the grid size and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the JumpTiles3D action. It's a value in seconds.
---@param gridSize vec2_table @(cocos2d::Vec2) Specify the size of the grid.
---@param numberOfJumps number @(unsigned int) Specify the jump tiles count.
---@param amplitude number @(float) Specify the amplitude of the JumpTiles3D action.
---@return cc.JumpTiles3D @(cocos2d::JumpTiles3D*) If the creation success, return a pointer of JumpTiles3D action; otherwise, return nil.
function JumpTiles3D:create(duration, gridSize, numberOfJumps, amplitude)
end

---
--- @brief SplitRows action.
--- @details Split the target node in many rows.
---         Then move out some rows from left, move out the other rows from right.
---@class cc.SplitRows:cc.TiledGrid3DAction
local SplitRows = {}
cc.SplitRows = SplitRows

---
--- @brief Initializes the action with the number rows and the duration.
---@param duration number @(float) Specify the duration of the SplitRows action. It's a value in seconds.
---@param rows number @(unsigned int) Specify the rows count should be split.
---@return boolean @(bool) If the creation success, return true; otherwise, return false.
function SplitRows:initWithDuration(duration, rows)
end

---
--- @brief Create the action with the number of rows and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the SplitRows action. It's a value in seconds.
---@param rows number @(unsigned int) Specify the rows count should be split.
---@return cc.SplitRows @(cocos2d::SplitRows*) If the creation success, return a pointer of SplitRows action; otherwise, return nil.
function SplitRows:create(duration, rows)
end

---
--- @brief SplitCols action.
--- @details Split the target node in many columns.
---         Then move out some columns from top, move out the other columns from bottom.
---@class cc.SplitCols:cc.TiledGrid3DAction
local SplitCols = {}
cc.SplitCols = SplitCols

---
--- @brief Initializes the action with the number columns and the duration.
---@param duration number @(float) Specify the duration of the SplitCols action. It's a value in seconds.
---@param cols number @(unsigned int) Specify the columns count should be split.
---@return boolean @(bool) If the creation success, return true; otherwise, return false.
function SplitCols:initWithDuration(duration, cols)
end

---
--- @brief Create the action with the number of columns and the duration.
--- (static)
---@param duration number @(float) Specify the duration of the SplitCols action. It's a value in seconds.
---@param cols number @(unsigned int) Specify the columns count should be split.
---@return cc.SplitCols @(cocos2d::SplitCols*) If the creation success, return a pointer of SplitCols action; otherwise, return nil.
function SplitCols:create(duration, cols)
end

--- ActionTween
---
---  ActionTween is an action that lets you update any property of an object.
---  For example, if you want to modify the "width" property of a target from 200 to 300 in 2 seconds, then:
---
---  @code
---      auto modifyWidth = ActionTween::create(2, "width", 200, 300);
---      target->runAction(modifyWidth);
---  @endcode
---
---  Another example: ScaleTo action could be rewritten using PropertyAction:
---
---  @code
---  scaleA and scaleB are equivalents
---      auto scaleA = ScaleTo::create(2, 3); (duration, to)
---      auto scaleB = ActionTween::create(2, "scale", 1, 3); (duration, key, from, to)
---  @endcode
---
---  @since v0.99.2
---@class cc.ActionTween:cc.ActionInterval
local ActionTween = {}
cc.ActionTween = ActionTween

---
--- @brief Initializes the action with the property name (key), and the from and to parameters.
---@param duration number @(float) The duration of the ActionTween. It's a value in seconds.
---@param key string @(std::string_view) The key of property which should be updated.
---@param from number @(float) The value of the specified property when the action begin.
---@param to number @(float) The value of the specified property when the action end.
---@return boolean @(bool) If the initialization success, return true; otherwise, return false.
function ActionTween:initWithDuration(duration, key, from, to)
end

---
--- @brief Create and initializes the action with the property name (key), and the from and to parameters.
--- (static)
---@param duration number @(float) The duration of the ActionTween. It's a value in seconds.
---@param key string @(std::string_view) The key of property which should be updated.
---@param from number @(float) The value of the specified property when the action begin.
---@param to number @(float) The value of the specified property when the action end.
---@return cc.ActionTween @(cocos2d::ActionTween*) If the creation success, return a pointer of ActionTween; otherwise, return nil.
function ActionTween:create(duration, key, from, to)
end

--- @brief AtlasNode is a subclass of Node that implements the RGBAProtocol and TextureProtocol protocol.
--- It knows how to render a TextureAtlas object.
--- If you are going to render a TextureAtlas consider subclassing AtlasNode (or a subclass of AtlasNode).
--- All features from Node are valid, plus the following features:
--- - opacity and RGB colors.
---@class cc.AtlasNode:cc.Node
local AtlasNode = {}
cc.AtlasNode = AtlasNode

---
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function AtlasNode:getBlendFunc()
end

---@return number @(size_t)
function AtlasNode:getQuadsToDraw()
end

---@return cc.Texture2D @(cocos2d::Texture2D*)
function AtlasNode:getTexture()
end

--- Return the buffer manager of the texture vertex.
---
---@return cc.TextureAtlas @(cocos2d::TextureAtlas*) Return A TextureAtlas.
function AtlasNode:getTextureAtlas()
end

--- Initializes an AtlasNode  with a texture the width and height of each item measured in points and the quantity
--- of items to render
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param tileWidth number @(int)
---@param tileHeight number @(int)
---@param itemsToRender number @(int)
---@return boolean @(bool)
function AtlasNode:initWithTexture(texture, tileWidth, tileHeight, itemsToRender)
end

--- Initializes an AtlasNode  with an Atlas file the width and height of each item and the quantity of items to
--- render
---@param tile string @(std::string_view)
---@param tileWidth number @(int)
---@param tileHeight number @(int)
---@param itemsToRender number @(int)
---@return boolean @(bool)
function AtlasNode:initWithTileFile(tile, tileWidth, tileHeight, itemsToRender)
end

---
--- @code
--- When this function bound into js or lua,the parameter will be changed
--- In js: var setBlendFunc(var src, var dst)
--- @endcode
--- @lua NA
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function AtlasNode:setBlendFunc(blendFunc)
end

---@param quadsToDraw number @(ssize_t)
---@return self @(void)
function AtlasNode:setQuadsToDraw(quadsToDraw)
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function AtlasNode:setTexture(texture)
end

--- Set an buffer manager of the texture vertex.
---@param textureAtlas cc.TextureAtlas @(cocos2d::TextureAtlas*)
---@return self @(void)
function AtlasNode:setTextureAtlas(textureAtlas)
end

--- updates the Atlas (indexed vertex array).
--- Shall be overridden in subclasses.
---@return self @(void)
function AtlasNode:updateAtlasValues()
end

--- creates a AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render.
---
--- (static)
---@param filename string @(std::string_view) The path of Atlas file.
---@param tileWidth number @(int) The width of the item.
---@param tileHeight number @(int) The height of the item.
---@param itemsToRender number @(int) The quantity of items to render.
---@return cc.AtlasNode @(cocos2d::AtlasNode*)
function AtlasNode:create(filename, tileWidth, tileHeight, itemsToRender)
end

---
---  @addtogroup _2d
---  @{
---
---  ClippingNode is a subclass of Node.
--- It draws its content (children) clipped using a stencil.
--- The stencil is an other Node that will not be drawn.
--- The clipping is done using the alpha part of the stencil (adjusted with an alphaThreshold).
---@class cc.ClippingNode:cc.Node
local ClippingNode = {}
cc.ClippingNode = ClippingNode

--- The alpha threshold.
--- The content is drawn only where the stencil have pixel with alpha greater than the alphaThreshold.
--- Should be a float between 0 and 1.
--- This default to 1 (so alpha test is disabled).
---
---@return number @(float) The alpha threshold value,Should be a float between 0 and 1.
function ClippingNode:getAlphaThreshold()
end

--- The Node to use as a stencil to do the clipping.
--- The stencil node will be retained.
--- This default to nil.
---
---@return cc.Node @(cocos2d::Node*) The stencil node.
function ClippingNode:getStencil()
end

--- If stencil has no children it will not be drawn.
--- If you have custom stencil-based node with stencil drawing mechanics other then children-based,
--- then this method should return true every time you wish stencil to be visited.
--- By default returns true if has any children attached.
---
--- then this method should return true every time you wish stencil to be visited.
--- By default returns true if has any children attached.
--- @js NA
---@return boolean @(bool) If you have custom stencil-based node with stencil drawing mechanics other then children-based,
function ClippingNode:hasContent()
end

--- Initializes a clipping node with an other node as its stencil.
--- The stencil node will be retained, and its parent will be set to this clipping node.
---@param stencil cc.Node @(cocos2d::Node*)
---@return boolean @(bool)
function ClippingNode:init(stencil)
end

--- Inverted. If this is set to true,
--- the stencil is inverted, so the content is drawn where the stencil is NOT drawn.
--- This default to false.
---
---@return boolean @(bool) If the clippingNode is Inverted, it will be return true.
function ClippingNode:isInverted()
end

--- Set the alpha threshold.
---
---@param alphaThreshold number @(float) The alpha threshold.
---@return self @(void)
function ClippingNode:setAlphaThreshold(alphaThreshold)
end

--- Set the ClippingNode whether or not invert.
---
---@param inverted boolean @(bool) A bool Type,to set the ClippingNode whether or not invert.
---@return self @(void)
function ClippingNode:setInverted(inverted)
end

--- Set the Node to use as a stencil to do the clipping.
---
---@param stencil cc.Node @(cocos2d::Node*) The Node to use as a stencil to do the clipping.
---@return self @(void)
function ClippingNode:setStencil(stencil)
end

--- Creates and initializes a clipping node with an other node as its stencil.
--- The stencil node will be retained.
--- (static)
---@param stencil cc.Node @(cocos2d::Node*) The stencil node.
---@return cc.ClippingNode @(cocos2d::ClippingNode*)
function ClippingNode:create(stencil)
end

--- Creates and initializes a clipping node without a stencil.
---
--- (static)
---@return cc.ClippingNode @(cocos2d::ClippingNode*) An autorelease ClippingNode.
function ClippingNode:create()
end

---
--- @brief Clipping Rectangle Node.
--- @details A node that clipped with specified rectangle.
---  The region of ClippingRectangleNode doesn't support any transform except scale.
--- @js NA
---@class cc.ClippingRectangleNode:cc.Node
local ClippingRectangleNode = {}
cc.ClippingRectangleNode = ClippingRectangleNode

---
--- @brief Get the clipping rectangle.
--- @return The clipping rectangle.
---@return rect_table @(const cocos2d::Rect&)
function ClippingRectangleNode:getClippingRegion()
end

---
--- @brief Get whether the clipping is enabled or not.
--- @return Whether the clipping is enabled or not. Default is true.
---@return boolean @(bool)
function ClippingRectangleNode:isClippingEnabled()
end

---
--- @brief EnableDisable the clipping.
--- @param enabled Pass true to enable clipping. Pass false to disable clipping.
---@param enabled boolean @(bool)
---@return self @(void)
function ClippingRectangleNode:setClippingEnabled(enabled)
end

---
--- @brief Set the clipping rectangle.
--- @param clippingRegion Specify the clipping rectangle.
---@param clippingRegion rect_table @(cocos2d::Rect)
---@return self @(void)
function ClippingRectangleNode:setClippingRegion(clippingRegion)
end

---
--- @brief Create node with specified clipping region.
--- @param clippingRegion Specify the clipping rectangle.
--- @return If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
--- (static)
---@param clippingRegion rect_table @(cocos2d::Rect)
---@return cc.ClippingRectangleNode @(cocos2d::ClippingRectangleNode*)
function ClippingRectangleNode:create(clippingRegion)
end

---
--- @brief Create a clipping rectangle node.
--- @return If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
--- (static)
---@return cc.ClippingRectangleNode @(cocos2d::ClippingRectangleNode*)
function ClippingRectangleNode:create()
end

--- @class DrawNode
--- @brief Node that draws dots, segments and polygons.
--- Faster than the "drawing primitives" since they draws everything in one single batch.
--- @since v2.1
---@class cc.DrawNode:cc.Node
local DrawNode = {}
cc.DrawNode = DrawNode

--- Clear the geometry in the node's buffer.
---@return self @(void)
function DrawNode:clear()
end

--- Draws a circle given the center, radius and number of segments.
---
---@param center vec2_table @(cocos2d::Vec2) The circle center point.
---@param radius number @(float) The circle rotate of radius.
---@param angle number @(float)  The circle angle.
---@param segments number @(unsigned int) The number of segments.
---@param drawLineToCenter boolean @(bool) Whether or not draw the line from the origin to center.
---@param scaleX number @(float) The scale value in x.
---@param scaleY number @(float) The scale value in y.
---@param color color4b_table @(cocos2d::Color4B) Set the circle color.
---@return self @(void)
function DrawNode:drawCircle(center, radius, angle, segments, drawLineToCenter, scaleX, scaleY, color)
end

--- Draws a circle given the center, radius and number of segments.
---
---@param center vec2_table @(cocos2d::Vec2) The circle center point.
---@param radius number @(float) The circle rotate of radius.
---@param angle number @(float)  The circle angle.
---@param segments number @(unsigned int) The number of segments.
---@param drawLineToCenter boolean @(bool) Whether or not draw the line from the origin to center.
---@param color color4b_table @(cocos2d::Color4B) Set the circle color.
---@return self @(void)
function DrawNode:drawCircle(center, radius, angle, segments, drawLineToCenter, color)
end

--- Draw a cubic bezier curve with color and number of segments
---
---@param origin vec2_table @(cocos2d::Vec2) The origin of the bezier path.
---@param control1 vec2_table @(cocos2d::Vec2) The first control of the bezier path.
---@param control2 vec2_table @(cocos2d::Vec2) The second control of the bezier path.
---@param destination vec2_table @(cocos2d::Vec2) The destination of the bezier path.
---@param segments number @(unsigned int) The number of segments.
---@param color color4b_table @(cocos2d::Color4B) Set the cubic bezier color.
---@return self @(void)
function DrawNode:drawCubicBezier(origin, control1, control2, destination, segments, color)
end

--- draw a dot at a position, with a given radius and color.
---
---@param pos vec2_table @(cocos2d::Vec2) The dot center.
---@param radius number @(float) The dot radius.
---@param color color4b_table @(cocos2d::Color4B) The dot color.
---@return self @(void)
function DrawNode:drawDot(pos, radius, color)
end

--- Draw an line from origin to destination with color.
---
--- @js NA
---@param origin vec2_table @(cocos2d::Vec2) The line origin.
---@param destination vec2_table @(cocos2d::Vec2) The line destination.
---@param color color4b_table @(cocos2d::Color4B) The line color.
---@return self @(void)
function DrawNode:drawLine(origin, destination, color)
end

--- Draw a point.
---
--- @js NA
---@param point vec2_table @(cocos2d::Vec2) A Vec2 used to point.
---@param pointSize number @(const float) The point size.
---@param color color4b_table @(cocos2d::Color4B) The point color.
---@return self @(void)
function DrawNode:drawPoint(point, pointSize, color)
end

--- Draws a quad bezier path.
---
---@param origin vec2_table @(cocos2d::Vec2) The origin of the bezier path.
---@param control vec2_table @(cocos2d::Vec2) The control of the bezier path.
---@param destination vec2_table @(cocos2d::Vec2) The destination of the bezier path.
---@param segments number @(unsigned int) The number of segments.
---@param color color4b_table @(cocos2d::Color4B) Set the quad bezier color.
---@return self @(void)
function DrawNode:drawQuadBezier(origin, control, destination, segments, color)
end

--- Draws a rectangle with 4 points.
---
---@param p1 vec2_table @(cocos2d::Vec2) The rectangle vertex point.
---@param p2 vec2_table @(cocos2d::Vec2) The rectangle vertex point.
---@param p3 vec2_table @(cocos2d::Vec2) The rectangle vertex point.
---@param p4 vec2_table @(cocos2d::Vec2) The rectangle vertex point.
---@param color color4b_table @(cocos2d::Color4B) The rectangle color.
---@return self @(void)
function DrawNode:drawRect(p1, p2, p3, p4, color)
end

--- Draws a rectangle given the origin and destination point measured in points.
--- The origin and the destination can not have the same x and y coordinate.
---
---@param origin vec2_table @(cocos2d::Vec2) The rectangle origin.
---@param destination vec2_table @(cocos2d::Vec2) The rectangle destination.
---@param color color4b_table @(cocos2d::Color4B) The rectangle color.
---@return self @(void)
function DrawNode:drawRect(origin, destination, color)
end

--- draw a segment with a radius and color.
---
---@param from vec2_table @(cocos2d::Vec2) The segment origin.
---@param to vec2_table @(cocos2d::Vec2) The segment destination.
---@param radius number @(float) The segment radius.
---@param color color4b_table @(cocos2d::Color4B) The segment color.
---@return self @(void)
function DrawNode:drawSegment(from, to, radius, color)
end

--- Draws a solid circle given the center, radius and number of segments.
--- @js NA
---@param center vec2_table @(cocos2d::Vec2) The circle center point.
---@param radius number @(float) The circle rotate of radius.
---@param angle number @(float)  The circle angle.
---@param segments number @(unsigned int) The number of segments.
---@param scaleX number @(float) The scale value in x.
---@param scaleY number @(float) The scale value in y.
---@param fillColor color4b_table @(cocos2d::Color4B) The color will fill in polygon.
---@param borderWidth number @(float) The border of line width.
---@param borderColor color4b_table @(cocos2d::Color4B) The border of line color.
---@return self @(void)
function DrawNode:drawSolidCircle(center, radius, angle, segments, scaleX, scaleY, fillColor, borderWidth, borderColor)
end

--- Draws a solid circle given the center, radius and number of segments.
--- @js NA
---@param center vec2_table @(cocos2d::Vec2) The circle center point.
---@param radius number @(float) The circle rotate of radius.
---@param angle number @(float)  The circle angle.
---@param segments number @(unsigned int) The number of segments.
---@param scaleX number @(float) The scale value in x.
---@param scaleY number @(float) The scale value in y.
---@param color color4b_table @(cocos2d::Color4B) The solid circle color.
---@return self @(void)
function DrawNode:drawSolidCircle(center, radius, angle, segments, scaleX, scaleY, color)
end

--- Draws a solid circle given the center, radius and number of segments.
--- @js NA
---@param center vec2_table @(cocos2d::Vec2) The circle center point.
---@param radius number @(float) The circle rotate of radius.
---@param angle number @(float)  The circle angle.
---@param segments number @(unsigned int) The number of segments.
---@param color color4b_table @(cocos2d::Color4B) The solid circle color.
---@return self @(void)
function DrawNode:drawSolidCircle(center, radius, angle, segments, color)
end

--- Draws a solid rectangle given the origin and destination point measured in points.
--- The origin and the destination can not have the same x and y coordinate.
---
--- @js NA
---@param origin vec2_table @(cocos2d::Vec2) The rectangle origin.
---@param destination vec2_table @(cocos2d::Vec2) The rectangle destination.
---@param color color4b_table @(cocos2d::Color4B) The rectangle color.
---@return self @(void)
function DrawNode:drawSolidRect(origin, destination, color)
end

--- draw a triangle with color.
---
--- @js NA
---@param p1 vec2_table @(cocos2d::Vec2) The triangle vertex point.
---@param p2 vec2_table @(cocos2d::Vec2) The triangle vertex point.
---@param p3 vec2_table @(cocos2d::Vec2) The triangle vertex point.
---@param color color4b_table @(cocos2d::Color4B) The triangle color.
---@return self @(void)
function DrawNode:drawTriangle(p1, p2, p3, color)
end

--- Get the color mixed mode.
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function DrawNode:getBlendFunc()
end

---@return number @(float)
function DrawNode:getLineWidth()
end

---@return boolean @(bool)
function DrawNode:isIsolated()
end

--- Set the color mixed mode.
--- @code
--- When this function bound into js or lua,the parameter will be changed
--- In js: var setBlendFunc(var src, var dst)
--- @endcode
--- @lua NA
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function DrawNode:setBlendFunc(blendFunc)
end

---
--- When isolated is set, the position of the node is no longer affected by parent nodes.
--- Which means it will be drawn just like a root node.
---@param isolated boolean @(bool)
---@return self @(void)
function DrawNode:setIsolated(isolated)
end

---@param lineWidth number @(float)
---@return self @(void)
function DrawNode:setLineWidth(lineWidth)
end

--- creates and initialize a DrawNode node.
---
--- (static)
---@param defaultLineWidth number @(float)
---@return cc.DrawNode @(cocos2d::DrawNode*) Return an autorelease object.
function DrawNode:create(defaultLineWidth)
end

--- creates and initialize a DrawNode node.
---
--- (static)
---@return cc.DrawNode @(cocos2d::DrawNode*) Return an autorelease object.
function DrawNode:create()
end

---
--- @brief Label is a subclass of Node that knows how to render text labels.
---
--- Label can be created with:
--- - A true type font file.
--- - A bitmap font file.
--- - A char map file.
--- - The built in system font.
---
--- Bitmap Font supported editors:
--- - http:glyphdesigner.71squared.com (Commercial, Mac OS X)
--- - http:www.n4te.comhierohiero.jnlp (Free, Java)
--- - http:slick.cokeandcode.comdemoshiero.jnlp (Free, Java)
--- - http:www.angelcode.comproductsbmfont (Free, Windows only)
--- @js NA
---@class cc.Label:cc.Node
local Label = {}
cc.Label = Label

---
--- Disable effect to Label.
---
--- @see `LabelEffect`
---@param effect cc.LabelEffect @(cocos2d::LabelEffect)
---@return self @(void)
function Label:disableEffect(effect)
end

---
--- Disable all effect applied to Label.
--- @warning Please use disableEffect(LabelEffect::ALL) instead of this API.
---@return self @(void)
function Label:disableEffect()
end

---
--- Enable bold rendering
---@return self @(void)
function Label:enableBold()
end

---
--- Enable glow effect to Label.
--- @warning Limiting use to only when the Label created with true type font.
---@param glowColor color4b_table @(cocos2d::Color4B)
---@return self @(void)
function Label:enableGlow(glowColor)
end

---
--- Enable italics rendering
---@return self @(void)
function Label:enableItalics()
end

---
--- Enable outline effect to Label.
--- @warning Limiting use to only when the Label created with true type font or system font.
---@param outlineColor color4b_table @(cocos2d::Color4B)
---@param outlineSize number @(int)
---@return self @(void)
function Label:enableOutline(outlineColor, outlineSize)
end

---
--- Enable outline effect to Label.
--- @warning Limiting use to only when the Label created with true type font or system font.
---@param outlineColor color4b_table @(cocos2d::Color4B)
---@return self @(void)
function Label:enableOutline(outlineColor)
end

---
--- Enable shadow effect to Label.
---
--- @todo Support blur for shadow effect.
---@param shadowColor color4b_table @(cocos2d::Color4B)
---@param offset vec2_table @(cocos2d::Vec2)
---@param blurRadius number @(int)
---@return self @(void)
function Label:enableShadow(shadowColor, offset, blurRadius)
end

---
--- Enable shadow effect to Label.
---
--- @todo Support blur for shadow effect.
---@param shadowColor color4b_table @(cocos2d::Color4B)
---@param offset vec2_table @(cocos2d::Vec2)
---@return self @(void)
function Label:enableShadow(shadowColor, offset)
end

---
--- Enable shadow effect to Label.
---
--- @todo Support blur for shadow effect.
---@param shadowColor color4b_table @(cocos2d::Color4B)
---@return self @(void)
function Label:enableShadow(shadowColor)
end

---
--- Enable shadow effect to Label.
---
--- @todo Support blur for shadow effect.
---@return self @(void)
function Label:enableShadow()
end

---
--- Enables strikethrough.
--- Underline and Strikethrough cannot be enabled at the same time.
--- Strikethrough is like an underline but at the middle of the glyph
---@return self @(void)
function Label:enableStrikethrough()
end

---
--- Enable underline
---@return self @(void)
function Label:enableUnderline()
end

---
--- Toggle wrap option of the label.
--- Note: System font doesn't support manually toggle wrap.
---
---@param enable boolean @(bool) Set true to enable wrap and false to disable wrap.
---@return self @(void)
function Label:enableWrap(enable)
end

---
--- Returns the additional kerning of the Label.
---
--- @warning Not support system font.
--- @since v3.2.0
---@return number @(float)
function Label:getAdditionalKerning()
end

--- Returns the bitmap font used by the Label.
---@return string @(std::string_view)
function Label:getBMFontFilePath()
end

---
--- Return the user define BMFont size.
---
---@return number @(float) The BMFont size in float value.
function Label:getBMFontSize()
end

---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function Label:getBlendFunc()
end

---@return vec2_table @(const cocos2d::Vec2&)
function Label:getDimensions()
end

---
--- Return current effect color value.
---@return color4f_table @(cocos2d::Color4F)
function Label:getEffectColor()
end

---@return cc.FontAtlas @(cocos2d::FontAtlas*)
function Label:getFontAtlas()
end

---@return number @(float)
function Label:getHeight()
end

--- Returns the Label's text horizontal alignment.
---@return cc.TextHAlignment @(cocos2d::TextHAlignment)
function Label:getHorizontalAlignment()
end

---
--- Return current effect type.
---@return cc.LabelEffect @(cocos2d::LabelEffect)
function Label:getLabelEffectType()
end

---
--- Returns type of label
---
--- @warning Not support system font.
--- @return the type of label
--- @since v3.18.0
---@return cc.Label.LabelType @(cocos2d::Label::LabelType)
function Label:getLabelType()
end

---
--- Provides a way to treat each character like a Sprite.
--- @warning No support system font.
---@param lettetIndex number @(int)
---@return cc.Sprite @(cocos2d::Sprite*)
function Label:getLetter(lettetIndex)
end

---
--- Returns the line height of this Label.
--- @warning Not support system font.
--- @since v3.2.0
---@return number @(float)
function Label:getLineHeight()
end

---@return number @(float)
function Label:getLineSpacing()
end

---@return number @(float)
function Label:getMaxLineWidth()
end

---
--- Return the outline effect size value.
---@return number @(float)
function Label:getOutlineSize()
end

---
--- Query the label's Overflow type.
---
---@return cc.Label.Overflow @(cocos2d::Label::Overflow) see `Overflow`
function Label:getOverflow()
end

---
--- Returns font size
---@return number @(float)
function Label:getRenderingFontSize()
end

---
--- Return the shadow effect blur radius.
---@return number @(float)
function Label:getShadowBlurRadius()
end

---
--- Return the shadow effect color value.
---@return color4f_table @(cocos2d::Color4F)
function Label:getShadowColor()
end

---
--- Return shadow effect offset value.
---@return vec2_table @(cocos2d::Vec2)
function Label:getShadowOffset()
end

--- Return the text the Label is currently displaying.
---@return string @(std::string_view)
function Label:getString()
end

---
--- Return length of string.
---@return number @(int)
function Label:getStringLength()
end

---
--- Return the number of lines of text.
---@return number @(int)
function Label:getStringNumLines()
end

--- Returns the system font used by the Label.
---@return string @(std::string_view)
function Label:getSystemFontName()
end

--- Returns the bitmap font path used by the Label.
---@return number @(float)
function Label:getSystemFontSize()
end

---
--- Returns the TTF configuration object used by the Label.
--- @see `TTFConfig`
---@return cc._ttfConfig @(const cocos2d::TTFConfig&)
function Label:getTTFConfig()
end

--- Returns the Label's text horizontal alignment.
---@return cc.TextHAlignment @(cocos2d::TextHAlignment)
function Label:getTextAlignment()
end

--- Returns the text color of the Label.
---@return color4b_table @(const cocos2d::Color4B&)
function Label:getTextColor()
end

--- Returns the Label's text vertical alignment.
---@return cc.TextVAlignment @(cocos2d::TextVAlignment)
function Label:getVerticalAlignment()
end

---@return number @(float)
function Label:getWidth()
end

---@param text string @(std::string_view)
---@param fontFilePath string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment)
---@return boolean @(bool)
function Label:initWithTTF(text, fontFilePath, fontSize, dimensions, hAlignment, vAlignment)
end

---@param text string @(std::string_view)
---@param fontFilePath string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@return boolean @(bool)
function Label:initWithTTF(text, fontFilePath, fontSize, dimensions, hAlignment)
end

---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig)
---@param text string @(std::string_view)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@param maxLineWidth number @(int)
---@return boolean @(bool)
function Label:initWithTTF(ttfConfig, text, hAlignment, maxLineWidth)
end

---@param text string @(std::string_view)
---@param fontFilePath string @(std::string_view)
---@param fontSize number @(float)
---@param dimensions vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function Label:initWithTTF(text, fontFilePath, fontSize, dimensions)
end

---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig)
---@param text string @(std::string_view)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@return boolean @(bool)
function Label:initWithTTF(ttfConfig, text, hAlignment)
end

---@param text string @(std::string_view)
---@param fontFilePath string @(std::string_view)
---@param fontSize number @(float)
---@return boolean @(bool)
function Label:initWithTTF(text, fontFilePath, fontSize)
end

---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig)
---@param text string @(std::string_view)
---@return boolean @(bool)
function Label:initWithTTF(ttfConfig, text)
end

---@return boolean @(bool)
function Label:isClipMarginEnabled()
end

---
--- Return whether the shadow effect is enabled.
---@return boolean @(bool)
function Label:isShadowEnabled()
end

---
--- Query the wrap is enabled or not.
--- Note: System font will always return true.
---@return boolean @(bool)
function Label:isWrapEnabled()
end

---@param cleanup boolean @(bool)
---@return self @(void)
function Label:removeAllChildrenWithCleanup(cleanup)
end

---
--- @warning This method is not recommended for game developers.
---@return self @(void)
function Label:requestSystemFontRefresh()
end

---
--- Sets the additional kerning of the Label.
---
--- @warning Not support system font.
--- @since v3.2.0
---@param space number @(float)
---@return self @(void)
function Label:setAdditionalKerning(space)
end

--- Sets the Label's text alignment.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment)
---@return self @(void)
function Label:setAlignment(hAlignment, vAlignment)
end

--- Sets the Label's text horizontal alignment.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@return self @(void)
function Label:setAlignment(hAlignment)
end

--- Sets a new bitmap font to Label
---@param bmfontFilePath string @(std::string_view)
---@param imageRect rect_table @(cocos2d::Rect)
---@param imageRotated boolean @(bool)
---@param fontSize number @(float)
---@return boolean @(bool)
function Label:setBMFontFilePath(bmfontFilePath, imageRect, imageRotated, fontSize)
end

--- Sets a new bitmap font to Label
---@param bmfontFilePath string @(std::string_view)
---@param subTextureKey string @(std::string_view)
---@param fontSize number @(float)
---@return boolean @(bool)
function Label:setBMFontFilePath(bmfontFilePath, subTextureKey, fontSize)
end

--- Sets a new bitmap font to Label
---@param bmfontFilePath string @(std::string_view)
---@param imageRect rect_table @(cocos2d::Rect)
---@param imageRotated boolean @(bool)
---@return boolean @(bool)
function Label:setBMFontFilePath(bmfontFilePath, imageRect, imageRotated)
end

--- Sets a new bitmap font to Label
---@param bmfontFilePath string @(std::string_view)
---@param subTextureKey string @(std::string_view)
---@return boolean @(bool)
function Label:setBMFontFilePath(bmfontFilePath, subTextureKey)
end

--- Sets a new bitmap font to Label
---@param bmfontFilePath string @(std::string_view)
---@param fontSize number @(float)
---@return boolean @(bool)
function Label:setBMFontFilePath(bmfontFilePath, fontSize)
end

--- Sets a new bitmap font to Label
---@param bmfontFilePath string @(std::string_view)
---@return boolean @(bool)
function Label:setBMFontFilePath(bmfontFilePath)
end

---
--- Change font size of label type BMFONT
--- Note: This function only scale the BMFONT letter to mimic the font size change effect.
---
---@param fontSize number @(float) The desired font size in float.
---@return self @(void)
function Label:setBMFontSize(fontSize)
end

---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function Label:setBlendFunc(blendFunc)
end

---
--- Sets a new char map configuration to Label.
---
--- @see `createWithCharMap(Texture2D*,int,int,int)`
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(int)
---@return boolean @(bool)
function Label:setCharMap(texture, itemWidth, itemHeight, startCharMap)
end

---
--- Sets a new char map configuration to Label.
---
--- @see `createWithCharMap(std::string_view,int,int,int)`
---@param charMapFile string @(std::string_view)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(int)
---@return boolean @(bool)
function Label:setCharMap(charMapFile, itemWidth, itemHeight, startCharMap)
end

---
--- Sets a new char map configuration to Label.
---
--- @see `createWithCharMap(std::string_view)`
---@param plistFile string @(std::string_view)
---@return boolean @(bool)
function Label:setCharMap(plistFile)
end

--- Clips upper and lower margin to reduce height of Label.
---@param clipEnabled boolean @(bool)
---@return self @(void)
function Label:setClipMarginEnabled(clipEnabled)
end

--- Sets the untransformed size of the Label in a more efficient way.
---@param width number @(float)
---@param height number @(float)
---@return self @(void)
function Label:setDimensions(width, height)
end

---
--- Makes the Label exactly this untransformed height.
---
--- The Label's height be used for text align if the value not equal zero.
--- The text will display incomplete if the size of Label is not large enough to display all text.
---@param height number @(float)
---@return self @(void)
function Label:setHeight(height)
end

--- Sets the Label's text horizontal alignment.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment)
---@return self @(void)
function Label:setHorizontalAlignment(hAlignment)
end

---
--- Specify what happens when a line is too long for Label.
---
---@param breakWithoutSpace boolean @(bool) Lines are automatically broken between words if this value is false.
---@return self @(void)
function Label:setLineBreakWithoutSpace(breakWithoutSpace)
end

--- Sets the line height of the Label.
--- @warning Not support system font.
--- @since v3.2.0
---@param height number @(float)
---@return self @(void)
function Label:setLineHeight(height)
end

---@param height number @(float)
---@return self @(void)
function Label:setLineSpacing(height)
end

---
--- Makes the Label at most this line untransformed width.
--- The Label's max line width be used for force line breaks if the value not equal zero.
---@param maxLineWidth number @(float)
---@return self @(void)
function Label:setMaxLineWidth(maxLineWidth)
end

---
--- Change the label's Overflow type, currently only TTF and BMFont support all the valid Overflow type.
--- Char Map font supports all the Overflow type except for SHRINK, because we can't measure it's font size.
--- System font only support Overflow::Normal and Overflow::RESIZE_HEIGHT.
---
---@param overflow cc.Label.Overflow @(cocos2d::Label::Overflow)   see `Overflow`
---@return self @(void)
function Label:setOverflow(overflow)
end

--- Sets the text that this Label is to display.
---@param text string @(std::string_view)
---@return self @(void)
function Label:setString(text)
end

---
--- Sets a new system font to Label.
---
--- @warning
---@param font string @(std::string_view) A font file or a font family name.
---@return self @(void)
function Label:setSystemFontName(font)
end

---@param fontSize number @(float)
---@return self @(void)
function Label:setSystemFontSize(fontSize)
end

---
--- Sets a new TTF configuration to Label.
--- @see `TTFConfig`
---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig)
---@return boolean @(bool)
function Label:setTTFConfig(ttfConfig)
end

---
--- Sets the text color of Label.
---
--- The text color is different from the color of Node.
---
--- @warning Limiting use to only when the Label created with true type font or system font.
---@param color color4b_table @(cocos2d::Color4B)
---@return self @(void)
function Label:setTextColor(color)
end

--- Sets the Label's text vertical alignment.
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment)
---@return self @(void)
function Label:setVerticalAlignment(vAlignment)
end

---
--- Makes the Label exactly this untransformed width.
---
--- The Label's width be used for text align if the value not equal zero.
---@param width number @(float)
---@return self @(void)
function Label:setWidth(width)
end

--- Update content immediately.
---@return self @(void)
function Label:updateContent()
end

---
--- Allocates and initializes a Label, with default settings.
---
--- (static)
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:create()
end

---
--- Allocates and initializes a Label, with a bitmap font file.
---
---
--- @see setBMFontFilePath setMaxLineWidth
--- (static)
---@param bmfontPath string @(std::string_view) A bitmap font file, it's a FNT format.
---@param text string @(std::string_view) The initial text.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) Text horizontal alignment.
---@param maxLineWidth number @(int) The max line width.
---@param imageRect rect_table @(cocos2d::Rect)
---@param imageRotated boolean @(bool)
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithBMFont(bmfontPath, text, hAlignment, maxLineWidth, imageRect, imageRotated)
end

---
--- Allocates and initializes a Label, with a bitmap font file.
---
---
--- @see setBMFontFilePath setMaxLineWidth
--- (static)
---@param bmfontPath string @(std::string_view) A bitmap font file, it's a FNT format.
---@param text string @(std::string_view) The initial text.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) Text horizontal alignment.
---@param maxLineWidth number @(int) The max line width.
---@param subTextureKey string @(std::string_view) Name of entry in PLIST texture atlassprite sheet
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithBMFont(bmfontPath, text, hAlignment, maxLineWidth, subTextureKey)
end

---
--- Allocates and initializes a Label, with a bitmap font file.
---
---
--- @see setBMFontFilePath setMaxLineWidth
--- (static)
---@param bmfontPath string @(std::string_view) A bitmap font file, it's a FNT format.
---@param text string @(std::string_view) The initial text.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) Text horizontal alignment.
---@param maxLineWidth number @(int) The max line width.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithBMFont(bmfontPath, text, hAlignment, maxLineWidth)
end

---
--- Allocates and initializes a Label, with a bitmap font file.
---
---
--- @see setBMFontFilePath setMaxLineWidth
--- (static)
---@param bmfontPath string @(std::string_view) A bitmap font file, it's a FNT format.
---@param text string @(std::string_view) The initial text.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) Text horizontal alignment.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithBMFont(bmfontPath, text, hAlignment)
end

---
--- Allocates and initializes a Label, with a bitmap font file.
---
---
--- @see setBMFontFilePath setMaxLineWidth
--- (static)
---@param bmfontPath string @(std::string_view) A bitmap font file, it's a FNT format.
---@param text string @(std::string_view) The initial text.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithBMFont(bmfontPath, text)
end

---
--- Allocates and initializes a Label, with char map configuration.
---
---
--- (static)
---@param texture cc.Texture2D @(cocos2d::Texture2D*) A pointer to an existing Texture2D object.
---@param itemWidth number @(int) The width in points of each element.
---@param itemHeight number @(int) The height in points of each element.
---@param startCharMap number @(int) The starting char of the char map.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithCharMap(texture, itemWidth, itemHeight, startCharMap)
end

---
--- Allocates and initializes a Label, with char map configuration.
---
---
--- (static)
---@param charMapFile string @(std::string_view) A char map file, it's a PNG format.
---@param itemWidth number @(int) The width in points of each element.
---@param itemHeight number @(int) The height in points of each element.
---@param startCharMap number @(int) The starting char of the char map.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithCharMap(charMapFile, itemWidth, itemHeight, startCharMap)
end

---
--- Allocates and initializes a Label, with char map configuration.
---
---
--- (static)
---@param plistFile string @(std::string_view) A configuration file of char map.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithCharMap(plistFile)
end

---
--- Allocates and initializes a Label, base on platform-dependent API.
---
---
--- @warning It will generate texture by the platform-dependent code.
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param font string @(std::string_view) A font file or a font family name.
---@param fontSize number @(float) The font size. This value must be > 0.
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) The text horizontal alignment.
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment) The text vertical alignment.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithSystemFont(text, font, fontSize, dimensions, hAlignment, vAlignment)
end

---
--- Allocates and initializes a Label, base on platform-dependent API.
---
---
--- @warning It will generate texture by the platform-dependent code.
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param font string @(std::string_view) A font file or a font family name.
---@param fontSize number @(float) The font size. This value must be > 0.
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) The text horizontal alignment.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithSystemFont(text, font, fontSize, dimensions, hAlignment)
end

---
--- Allocates and initializes a Label, base on platform-dependent API.
---
---
--- @warning It will generate texture by the platform-dependent code.
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param font string @(std::string_view) A font file or a font family name.
---@param fontSize number @(float) The font size. This value must be > 0.
---@param dimensions vec2_table @(cocos2d::Vec2)
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithSystemFont(text, font, fontSize, dimensions)
end

---
--- Allocates and initializes a Label, base on platform-dependent API.
---
---
--- @warning It will generate texture by the platform-dependent code.
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param font string @(std::string_view) A font file or a font family name.
---@param fontSize number @(float) The font size. This value must be > 0.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithSystemFont(text, font, fontSize)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param fontFilePath string @(std::string_view) A font file.
---@param fontSize number @(float) The font size. This value must be > 0.
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) The text horizontal alignment.
---@param vAlignment cc.TextVAlignment @(cocos2d::TextVAlignment) The text vertical alignment.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(text, fontFilePath, fontSize, dimensions, hAlignment, vAlignment)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param fontFilePath string @(std::string_view) A font file.
---@param fontSize number @(float) The font size. This value must be > 0.
---@param dimensions vec2_table @(cocos2d::Vec2)
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) The text horizontal alignment.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(text, fontFilePath, fontSize, dimensions, hAlignment)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- @see TTFConfig setTTFConfig setMaxLineWidth
--- (static)
---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig) A pointer to a TTFConfig object.
---@param text string @(std::string_view) The initial text.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) The text horizontal alignment.
---@param maxLineWidth number @(int) The max line width.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(ttfConfig, text, hAlignment, maxLineWidth)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param fontFilePath string @(std::string_view) A font file.
---@param fontSize number @(float) The font size. This value must be > 0.
---@param dimensions vec2_table @(cocos2d::Vec2)
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(text, fontFilePath, fontSize, dimensions)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- @see TTFConfig setTTFConfig setMaxLineWidth
--- (static)
---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig) A pointer to a TTFConfig object.
---@param text string @(std::string_view) The initial text.
---@param hAlignment cc.TextHAlignment @(cocos2d::TextHAlignment) The text horizontal alignment.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(ttfConfig, text, hAlignment)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- (static)
---@param text string @(std::string_view) The initial text.
---@param fontFilePath string @(std::string_view) A font file.
---@param fontSize number @(float) The font size. This value must be > 0.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(text, fontFilePath, fontSize)
end

---
--- Allocates and initializes a Label, base on FreeType2.
---
---
--- @see TTFConfig setTTFConfig setMaxLineWidth
--- (static)
---@param ttfConfig cc._ttfConfig @(cocos2d::TTFConfig) A pointer to a TTFConfig object.
---@param text string @(std::string_view) The initial text.
---@return cc.Label @(cocos2d::Label*) An automatically released Label object.
function Label:createWithTTF(ttfConfig, text)
end

---
--- @class LabelAtlas
--- @brief LabelAtlas is a subclass of AtlasNode.
---
--- It can be as a replacement of Label since it is MUCH faster.
---
--- LabelAtlas versus Label:
--- - LabelAtlas is MUCH faster than Label.
--- - LabelAtlas "characters" have a fixed height and width.
--- - LabelAtlas "characters" can be anything you want since they are taken from an image file.
---
--- A more flexible class is LabelBMFont. It supports variable width characters and it also has a nice editor.
---@class cc.LabelAtlas:cc.AtlasNode
local LabelAtlas = {}
cc.LabelAtlas = LabelAtlas

---@return string @(std::string_view)
function LabelAtlas:getString()
end

--- Initializes the LabelAtlas with a string, a texture, the width and height in points of each element and the
--- starting char of the atlas
---@param string string @(std::string_view)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(int)
---@return boolean @(bool)
function LabelAtlas:initWithString(string, texture, itemWidth, itemHeight, startCharMap)
end

--- Initializes the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and
--- the starting char of the atlas.
---@param string string @(std::string_view)
---@param charMapFile string @(std::string_view)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(int)
---@return boolean @(bool)
function LabelAtlas:initWithString(string, charMapFile, itemWidth, itemHeight, startCharMap)
end

---
--- Initializes the LabelAtlas with a string and a configuration file.
--- @since v2.0
---@param string string @(std::string_view)
---@param fntFile string @(std::string_view)
---@return boolean @(bool)
function LabelAtlas:initWithString(string, fntFile)
end

---@param label string @(std::string_view)
---@return self @(void)
function LabelAtlas:setString(label)
end

---
--- Creates the LabelAtlas with a string, a texture, the width and height of each element and the starting char of
--- the atlas.
--- (static)
---@param string string @(std::string_view)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(int)
---@return cc.LabelAtlas @(cocos2d::LabelAtlas*)
function LabelAtlas:_create(string, texture, itemWidth, itemHeight, startCharMap)
end

--- Creates the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the
--- starting char of the atlas.
--- (static)
---@param string string @(std::string_view)
---@param charMapFile string @(std::string_view)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(int)
---@return cc.LabelAtlas @(cocos2d::LabelAtlas*)
function LabelAtlas:_create(string, charMapFile, itemWidth, itemHeight, startCharMap)
end

---
--- Creates the LabelAtlas with a string and a configuration file.
--- @since v2.0
--- (static)
---@param string string @(std::string_view)
---@param fntFile string @(std::string_view)
---@return cc.LabelAtlas @(cocos2d::LabelAtlas*)
function LabelAtlas:_create(string, fntFile)
end

---
--- Sprite is a 2d image ( http:en.wikipedia.orgwikiSprite_(computer_graphics) ).
---
--- Sprite can be created with an image, or with a sub-rectangle of an image.
---
--- To optimize the Sprite rendering, please follow the following best practices:
---  - Put all your sprites in the same spritesheet (http:www.codeandweb.comwhat-is-a-sprite-sheet).
---  - Use the same blending function for all your sprites.
---  - ...and the Renderer will automatically "batch" your sprites (will draw all of them in one OpenGL call).
---
---  Sprite has 4 types or rendering modes:
---
---  - `QUAD`: Renders the sprite using 2 triangles (1 rectangle): uses small memory, but renders empty pixels (slow)
---  - `POLYGON`: Renders the sprite using many triangles (depending on the setting): Uses more memory, but doesn't
--- render so much empty pixels (faster)
---  - `SLICE9`: Renders the sprite using 18 triangles (9 rectangles). Useful to to scale buttons an other rectangular
--- sprites
---  - `QUAD_BATCHNODE`: Renders the sprite using 2 triangles (1 rectangle) with a static batch, which has some
--- limitations (see below)
---
--- By default, the sprite uses `QUAD` mode. But can be changed to `POLYGON` when calling `setPolygonInfo()`. To use
--- `SLICE9` call `setCenterRect()` or `serCenterRectNormalized()`. To use `QUAD_BATCHNODE` parent the sprite to a
--- `SpriteBatchNode` object.
---
---  *
---  `QUAD_BATCHNODE` is deprecated and should be avoid. It has the following limitations:
---
---  - The AliasAntialias property belongs to `SpriteBatchNode`, so you can't individually set the aliased property.
---  - The Blending function property belongs to `SpriteBatchNode`, so you can't individually set the blending function
--- property.
---  - `ParallaxNode` is not supported, but can be simulated with a "proxy" sprite.
---  - Sprites can only have other Sprites (or subclasses of Sprite) as children.
---
--- The default anchorPoint in Sprite is (0.5, 0.5).
---@class cc.Sprite:cc.Node
local Sprite = {}
cc.Sprite = Sprite

---
--- Returns the index used on the TextureAtlas.
---@return number @(unsigned int)
function Sprite:getAtlasIndex()
end

---
--- Returns the batch node object if this sprite is rendered by SpriteBatchNode.
---
--- nullptr if the sprite isn't used batch node.
---@return cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*) The SpriteBatchNode object if this sprite is rendered by SpriteBatchNode,
function Sprite:getBatchNode()
end

---
--- @js  NA
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function Sprite:getBlendFunc()
end

---
--- @brief Returns the Cap Insets rect
---
---@return rect_table @(cocos2d::Rect) Scale9Sprite's cap inset.
function Sprite:getCenterRect()
end

---
--- getCenterRectNormalized
---
--- Returns the CenterRect in normalized coordinates
---@return rect_table @(cocos2d::Rect)
function Sprite:getCenterRectNormalized()
end

---
--- Gets the offset position of the sprite. Calculated automatically by editors like Zwoptex.
---@return vec2_table @(const cocos2d::Vec2&)
function Sprite:getOffsetPosition()
end

---@return string @(std::string_view)
function Sprite:getResourceName()
end

--- @}
---@return number @(int)
function Sprite:getResourceType()
end

---
--- Returns the current displayed frame.
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*)
function Sprite:getSpriteFrame()
end

--- Returns the Texture2D object used by the sprite.
---@return cc.Texture2D @(cocos2d::Texture2D*)
function Sprite:getTexture()
end

---
--- Gets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
---@return cc.TextureAtlas @(cocos2d::TextureAtlas*)
function Sprite:getTextureAtlas()
end

---
--- Returns the rect of the Sprite in points.
---@return rect_table @(const cocos2d::Rect&)
function Sprite:getTextureRect()
end

---
--- Initializes a sprite with an image filename, and a rect.
---
--- This method will find filename from local file system, load its content to Texture2D,
--- then use Texture2D to create a sprite.
--- After initialization, the offset will be (0,0).
---
--- @lua     init
---@param filename string @(std::string_view)
---@param rect rect_table @(cocos2d::Rect)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithFile(filename, rect)
end

---@param filename string @(std::string_view)
---@param format ccb.PixelFormat @(cocos2d::PixelFormat)
---@return boolean @(bool)
function Sprite:initWithFile(filename, format)
end

---
--- Initializes a sprite with an image filename.
---
--- This method will find filename from local file system, load its content to Texture2D,
--- then use Texture2D to create a sprite.
--- After initialization, the rect used will be the size of the image. The offset will be (0,0).
---
--- @lua     init
---@param filename string @(std::string_view)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithFile(filename)
end

---
--- Initializes a sprite with an SpriteFrame. The texture and rect in SpriteFrame will be applied on this sprite.
---
---@param spriteFrame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithSpriteFrame(spriteFrame)
end

---
--- Initializes a sprite with an sprite frame name.
---
--- A SpriteFrame will be fetched from the SpriteFrameCache by name.
--- If the SpriteFrame doesn't exist it will raise an exception.
---
---@param spriteFrameName string @(std::string_view)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithSpriteFrameName(spriteFrameName)
end

---
--- Initializes a sprite with a texture and a rect in points, optionally rotated.
---
--- After initialization, the offset will be (0,0).
--- @note    This is the designated initializer.
---
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param rect rect_table @(cocos2d::Rect)
---@param rotated boolean @(bool)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithTexture(texture, rect, rotated)
end

---
--- Initializes a sprite with a texture and a rect.
---
--- After initialization, the offset will be (0,0).
---
--- You can use a Texture2D object for many sprites.
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param rect rect_table @(cocos2d::Rect)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithTexture(texture, rect)
end

---
--- Initializes a sprite with a texture.
---
--- After initialization, the rect used will be the size of the texture, and the offset will be (0,0).
---
--- You can use a Texture2D object for many sprites.
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return boolean @(bool)  True if the sprite is initialized properly, false otherwise.
function Sprite:initWithTexture(texture)
end

---
--- Whether or not the Sprite needs to be updated in the Atlas.
---
---@return boolean @(bool) True if the sprite needs to be updated in the Atlas, false otherwise.
function Sprite:isDirty()
end

---
--- Returns the flag which indicates whether the sprite is flipped horizontally or not.
---
--- It only flips the texture of the sprite, and not the texture of the sprite's children.
--- Also, flipping the texture doesn't alter the anchorPoint.
--- If you want to flip the anchorPoint too, andor to flip the children too use:
--- sprite->setScaleX(sprite->getScaleX() * -1);
---
---@return boolean @(bool) true if the sprite is flipped horizontally, false otherwise.
function Sprite:isFlippedX()
end

---
--- Return the flag which indicates whether the sprite is flipped vertically or not.
---
--- It only flips the texture of the sprite, and not the texture of the sprite's children.
--- Also, flipping the texture doesn't alter the anchorPoint.
--- If you want to flip the anchorPoint too, andor to flip the children too use:
--- sprite->setScaleY(sprite->getScaleY() * -1);
---
---@return boolean @(bool) true if the sprite is flipped vertically, false otherwise.
function Sprite:isFlippedY()
end

---
--- Returns whether or not a SpriteFrame is being displayed.
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return boolean @(bool)
function Sprite:isFrameDisplayed(frame)
end

--- returns whether or not contentSize stretches the sprite's texture
---@return boolean @(bool)
function Sprite:isStretchEnabled()
end

---
--- Returns whether or not the texture rectangle is rotated.
---@return boolean @(bool)
function Sprite:isTextureRectRotated()
end

---@param cleanup boolean @(bool)
---@return self @(void)
function Sprite:removeAllChildrenWithCleanup(cleanup)
end

---
--- Sets the index used on the TextureAtlas.
---
--- @warning Don't modify this value unless you know what you are doing.
---@param atlasIndex number @(unsigned int)
---@return self @(void)
function Sprite:setAtlasIndex(atlasIndex)
end

---
--- Sets the batch node to sprite.
--- @warning This method is not recommended for game developers. Sample code for using batch node
--- @code
--- SpriteBatchNode *batch = SpriteBatchNode::create("Imagesgrossini_dance_atlas.png", 15);
--- Sprite *sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0, 0, 57, 57));
--- batch->addChild(sprite);
--- layer->addChild(batch);
--- @endcode
---@param spriteBatchNode cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*)
---@return self @(void)
function Sprite:setBatchNode(spriteBatchNode)
end

--- @{
--- @name Functions inherited from TextureProtocol.
---
--- *@code
--- *When this function bound into js or lua,the parameter will be changed.
--- *In js: var setBlendFunc(var src, var dst).
--- *In lua: local setBlendFunc(local src, local dst).
--- *@endcode
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function Sprite:setBlendFunc(blendFunc)
end

---@param rect rect_table @(cocos2d::Rect)
---@return self @(void)
function Sprite:setCenterRect(rect)
end

---
--- setCenterRectNormalized
---
--- Useful to implement "9 sliced" sprites.
--- The default value is (0,0) - (1,1), which means that only one "slice" will be used: From top-left (0,0) to
--- bottom-right (1,1). If the value is different than (0,0), (1,1), then the sprite will be sliced into a 3 x 3
--- grid. The four corners of this grid are applied without performing any scaling. The upper- and lower-middle parts
--- are scaled horizontally, and the left- and right-middle parts are scaled vertically. The center is scaled in both
--- directions. Important: The scaling is based the Sprite's trimmed size.
---
--- Limitations: Does not work when the sprite is part of `SpriteBatchNode`.
---@param rect rect_table @(cocos2d::Rect)
---@return self @(void)
function Sprite:setCenterRectNormalized(rect)
end

---
--- Makes the Sprite to be updated in the Atlas.
---@param dirty boolean @(bool)
---@return self @(void)
function Sprite:setDirty(dirty)
end

--- @{
--- @name Animation methods
---
--- Changes the display frame with animation name and index.
--- The animation name will be get from the AnimationCache.
---@param animationName string @(std::string_view)
---@param frameIndex number @(unsigned int)
---@return self @(void)
function Sprite:setDisplayFrameWithAnimationName(animationName, frameIndex)
end

---
--- Sets whether the sprite should be flipped horizontally or not.
---
---@param flippedX boolean @(bool) true if the sprite should be flipped horizontally, false otherwise.
---@return self @(void)
function Sprite:setFlippedX(flippedX)
end

---
--- Sets whether the sprite should be flipped vertically or not.
---
---@param flippedY boolean @(bool) true if the sprite should be flipped vertically, false otherwise.
---@return self @(void)
function Sprite:setFlippedY(flippedY)
end

---@param newFrame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return self @(void)
function Sprite:setSpriteFrame(newFrame)
end

--- @{
--- Sets a new SpriteFrame to the Sprite.
---@param spriteFrameName string @(std::string_view)
---@return self @(void)
function Sprite:setSpriteFrame(spriteFrameName)
end

--- whether or not contentSize stretches the sprite's texture
---@param enabled boolean @(bool)
---@return self @(void)
function Sprite:setStretchEnabled(enabled)
end

--- @overload
---
--- The Texture's rect is not changed.
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function Sprite:setTexture(texture)
end

--- Sets a new texture (from a filename) to the sprite.
---
--- @memberof Sprite
--- It will call `setTextureRect()` with the texture's content size.
---@param filename string @(std::string_view)
---@return self @(void)
function Sprite:setTexture(filename)
end

---
--- Sets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
---@param textureAtlas cc.TextureAtlas @(cocos2d::TextureAtlas*)
---@return self @(void)
function Sprite:setTextureAtlas(textureAtlas)
end

--- @overload
---
--- It will update the texture coordinates and the vertex rectangle.
---@param rect rect_table @(cocos2d::Rect)
---@param rotated boolean @(bool)
---@param untrimmedSize vec2_table @(cocos2d::Vec2)
---@return self @(void)
function Sprite:setTextureRect(rect, rotated, untrimmedSize)
end

---
--- Updates the texture rect of the Sprite in points.
---
--- It will call setTextureRect(const Rect& rect, bool rotated, const Vec2& untrimmedSize) with \p rotated = false,
--- and \p utrimmedSize = rect.size.
---@param rect rect_table @(cocos2d::Rect)
---@return self @(void)
function Sprite:setTextureRect(rect)
end

---@return self @(void)
function Sprite:setVertexLayout()
end

---
--- Sets the vertex rect.
---
--- It will be called internally by setTextureRect.
--- Useful if you want to create 2x images from SD images in Retina Display.
--- Do not call it manually. Use setTextureRect instead.
---@param rect rect_table @(cocos2d::Rect)
---@return self @(void)
function Sprite:setVertexRect(rect)
end

---
--- Creates an empty sprite without texture. You can call setTexture method subsequently.
---
--- @memberof Sprite
--- (static)
---@return cc.Sprite @(cocos2d::Sprite*) An autoreleased sprite object.
function Sprite:create()
end

---
--- Creates a sprite with an image filename.
---
--- After creation, the rect of sprite will be the size of the image,
--- and the offset will be (0,0).
---
--- (static)
---@param filename string @(std::string_view)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:create(filename)
end

---
--- Creates a sprite with an image filename and a rect.
---
--- (static)
---@param filename string @(std::string_view)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:create(filename, rect)
end

---
--- Creates a sprite with an sprite frame.
---
--- (static)
---@param spriteFrame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:createWithSpriteFrame(spriteFrame)
end

---
--- Creates a sprite with an sprite frame name.
---
--- A SpriteFrame will be fetched from the SpriteFrameCache by spriteFrameName param.
--- If the SpriteFrame doesn't exist it will raise an exception.
---
--- (static)
---@param spriteFrameName string @(std::string_view)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:createWithSpriteFrameName(spriteFrameName)
end

---
--- Creates a sprite with a texture and a rect.
---
--- After creation, the offset will be (0,0).
---
--- You can use a Texture2D object for many sprites.
--- (static)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param rect rect_table @(cocos2d::Rect)
---@param rotated boolean @(bool)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:createWithTexture(texture, rect, rotated)
end

---
--- Creates a sprite with a texture and a rect.
---
--- After creation, the offset will be (0,0).
---
--- You can use a Texture2D object for many sprites.
--- (static)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:createWithTexture(texture, rect)
end

---
--- Creates a sprite with a Texture2D object.
---
--- After creation, the rect will be the size of the texture, and the offset will be (0,0).
---
--- (static)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return cc.Sprite @(cocos2d::Sprite*)  An autoreleased sprite object.
function Sprite:createWithTexture(texture)
end

---
--- @addtogroup _2d
--- @{
---@class cc.Layer:cc.Node
local Layer = {}
cc.Layer = Layer

--- (static)
---@return cc.Layer @(cocos2d::Layer*)
function Layer:create()
end

--- @class LayerColor
--- @brief LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.
--- All features from Layer are valid, plus the following new features:
--- - opacity
--- - RGB colors
---@class cc.LayerColor:cc.Sprite
local LayerColor = {}
cc.LayerColor = LayerColor

--- Change height in Points.
---
---@param h number @(float) The height of layer.
---@return self @(void)
function LayerColor:changeHeight(h)
end

--- Change width in Points.
---
---@param w number @(float) The width of layer.
---@return self @(void)
function LayerColor:changeWidth(w)
end

--- Change width and height in Points.
---
--- @since v0.8
---@param w number @(float) The width of layer.
---@param h number @(float) The Height of layer.
---@return self @(void)
function LayerColor:changeWidthAndHeight(w, h)
end

---@param color color4b_table @(cocos2d::Color4B)
---@param width number @(float)
---@param height number @(float)
---@return boolean @(bool)
function LayerColor:initWithColor(color, width, height)
end

---@param color color4b_table @(cocos2d::Color4B)
---@return boolean @(bool)
function LayerColor:initWithColor(color)
end

--- Creates a Layer with color, width and height in Points.
---
--- (static)
---@param color color4b_table @(cocos2d::Color4B) The color of layer.
---@param width number @(float) The width of layer.
---@param height number @(float) The height of layer.
---@return cc.LayerColor @(cocos2d::LayerColor*) An autoreleased LayerColor object.
function LayerColor:create(color, width, height)
end

--- Creates a Layer with color. Width and height are the window size.
---
--- (static)
---@param color color4b_table @(cocos2d::Color4B) The color of layer.
---@return cc.LayerColor @(cocos2d::LayerColor*) An autoreleased LayerColor object.
function LayerColor:create(color)
end

--- Creates a fullscreen black layer.
---
--- (static)
---@return cc.LayerColor @(cocos2d::LayerColor*) An autoreleased LayerColor object.
function LayerColor:create()
end

--- @class LayerGradient
--- @brief LayerGradient is a subclass of LayerColor that draws gradients across the background.
---
--- All features from LayerColor are valid, plus the following new features:
--- - direction
--- - final color
--- - interpolation mode
---
--- Color is interpolated between the startColor and endColor along the given
--- vector (starting at the origin, ending at the terminus).  If no vector is
--- supplied, it defaults to (0, -1) -- a fade from top to bottom.
---
--- If 'compressedInterpolation' is disabled, you will not see either the start or end color for
--- non-cardinal vectors; a smooth gradient implying both end points will be still
--- be drawn, however.
---
--- If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
---
--- @since v0.99.5
---@class cc.LayerGradient:cc.LayerColor
local LayerGradient = {}
cc.LayerGradient = LayerGradient

--- Returns the end color of the gradient.
---
---@return color3b_table @(const cocos2d::Color3B&) The end color.
function LayerGradient:getEndColor()
end

--- Returns the end opacity of the gradient.
---
---@return number @(uint8_t) The end opacity.
function LayerGradient:getEndOpacity()
end

--- Returns the start color of the gradient.
---
---@return color3b_table @(const cocos2d::Color3B&) The start color.
function LayerGradient:getStartColor()
end

--- Returns the start opacity of the gradient.
---
---@return number @(uint8_t) The start opacity.
function LayerGradient:getStartOpacity()
end

--- Returns the directional vector used for the gradient.
---
---@return vec2_table @(const cocos2d::Vec2&) The direction of gradient.
function LayerGradient:getVector()
end

--- Initializes the Layer with a gradient between start and end in the direction of v.
--- @js init
--- @lua init
---@param start color4b_table @(cocos2d::Color4B)
---@param end_ color4b_table @(cocos2d::Color4B)
---@param v vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function LayerGradient:initWithColor(start, end_, v)
end

--- Initializes the Layer with a gradient between start and end.
--- @js init
--- @lua init
---@param start color4b_table @(cocos2d::Color4B)
---@param end_ color4b_table @(cocos2d::Color4B)
---@return boolean @(bool)
function LayerGradient:initWithColor(start, end_)
end

--- Get the compressedInterpolation
---
---@return boolean @(bool) The interpolation will be compressed if true.
function LayerGradient:isCompressedInterpolation()
end

--- Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in
--- canonical and non canonical vectors. Default: true.
---
---@param compressedInterpolation boolean @(bool) The interpolation will be compressed if true.
---@return self @(void)
function LayerGradient:setCompressedInterpolation(compressedInterpolation)
end

--- Sets the end color of the gradient.
---
---@param endColor color3b_table @(cocos2d::Color3B) The end color.
---@return self @(void)
function LayerGradient:setEndColor(endColor)
end

--- Returns the end opacity of the gradient.
---
---@param endOpacity number @(uint8_t) The end opacity, from 0 to 255.
---@return self @(void)
function LayerGradient:setEndOpacity(endOpacity)
end

--- Sets the start color of the gradient.
---
---@param startColor color3b_table @(cocos2d::Color3B) The start color.
---@return self @(void)
function LayerGradient:setStartColor(startColor)
end

--- Returns the start opacity of the gradient.
---
---@param startOpacity number @(uint8_t) The start opacity, from 0 to 255.
---@return self @(void)
function LayerGradient:setStartOpacity(startOpacity)
end

--- Sets the directional vector that will be used for the gradient.
--- The default value is vertical direction (0,-1).
---
---@param alongVector vec2_table @(cocos2d::Vec2) The direction of gradient.
---@return self @(void)
function LayerGradient:setVector(alongVector)
end

--- Creates a full-screen Layer with a gradient between start and end in the direction of v.
---
--- (static)
---@param start color4b_table @(cocos2d::Color4B) The start color.
---@param end_ color4b_table @(cocos2d::Color4B) The end color.
---@param v vec2_table @(cocos2d::Vec2) The direction of gradient color.
---@return cc.LayerGradient @(cocos2d::LayerGradient*) An autoreleased LayerGradient object.
function LayerGradient:create(start, end_, v)
end

--- Creates a full-screen Layer with a gradient between start and end.
---
--- (static)
---@param start color4b_table @(cocos2d::Color4B) The start color.
---@param end_ color4b_table @(cocos2d::Color4B) The end color.
---@return cc.LayerGradient @(cocos2d::LayerGradient*) An autoreleased LayerGradient object.
function LayerGradient:create(start, end_)
end

--- Creates a fullscreen black layer.
---
--- (static)
---@return cc.LayerGradient @(cocos2d::LayerGradient*) An autoreleased LayerGradient object.
function LayerGradient:create()
end

--- @class LayerRadialGradient
--- @brief LayerRadialGradient is a subclass of Layer that draws radial gradients across the background.
---  @since v3.16
---@class cc.LayerRadialGradient:cc.Node
local LayerRadialGradient = {}
cc.LayerRadialGradient = LayerRadialGradient

---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function LayerRadialGradient:getBlendFunc()
end

---@return vec2_table @(cocos2d::Vec2)
function LayerRadialGradient:getCenter()
end

---@return color4b_table @(cocos2d::Color4B)
function LayerRadialGradient:getEndColor()
end

---@return color3b_table @(cocos2d::Color3B)
function LayerRadialGradient:getEndColor3B()
end

---@return number @(uint8_t)
function LayerRadialGradient:getEndOpacity()
end

---@return number @(float)
function LayerRadialGradient:getExpand()
end

---@return number @(float)
function LayerRadialGradient:getRadius()
end

---@return color4b_table @(cocos2d::Color4B)
function LayerRadialGradient:getStartColor()
end

---@return color3b_table @(cocos2d::Color3B)
function LayerRadialGradient:getStartColor3B()
end

---@return number @(uint8_t)
function LayerRadialGradient:getStartOpacity()
end

---@param startColor color4b_table @(cocos2d::Color4B)
---@param endColor color4b_table @(cocos2d::Color4B)
---@param radius number @(float)
---@param center vec2_table @(cocos2d::Vec2)
---@param expand number @(float)
---@return boolean @(bool)
function LayerRadialGradient:initWithColor(startColor, endColor, radius, center, expand)
end

---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function LayerRadialGradient:setBlendFunc(blendFunc)
end

---@param center vec2_table @(cocos2d::Vec2)
---@return self @(void)
function LayerRadialGradient:setCenter(center)
end

---@param color color4b_table @(cocos2d::Color4B)
---@return self @(void)
function LayerRadialGradient:setEndColor(color)
end

---@param color color3b_table @(cocos2d::Color3B)
---@return self @(void)
function LayerRadialGradient:setEndColor(color)
end

---@param opacity number @(uint8_t)
---@return self @(void)
function LayerRadialGradient:setEndOpacity(opacity)
end

---@param expand number @(float)
---@return self @(void)
function LayerRadialGradient:setExpand(expand)
end

---@param radius number @(float)
---@return self @(void)
function LayerRadialGradient:setRadius(radius)
end

---@param color color4b_table @(cocos2d::Color4B)
---@return self @(void)
function LayerRadialGradient:setStartColor(color)
end

---@param color color3b_table @(cocos2d::Color3B)
---@return self @(void)
function LayerRadialGradient:setStartColor(color)
end

---@param opacity number @(uint8_t)
---@return self @(void)
function LayerRadialGradient:setStartOpacity(opacity)
end

--- Create a LayerRadialGradient
--- starts outside of that amount)
--- (static)
---@param startColor color4b_table @(cocos2d::Color4B) the inner color of the gradient
---@param endColor color4b_table @(cocos2d::Color4B) the out color of the gradient
---@param radius number @(float) the radius of the gradient(length from center of gradient to outer color)
---@param center vec2_table @(cocos2d::Vec2) the position of the center of the gradient
---@param expand number @(float) an alpha value(0.f-1.f) that specifies how much of that radius in only inner color(the gradient
---@return cc.LayerRadialGradient @(cocos2d::LayerRadialGradient*)
function LayerRadialGradient:create(startColor, endColor, radius, center, expand)
end

--- (static)
---@return cc.LayerRadialGradient @(cocos2d::LayerRadialGradient*)
function LayerRadialGradient:create()
end

--- @class LayerMultiplex
--- @brief MultipleLayer is a Layer with the ability to multiplex it's children.
--- Features:
--- - It supports one or more children
--- - Only one children will be active a time
---@class cc.LayerMultiplex:cc.Node
local LayerMultiplex = {}
cc.LayerMultiplex = LayerMultiplex

--- Add a certain layer to LayerMultiplex.
---
---@param layer cc.Node @(cocos2d::Node*) A layer need to be added to the LayerMultiplex.
---@return self @(void)
function LayerMultiplex:addLayer(layer)
end

--- initializes a MultiplexLayer with an array of layers
--- @since v2.1
---@param arrayOfLayers cc.Node [] @(cocos2d::Vector<cocos2d::Node *>)
---@return boolean @(bool)
function LayerMultiplex:initWithArray(arrayOfLayers)
end

--- The same as switchTo(int), but has a parameter to set if need to clean up child.
---@param n number @(int)
---@param cleanup boolean @(bool)
---@return self @(void)
function LayerMultiplex:switchTo(n, cleanup)
end

--- Switches to a certain layer indexed by n.
--- The current (old) layer will be removed from it's parent with 'cleanup=true'.
---
---@param n number @(int) The layer indexed by n will display.
---@return self @(void)
function LayerMultiplex:switchTo(n)
end

--- release the current layer and switches to another layer indexed by n.
--- The current (old) layer will be removed from it's parent with 'cleanup=true'.
---
---@param n number @(int) The layer indexed by n will display.
---@return self @(void)
function LayerMultiplex:switchToAndReleaseMe(n)
end

--- @brief MenuItem base class.
---
---  Subclass MenuItem (or any subclass) to create your custom MenuItem objects.
---@class cc.MenuItem:cc.Node
local MenuItem = {}
cc.MenuItem = MenuItem

--- Activate the item.
---@return self @(void)
function MenuItem:activate()
end

--- Returns whether or not the item is enabled.
---@return boolean @(bool)
function MenuItem:isEnabled()
end

--- Returns whether or not the item is selected.
---@return boolean @(bool)
function MenuItem:isSelected()
end

--- Returns the outside box.
---@return rect_table @(cocos2d::Rect)
function MenuItem:rect()
end

--- The item was selected (not activated), similar to "mouse-over".
---@return self @(void)
function MenuItem:selected()
end

--- Enables or disables the item.
---@param value boolean @(bool)
---@return self @(void)
function MenuItem:setEnabled(value)
end

--- The item was unselected.
---@return self @(void)
function MenuItem:unselected()
end

--- @brief An abstract class for "label" MenuItemLabel items.
---  Any Node that supports the LabelProtocol protocol can be added.
---  Supported nodes:
---  - BitmapFontAtlas
---  - LabelAtlas
---  - LabelTTF
---  - Label
---@class cc.MenuItemLabel:cc.MenuItem
local MenuItemLabel = {}
cc.MenuItemLabel = MenuItemLabel

--- Gets the color that will be used when the item is disabled.
---@return color3b_table @(const cocos2d::Color3B&)
function MenuItemLabel:getDisabledColor()
end

--- Gets the label that is rendered.
---@return cc.Node @(cocos2d::Node*)
function MenuItemLabel:getLabel()
end

--- Get the inner string of the inner label.
---@return string @(std::string_view)
function MenuItemLabel:getString()
end

--- Initializes a MenuItemLabel with a Label, target and selector.
---@param label cc.Node @(cocos2d::Node*)
---@param callback function @(cocos2d::ccMenuCallback)
---@return boolean @(bool)
function MenuItemLabel:initWithLabel(label, callback)
end

--- Sets the color that will be used when the item is disabled.
---@param color color3b_table @(cocos2d::Color3B)
---@return self @(void)
function MenuItemLabel:setDisabledColor(color)
end

--- Sets the label that is rendered.
---@param node cc.Node @(cocos2d::Node*)
---@return self @(void)
function MenuItemLabel:setLabel(node)
end

--- Sets a new string to the inner label.
---@param label string @(std::string_view)
---@return self @(void)
function MenuItemLabel:setString(label)
end

--- Creates a MenuItemLabel with a Label. Target and selector will be nil.
--- (static)
---@param label cc.Node @(cocos2d::Node*)
---@return cc.MenuItemLabel @(cocos2d::MenuItemLabel*)
function MenuItemLabel:create(label)
end

--- @brief A MenuItemAtlasFont.
---  Helper class that creates a MenuItemLabel class with a LabelAtlas.
---@class cc.MenuItemAtlasFont:cc.MenuItemLabel
local MenuItemAtlasFont = {}
cc.MenuItemAtlasFont = MenuItemAtlasFont

--- Initializes a menu item from a string and atlas with a targetselector.
---@param value string @(std::string_view)
---@param charMapFile string @(std::string_view)
---@param itemWidth number @(int)
---@param itemHeight number @(int)
---@param startCharMap number @(char)
---@param callback function @(cocos2d::ccMenuCallback)
---@return boolean @(bool)
function MenuItemAtlasFont:initWithString(value, charMapFile, itemWidth, itemHeight, startCharMap, callback)
end

--- @brief A MenuItemFont.
---  Helper class that creates a MenuItemLabel class with a Label.
---@class cc.MenuItemFont:cc.MenuItemLabel
local MenuItemFont = {}
cc.MenuItemFont = MenuItemFont

--- Returns the name of the Font.
--- @js getFontNameObj
--- @js NA
---@return string @(std::string_view)
function MenuItemFont:getFontNameObj()
end

--- get font size .
--- @js getFontSize
--- @js NA
---@return number @(int)
function MenuItemFont:getFontSizeObj()
end

--- Initializes a menu item from a string with a targetselector.
---@param value string @(std::string_view)
---@param callback function @(cocos2d::ccMenuCallback)
---@return boolean @(bool)
function MenuItemFont:initWithString(value, callback)
end

---
--- Set the font name .
--- c++ can not overload static and non-static member functions with the same parameter types.
--- so change the name to setFontNameObj.
--- @js setFontName
--- @js NA
---@param name string @(std::string_view)
---@return self @(void)
function MenuItemFont:setFontNameObj(name)
end

--- Set font size.
--- c++ can not overload static and non-static member functions with the same parameter types.
--- so change the name to setFontSizeObj.
--- @js setFontSize
--- @js NA
---@param size number @(int)
---@return self @(void)
function MenuItemFont:setFontSizeObj(size)
end

--- Creates a menu item from a string without targetselector. To be used with MenuItemToggle.
--- (static)
---@param value string @(std::string_view)
---@return cc.MenuItemFont @(cocos2d::MenuItemFont*)
function MenuItemFont:create(value)
end

--- Get the default font name.
--- (static)
---@return string @(std::string_view)
function MenuItemFont:getFontName()
end

--- Get default font size.
--- (static)
---@return number @(int)
function MenuItemFont:getFontSize()
end

--- Set the default font name.
--- (static)
---@param name string @(std::string_view)
---@return self @(void)
function MenuItemFont:setFontName(name)
end

--- Set default font size.
--- (static)
---@param size number @(int)
---@return self @(void)
function MenuItemFont:setFontSize(size)
end

--- @brief MenuItemSprite accepts Node<RGBAProtocol> objects as items.
---  The images has 3 different states:
---  - unselected image
---  - selected image
---  - disabled image
---
---  @since v0.8.0
---@class cc.MenuItemSprite:cc.MenuItem
local MenuItemSprite = {}
cc.MenuItemSprite = MenuItemSprite

--- Gets the image used when the item is disabled.
---@return cc.Node @(cocos2d::Node*)
function MenuItemSprite:getDisabledImage()
end

--- Gets the image used when the item is not selected.
---@return cc.Node @(cocos2d::Node*)
function MenuItemSprite:getNormalImage()
end

--- Gets the image used when the item is selected.
---@return cc.Node @(cocos2d::Node*)
function MenuItemSprite:getSelectedImage()
end

--- Initializes a menu item with a normal, selected and disabled image with a callable object.
---@param normalSprite cc.Node @(cocos2d::Node*)
---@param selectedSprite cc.Node @(cocos2d::Node*)
---@param disabledSprite cc.Node @(cocos2d::Node*)
---@param callback function @(cocos2d::ccMenuCallback)
---@return boolean @(bool)
function MenuItemSprite:initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback)
end

--- Sets the image used when the item is disabled.
---@param image cc.Node @(cocos2d::Node*)
---@return self @(void)
function MenuItemSprite:setDisabledImage(image)
end

--- Sets the image used when the item is not selected.
---@param image cc.Node @(cocos2d::Node*)
---@return self @(void)
function MenuItemSprite:setNormalImage(image)
end

--- Sets the image used when the item is selected.
---@param image cc.Node @(cocos2d::Node*)
---@return self @(void)
function MenuItemSprite:setSelectedImage(image)
end

--- Creates a menu item with a normal, selected and disabled image.
--- (static)
---@param normalSprite cc.Node @(cocos2d::Node*)
---@param selectedSprite cc.Node @(cocos2d::Node*)
---@param disabledSprite cc.Node @(cocos2d::Node*)
---@return cc.MenuItemSprite @(cocos2d::MenuItemSprite*)
function MenuItemSprite:create(normalSprite, selectedSprite, disabledSprite)
end

--- Creates a menu item with a normal, selected and disabled image.
--- (static)
---@param normalSprite cc.Node @(cocos2d::Node*)
---@param selectedSprite cc.Node @(cocos2d::Node*)
---@return cc.MenuItemSprite @(cocos2d::MenuItemSprite*)
function MenuItemSprite:create(normalSprite, selectedSprite)
end

--- @brief MenuItemImage accepts images as items.
---  The images has 3 different states:
---  - unselected image
---  - selected image
---  - disabled image
---
---  For best results try that all images are of the same size.
---@class cc.MenuItemImage:cc.MenuItemSprite
local MenuItemImage = {}
cc.MenuItemImage = MenuItemImage

---@return boolean @(bool)
function MenuItemImage:init()
end

--- Initializes a menu item with a normal, selected and disabled image with a callable object.
---@param normalImage string @(std::string_view)
---@param selectedImage string @(std::string_view)
---@param disabledImage string @(std::string_view)
---@param callback function @(cocos2d::ccMenuCallback)
---@return boolean @(bool)
function MenuItemImage:initWithNormalImage(normalImage, selectedImage, disabledImage, callback)
end

--- Sets the sprite frame for the disabled image.
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return self @(void)
function MenuItemImage:setDisabledSpriteFrame(frame)
end

--- Sets the sprite frame for the normal image.
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return self @(void)
function MenuItemImage:setNormalSpriteFrame(frame)
end

--- Sets the sprite frame for the selected image.
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@return self @(void)
function MenuItemImage:setSelectedSpriteFrame(frame)
end

--- Creates an MenuItemImage.
--- (static)
---@return cc.MenuItemImage @(cocos2d::MenuItemImage*)
function MenuItemImage:create()
end

--- Creates a menu item with a normal and selected image.
--- (static)
---@param normalImage string @(std::string_view)
---@param selectedImage string @(std::string_view)
---@return cc.MenuItemImage @(cocos2d::MenuItemImage*)
function MenuItemImage:create(normalImage, selectedImage)
end

--- Creates a menu item with a normal,selected  and disabled image.
--- (static)
---@param normalImage string @(std::string_view)
---@param selectedImage string @(std::string_view)
---@param disabledImage string @(std::string_view)
---@return cc.MenuItemImage @(cocos2d::MenuItemImage*)
function MenuItemImage:create(normalImage, selectedImage, disabledImage)
end

--- @brief A MenuItemToggle.
---  A simple container class that "toggles" it's inner items.
---  The inner items can be any MenuItem.
---@class cc.MenuItemToggle:cc.MenuItem
local MenuItemToggle = {}
cc.MenuItemToggle = MenuItemToggle

--- Add more menu item.
---@param item cc.MenuItem @(cocos2d::MenuItem*)
---@return self @(void)
function MenuItemToggle:addSubItem(item)
end

--- Gets the index of the selected item.
---@return number @(unsigned int)
function MenuItemToggle:getSelectedIndex()
end

--- Return the selected item.
---@return cc.MenuItem @(cocos2d::MenuItem*)
function MenuItemToggle:getSelectedItem()
end

--- Initializes a menu item with a item.
---@param item cc.MenuItem @(cocos2d::MenuItem*)
---@return boolean @(bool)
function MenuItemToggle:initWithItem(item)
end

--- Sets the index of the selected item.
---@param index number @(unsigned int)
---@return self @(void)
function MenuItemToggle:setSelectedIndex(index)
end

--- Sets the array that contains the subitems.
---@param items cc.MenuItem [] @(cocos2d::Vector<cocos2d::MenuItem *>)
---@return self @(void)
function MenuItemToggle:setSubItems(items)
end

--- @brief A Menu for touch handling.
---
--- Features and Limitation:
---  - You can add MenuItem objects in runtime using addChild.
---  - But the only accepted children are MenuItem objects.
---@class cc.Menu:cc.Node
local Menu = {}
cc.Menu = Menu

--- Align items horizontally.
---@return self @(void)
function Menu:alignItemsHorizontally()
end

--- Align items horizontally with padding.
--- @since v0.7.2
---@param padding number @(float)
---@return self @(void)
function Menu:alignItemsHorizontallyWithPadding(padding)
end

--- Align items vertically.
---@return self @(void)
function Menu:alignItemsVertically()
end

--- Align items vertically with padding.
--- @since v0.7.2
---@param padding number @(float)
---@return self @(void)
function Menu:alignItemsVerticallyWithPadding(padding)
end

--- initializes a Menu with a NSArray of MenuItem objects
---@param arrayOfItems cc.MenuItem [] @(cocos2d::Vector<cocos2d::MenuItem *>)
---@return boolean @(bool)
function Menu:initWithArray(arrayOfItems)
end

---
--- Determines if the menu is enabled.
--- @see `setEnabled(bool)`.
---@return boolean @(bool) whether the menu is enabled or not.
function Menu:isEnabled()
end

---
--- Set whether the menu is enabled. If set to false, interacting with the menu
--- will have no effect.
--- The default value is true, a menu is enabled by default.
---@param value boolean @(bool) true if menu is to be enabled, false if menu is to be disabled.
---@return self @(void)
function Menu:setEnabled(value)
end

--- @class MotionStreak.
--- @brief Creates a trailing path.
---@class cc.MotionStreak:cc.Node
local MotionStreak = {}
cc.MotionStreak = MotionStreak

---
--- @js NA
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function MotionStreak:getBlendFunc()
end

--- Get stroke.
---
---@return number @(float) float stroke.
function MotionStreak:getStroke()
end

---@return cc.Texture2D @(cocos2d::Texture2D*)
function MotionStreak:getTexture()
end

--- initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture
---@param fade number @(float)
---@param minSeg number @(float)
---@param stroke number @(float)
---@param color color3b_table @(cocos2d::Color3B)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return boolean @(bool)
function MotionStreak:initWithFade(fade, minSeg, stroke, color, texture)
end

--- initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename
---@param fade number @(float)
---@param minSeg number @(float)
---@param stroke number @(float)
---@param color color3b_table @(cocos2d::Color3B)
---@param path string @(std::string_view)
---@return boolean @(bool)
function MotionStreak:initWithFade(fade, minSeg, stroke, color, path)
end

--- When fast mode is enabled, new points are added faster but with lower precision.
---
---@return boolean @(bool) True if fast mode is enabled.
function MotionStreak:isFastMode()
end

--- Is the starting position initialized or not.
---
---@return boolean @(bool) True if the starting position is initialized.
function MotionStreak:isStartingPositionInitialized()
end

--- Remove all living segments of the ribbon.
---@return self @(void)
function MotionStreak:reset()
end

---
--- @js NA
--- @lua NA
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function MotionStreak:setBlendFunc(blendFunc)
end

--- Sets fast mode or not.
---
---@param bFastMode boolean @(bool) True if enabled fast mode.
---@return self @(void)
function MotionStreak:setFastMode(bFastMode)
end

--- Sets the starting position initialized or not.
---
---@param bStartingPositionInitialized boolean @(bool) True if initialized the starting position.
---@return self @(void)
function MotionStreak:setStartingPositionInitialized(bStartingPositionInitialized)
end

--- Set stroke.
---
---@param stroke number @(float) The width of stroke.
---@return self @(void)
function MotionStreak:setStroke(stroke)
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function MotionStreak:setTexture(texture)
end

--- Color used for the tint.
---
---@param colors color3b_table @(cocos2d::Color3B) The color used for the tint.
---@return self @(void)
function MotionStreak:tintWithColor(colors)
end

--- Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture.
---
--- (static)
---@param timeToFade number @(float) The fade time, in seconds.
---@param minSeg number @(float) The minimum segments.
---@param strokeWidth number @(float) The width of stroke.
---@param strokeColor color3b_table @(cocos2d::Color3B) The color of stroke.
---@param texture cc.Texture2D @(cocos2d::Texture2D*) The texture name of stoke.
---@return cc.MotionStreak @(cocos2d::MotionStreak*) An autoreleased MotionStreak object.
function MotionStreak:create(timeToFade, minSeg, strokeWidth, strokeColor, texture)
end

--- Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture
--- filename.
---
--- (static)
---@param timeToFade number @(float) The fade time, in seconds.
---@param minSeg number @(float) The minimum segments.
---@param strokeWidth number @(float) The width of stroke.
---@param strokeColor color3b_table @(cocos2d::Color3B) The color of stroke.
---@param imagePath string @(std::string_view) The texture file name of stoke.
---@return cc.MotionStreak @(cocos2d::MotionStreak*) An autoreleased MotionStreak object.
function MotionStreak:create(timeToFade, minSeg, strokeWidth, strokeColor, imagePath)
end

---
--- @brief Base class for Grid Node.
---@class cc.NodeGrid:cc.Node
local NodeGrid = {}
cc.NodeGrid = NodeGrid

---
--- @js NA
---@return cc.GridBase @(const cocos2d::GridBase*)
function NodeGrid:getGrid()
end

--- Get a Grid Node.
---
---@return cc.GridBase @(cocos2d::GridBase*) Return a GridBase.
function NodeGrid:getGrid()
end

---
--- @brief Get the effect grid rect.
---@return rect_table @(const cocos2d::Rect&) Return the effect grid rect.
function NodeGrid:getGridRect()
end

---
--- Changes a grid object that is used when applying effects.
---
---@param grid cc.GridBase @(cocos2d::GridBase*)  A Grid object that is used when applying effects.
---@return self @(void)
function NodeGrid:setGrid(grid)
end

---
--- @brief Set the effect grid rect.
---@param gridRect rect_table @(cocos2d::Rect) The effect grid rect.
---@return self @(void)
function NodeGrid:setGridRect(gridRect)
end

--- Set the Grid Target.
---
---@param target cc.Node @(cocos2d::Node*) A Node is used to set the Grid Target.
---@return self @(void)
function NodeGrid:setTarget(target)
end

--- (static)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.NodeGrid @(cocos2d::NodeGrid*)
function NodeGrid:create(rect)
end

--- Create a Grid Node.
---
--- (static)
---@return cc.NodeGrid @(cocos2d::NodeGrid*) An autorelease Grid Node.
function NodeGrid:create()
end

--- @class ParticleBatchNode
--- @brief ParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
--- (often known as "batch draw").
---
--- A ParticleBatchNode can reference one and only one texture (one image file, one texture atlas).
--- Only the ParticleSystems that are contained in that texture can be added to the SpriteBatchNode.
--- All ParticleSystems added to a SpriteBatchNode are drawn in one OpenGL ES draw call.
--- If the ParticleSystems are not added to a ParticleBatchNode then an OpenGL ES draw call will be needed for each one,
--- which is less efficient.
---
---  *
--- Limitations:
--- - At the moment only ParticleSystemQuad is supported
--- - All systems need to be drawn with the same parameters, blend function, aliasing, texture
---
--- Most efficient usage
--- - Initialize the ParticleBatchNode with the texture and enough capacity for all the particle systems
--- - Initialize all particle systems and add them as child to the batch node
--- @since v1.1
---@class cc.ParticleBatchNode:cc.Node
local ParticleBatchNode = {}
cc.ParticleBatchNode = ParticleBatchNode

--- Disables a particle by inserting a 0'd quad into the texture atlas.
---
---@param particleIndex number @(int) The index of the particle.
---@return self @(void)
function ParticleBatchNode:disableParticle(particleIndex)
end

---
--- @js NA
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function ParticleBatchNode:getBlendFunc()
end

---@return cc.Texture2D @(cocos2d::Texture2D*)
function ParticleBatchNode:getTexture()
end

--- Gets the texture atlas used for drawing the quads.
---
---@return cc.TextureAtlas @(cocos2d::TextureAtlas*) The texture atlas used for drawing the quads.
function ParticleBatchNode:getTextureAtlas()
end

--- initializes the particle system with the name of a file on disk (for a list of supported formats look at the
--- Texture2D class), a capacity of particles
---@param fileImage string @(std::string_view)
---@param capacity number @(int)
---@return boolean @(bool)
function ParticleBatchNode:initWithFile(fileImage, capacity)
end

--- initializes the particle system with Texture2D, a capacity of particles
---@param tex cc.Texture2D @(cocos2d::Texture2D*)
---@param capacity number @(int)
---@return boolean @(bool)
function ParticleBatchNode:initWithTexture(tex, capacity)
end

--- Inserts a child into the ParticleBatchNode.
---
---@param system cc.ParticleSystem @(cocos2d::ParticleSystem*) A given particle system.
---@param index number @(int) The insert index.
---@return self @(void)
function ParticleBatchNode:insertChild(system, index)
end

---@param doCleanup boolean @(bool)
---@return self @(void)
function ParticleBatchNode:removeAllChildrenWithCleanup(doCleanup)
end

--- Remove a child of the ParticleBatchNode.
---
---@param index number @(int) The index of the child.
---@param doCleanup boolean @(bool) True if all actions and callbacks on this node should be removed, false otherwise.
---@return self @(void)
function ParticleBatchNode:removeChildAtIndex(index, doCleanup)
end

---
--- @code
--- When this function bound into js or lua,the parameter will be changed
--- In js: var setBlendFunc(var src, var dst)
--- @endcode
--- @lua NA
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function ParticleBatchNode:setBlendFunc(blendFunc)
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function ParticleBatchNode:setTexture(texture)
end

--- Sets the texture atlas used for drawing the quads.
---
---@param atlas cc.TextureAtlas @(cocos2d::TextureAtlas*) The texture atlas used for drawing the quads.
---@return self @(void)
function ParticleBatchNode:setTextureAtlas(atlas)
end

--- Create the particle system with the name of a file on disk (for a list of supported formats look at the
--- Texture2D class), a capacity of particles.
---
--- (static)
---@param fileImage string @(std::string_view) A given file name.
---@param capacity number @(int) A capacity of particles.
---@return cc.ParticleBatchNode @(cocos2d::ParticleBatchNode*) An autoreleased ParticleBatchNode object.
function ParticleBatchNode:create(fileImage, capacity)
end

--- Create the particle system with the name of a file on disk (for a list of supported formats look at the
--- Texture2D class), a capacity of particles.
---
--- (static)
---@param fileImage string @(std::string_view) A given file name.
---@return cc.ParticleBatchNode @(cocos2d::ParticleBatchNode*) An autoreleased ParticleBatchNode object.
function ParticleBatchNode:create(fileImage)
end

--- Create the particle system with Texture2D, a capacity of particles, which particle system to use.
---
--- @js NA
--- (static)
---@param tex cc.Texture2D @(cocos2d::Texture2D*) A given texture.
---@param capacity number @(int) A capacity of particles.
---@return cc.ParticleBatchNode @(cocos2d::ParticleBatchNode*) An autoreleased ParticleBatchNode object.
function ParticleBatchNode:createWithTexture(tex, capacity)
end

--- Create the particle system with Texture2D, a capacity of particles, which particle system to use.
---
--- @js NA
--- (static)
---@param tex cc.Texture2D @(cocos2d::Texture2D*) A given texture.
---@return cc.ParticleBatchNode @(cocos2d::ParticleBatchNode*) An autoreleased ParticleBatchNode object.
function ParticleBatchNode:createWithTexture(tex)
end

--- @class SpriteFrameCache
--- @brief Singleton that handles the loading of the sprite frames.
---
---  The SpriteFrameCache loads SpriteFrames from a .plist file.
---  A SpriteFrame contains information about how to use a sprite
---  located in a sprite sheet.
---
---  The .plist file contains the following elements:
---
---  - `frames`:
---    Dictionary of sprites. Key is the sprite's name, value a dict containing the sprite frame data.
---    A sprite frame consists of the following values:
---     - `spriteOffset`:     difference vector between the original sprite's center and the center of the trimmed sprite
---     - `spriteSize`:       size of the trimmed sprite
---     - `spriteSourceSize`: size of the original sprite
---     - `textureRect`:      the position of the sprite in the sprite sheet
---     - `textureRotated`:   true if the sprite is rotated clockwise
---     - `anchor`:           anchor point in normalized coordinates (optional)
---    Optional values when using polygon outlines
---     - `triangles`:        3 indices per triangle, pointing to vertices and verticesUV coordinates
---     - `vertices`:         vertices in sprite coordinates, each vertex consists of a pair of x and y coordinates
---     - `verticesUV`:       vertices in the sprite sheet, each vertex consists of a pair of x and y coordinates
---
---  - `metadata`:
---    Dictionary containing additional information about the sprite sheet:
---      - `format`:          plist file format, currently 3
---      - `size`:            size of the texture (optional)
---      - `textureFileName`: name of the texture's image file
---
---  Use one of the following tools to create the .plist file and sprite sheet:
---  - [TexturePacker](https:www.codeandweb.comtexturepackercocos2d)
---  - [Zwoptex](https:zwopple.comzwoptex)
---
---  @since v0.9
---  @js cc.spriteFrameCache
---@class cc.SpriteFrameCache:cc.Ref
local SpriteFrameCache = {}
cc.SpriteFrameCache = SpriteFrameCache

--- Adds an sprite frame with a given name.
--- If the name already exists, then the contents of the old name will be replaced with the new one.
---
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*) A certain sprite frame.
---@param frameName string @(std::string_view) The name of the sprite frame.
---@return self @(void)
function SpriteFrameCache:addSpriteFrame(frame, frameName)
end

---@param spriteFrame cc.SpriteFrame @(cocos2d::SpriteFrame*)
---@param capInsets rect_table @(cocos2d::Rect)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function SpriteFrameCache:addSpriteFrameCapInset(spriteFrame, capInsets, texture)
end

--- Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
--- @js addSpriteFrames
--- @lua addSpriteFrames
---
---@param spriteSheetFileName string @(std::string_view) file name.
---@param texture cc.Texture2D @(cocos2d::Texture2D*) Texture pointer.
---@param spriteSheetFormat number @(uint32_t)
---@return self @(void)
function SpriteFrameCache:addSpriteFrames(spriteSheetFileName, texture, spriteSheetFormat)
end

--- Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
--- @since v0.99.5
--- @js addSpriteFrames
--- @lua addSpriteFrames
---
---@param spriteSheetFileName string @(std::string_view) Plist file name.
---@param textureFileName string @(std::string_view) Texture file name.
---@param spriteSheetFormat number @(uint32_t)
---@return self @(void)
function SpriteFrameCache:addSpriteFrames(spriteSheetFileName, textureFileName, spriteSheetFormat)
end

--- Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
--- @js addSpriteFrames
--- @lua addSpriteFrames
---
---@param spriteSheetFileName string @(std::string_view) file name.
---@param texture cc.Texture2D @(cocos2d::Texture2D*) Texture pointer.
---@return self @(void)
function SpriteFrameCache:addSpriteFrames(spriteSheetFileName, texture)
end

--- Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
--- @since v0.99.5
--- @js addSpriteFrames
--- @lua addSpriteFrames
---
---@param spriteSheetFileName string @(std::string_view) Plist file name.
---@param textureFileName string @(std::string_view) Texture file name.
---@return self @(void)
function SpriteFrameCache:addSpriteFrames(spriteSheetFileName, textureFileName)
end

--- Adds multiple Sprite Frames from a plist file.
--- A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png.
--- If you want to use another texture, you should use the addSpriteFramesWithFile(std::string_view plist, const
--- std::string& textureFileName) method.
--- @js addSpriteFrames
--- @lua addSpriteFrames
---
---@param spriteSheetFileName string @(std::string_view) file name.
---@param spriteSheetFormat number @(uint32_t)
---@return self @(void)
function SpriteFrameCache:addSpriteFrames(spriteSheetFileName, spriteSheetFormat)
end

--- Adds multiple Sprite Frames from a plist file.
--- A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png.
--- If you want to use another texture, you should use the addSpriteFramesWithFile(std::string_view plist, const
--- std::string& textureFileName) method.
--- @js addSpriteFrames
--- @lua addSpriteFrames
---
---@param spriteSheetFileName string @(std::string_view) file name.
---@return self @(void)
function SpriteFrameCache:addSpriteFrames(spriteSheetFileName)
end

---@param spriteSheetFormat number @(uint32_t)
---@return self @(void)
function SpriteFrameCache:deregisterSpriteSheetLoader(spriteSheetFormat)
end

--- Delete frame from cache, rebuild index
---@param frameName string @(std::string_view)
---@return boolean @(bool)
function SpriteFrameCache:eraseFrame(frameName)
end

---@param frame string @(std::string_view)
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*)
function SpriteFrameCache:findFrame(frame)
end

--- Returns an Sprite Frame that was previously added.
--- If the name is not found it will return nil.
--- You should retain the returned copy if you are going to use it.
--- @js getSpriteFrame
--- @lua getSpriteFrame
---
---@param name string @(std::string_view) A certain sprite frame name.
---@return cc.SpriteFrame @(cocos2d::SpriteFrame*) The sprite frame.
function SpriteFrameCache:getSpriteFrame(name)
end

---@param spriteSheetFormat number @(uint32_t)
---@return cc.ISpriteSheetLoader @(cocos2d::ISpriteSheetLoader*)
function SpriteFrameCache:getSpriteSheetLoader(spriteSheetFormat)
end

--- Initialize method.
---
---@return boolean @(bool) if success return true.
function SpriteFrameCache:init()
end

--- Check if multiple Sprite Frames from a plist file have been loaded.
--- @js NA
--- @lua NA
---
---@param plist string @(std::string_view) Plist file name.
---@return boolean @(bool) True if the file is loaded.
function SpriteFrameCache:isSpriteFramesWithFileLoaded(plist)
end

---@param spriteSheetFileName string @(std::string_view)
---@return boolean @(bool)
function SpriteFrameCache:reloadTexture(spriteSheetFileName)
end

--- Deletes an sprite frame from the sprite frame cache.
---
---@param name string @(std::string_view) The name of the sprite frame that needs to removed.
---@return self @(void)
function SpriteFrameCache:removeSpriteFrameByName(name)
end

--- Purges the dictionary of loaded sprite frames.
--- Call this method if you receive the "Memory Warning".
--- In the short term: it will free some resources preventing your app from being killed.
--- In the medium term: it will allocate more resources.
--- In the long term: it will be the same.
---@return self @(void)
function SpriteFrameCache:removeSpriteFrames()
end

--- Removes multiple Sprite Frames from a plist file.
--- Sprite Frames stored in this file will be removed.
--- It is convenient to call this method when a specific texture needs to be removed.
--- @since v0.99.5
---
---@param plist string @(std::string_view) The name of the plist that needs to removed.
---@return self @(void)
function SpriteFrameCache:removeSpriteFramesFromFile(plist)
end

--- Removes multiple Sprite Frames from a plist file content.
--- Sprite Frames stored in this file will be removed.
--- It is convenient to call this method when a specific texture needs to be removed.
---
--- @js NA
---@param plist_content string @(std::string_view) The string of the plist content that needs to removed.
---@return self @(void)
function SpriteFrameCache:removeSpriteFramesFromFileContent(plist_content)
end

--- Removes all Sprite Frames associated with the specified textures.
--- It is convenient to call this method when a specific texture needs to be removed.
--- @since v0.995.
---
---@param texture cc.Texture2D @(cocos2d::Texture2D*) The texture that needs to removed.
---@return self @(void)
function SpriteFrameCache:removeSpriteFramesFromTexture(texture)
end

--- Removes unused sprite frames.
--- Sprite Frames that have a retain count of 1 will be deleted.
--- It is convenient to call this method after when starting a new Scene.
--- @js NA
---@return self @(void)
function SpriteFrameCache:removeUnusedSpriteFrames()
end

--- Returns the shared instance of the Sprite Frame cache.
---
--- @js NA
--- (static)
---@return cc.SpriteFrameCache @(cocos2d::SpriteFrameCache*) The instance of the Sprite Frame Cache.
function SpriteFrameCache:getInstance()
end

---
--- Particle emission mask cache.
--- @since axmol-1.0.0b8
---@class cc.ParticleEmissionMaskCache:cc.Ref
local ParticleEmissionMaskCache = {}
cc.ParticleEmissionMaskCache = ParticleEmissionMaskCache

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param imageTexture cc.Image @(cocos2d::Image*) Image object containing texture data with alpha channel.
---@param alphaThreshold number @(float) The threshold at which pixels are picked, If a pixel's alpha channel is greater than
---@param inverted boolean @(bool) Inverts the pick condition so that If a pixel's alpha channel is lower than alphaThreshold then
---@param inbetweenSamples number @(int) How many times should pixels be filled inbetween, this value should be increased If
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, imageTexture, alphaThreshold, inverted, inbetweenSamples)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param texturePath string @(std::string_view) Path of the texture that holds alpha data.
---@param alphaThreshold number @(float) The threshold at which pixels are picked, If a pixel's alpha channel is greater than
---@param inverted boolean @(bool) Inverts the pick condition so that If a pixel's alpha channel is lower than alphaThreshold then
---@param inbetweenSamples number @(int) How many times should pixels be filled inbetween, this value should be increased If
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, texturePath, alphaThreshold, inverted, inbetweenSamples)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param imageTexture cc.Image @(cocos2d::Image*) Image object containing texture data with alpha channel.
---@param alphaThreshold number @(float) The threshold at which pixels are picked, If a pixel's alpha channel is greater than
---@param inverted boolean @(bool) Inverts the pick condition so that If a pixel's alpha channel is lower than alphaThreshold then
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, imageTexture, alphaThreshold, inverted)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param texturePath string @(std::string_view) Path of the texture that holds alpha data.
---@param alphaThreshold number @(float) The threshold at which pixels are picked, If a pixel's alpha channel is greater than
---@param inverted boolean @(bool) Inverts the pick condition so that If a pixel's alpha channel is lower than alphaThreshold then
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, texturePath, alphaThreshold, inverted)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param imageTexture cc.Image @(cocos2d::Image*) Image object containing texture data with alpha channel.
---@param alphaThreshold number @(float) The threshold at which pixels are picked, If a pixel's alpha channel is greater than
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, imageTexture, alphaThreshold)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param texturePath string @(std::string_view) Path of the texture that holds alpha data.
---@param alphaThreshold number @(float) The threshold at which pixels are picked, If a pixel's alpha channel is greater than
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, texturePath, alphaThreshold)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param imageTexture cc.Image @(cocos2d::Image*) Image object containing texture data with alpha channel.
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, imageTexture)
end

--- Bakes a particle emission mask from texture data on cpu and stores it in memory by it's name.
--- If the mask already exists then it will be overwritten.
---
--- alphaThreshold then it will be picked.
--- it will be picked.
--- you're planning to scale the emission shape up. WARNING: it will use more memory.
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@param texturePath string @(std::string_view) Path of the texture that holds alpha data.
---@return self @(void)
function ParticleEmissionMaskCache:bakeEmissionMask(maskId, texturePath)
end

--- Remove all baked masks and releases their data from memory.
---@return self @(void)
function ParticleEmissionMaskCache:removeAllMasks()
end

--- Removes a baked mask and releases the data from memory with the specified name if it exists.
---
---@param maskId string @(std::string_view) The id of the mask, FOURCC starts with '#', such as "#abcd"
---@return self @(void)
function ParticleEmissionMaskCache:removeMask(maskId)
end

--- (static)
---@return cc.ParticleEmissionMaskCache @(cocos2d::ParticleEmissionMaskCache*)
function ParticleEmissionMaskCache:getInstance()
end

--- @class ParticleSystem
--- @brief Particle System base class.
--- Attributes of a Particle System:
--- - emission rate of the particles
--- - Gravity Mode (Mode A):
--- - gravity
--- - direction
--- - speed +-  variance
--- - tangential acceleration +- variance
--- - radial acceleration +- variance
--- - Radius Mode (Mode B):
--- - startRadius +- variance
--- - endRadius +- variance
--- - rotate +- variance
--- - Properties common to all modes:
--- - life +- life variance
--- - start spin +- variance
--- - end spin +- variance
--- - start size +- variance
--- - end size +- variance
--- - start color +- variance
--- - end color +- variance
--- - life +- variance
--- - blending function
--- - texture
---
--- Cocos2d also supports particles generated by Particle Designer (http:particledesigner.71squared.com).
--- 'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guaranteed in cocos2d,
--- cocos2d uses a another approach, but the results are almost identical.
---
--- Cocos2d supports all the variables used by Particle Designer plus a bit more:
--- - spinning particles (supported when using ParticleSystemQuad)
--- - tangential acceleration (Gravity mode)
--- - radial acceleration (Gravity mode)
--- - radius direction (Radius mode) (Particle Designer supports outwards to inwards direction only)
---
--- It is possible to customize any of the above mentioned properties in runtime. Example:
---
--- @code
--- emitter.radialAccel = 15;
--- emitter.startSpin = 0;
--- @endcode
---
---@class cc.ParticleSystem:cc.Node
local ParticleSystem = {}
cc.ParticleSystem = ParticleSystem

--- Add a particle animation index based on tex coords spicified.
--- you can specify which index you want to override in this function
---
---
---@param index number @(unsigned short) Index id to add the frame to or override it with the new rect
---@param rect rect_table @(cocos2d::Rect) Rect containting data about tex coords in pixels
---@param rotated boolean @(bool) Not implemented.
---@return boolean @(bool) Returns true of the index was successfully found and added. Otherwise, false
function ParticleSystem:addAnimationIndex(index, rect, rotated)
end

--- Add a particle animation index based on tex coords spicified.
--- you can specify which index you want to override in this function
---
---
---@param index number @(unsigned short) Index id to add the frame to or override it with the new rect
---@param rect rect_table @(cocos2d::Rect) Rect containting data about tex coords in pixels
---@return boolean @(bool) Returns true of the index was successfully found and added. Otherwise, false
function ParticleSystem:addAnimationIndex(index, rect)
end

--- Add a particle animation index based on tex coords spicified using a sprite frame.
--- you can specify which index you want to override in this function
---
---
---@param index number @(unsigned short) Index id to add the frame to or override it with the new frame
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*) SpriteFrame containting data about tex coords
---@return boolean @(bool) Returns true of the index was successfully found and added. Otherwise, false
function ParticleSystem:addAnimationIndex(index, frame)
end

--- Add a particle animation index based on tex coords spicified using a sprite frame.
---
---
---@param index number @(unsigned short) Index id to add the frame to or override it with the new frame
---@param frameName string @(std::string_view) SpriteFrame name to search for
---@return boolean @(bool) Returns true of the index was successfully found and added. Otherwise, false
function ParticleSystem:addAnimationIndex(index, frameName)
end

--- Add a particle animation index based on tex coords spicified using a sprite frame.
--- The index is automatically incremented on each addition.
---
---
---@param frame cc.SpriteFrame @(cocos2d::SpriteFrame*) SpriteFrame containting data about tex coords
---@return boolean @(bool) Returns true of the index was successfully found and added. Otherwise, false
function ParticleSystem:addAnimationIndex(frame)
end

--- Add a particle animation index based on tex coords spicified using a sprite frame.
--- The index is automatically incremented on each addition.
---
---
---@param frameName string @(std::string_view) SpriteFrame name to search for
---@return boolean @(bool) Returns true of the index was successfully found and added. Otherwise, false
function ParticleSystem:addAnimationIndex(frameName)
end

---@param count number @(int)
---@param animationIndex number @(int)
---@param animationCellIndex number @(int)
---@return self @(void)
function ParticleSystem:addParticles(count, animationIndex, animationCellIndex)
end

---@param count number @(int)
---@param animationIndex number @(int)
---@return self @(void)
function ParticleSystem:addParticles(count, animationIndex)
end

---@param count number @(int)
---@return self @(void)
function ParticleSystem:addParticles(count)
end

--- Gets the angle of each particle.
---
---@return number @(float) The angle of each particle.
function ParticleSystem:getAngle()
end

--- Gets the angle variance of each particle.
---
---@return number @(float) The angle variance of each particle.
function ParticleSystem:getAngleVar()
end

--- Gets the index of system in batch node array.
---
---@return number @(int) The index of system in batch node array.
function ParticleSystem:getAtlasIndex()
end

--- Gets the batch node.
---
---@return cc.ParticleBatchNode @(cocos2d::ParticleBatchNode*) The batch node.
function ParticleSystem:getBatchNode()
end

---
--- @js NA
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function ParticleSystem:getBlendFunc()
end

--- Gets how many seconds the emitter will run. -1 means 'forever'.
---
---@return number @(float) The seconds that the emitter will run. -1 means 'forever'.
function ParticleSystem:getDuration()
end

--- Gets the emission rate of the particles.
---
---@return number @(float) The emission rate of the particles.
function ParticleSystem:getEmissionRate()
end

--- Switch between different kind of emitter modes:
--- - kParticleModeGravity: uses gravity, speed, radial and tangential acceleration.
--- - kParticleModeRadius: uses radius movement + rotation.
---
---@return cc.ParticleSystem.Mode @(cocos2d::ParticleSystem::Mode) The mode of the emitter.
function ParticleSystem:getEmitterMode()
end

--- Gets the end color and end color variation of each particle.
---
---@return color4f_table @(const cocos2d::Color4F&) The end color and end color variation of each particle.
function ParticleSystem:getEndColor()
end

--- Gets the end color variance of each particle.
---
---@return color4f_table @(const cocos2d::Color4F&) The end color variance of each particle.
function ParticleSystem:getEndColorVar()
end

--- Gets the end radius.
---
---@return number @(float) The end radius.
function ParticleSystem:getEndRadius()
end

--- Gets the end radius variance.
---
---@return number @(float) The end radius variance.
function ParticleSystem:getEndRadiusVar()
end

--- Gets the end size in pixels of each particle.
---
---@return number @(float) The end size in pixels of each particle.
function ParticleSystem:getEndSize()
end

--- Gets the end size variance in pixels of each particle.
---
---@return number @(float) The end size variance in pixels of each particle.
function ParticleSystem:getEndSizeVar()
end

--- Gets the end spin of each particle.
---
---@return number @(float) The end spin of each particle.
function ParticleSystem:getEndSpin()
end

--- Gets the end spin variance of each particle.
---
---@return number @(float) The end spin variance of each particle.
function ParticleSystem:getEndSpinVar()
end

--- Gets the fixed frame rate count of the particle system.
--- @return Fixed frame rate count of the particle system.
---@return number @(float)
function ParticleSystem:getFixedFPS()
end

--- Gets the gravity.
---
---@return vec2_table @(const cocos2d::Vec2&) The gravity.
function ParticleSystem:getGravity()
end

--- Gets the hue of each particle.
---
---@return number @(float) The hue of each particle.
function ParticleSystem:getHue()
end

--- Gets the hue variance of each particle.
---
---@return number @(float) The hue variance of each particle.
function ParticleSystem:getHueVar()
end

--- Gets the life of each particle.
---
---@return number @(float) The life of each particle.
function ParticleSystem:getLife()
end

--- Gets the life variance of each particle.
---
---@return number @(float) The life variance of each particle.
function ParticleSystem:getLifeVar()
end

--- Gets the Quantity of particles that are being simulated at the moment.
---
---@return number @(unsigned int) The Quantity of particles that are being simulated at the moment.
function ParticleSystem:getParticleCount()
end

--- Gets the position variance of the emitter.
---
---@return vec2_table @(const cocos2d::Vec2&) The position variance of the emitter.
function ParticleSystem:getPosVar()
end

--- Gets the particles movement type: Free or Grouped.
--- @since v0.8
---
---@return cc.ParticleSystem.PositionType @(cocos2d::ParticleSystem::PositionType) The particles movement type.
function ParticleSystem:getPositionType()
end

--- Gets the radial acceleration.
---
---@return number @(float) The radial acceleration.
function ParticleSystem:getRadialAccel()
end

--- Gets the radial acceleration variance.
---
---@return number @(float) The radial acceleration variance.
function ParticleSystem:getRadialAccelVar()
end

---@return string @(std::string_view)
function ParticleSystem:getResourceFile()
end

--- Gets the number of degrees to rotate a particle around the source pos per second.
---
---@return number @(float) The number of degrees to rotate a particle around the source pos per second.
function ParticleSystem:getRotatePerSecond()
end

--- Gets the rotate per second variance.
---
---@return number @(float) The rotate per second variance.
function ParticleSystem:getRotatePerSecondVar()
end

--- Whether or not the rotation of each particle to its direction.
---
---@return boolean @(bool) True if the rotation is the direction.
function ParticleSystem:getRotationIsDir()
end

--- Gets the source position of the emitter.
---
---@return vec2_table @(const cocos2d::Vec2&) The source position of the emitter.
function ParticleSystem:getSourcePosition()
end

--- Gets the spawn angle of each particle
---
---@return number @(float) The angle in degrees of each particle.
function ParticleSystem:getSpawnAngle()
end

--- Sets the spawn angle variance of each particle.
---
---@return number @(float) The angle variance in degrees of each particle.
function ParticleSystem:getSpawnAngleVar()
end

--- Gets the spawn opacity fade in time of each particle.
--- Particles have the ability to spawn while having 0 opacity and gradually start going to 255 opacity with a
--- specified time.
---
---@return number @(float) The spawn opacity fade in time in seconds.
function ParticleSystem:getSpawnFadeIn()
end

--- Gets the spawn opacity fade in time variance of each particle.
--- Particles have the ability to spawn while having 0 opacity and gradually start going to 255 opacity with a
--- specified time.
---
---@return number @(float) The spawn opacity fade in time variance in seconds.
function ParticleSystem:getSpawnFadeInVar()
end

--- Gets the spawn scale fade in time of each particle.
--- Particles have the ability to spawn while having 0.0 size and gradually start going to 1.0 size with a specified
--- time.
---
---@return number @(float) The spawn opacity fade in time in seconds.
function ParticleSystem:getSpawnScaleIn()
end

--- Gets the spawn scale fade in time variance of each particle.
--- Particles have the ability to spawn while having 0.0 size and gradually start going to 1.0 size with a specified
--- time.
---
---@return number @(float) The spawn opacity fade in time variance in seconds.
function ParticleSystem:getSpawnScaleInVar()
end

--- Gets the speed.
---
---@return number @(float) The speed.
function ParticleSystem:getSpeed()
end

--- Gets the speed variance.
---
---@return number @(float) The speed variance.
function ParticleSystem:getSpeedVar()
end

--- Gets the start color of each particle.
---
---@return color4f_table @(const cocos2d::Color4F&) The start color of each particle.
function ParticleSystem:getStartColor()
end

--- Gets the start color variance of each particle.
---
---@return color4f_table @(const cocos2d::Color4F&) The start color variance of each particle.
function ParticleSystem:getStartColorVar()
end

--- Gets the start radius.
---
---@return number @(float) The start radius.
function ParticleSystem:getStartRadius()
end

--- Gets the start radius variance.
---
---@return number @(float) The start radius variance.
function ParticleSystem:getStartRadiusVar()
end

--- Gets the start size in pixels of each particle.
---
---@return number @(float) The start size in pixels of each particle.
function ParticleSystem:getStartSize()
end

--- Gets the start size variance in pixels of each particle.
---
---@return number @(float) The start size variance in pixels of each particle.
function ParticleSystem:getStartSizeVar()
end

--- Gets the start spin of each particle.
---
---@return number @(float) The start spin of each particle.
function ParticleSystem:getStartSpin()
end

--- Gets the start spin variance of each particle.
---
---@return number @(float) The start spin variance of each particle.
function ParticleSystem:getStartSpinVar()
end

--- Gets the tangential acceleration.
---
---@return number @(float) The tangential acceleration.
function ParticleSystem:getTangentialAccel()
end

--- Gets the tangential acceleration variance.
---
---@return number @(float) The tangential acceleration variance.
function ParticleSystem:getTangentialAccelVar()
end

---@return cc.Texture2D @(cocos2d::Texture2D*)
function ParticleSystem:getTexture()
end

--- Gets the time scale of the particle system.
--- @return Time scale of the particle system.
---@return number @(float)
function ParticleSystem:getTimeScale()
end

--- Gets the total number of indices.
---
---@return number @(int) The size of the list holding animation indices.
function ParticleSystem:getTotalAnimationIndices()
end

--- Gets the maximum particles of the system.
---
---@return number @(int) The maximum particles of the system.
function ParticleSystem:getTotalParticles()
end

--- initializes a particle system from a NSDictionary and the path from where to load the png
--- @since v2.1
---@param dictionary tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@param dirname string @(std::string_view)
---@return boolean @(bool)
function ParticleSystem:initWithDictionary(dictionary, dirname)
end

--- initializes a QuadParticleSystem from a Dictionary.
--- @since v0.99.3
---@param dictionary tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@return boolean @(bool)
function ParticleSystem:initWithDictionary(dictionary)
end

--- initializes a ParticleSystem from a plist file.
--- This plist files can be created manually or with Particle Designer:
--- http:particledesigner.71squared.com
--- @since v0.99.3
---@param plistFile string @(std::string_view)
---@return boolean @(bool)
function ParticleSystem:initWithFile(plistFile)
end

--- Initializes a system with a fixed number of particles
---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleSystem:initWithTotalParticles(numberOfParticles)
end

--- Whether or not the particle system is active.
---
---@return boolean @(bool) True if the particle system is active.
function ParticleSystem:isActive()
end

---@return boolean @(bool)
function ParticleSystem:isAnimationReversed()
end

---@return boolean @(bool)
function ParticleSystem:isAnimationSpeedTimescaleIndependent()
end

--- Whether or not the particle system removed self on finish.
---
---@return boolean @(bool) True if the particle system removed self on finish.
function ParticleSystem:isAutoRemoveOnFinish()
end

--- Whether or not the particle system is blend additive.
---
---@return boolean @(bool) True if the particle system is blend additive.
function ParticleSystem:isBlendAdditive()
end

---@return boolean @(bool)
function ParticleSystem:isEmissionShapes()
end

---@return boolean @(bool)
function ParticleSystem:isEmitterAnimated()
end

--- Whether or not the system is full.
---
---@return boolean @(bool) True if the system is full.
function ParticleSystem:isFull()
end

---@return boolean @(bool)
function ParticleSystem:isHSV()
end

---@return boolean @(bool)
function ParticleSystem:isLifeAnimated()
end

---@return boolean @(bool)
function ParticleSystem:isLoopAnimated()
end

--- Are the emissions paused
--- @return True if the emissions are paused, else false
---@return boolean @(bool)
function ParticleSystem:isPaused()
end

---@return boolean @(bool)
function ParticleSystem:isSourcePositionCompatible()
end

---@return self @(void)
function ParticleSystem:pauseEmissions()
end

--- Update the VBO verts buffer which does not use batch node,
--- should be overridden by subclasses.
---@return self @(void)
function ParticleSystem:postStep()
end

--- Empties the container of animation descriptors
---@return self @(void)
function ParticleSystem:resetAnimationDescriptors()
end

--- Resets the count of indices to 0 and empties the animation index array
---@return self @(void)
function ParticleSystem:resetAnimationIndices()
end

--- Resets the count of emission shapes to 0 and empties the emission shapes array
---@return self @(void)
function ParticleSystem:resetEmissionShapes()
end

--- Kill all living particles.
---@return self @(void)
function ParticleSystem:resetSystem()
end

--- Resets the particle system and then advances the particle system and make it seem like it ran for this many
--- seconds. The frame rate used for simulation accuracy is the director's animation interval.
---
--- accurate the simulation will be at the cost of performance. value of -1 means
--- (SIMULATION_USE_GAME_ANIMATION_INTERVAL)
---@param seconds number @(float) Seconds to advance. value of -1 means (SIMULATION_USE_PARTICLE_LIFETIME)
---@param frameRate number @(float) Frame rate to run the simulation with (preferred: 30.0) The higher this value is the more
---@return self @(void)
function ParticleSystem:resimulate(seconds, frameRate)
end

--- Resets the particle system and then advances the particle system and make it seem like it ran for this many
--- seconds. The frame rate used for simulation accuracy is the director's animation interval.
---
--- accurate the simulation will be at the cost of performance. value of -1 means
--- (SIMULATION_USE_GAME_ANIMATION_INTERVAL)
---@param seconds number @(float) Seconds to advance. value of -1 means (SIMULATION_USE_PARTICLE_LIFETIME)
---@return self @(void)
function ParticleSystem:resimulate(seconds)
end

--- Resets the particle system and then advances the particle system and make it seem like it ran for this many
--- seconds. The frame rate used for simulation accuracy is the director's animation interval.
---
--- accurate the simulation will be at the cost of performance. value of -1 means
--- (SIMULATION_USE_GAME_ANIMATION_INTERVAL)
---@return self @(void)
function ParticleSystem:resimulate()
end

---@return self @(void)
function ParticleSystem:resumeEmissions()
end

--- Sets the angle of each particle.
---
---@param angle number @(float) The angle of each particle.
---@return self @(void)
function ParticleSystem:setAngle(angle)
end

--- Sets the angle variance of each particle.
---
---@param angleVar number @(float) The angle variance of each particle.
---@return self @(void)
function ParticleSystem:setAngleVar(angleVar)
end

--- Add a particle animation descriptor with an index.
---
--- pervious animation descriptor
---@param indexOfDescriptor number @(unsigned short) Index of the animation to be added, adding to the same index will just override the
---@param time number @(float) length of the animation in seconds
---@param timeVariance number @(float) Time randomly selected for each different particle added on the animation length
---@param indices number[] @(std::vector<unsigned short>) An array of the indicies
---@param reverse boolean @(bool) Should the animation indicies be played backwards? (default: false)
---@return self @(void)
function ParticleSystem:setAnimationDescriptor(indexOfDescriptor, time, timeVariance, indices, reverse)
end

--- Add a particle animation descriptor with an index.
---
--- pervious animation descriptor
---@param indexOfDescriptor number @(unsigned short) Index of the animation to be added, adding to the same index will just override the
---@param time number @(float) length of the animation in seconds
---@param timeVariance number @(float) Time randomly selected for each different particle added on the animation length
---@param indices number[] @(std::vector<unsigned short>) An array of the indicies
---@return self @(void)
function ParticleSystem:setAnimationDescriptor(indexOfDescriptor, time, timeVariance, indices)
end

--- Add a particle animation descriptor with the index 0.
---
---@param indices number[] @(std::vector<unsigned short>) An array of the indicies
---@param reverse boolean @(bool) Should the animation indicies be played backwards? (default: false)
---@return self @(void)
function ParticleSystem:setAnimationDescriptor(indices, reverse)
end

--- Add a particle animation descriptor with the index 0.
---
---@param indices number[] @(std::vector<unsigned short>) An array of the indicies
---@return self @(void)
function ParticleSystem:setAnimationDescriptor(indices)
end

--- Add all particle animation indices based on cell size and direction spicified if the method of rendering
--- preferred is texture atlas. will erase the array and add new indices from the atlas.
---
---@param unifiedCellSize number @(unsigned int) The size of cell unified.
---@param direction cc.ParticleSystem.TexAnimDir @(cocos2d::ParticleSystem::TexAnimDir) What direction is the atlas
---@return self @(void)
function ParticleSystem:setAnimationIndicesAtlas(unifiedCellSize, direction)
end

--- Add all particle animation indices based on cell size and direction spicified if the method of rendering
--- preferred is texture atlas. will erase the array and add new indices from the atlas.
---
---@param unifiedCellSize number @(unsigned int) The size of cell unified.
---@return self @(void)
function ParticleSystem:setAnimationIndicesAtlas(unifiedCellSize)
end

--- Add all particle animation indices based on cells size and direction spicified using a texture atlas.
--- will erase the array and add new indices from the atlas.
--- This function will automatically figure out your atlas cell size and direction for you! thank her later :)
---@return self @(void)
function ParticleSystem:setAnimationIndicesAtlas()
end

--- Sets wether to start from first cell and go forwards (normal) or last cell and go backwards (reversed)
---@param reverse boolean @(bool)
---@return self @(void)
function ParticleSystem:setAnimationReverse(reverse)
end

--- Sets wether the animation descriptors should follow the time scale of the system or not.
---
---@param independent boolean @(bool) Should the animation descriptor speeds be played independently? (default: false)
---@return self @(void)
function ParticleSystem:setAnimationSpeedTimescaleIndependent(independent)
end

--- Sets the index of system in batch node array.
---
---@param index number @(int) The index of system in batch node array.
---@return self @(void)
function ParticleSystem:setAtlasIndex(index)
end

--- Set the particle system auto removed it self on finish.
---
---@param var boolean @(bool) True if the particle system removed self on finish.
---@return self @(void)
function ParticleSystem:setAutoRemoveOnFinish(var)
end

--- Sets the batch node.
---
---@param batchNode cc.ParticleBatchNode @(cocos2d::ParticleBatchNode*) The batch node.
---@return self @(void)
function ParticleSystem:setBatchNode(batchNode)
end

--- Sets the particle system blend additive.
---
---@param value boolean @(bool) True if the particle system is blend additive.
---@return self @(void)
function ParticleSystem:setBlendAdditive(value)
end

---
--- *@code
--- *When this function bound into js or lua,the parameter will be changed
--- *In js: var setBlendFunc(var src, var dst)
--- *In lua: local setBlendFunc(local src, local dst)
--- *@endcode
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function ParticleSystem:setBlendFunc(blendFunc)
end

--- Sets how many seconds the emitter will run. -1 means 'forever'.
---
---@param duration number @(float) The seconds that the emitter will run. -1 means 'forever'.
---@return self @(void)
function ParticleSystem:setDuration(duration)
end

--- Sets the emission rate of the particles.
---
---@param rate number @(float) The emission rate of the particles.
---@return self @(void)
function ParticleSystem:setEmissionRate(rate)
end

--- Sets wether to use emission shapes for this particle system or not
---@param enabled boolean @(bool)
---@return self @(void)
function ParticleSystem:setEmissionShapes(enabled)
end

--- Enables or disables tex coord animations that are set by the emitter randomly when a particle is emitted.
---@param enabled boolean @(bool)
---@return self @(void)
function ParticleSystem:setEmitterAnimation(enabled)
end

--- Sets the mode of the emitter.
---
---@param mode cc.ParticleSystem.Mode @(cocos2d::ParticleSystem::Mode) The mode of the emitter.
---@return self @(void)
function ParticleSystem:setEmitterMode(mode)
end

--- Sets the end color and end color variation of each particle.
---
---@param color color4f_table @(cocos2d::Color4F) The end color and end color variation of each particle.
---@return self @(void)
function ParticleSystem:setEndColor(color)
end

--- Sets the end color variance of each particle.
---
---@param color color4f_table @(cocos2d::Color4F) The end color variance of each particle.
---@return self @(void)
function ParticleSystem:setEndColorVar(color)
end

--- Sets the end radius.
---
---@param endRadius number @(float) The end radius.
---@return self @(void)
function ParticleSystem:setEndRadius(endRadius)
end

--- Sets the end radius variance.
---
---@param endRadiusVar number @(float) The end radius variance.
---@return self @(void)
function ParticleSystem:setEndRadiusVar(endRadiusVar)
end

--- Sets the end size in pixels of each particle.
---
---@param endSize number @(float) The end size in pixels of each particle.
---@return self @(void)
function ParticleSystem:setEndSize(endSize)
end

--- Sets the end size variance in pixels of each particle.
---
---@param sizeVar number @(float) The end size variance in pixels of each particle.
---@return self @(void)
function ParticleSystem:setEndSizeVar(sizeVar)
end

--- Sets the end spin of each particle.
---
---@param endSpin number @(float) The end spin of each particle.
---@return self @(void)
function ParticleSystem:setEndSpin(endSpin)
end

--- Sets the end spin variance of each particle.
---
---@param endSpinVar number @(float) The end spin variance of each particle.
---@return self @(void)
function ParticleSystem:setEndSpinVar(endSpinVar)
end

--- Sets the fixed frame rate count of the particle system.
--- i.e. if the framerate is set to 30.0 while the refresh rate is greater than 30.0 then the particle system will
--- wait until it hits the 30.0 FPS mark.
--- This is usefull for increasing performance or for creating old-school effects with it.
--- @param Fixed frame rate count of the particle system. (default: 0.0)
---@param frameRate number @(float)
---@return self @(void)
function ParticleSystem:setFixedFPS(frameRate)
end

--- Sets the fixed frame rate count of the particle system.
--- i.e. if the framerate is set to 30.0 while the refresh rate is greater than 30.0 then the particle system will
--- wait until it hits the 30.0 FPS mark.
--- This is usefull for increasing performance or for creating old-school effects with it.
--- @param Fixed frame rate count of the particle system. (default: 0.0)
---@return self @(void)
function ParticleSystem:setFixedFPS()
end

--- Sets the gravity.
---
---@param g vec2_table @(cocos2d::Vec2) The gravity.
---@return self @(void)
function ParticleSystem:setGravity(g)
end

--- Sets the hue of each particle.
---
---@param hue number @(float)
---@return self @(void)
function ParticleSystem:setHue(hue)
end

--- Sets the hue variance of each particle.
---
---@param hue number @(float)
---@return self @(void)
function ParticleSystem:setHueVar(hue)
end

--- Sets the life of each particle.
---
---@param life number @(float) The life of each particle.
---@return self @(void)
function ParticleSystem:setLife(life)
end

--- Enables or disables tex coord animations that are set based on particle life.
---@param enabled boolean @(bool)
---@return self @(void)
function ParticleSystem:setLifeAnimation(enabled)
end

--- Sets the life variance of each particle.
---
---@param lifeVar number @(float) The life variance of each particle.
---@return self @(void)
function ParticleSystem:setLifeVar(lifeVar)
end

--- Enables or disables tex coord animations that are used to make particles play a sequence forever until they die
---@param enabled boolean @(bool)
---@return self @(void)
function ParticleSystem:setLoopAnimation(enabled)
end

--- Choose ALL animation descriptors to be selected at random for particles.
--- This function should be called after you've insertedoverwritten any animation descriptors.
---@return self @(void)
function ParticleSystem:setMultiAnimationRandom()
end

--- Choose what animation descriptors are to be selected at random for particles.
--- This function should be called after you've insertedoverwritten any animation descriptors.
---
---@param animations number[] @(std::vector<unsigned short>) Array of specific indices of animations to play at random
---@return self @(void)
function ParticleSystem:setMultiAnimationRandomSpecific(animations)
end

--- Sets the position variance of the emitter.
---
---@param pos vec2_table @(cocos2d::Vec2) The position variance of the emitter.
---@return self @(void)
function ParticleSystem:setPosVar(pos)
end

--- Sets the particles movement type: Free or Grouped.
--- @since v0.8
---
---@param type cc.ParticleSystem.PositionType @(cocos2d::ParticleSystem::PositionType) The particles movement type.
---@return self @(void)
function ParticleSystem:setPositionType(type)
end

--- Sets the radial acceleration.
---
---@param t number @(float) The radial acceleration.
---@return self @(void)
function ParticleSystem:setRadialAccel(t)
end

--- Sets the radial acceleration variance.
---
---@param t number @(float) The radial acceleration variance.
---@return self @(void)
function ParticleSystem:setRadialAccelVar(t)
end

--- You can specify what rect is used if an index in an animation descriptor wasn't found.
---
---@param rect rect_table @(cocos2d::Rect) Rect containting data about tex coords in pixels
---@return self @(void)
function ParticleSystem:setRectForUndefinedIndices(rect)
end

--- Sets the number of degrees to rotate a particle around the source pos per second.
---
---@param degrees number @(float) The number of degrees to rotate a particle around the source pos per second.
---@return self @(void)
function ParticleSystem:setRotatePerSecond(degrees)
end

--- Sets the rotate per second variance.
---
---@param degrees number @(float) The rotate per second variance.
---@return self @(void)
function ParticleSystem:setRotatePerSecondVar(degrees)
end

--- Sets the rotation of each particle to its direction.
---
---@param t boolean @(bool) True if the rotation is the direction.
---@return self @(void)
function ParticleSystem:setRotationIsDir(t)
end

--- Sets the source position of the emitter.
---
---@param pos vec2_table @(cocos2d::Vec2) The source position of the emitter.
---@return self @(void)
function ParticleSystem:setSourcePosition(pos)
end

--- @} end of PlayableProtocol
---@param sourcePositionCompatible boolean @(bool)
---@return self @(void)
function ParticleSystem:setSourcePositionCompatible(sourcePositionCompatible)
end

--- Sets the spawn angle of each particle
---
---@param angle number @(float) The angle in degrees of each particle.
---@return self @(void)
function ParticleSystem:setSpawnAngle(angle)
end

--- Sets the spawn angle variance of each particle.
---
---@param angle number @(float) The angle variance in degrees of each particle.
---@return self @(void)
function ParticleSystem:setSpawnAngleVar(angle)
end

--- Sets the spawn opacity fade in time of each particle when it's created.
--- Particles have the ability to spawn while having 0 opacity and gradually start going to 255 opacity with a
--- specified time.
---
---@param time number @(float) The spawn opacity fade in time in seconds.
---@return self @(void)
function ParticleSystem:setSpawnFadeIn(time)
end

--- Sets the spawn opacity fade in time variance of each particle when it's created.
--- Particles have the ability to spawn while having 0 opacity and gradually start going to 255 opacity with a
--- specified time.
---
---@param time number @(float) The spawn opacity fade in time variance in seconds.
---@return self @(void)
function ParticleSystem:setSpawnFadeInVar(time)
end

--- Sets the spawn scale fade in time of each particle when it's created.
--- Particles have the ability to spawn while having 0.0 size and gradually start going to 1.0 size with a specified
--- time.
---
---@param time number @(float) The spawn opacity fade in time in seconds.
---@return self @(void)
function ParticleSystem:setSpawnScaleIn(time)
end

--- Sets the spawn scale fade in time variance of each particle when it's created.
--- Particles have the ability to spawn while having 0.0 size and gradually start going to 1.0 size with a specified
--- time.
---
---@param time number @(float) The spawn opacity fade in time variance in seconds.
---@return self @(void)
function ParticleSystem:setSpawnScaleInVar(time)
end

--- Sets the speed.
---
---@param speed number @(float) The speed.
---@return self @(void)
function ParticleSystem:setSpeed(speed)
end

--- Sets the speed variance.
---
---@param speed number @(float) The speed variance.
---@return self @(void)
function ParticleSystem:setSpeedVar(speed)
end

--- Sets the start color of each particle.
---
---@param color color4f_table @(cocos2d::Color4F) The start color of each particle.
---@return self @(void)
function ParticleSystem:setStartColor(color)
end

--- Sets the start color variance of each particle.
---
---@param color color4f_table @(cocos2d::Color4F) The start color variance of each particle.
---@return self @(void)
function ParticleSystem:setStartColorVar(color)
end

--- Sets the start radius.
---
---@param startRadius number @(float) The start radius.
---@return self @(void)
function ParticleSystem:setStartRadius(startRadius)
end

--- Sets the start radius variance.
---
---@param startRadiusVar number @(float) The start radius variance.
---@return self @(void)
function ParticleSystem:setStartRadiusVar(startRadiusVar)
end

--- Sets the start size in pixels of each particle.
---
---@param startSize number @(float) The start size in pixels of each particle.
---@return self @(void)
function ParticleSystem:setStartSize(startSize)
end

--- Sets the start size variance in pixels of each particle.
---
---@param sizeVar number @(float) The start size variance in pixels of each particle.
---@return self @(void)
function ParticleSystem:setStartSizeVar(sizeVar)
end

--- Sets the start spin of each particle.
---
---@param spin number @(float) The start spin of each particle.
---@return self @(void)
function ParticleSystem:setStartSpin(spin)
end

--- Sets the start spin variance of each particle.
---
---@param pinVar number @(float) The start spin variance of each particle.
---@return self @(void)
function ParticleSystem:setStartSpinVar(pinVar)
end

--- Sets the tangential acceleration.
---
---@param t number @(float) The tangential acceleration.
---@return self @(void)
function ParticleSystem:setTangentialAccel(t)
end

--- Sets the tangential acceleration variance.
---
---@param t number @(float) The tangential acceleration variance.
---@return self @(void)
function ParticleSystem:setTangentialAccelVar(t)
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function ParticleSystem:setTexture(texture)
end

--- Sets the time scale of the particle system.
--- @param Time scale of the particle system. (default: 1.0)
---@param scale number @(float)
---@return self @(void)
function ParticleSystem:setTimeScale(scale)
end

--- Sets the time scale of the particle system.
--- @param Time scale of the particle system. (default: 1.0)
---@return self @(void)
function ParticleSystem:setTimeScale()
end

--- Sets the maximum particles of the system.
---
---@param totalParticles number @(int) The maximum particles of the system.
---@return self @(void)
function ParticleSystem:setTotalParticles(totalParticles)
end

--- Advance the particle system and make it seem like it ran for this many seconds.
---
--- accurate the simulation will be at the cost of performance. value of -1 means
--- (SIMULATION_USE_GAME_ANIMATION_INTERVAL)
---@param seconds number @(float) Seconds to advance. value of -1 means (SIMULATION_USE_PARTICLE_LIFETIME)
---@param frameRate number @(float) Frame rate to run the simulation with (preferred: 30.0) The higher this value is the more
---@return self @(void)
function ParticleSystem:simulate(seconds, frameRate)
end

--- Advance the particle system and make it seem like it ran for this many seconds.
---
--- accurate the simulation will be at the cost of performance. value of -1 means
--- (SIMULATION_USE_GAME_ANIMATION_INTERVAL)
---@param seconds number @(float) Seconds to advance. value of -1 means (SIMULATION_USE_PARTICLE_LIFETIME)
---@return self @(void)
function ParticleSystem:simulate(seconds)
end

--- Advance the particle system and make it seem like it ran for this many seconds.
---
--- accurate the simulation will be at the cost of performance. value of -1 means
--- (SIMULATION_USE_GAME_ANIMATION_INTERVAL)
---@return self @(void)
function ParticleSystem:simulate()
end

--- @{
--- @name implement Playable Protocol
---@return self @(void)
function ParticleSystem:start()
end

---@return self @(void)
function ParticleSystem:stop()
end

---@return self @(void)
function ParticleSystem:stopSystem()
end

--- Update the verts position data of particle,
--- should be overridden by subclasses.
---@return self @(void)
function ParticleSystem:updateParticleQuads()
end

--- Call the update method with no time..
---@return self @(void)
function ParticleSystem:updateWithNoTime()
end

--- Sets wether to use HSV color system.
--- WARNING: becareful when using HSV with too many particles because it's expensive.
---
---@param hsv boolean @(bool) Use HSV color system.
---@return self @(void)
function ParticleSystem:useHSV(hsv)
end

--- Creates an initializes a ParticleSystem from a plist file.
--- This plist files can be created manually or with Particle Designer:
--- http:particledesigner.71squared.com
--- @since v2.0
---
--- (static)
---@param plistFile string @(std::string_view) Particle plist file name.
---@return cc.ParticleSystem @(cocos2d::ParticleSystem*) An autoreleased ParticleSystem object.
function ParticleSystem:create(plistFile)
end

--- Create a system with a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleSystem @(cocos2d::ParticleSystem*) An autoreleased ParticleSystemQuad object.
function ParticleSystem:createWithTotalParticles(numberOfParticles)
end

--- Gets all ParticleSystem references
--- (static)
---@return cc.ParticleSystem [] @(cocos2d::Vector<cocos2d::ParticleSystem *>&)
function ParticleSystem:getAllParticleSystems()
end

--- @class ParticleSystemQuad
--- @brief ParticleSystemQuad is a subclass of ParticleSystem.
---
--- It includes all the features of ParticleSystem.
---
--- Special features and Limitations:
--- - Particle size can be any float number.
--- - The system can be scaled.
--- - The particles can be rotated.
--- - It supports subrects.
--- - It supports batched rendering since 1.1.
--- @since v0.8
--- @js NA
---@class cc.ParticleSystemQuad:cc.ParticleSystem
local ParticleSystemQuad = {}
cc.ParticleSystemQuad = ParticleSystemQuad

--- Listen the event that renderer was recreated on AndroidWP8.
--- @js NA
--- @lua NA
---
---@param event cc.EventCustom @(cocos2d::EventCustom*) the event that renderer was recreated on AndroidWP8.
---@return self @(void)
function ParticleSystemQuad:listenRendererRecreated(event)
end

--- Sets a new SpriteFrame as particle.
--- WARNING: this method is experimental. Use setTextureWithRect instead.
---
--- @since v0.99.4
---@param spriteFrame cc.SpriteFrame @(cocos2d::SpriteFrame*) A given sprite frame as particle texture.
---@return self @(void)
function ParticleSystemQuad:setDisplayFrame(spriteFrame)
end

--- Sets a new texture with a rect. The rect is in Points.
--- @since v0.99.4
--- @js NA
--- @lua NA
---
--- 8 @param rect A given rect, in points.
---@param texture cc.Texture2D @(cocos2d::Texture2D*) A given texture.
---@param rect rect_table @(cocos2d::Rect)
---@return self @(void)
function ParticleSystemQuad:setTextureWithRect(texture, rect)
end

--- Creates a Particle Emitter with a dictionary.
---
--- (static)
---@param dictionary tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap&) Particle dictionary.
---@return cc.ParticleSystemQuad @(cocos2d::ParticleSystemQuad*) An autoreleased ParticleSystemQuad object.
function ParticleSystemQuad:create(dictionary)
end

--- Creates an initializes a ParticleSystemQuad from a plist file.
--- This plist files can be created manually or with Particle Designer.
---
--- (static)
---@param filename string @(std::string_view) Particle plist file name.
---@return cc.ParticleSystemQuad @(cocos2d::ParticleSystemQuad*) An autoreleased ParticleSystemQuad object.
function ParticleSystemQuad:create(filename)
end

--- Creates a Particle Emitter.
---
--- (static)
---@return cc.ParticleSystemQuad @(cocos2d::ParticleSystemQuad*) An autoreleased ParticleSystemQuad object.
function ParticleSystemQuad:create()
end

--- Creates a Particle Emitter with a number of particles.
---
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleSystemQuad @(cocos2d::ParticleSystemQuad*) An autoreleased ParticleSystemQuad object.
function ParticleSystemQuad:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleFire
--- @brief A fire particle system.
---@class cc.ParticleFire:cc.ParticleSystemQuad
local ParticleFire = {}
cc.ParticleFire = ParticleFire

--- Create a fire particle system.
---
--- (static)
---@return cc.ParticleFire @(cocos2d::ParticleFire*) An autoreleased ParticleFire object.
function ParticleFire:create()
end

--- Create a fire particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleFire @(cocos2d::ParticleFire*) An autoreleased ParticleFire object.
function ParticleFire:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleFireworks
--- @brief A fireworks particle system.
---@class cc.ParticleFireworks:cc.ParticleSystemQuad
local ParticleFireworks = {}
cc.ParticleFireworks = ParticleFireworks

---@return boolean @(bool)
function ParticleFireworks:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleFireworks:initWithTotalParticles(numberOfParticles)
end

--- Create a fireworks particle system.
---
--- (static)
---@return cc.ParticleFireworks @(cocos2d::ParticleFireworks*) An autoreleased ParticleFireworks object.
function ParticleFireworks:create()
end

--- Create a fireworks particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleFireworks @(cocos2d::ParticleFireworks*) An autoreleased ParticleFireworks object.
function ParticleFireworks:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleSun
--- @brief A sun particle system.
---@class cc.ParticleSun:cc.ParticleSystemQuad
local ParticleSun = {}
cc.ParticleSun = ParticleSun

---@return boolean @(bool)
function ParticleSun:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleSun:initWithTotalParticles(numberOfParticles)
end

--- Create a sun particle system.
---
--- (static)
---@return cc.ParticleSun @(cocos2d::ParticleSun*) An autoreleased ParticleSun object.
function ParticleSun:create()
end

--- Create a sun particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleSun @(cocos2d::ParticleSun*) An autoreleased ParticleSun object.
function ParticleSun:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleGalaxy
--- @brief A galaxy particle system.
---@class cc.ParticleGalaxy:cc.ParticleSystemQuad
local ParticleGalaxy = {}
cc.ParticleGalaxy = ParticleGalaxy

---@return boolean @(bool)
function ParticleGalaxy:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleGalaxy:initWithTotalParticles(numberOfParticles)
end

--- Create a galaxy particle system.
---
--- (static)
---@return cc.ParticleGalaxy @(cocos2d::ParticleGalaxy*) An autoreleased ParticleGalaxy object.
function ParticleGalaxy:create()
end

--- Create a galaxy particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleGalaxy @(cocos2d::ParticleGalaxy*) An autoreleased ParticleGalaxy object.
function ParticleGalaxy:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleFlower
--- @brief A flower particle system.
---@class cc.ParticleFlower:cc.ParticleSystemQuad
local ParticleFlower = {}
cc.ParticleFlower = ParticleFlower

---@return boolean @(bool)
function ParticleFlower:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleFlower:initWithTotalParticles(numberOfParticles)
end

--- Create a flower particle system.
---
--- (static)
---@return cc.ParticleFlower @(cocos2d::ParticleFlower*) An autoreleased ParticleFlower object.
function ParticleFlower:create()
end

--- Create a flower particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleFlower @(cocos2d::ParticleFlower*) An autoreleased ParticleFlower object.
function ParticleFlower:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleMeteor
--- @brief A meteor particle system.
---@class cc.ParticleMeteor:cc.ParticleSystemQuad
local ParticleMeteor = {}
cc.ParticleMeteor = ParticleMeteor

---@return boolean @(bool)
function ParticleMeteor:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleMeteor:initWithTotalParticles(numberOfParticles)
end

--- Create a meteor particle system.
---
--- (static)
---@return cc.ParticleMeteor @(cocos2d::ParticleMeteor*) An autoreleased ParticleMeteor object.
function ParticleMeteor:create()
end

--- Create a meteor particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleMeteor @(cocos2d::ParticleMeteor*) An autoreleased ParticleMeteor object.
function ParticleMeteor:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleSpiral
--- @brief An spiral particle system.
---@class cc.ParticleSpiral:cc.ParticleSystemQuad
local ParticleSpiral = {}
cc.ParticleSpiral = ParticleSpiral

---@return boolean @(bool)
function ParticleSpiral:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleSpiral:initWithTotalParticles(numberOfParticles)
end

--- Create a spiral particle system.
---
--- (static)
---@return cc.ParticleSpiral @(cocos2d::ParticleSpiral*) An autoreleased ParticleSpiral object.
function ParticleSpiral:create()
end

--- Create a spiral particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleSpiral @(cocos2d::ParticleSpiral*) An autoreleased ParticleSpiral object.
function ParticleSpiral:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleExplosion
--- @brief An explosion particle system.
---@class cc.ParticleExplosion:cc.ParticleSystemQuad
local ParticleExplosion = {}
cc.ParticleExplosion = ParticleExplosion

---@return boolean @(bool)
function ParticleExplosion:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleExplosion:initWithTotalParticles(numberOfParticles)
end

--- Create a explosion particle system.
---
--- (static)
---@return cc.ParticleExplosion @(cocos2d::ParticleExplosion*) An autoreleased ParticleExplosion object.
function ParticleExplosion:create()
end

--- Create a explosion particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleExplosion @(cocos2d::ParticleExplosion*) An autoreleased ParticleExplosion object.
function ParticleExplosion:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleSmoke
--- @brief An smoke particle system.
---@class cc.ParticleSmoke:cc.ParticleSystemQuad
local ParticleSmoke = {}
cc.ParticleSmoke = ParticleSmoke

---@return boolean @(bool)
function ParticleSmoke:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleSmoke:initWithTotalParticles(numberOfParticles)
end

--- Create a smoke particle system.
---
--- (static)
---@return cc.ParticleSmoke @(cocos2d::ParticleSmoke*) An autoreleased ParticleSmoke object.
function ParticleSmoke:create()
end

--- Create a smoke particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleSmoke @(cocos2d::ParticleSmoke*) An autoreleased ParticleSmoke object.
function ParticleSmoke:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleSnow
--- @brief An snow particle system.
---@class cc.ParticleSnow:cc.ParticleSystemQuad
local ParticleSnow = {}
cc.ParticleSnow = ParticleSnow

---@return boolean @(bool)
function ParticleSnow:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleSnow:initWithTotalParticles(numberOfParticles)
end

--- Create a snow particle system.
---
--- (static)
---@return cc.ParticleSnow @(cocos2d::ParticleSnow*) An autoreleased ParticleSnow object.
function ParticleSnow:create()
end

--- Create a snow particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleSnow @(cocos2d::ParticleSnow*) An autoreleased ParticleSnow object.
function ParticleSnow:createWithTotalParticles(numberOfParticles)
end

--- @class ParticleRain
--- @brief A rain particle system.
---@class cc.ParticleRain:cc.ParticleSystemQuad
local ParticleRain = {}
cc.ParticleRain = ParticleRain

---@return boolean @(bool)
function ParticleRain:init()
end

---@param numberOfParticles number @(int)
---@return boolean @(bool)
function ParticleRain:initWithTotalParticles(numberOfParticles)
end

--- Create a rain particle system.
---
--- (static)
---@return cc.ParticleRain @(cocos2d::ParticleRain*) An autoreleased ParticleRain object.
function ParticleRain:create()
end

--- Create a rain particle system withe a fixed number of particles.
---
--- @js NA
--- (static)
---@param numberOfParticles number @(int) A given number of particles.
---@return cc.ParticleRain @(cocos2d::ParticleRain*) An autoreleased ParticleRain object.
function ParticleRain:createWithTotalParticles(numberOfParticles)
end

---
--- @brief ProgressTimer is a subclass of Node.
--- It renders the inner sprite according to the percentage.
--- The progress can be Radial, Horizontal or vertical.
--- @since v0.99.1
---@class cc.ProgressTimer:cc.Node
local ProgressTimer = {}
cc.ProgressTimer = ProgressTimer

--- Returns the BarChangeRate.
---
---@return vec2_table @(cocos2d::Vec2) A barChangeRate.
function ProgressTimer:getBarChangeRate()
end

--- Returns the Midpoint.
---
---@return vec2_table @(cocos2d::Vec2) A Vec2.
function ProgressTimer:getMidpoint()
end

--- Percentages are from 0 to 100.
---
---@return number @(float) Percentages.
function ProgressTimer:getPercentage()
end

--- The image to show the progress percentage, retain.
---
---@return cc.Sprite @(cocos2d::Sprite*) A sprite.
function ProgressTimer:getSprite()
end

--- Change the percentage to change progress.
---
---@return cc.ProgressTimer.Type @(cocos2d::ProgressTimer::Type) A Type
function ProgressTimer:getType()
end

--- Initializes a progress timer with the sprite as the shape the timer goes through
---@param sp cc.Sprite @(cocos2d::Sprite*)
---@return boolean @(bool)
function ProgressTimer:initWithSprite(sp)
end

--- Return the Reverse direction.
---
---@return boolean @(bool) If the direction is Anti-clockwise,it will return true.
function ProgressTimer:isReverseDirection()
end

---
--- This allows the bar type to move the component at a specific rate.
--- Set the component to 0 to make sure it stays at 100%.
--- For example you want a left to right bar but not have the height stay 100%.
--- Set the rate to be Vec2(0,1); and set the midpoint to = Vec2(0,.5f).
---@param barChangeRate vec2_table @(cocos2d::Vec2) A Vec2.
---@return self @(void)
function ProgressTimer:setBarChangeRate(barChangeRate)
end

---
--- Midpoint is used to modify the progress start position.
--- If you're using radials type then the midpoint changes the center point.
--- If you're using bar type then the midpoint changes the bar growth.
--- it expands from the center but clamps to the sprites edge so:
--- you want a left to right then set the midpoint all the way to Vec2(0,y).
--- you want a right to left then set the midpoint all the way to Vec2(1,y).
--- you want a bottom to top then set the midpoint all the way to Vec2(x,0).
--- you want a top to bottom then set the midpoint all the way to Vec2(x,1).
---@param point vec2_table @(cocos2d::Vec2) A Vec2 point.
---@return self @(void)
function ProgressTimer:setMidpoint(point)
end

--- Set the initial percentage values.
---
---@param percentage number @(float) The initial percentage values.
---@return self @(void)
function ProgressTimer:setPercentage(percentage)
end

--- Set the Reverse direction.
---
---@param value boolean @(bool) If value is false it will clockwise,if is true it will Anti-clockwise.
---@return self @(void)
function ProgressTimer:setReverseDirection(value)
end

--- Set the sprite as the shape.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) The sprite as the shape.
---@return self @(void)
function ProgressTimer:setSprite(sprite)
end

--- Set the ProgressTimer type.
---
---@param type cc.ProgressTimer.Type @(cocos2d::ProgressTimer::Type) Is an Type.
---@return self @(void)
function ProgressTimer:setType(type)
end

--- Creates a progress timer with the sprite as the shape the timer goes through.
---
--- (static)
---@param sp cc.Sprite @(cocos2d::Sprite*) The sprite as the shape the timer goes through.
---@return cc.ProgressTimer @(cocos2d::ProgressTimer*) A ProgressTimer.
function ProgressTimer:create(sp)
end

---
---  *@brief A inner node type mainly used for UI module.
--- It is useful for composing complex node type and it's children are protected.
---@class cc.ProtectedNode:cc.Node
local ProtectedNode = {}
cc.ProtectedNode = ProtectedNode

---
--- Adds a child to the container with z order and tag.
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---@param child cc.Node @(cocos2d::Node*)     A child node
---@param localZOrder number @(int)    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
---@param tag number @(int)       An integer to identify the node easily. Please refer to `setTag(int)`
---@return self @(void)
function ProtectedNode:addProtectedChild(child, localZOrder, tag)
end

---
--- Adds a child to the container with a local z-order.
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---@param child cc.Node @(cocos2d::Node*)     A child node
---@param localZOrder number @(int)    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
---@return self @(void)
function ProtectedNode:addProtectedChild(child, localZOrder)
end

---
--- Adds a child to the container with z-order as 0.
---
--- If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called
--- immediately.
---
---@param child cc.Node @(cocos2d::Node*) A child node
---@return self @(void)
function ProtectedNode:addProtectedChild(child)
end

---@return self @(void)
function ProtectedNode:disableCascadeColor()
end

---@return self @(void)
function ProtectedNode:disableCascadeOpacity()
end

---
--- Gets a child from the container with its tag.
---
---
---@param tag number @(int)   An identifier to find the child node.
---@return cc.Node @(cocos2d::Node*) a Node object whose tag equals to the input parameter.
function ProtectedNode:getProtectedChildByTag(tag)
end

---
--- Removes all children from the container with a cleanup.
---
--- @see `removeAllChildrenWithCleanup(bool)`.
---@return self @(void)
function ProtectedNode:removeAllProtectedChildren()
end

---
--- Removes all children from the container, and do a cleanup to all running actions depending on the cleanup
--- parameter.
---
--- @js removeAllChildren
--- @lua removeAllChildren
---@param cleanup boolean @(bool)   true if all running actions on all children nodes should be cleanup, false otherwise.
---@return self @(void)
function ProtectedNode:removeAllProtectedChildrenWithCleanup(cleanup)
end

---
--- Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
---
---@param child cc.Node @(cocos2d::Node*)     The child node which will be removed.
---@param cleanup boolean @(bool)   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
---@return self @(void)
function ProtectedNode:removeProtectedChild(child, cleanup)
end

---
--- Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
---
---@param child cc.Node @(cocos2d::Node*)     The child node which will be removed.
---@return self @(void)
function ProtectedNode:removeProtectedChild(child)
end

---
--- Removes a child from the container by tag value. It will also cleanup all running actions depending on the
--- cleanup parameter.
---
---@param tag number @(int)       An integer number that identifies a child node.
---@param cleanup boolean @(bool)   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
---@return self @(void)
function ProtectedNode:removeProtectedChildByTag(tag, cleanup)
end

---
--- Removes a child from the container by tag value. It will also cleanup all running actions depending on the
--- cleanup parameter.
---
---@param tag number @(int)       An integer number that identifies a child node.
---@return self @(void)
function ProtectedNode:removeProtectedChildByTag(tag)
end

---
--- Reorders a child according to a new z value.
---
---@param child cc.Node @(cocos2d::Node*)     An already added child node. It MUST be already added.
---@param localZOrder number @(int) Z order for drawing priority. Please refer to setLocalZOrder(int)
---@return self @(void)
function ProtectedNode:reorderProtectedChild(child, localZOrder)
end

---
--- Sorts the children array once before drawing, instead of every time when a child is added or reordered.
--- This approach can improves the performance massively.
--- @note Don't call this manually unless a child added needs to be removed in the same frame
---@return self @(void)
function ProtectedNode:sortAllProtectedChildren()
end

---
--- Creates a ProtectedNode with no argument.
--- *@return A instance of ProtectedNode.
--- (static)
---@return cc.ProtectedNode @(cocos2d::ProtectedNode*)
function ProtectedNode:create()
end

---
--- @brief RenderTexture is a generic rendering target. To render things into it,
--- simply construct a render target, call begin on it, call visit on any cocos
--- scenes or objects to render them, and call end. For convenience, render texture
--- adds a sprite as it's display child with the results, so you can simply add
--- the render texture to your scene and treat it like any other CocosNode.
--- There are also functions for saving the render texture to disk in PNG or JPG format.
--- @since v0.8.1
---@class cc.RenderTexture:cc.Node
local RenderTexture = {}
cc.RenderTexture = RenderTexture

--- Starts grabbing.
---@return self @(void)
function RenderTexture:begin()
end

--- Starts rendering to the texture while clearing the texture first.
--- This is more efficient then calling -clear first and then -begin.
---
---@param r number @(float) Red.
---@param g number @(float) Green.
---@param b number @(float) Blue.
---@param a number @(float) Alpha.
---@param depthValue number @(float) A specified depth value.
---@param stencilValue number @(int) A specified stencil value.
---@return self @(void)
function RenderTexture:beginWithClear(r, g, b, a, depthValue, stencilValue)
end

--- Starts rendering to the texture while clearing the texture first.
--- This is more efficient then calling -clear first and then -begin.
---
---@param r number @(float) Red.
---@param g number @(float) Green.
---@param b number @(float) Blue.
---@param a number @(float) Alpha.
---@param depthValue number @(float) The depth Value.
---@return self @(void)
function RenderTexture:beginWithClear(r, g, b, a, depthValue)
end

--- Starts rendering to the texture while clearing the texture first.
--- This is more efficient then calling -clear first and then -begin.
---
---@param r number @(float) Red.
---@param g number @(float) Green.
---@param b number @(float) Blue.
---@param a number @(float) Alpha.
---@return self @(void)
function RenderTexture:beginWithClear(r, g, b, a)
end

--- Clears the texture with a color.
---
---@param r number @(float) Red.
---@param g number @(float) Green.
---@param b number @(float) Blue.
---@param a number @(float) Alpha.
---@return self @(void)
function RenderTexture:clear(r, g, b, a)
end

--- Clears the texture with a specified depth value.
---
---@param depthValue number @(float) A specified depth value.
---@return self @(void)
function RenderTexture:clearDepth(depthValue)
end

--- Clears the texture with a specified stencil value.
---
---@param stencilValue number @(int) A specified stencil value.
---@return self @(void)
function RenderTexture:clearStencil(stencilValue)
end

--- Ends grabbing.
--- @lua endToLua
---@return self @(void)
function RenderTexture:endToLua()
end

--- Clear color value. Valid only when "autoDraw" is true.
---
---@return color4f_table @(const cocos2d::Color4F&) Color value.
function RenderTexture:getClearColor()
end

--- Value for clearDepth. Valid only when "autoDraw" is true.
---
---@return number @(float) Value for clearDepth.
function RenderTexture:getClearDepth()
end

--- Valid when "autoDraw" is true.
---
---@return ccb.TargetBufferFlags @(cocos2d::ClearFlag) Clear flags.
function RenderTexture:getClearFlags()
end

--- Value for clear Stencil. Valid only when "autoDraw" is true.
---
---@return number @(int) Value for clear Stencil.
function RenderTexture:getClearStencil()
end

---@return ccb.RenderTarget @(cocos2d::backend::RenderTarget*)
function RenderTexture:getRenderTarget()
end

--- Gets the Sprite being used.
---
---@return cc.Sprite @(cocos2d::Sprite*) A Sprite.
function RenderTexture:getSprite()
end

--- Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats
--- are valid ) and depthStencil format.
---
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@param depthStencilFormat ccb.PixelFormat @(cocos2d::backend::PixelFormat) The depthStencil format.
---@param sharedRenderTarget boolean @(bool) Select whether to use a new or shared render target.
---@return boolean @(bool) If succeed, it will return true.
function RenderTexture:initWithWidthAndHeight(w, h, format, depthStencilFormat, sharedRenderTarget)
end

--- Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats
--- are valid ) and depthStencil format.
---
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@param depthStencilFormat ccb.PixelFormat @(cocos2d::backend::PixelFormat) The depthStencil format.
---@return boolean @(bool) If succeed, it will return true.
function RenderTexture:initWithWidthAndHeight(w, h, format, depthStencilFormat)
end

--- Initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats
--- are valid.
---
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@param sharedRenderTarget boolean @(bool) Select whether to use a new or shared render target.
---@return boolean @(bool) If succeed, it will return true.
function RenderTexture:initWithWidthAndHeight(w, h, format, sharedRenderTarget)
end

--- Initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats
--- are valid.
---
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@return boolean @(bool) If succeed, it will return true.
function RenderTexture:initWithWidthAndHeight(w, h, format)
end

--- When enabled, it will render its children into the texture automatically. Disabled by default for compatibility
--- reasons. Will be enabled in the future.
---
---@return boolean @(bool) Return the autoDraw value.
function RenderTexture:isAutoDraw()
end

--- Check if the render target is shared
---
---@return boolean @(bool) Returns true if this using a shared render target.
function RenderTexture:isSharedRenderTarget()
end

--- saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
--- Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following
--- render->render().
--- So if this function is called in a event handler, the actual save file will be called in the next frame. If we
--- switch to a different scene, the game will crash.
--- To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
---
---@param filename string @(std::string_view) The file name.
---@param format cc.Image.Format @(cocos2d::Image::Format) The image format.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@param callback function @(cocos2d::RenderTexture::SaveFileCallbackType) When the file is save finished,it will callback this function.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFile(filename, format, isRGBA, callback)
end

--- saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
--- Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following
--- render->render().
--- So if this function is called in a event handler, the actual save file will be called in the next frame. If we
--- switch to a different scene, the game will crash.
--- To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
---
---@param filename string @(std::string_view) The file name.
---@param format cc.Image.Format @(cocos2d::Image::Format) The image format.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFile(filename, format, isRGBA)
end

--- Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
---
---@param filename string @(std::string_view) The file name.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@param param3 function @(cocos2d::RenderTexture::SaveFileCallbackType)
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFile(filename, isRGBA, param3)
end

--- saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
--- Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following
--- render->render().
--- So if this function is called in a event handler, the actual save file will be called in the next frame. If we
--- switch to a different scene, the game will crash.
--- To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
---
---@param filename string @(std::string_view) The file name.
---@param format cc.Image.Format @(cocos2d::Image::Format) The image format.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFile(filename, format)
end

--- Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
---
---@param filename string @(std::string_view) The file name.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFile(filename, isRGBA)
end

--- Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
---
---@param filename string @(std::string_view) The file name.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFile(filename)
end

--- saves the texture into a file in non-PMA. The format could be JPG or PNG. The file will be saved in the
--- Documents folder. Returns true if the operation is successful.
--- Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following
--- render->render().
--- So if this function is called in a event handler, the actual save file will be called in the next frame. If we
--- switch to a different scene, the game will crash.
--- To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
---
---@param fileName string @(std::string_view)
---@param format cc.Image.Format @(cocos2d::Image::Format) The image format.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@param callback function @(cocos2d::RenderTexture::SaveFileCallbackType) When the file is save finished,it will callback this function.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFileAsNonPMA(fileName, format, isRGBA, callback)
end

--- Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
---
---@param filename string @(std::string_view) The file name.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@param param3 function @(cocos2d::RenderTexture::SaveFileCallbackType)
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFileAsNonPMA(filename, isRGBA, param3)
end

--- Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
---
---@param filename string @(std::string_view) The file name.
---@param isRGBA boolean @(bool) The file is RGBA or not.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFileAsNonPMA(filename, isRGBA)
end

--- Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
--- Returns true if the operation is successful.
---
---@param filename string @(std::string_view) The file name.
---@return boolean @(bool) Returns true if the operation is successful.
function RenderTexture:saveToFileAsNonPMA(filename)
end

--- Set a valve to control whether or not render its children into the texture automatically.
---
---@param isAutoDraw boolean @(bool) Whether or not render its children into the texture automatically.
---@return self @(void)
function RenderTexture:setAutoDraw(isAutoDraw)
end

--- Set color value.
---
---@param clearColor color4f_table @(cocos2d::Color4F) Color value.
---@return self @(void)
function RenderTexture:setClearColor(clearColor)
end

--- Set Value for clearDepth.
---
---@param clearDepth number @(float) Value for clearDepth.
---@return self @(void)
function RenderTexture:setClearDepth(clearDepth)
end

--- Set flags.
---
---@param clearFlags ccb.TargetBufferFlags @(cocos2d::ClearFlag) set clear flags.
---@return self @(void)
function RenderTexture:setClearFlags(clearFlags)
end

--- Set Value for clear Stencil.
---
---@param clearStencil number @(int) Value for clear Stencil.
---@return self @(void)
function RenderTexture:setClearStencil(clearStencil)
end

--- Flag: Use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
---
--- projection matrix.
--- @js NA
---@param keepMatrix boolean @(bool) Whether or not use stack matrix computed from scene hierarchy or generate new modelView and
---@return self @(void)
function RenderTexture:setKeepMatrix(keepMatrix)
end

--- Sets the Sprite being used.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) A Sprite.
---@return self @(void)
function RenderTexture:setSprite(sprite)
end

--- Used for grab part of screen to a texture.
---@param rtBegin vec2_table @(cocos2d::Vec2) The position of renderTexture on the fullRect.
---@param fullRect rect_table @(cocos2d::Rect) The total size of screen.
---@param fullViewport rect_table @(cocos2d::Rect) The total viewportSize.
---@return self @(void)
function RenderTexture:setVirtualViewport(rtBegin, fullRect, fullViewport)
end

--- Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats
--- are valid ) and depthStencil format.
---
--- (static)
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@param depthStencilFormat ccb.PixelFormat @(cocos2d::backend::PixelFormat) The depthStencil format.
---@param sharedRenderTarget boolean @(bool) Select whether to use a new or shared render target.
---@return cc.RenderTexture @(cocos2d::RenderTexture*)
function RenderTexture:create(w, h, format, depthStencilFormat, sharedRenderTarget)
end

--- Creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are
--- valid.
---
--- (static)
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@param sharedRenderTarget boolean @(bool) Select whether to use a new or shared render target.
---@return cc.RenderTexture @(cocos2d::RenderTexture*)
function RenderTexture:create(w, h, format, sharedRenderTarget)
end

--- Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats
--- are valid ) and depthStencil format.
---
--- (static)
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@param depthStencilFormat ccb.PixelFormat @(cocos2d::backend::PixelFormat) The depthStencil format.
---@return cc.RenderTexture @(cocos2d::RenderTexture*)
function RenderTexture:create(w, h, format, depthStencilFormat)
end

--- Creates a RenderTexture object with width and height in Points, pixel format is RGBA8888.
---
--- (static)
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param sharedRenderTarget boolean @(bool) Select wether to use a new or shared render target.
---@return cc.RenderTexture @(cocos2d::RenderTexture*)
function RenderTexture:create(w, h, sharedRenderTarget)
end

--- Creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are
--- valid.
---
--- (static)
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@param format ccb.PixelFormat @(cocos2d::backend::PixelFormat) In Points and a pixel format( only RGB and RGBA formats are valid ).
---@return cc.RenderTexture @(cocos2d::RenderTexture*)
function RenderTexture:create(w, h, format)
end

--- Creates a RenderTexture object with width and height in Points, pixel format is RGBA8888.
---
--- (static)
---@param w number @(int) The RenderTexture object width.
---@param h number @(int) The RenderTexture object height.
---@return cc.RenderTexture @(cocos2d::RenderTexture*)
function RenderTexture:create(w, h)
end

--- @class TransitionScene
--- @brief Base class for Transition scenes.
---@class cc.TransitionScene:cc.Scene
local TransitionScene = {}
cc.TransitionScene = TransitionScene

--- Called after the transition finishes.
---@return self @(void)
function TransitionScene:finish()
end

---@return number @(float)
function TransitionScene:getDuration()
end

---@return cc.Scene @(cocos2d::Scene*)
function TransitionScene:getInScene()
end

--- Used by some transitions to hide the outer scene.
---@return self @(void)
function TransitionScene:hideOutShowIn()
end

--- initializes a transition with duration and incoming scene
---@param t number @(float)
---@param scene cc.Scene @(cocos2d::Scene*)
---@return boolean @(bool)
function TransitionScene:initWithDuration(t, scene)
end

--- Creates a base transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionScene @(cocos2d::TransitionScene*) A autoreleased TransitionScene object.
function TransitionScene:create(t, scene)
end

--- @class TransitionSceneOriented
--- @brief A Transition that supports orientation like.
--- Possible orientation: LeftOver, RightOver, UpOver, DownOver
---@class cc.TransitionSceneOriented:cc.TransitionScene
local TransitionSceneOriented = {}
cc.TransitionSceneOriented = TransitionSceneOriented

--- initializes a transition with duration and incoming scene
---@param t number @(float)
---@param scene cc.Scene @(cocos2d::Scene*)
---@param orientation cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation)
---@return boolean @(bool)
function TransitionSceneOriented:initWithDuration(t, scene, orientation)
end

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@param orientation cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation: LeftOver, RightOver, UpOver, DownOver.
---@return cc.TransitionSceneOriented @(cocos2d::TransitionSceneOriented*) A autoreleased TransitionSceneOriented object.
function TransitionSceneOriented:create(t, scene, orientation)
end

--- @class TransitionRotoZoom
--- @brief TransitionRotoZoom:
--- Rotate and zoom out the outgoing scene, and then rotate and zoom in the incoming
---@class cc.TransitionRotoZoom:cc.TransitionScene
local TransitionRotoZoom = {}
cc.TransitionRotoZoom = TransitionRotoZoom

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionRotoZoom @(cocos2d::TransitionRotoZoom*) A autoreleased TransitionRotoZoom object.
function TransitionRotoZoom:create(t, scene)
end

--- @class TransitionJumpZoom
--- @brief TransitionJumpZoom:
--- Zoom out and jump the outgoing scene, and then jump and zoom in the incoming
---@class cc.TransitionJumpZoom:cc.TransitionScene
local TransitionJumpZoom = {}
cc.TransitionJumpZoom = TransitionJumpZoom

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionJumpZoom @(cocos2d::TransitionJumpZoom*) A autoreleased TransitionJumpZoom object.
function TransitionJumpZoom:create(t, scene)
end

--- @class TransitionMoveInL
--- @brief TransitionMoveInL:
--- Move in from to the left the incoming scene.
---@class cc.TransitionMoveInL:cc.TransitionScene
local TransitionMoveInL = {}
cc.TransitionMoveInL = TransitionMoveInL

--- Returns the action that will be performed.
---
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The action that will be performed.
function TransitionMoveInL:action()
end

---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function TransitionMoveInL:easeActionWithAction(action)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionMoveInL @(cocos2d::TransitionMoveInL*) A autoreleased TransitionMoveInL object.
function TransitionMoveInL:create(t, scene)
end

--- @class TransitionMoveInR
--- @brief TransitionMoveInR:
--- Move in from to the right the incoming scene.
---@class cc.TransitionMoveInR:cc.TransitionMoveInL
local TransitionMoveInR = {}
cc.TransitionMoveInR = TransitionMoveInR

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionMoveInR @(cocos2d::TransitionMoveInR*) A autoreleased TransitionMoveInR object.
function TransitionMoveInR:create(t, scene)
end

--- @class TransitionMoveInT
--- @brief TransitionMoveInT:
--- Move in from to the top the incoming scene.
---@class cc.TransitionMoveInT:cc.TransitionMoveInL
local TransitionMoveInT = {}
cc.TransitionMoveInT = TransitionMoveInT

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionMoveInT @(cocos2d::TransitionMoveInT*) A autoreleased TransitionMoveInT object.
function TransitionMoveInT:create(t, scene)
end

--- @class TransitionMoveInB
--- @brief TransitionMoveInB:
--- Move in from to the bottom the incoming scene.
---@class cc.TransitionMoveInB:cc.TransitionMoveInL
local TransitionMoveInB = {}
cc.TransitionMoveInB = TransitionMoveInB

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionMoveInB @(cocos2d::TransitionMoveInB*) A autoreleased TransitionMoveInB object.
function TransitionMoveInB:create(t, scene)
end

--- @class TransitionSlideInL
--- @brief TransitionSlideInL:
--- Slide in the incoming scene from the left border.
---@class cc.TransitionSlideInL:cc.TransitionScene
local TransitionSlideInL = {}
cc.TransitionSlideInL = TransitionSlideInL

--- Returns the action that will be performed by the incoming and outgoing scene.
---
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The action that will be performed by the incoming and outgoing scene.
function TransitionSlideInL:action()
end

---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function TransitionSlideInL:easeActionWithAction(action)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionSlideInL @(cocos2d::TransitionSlideInL*) A autoreleased TransitionSlideInL object.
function TransitionSlideInL:create(t, scene)
end

--- @class TransitionSlideInR
---  *@brief TransitionSlideInR:
--- Slide in the incoming scene from the right border.
---@class cc.TransitionSlideInR:cc.TransitionSlideInL
local TransitionSlideInR = {}
cc.TransitionSlideInR = TransitionSlideInR

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionSlideInR @(cocos2d::TransitionSlideInR*) A autoreleased TransitionSlideInR object.
function TransitionSlideInR:create(t, scene)
end

--- @class TransitionSlideInB
--- @brief TransitionSlideInB:
--- Slide in the incoming scene from the bottom border.
---@class cc.TransitionSlideInB:cc.TransitionSlideInL
local TransitionSlideInB = {}
cc.TransitionSlideInB = TransitionSlideInB

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionSlideInB @(cocos2d::TransitionSlideInB*) A autoreleased TransitionSlideInB object.
function TransitionSlideInB:create(t, scene)
end

--- @class TransitionSlideInT
--- @brief TransitionSlideInT:
--- Slide in the incoming scene from the top border.
---@class cc.TransitionSlideInT:cc.TransitionSlideInL
local TransitionSlideInT = {}
cc.TransitionSlideInT = TransitionSlideInT

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionSlideInT @(cocos2d::TransitionSlideInT*) A autoreleased TransitionSlideInT object.
function TransitionSlideInT:create(t, scene)
end

--- @class TransitionShrinkGrow
--- @brief Shrink the outgoing scene while grow the incoming scene
---@class cc.TransitionShrinkGrow:cc.TransitionScene
local TransitionShrinkGrow = {}
cc.TransitionShrinkGrow = TransitionShrinkGrow

---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function TransitionShrinkGrow:easeActionWithAction(action)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionShrinkGrow @(cocos2d::TransitionShrinkGrow*) A autoreleased TransitionShrinkGrow object.
function TransitionShrinkGrow:create(t, scene)
end

--- @class TransitionFlipX
--- @brief TransitionFlipX:
--- Flips the screen horizontally.
--- The front face is the outgoing scene and the back face is the incoming scene.
---@class cc.TransitionFlipX:cc.TransitionSceneOriented
local TransitionFlipX = {}
cc.TransitionFlipX = TransitionFlipX

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@param o cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation.
---@return cc.TransitionFlipX @(cocos2d::TransitionFlipX*) A autoreleased TransitionFlipX object.
function TransitionFlipX:create(t, s, o)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFlipX @(cocos2d::TransitionFlipX*) A autoreleased TransitionFlipX object.
function TransitionFlipX:create(t, s)
end

--- @class TransitionFlipY
--- @brief TransitionFlipY:
--- Flips the screen vertically.
--- The front face is the outgoing scene and the back face is the incoming scene.
---@class cc.TransitionFlipY:cc.TransitionSceneOriented
local TransitionFlipY = {}
cc.TransitionFlipY = TransitionFlipY

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@param o cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation.
---@return cc.TransitionFlipY @(cocos2d::TransitionFlipY*) A autoreleased TransitionFlipY object.
function TransitionFlipY:create(t, s, o)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFlipY @(cocos2d::TransitionFlipY*) A autoreleased TransitionFlipY object.
function TransitionFlipY:create(t, s)
end

--- @class TransitionFlipAngular
--- @brief TransitionFlipAngular:
--- Flips the screen half horizontally and half vertically.
--- The front face is the outgoing scene and the back face is the incoming scene.
---@class cc.TransitionFlipAngular:cc.TransitionSceneOriented
local TransitionFlipAngular = {}
cc.TransitionFlipAngular = TransitionFlipAngular

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@param o cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation.
---@return cc.TransitionFlipAngular @(cocos2d::TransitionFlipAngular*) A autoreleased TransitionFlipAngular object.
function TransitionFlipAngular:create(t, s, o)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFlipAngular @(cocos2d::TransitionFlipAngular*) A autoreleased TransitionFlipAngular object.
function TransitionFlipAngular:create(t, s)
end

--- @class TransitionZoomFlipX
--- @brief TransitionZoomFlipX:
--- Flips the screen horizontally doing a zoom outin
--- The front face is the outgoing scene and the back face is the incoming scene.
---@class cc.TransitionZoomFlipX:cc.TransitionSceneOriented
local TransitionZoomFlipX = {}
cc.TransitionZoomFlipX = TransitionZoomFlipX

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@param o cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation.
---@return cc.TransitionZoomFlipX @(cocos2d::TransitionZoomFlipX*) A autoreleased TransitionZoomFlipX object.
function TransitionZoomFlipX:create(t, s, o)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionZoomFlipX @(cocos2d::TransitionZoomFlipX*) A autoreleased TransitionZoomFlipX object.
function TransitionZoomFlipX:create(t, s)
end

--- @class TransitionZoomFlipY
--- @brief TransitionZoomFlipY:
--- Flips the screen vertically doing a little zooming outin
--- The front face is the outgoing scene and the back face is the incoming scene.
---@class cc.TransitionZoomFlipY:cc.TransitionSceneOriented
local TransitionZoomFlipY = {}
cc.TransitionZoomFlipY = TransitionZoomFlipY

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@param o cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation.
---@return cc.TransitionZoomFlipY @(cocos2d::TransitionZoomFlipY*) A autoreleased TransitionZoomFlipY object.
function TransitionZoomFlipY:create(t, s, o)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionZoomFlipY @(cocos2d::TransitionZoomFlipY*) A autoreleased TransitionZoomFlipY object.
function TransitionZoomFlipY:create(t, s)
end

--- @class TransitionZoomFlipAngular
--- @brief TransitionZoomFlipAngular:
--- Flips the screen half horizontally and half vertically doing a little zooming outin.
--- The front face is the outgoing scene and the back face is the incoming scene.
---@class cc.TransitionZoomFlipAngular:cc.TransitionSceneOriented
local TransitionZoomFlipAngular = {}
cc.TransitionZoomFlipAngular = TransitionZoomFlipAngular

--- Creates a transition with duration, incoming scene and orientation.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@param o cc.TransitionScene.Orientation @(cocos2d::TransitionScene::Orientation) A given orientation.
---@return cc.TransitionZoomFlipAngular @(cocos2d::TransitionZoomFlipAngular*) A autoreleased TransitionZoomFlipAngular object.
function TransitionZoomFlipAngular:create(t, s, o)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param s cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionZoomFlipAngular @(cocos2d::TransitionZoomFlipAngular*) A autoreleased TransitionZoomFlipAngular object.
function TransitionZoomFlipAngular:create(t, s)
end

--- @class TransitionFade
--- @brief TransitionFade:
--- Fade out the outgoing scene and then fade in the incoming scene.'''
---@class cc.TransitionFade:cc.TransitionScene
local TransitionFade = {}
cc.TransitionFade = TransitionFade

--- initializes the transition with a duration and with an RGB color
---@param t number @(float)
---@param scene cc.Scene @(cocos2d::Scene*)
---@param color color3b_table @(cocos2d::Color3B)
---@return boolean @(bool)
function TransitionFade:initWithDuration(t, scene, color)
end

---@param t number @(float)
---@param scene cc.Scene @(cocos2d::Scene*)
---@return boolean @(bool)
function TransitionFade:initWithDuration(t, scene)
end

--- Creates the transition with a duration and with an RGB color
--- Example: FadeTransition::create(2, scene, Color3B(255,0,0); red color
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@param color color3b_table @(cocos2d::Color3B) A given transition color.
---@return cc.TransitionFade @(cocos2d::TransitionFade*) A autoreleased TransitionFade object.
function TransitionFade:create(duration, scene, color)
end

--- Creates the transition with a duration.
---
--- (static)
---@param duration number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFade @(cocos2d::TransitionFade*) A autoreleased TransitionFade object.
function TransitionFade:create(duration, scene)
end

--- @class TransitionCrossFade
--- @brief TransitionCrossFade:
--- Cross fades two scenes using the RenderTexture object.
---@class cc.TransitionCrossFade:cc.TransitionScene
local TransitionCrossFade = {}
cc.TransitionCrossFade = TransitionCrossFade

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionCrossFade @(cocos2d::TransitionCrossFade*) A autoreleased TransitionCrossFade object.
function TransitionCrossFade:create(t, scene)
end

--- @class TransitionTurnOffTiles
--- @brief TransitionTurnOffTiles:
--- Turn off the tiles of the outgoing scene in random order
---@class cc.TransitionTurnOffTiles:cc.TransitionScene
local TransitionTurnOffTiles = {}
cc.TransitionTurnOffTiles = TransitionTurnOffTiles

---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function TransitionTurnOffTiles:easeActionWithAction(action)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionTurnOffTiles @(cocos2d::TransitionTurnOffTiles*) A autoreleased TransitionTurnOffTiles object.
function TransitionTurnOffTiles:create(t, scene)
end

--- @class TransitionSplitCols
--- @brief TransitionSplitCols:
--- The odd columns goes upwards while the even columns goes downwards.
---@class cc.TransitionSplitCols:cc.TransitionScene
local TransitionSplitCols = {}
cc.TransitionSplitCols = TransitionSplitCols

--- Returns the action that will be performed.
---
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The action that will be performed.
function TransitionSplitCols:action()
end

---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function TransitionSplitCols:easeActionWithAction(action)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionSplitCols @(cocos2d::TransitionSplitCols*) A autoreleased TransitionSplitCols object.
function TransitionSplitCols:create(t, scene)
end

--- @class TransitionSplitRows
--- @brief TransitionSplitRows:
--- The odd rows goes to the left while the even rows goes to the right.
---@class cc.TransitionSplitRows:cc.TransitionSplitCols
local TransitionSplitRows = {}
cc.TransitionSplitRows = TransitionSplitRows

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionSplitRows @(cocos2d::TransitionSplitRows*) A autoreleased TransitionSplitRows object.
function TransitionSplitRows:create(t, scene)
end

--- @class TransitionFadeTR
--- @brief TransitionFadeTR:
--- Fade the tiles of the outgoing scene from the left-bottom corner the to top-right corner.
---@class cc.TransitionFadeTR:cc.TransitionScene
local TransitionFadeTR = {}
cc.TransitionFadeTR = TransitionFadeTR

--- Returns the action that will be performed with size.
---
---@param size vec2_table @(cocos2d::Vec2) A given size.
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The action that will be performed.
function TransitionFadeTR:actionWithSize(size)
end

---@param action cc.ActionInterval @(cocos2d::ActionInterval*)
---@return cc.ActionInterval @(cocos2d::ActionInterval*)
function TransitionFadeTR:easeActionWithAction(action)
end

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFadeTR @(cocos2d::TransitionFadeTR*) A autoreleased TransitionFadeTR object.
function TransitionFadeTR:create(t, scene)
end

--- @class TransitionFadeBL
--- @brief TransitionFadeBL:
--- Fade the tiles of the outgoing scene from the top-right corner to the bottom-left corner.
---@class cc.TransitionFadeBL:cc.TransitionFadeTR
local TransitionFadeBL = {}
cc.TransitionFadeBL = TransitionFadeBL

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFadeBL @(cocos2d::TransitionFadeBL*) A autoreleased TransitionFadeBL object.
function TransitionFadeBL:create(t, scene)
end

--- @class TransitionFadeUp
--- @brief TransitionFadeUp:
--- Fade the tiles of the outgoing scene from the bottom to the top.
---@class cc.TransitionFadeUp:cc.TransitionFadeTR
local TransitionFadeUp = {}
cc.TransitionFadeUp = TransitionFadeUp

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFadeUp @(cocos2d::TransitionFadeUp*) A autoreleased TransitionFadeUp object.
function TransitionFadeUp:create(t, scene)
end

--- @class TransitionFadeDown
--- @brief TransitionFadeDown:
--- Fade the tiles of the outgoing scene from the top to the bottom.
---@class cc.TransitionFadeDown:cc.TransitionFadeTR
local TransitionFadeDown = {}
cc.TransitionFadeDown = TransitionFadeDown

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionFadeDown @(cocos2d::TransitionFadeDown*) A autoreleased TransitionFadeDown object.
function TransitionFadeDown:create(t, scene)
end

--- @class TransitionPageTurn
--- @brief A transition which peels back the bottom right hand corner of a scene
--- to transition to the scene beneath it simulating a page turn.
---
--- This uses a 3DAction so it's strongly recommended that depth buffering
--- is turned on in Director using:
---
---  Director::getInstance()->setDepthBufferFormat(kDepthBuffer16);
---
---  @since v0.8.2
---@class cc.TransitionPageTurn:cc.TransitionScene
local TransitionPageTurn = {}
cc.TransitionPageTurn = TransitionPageTurn

--- Returns the action that will be performed with size.
---
---@param vector vec2_table @(cocos2d::Vec2) A given size.
---@return cc.ActionInterval @(cocos2d::ActionInterval*) The action that will be performed.
function TransitionPageTurn:actionWithSize(vector)
end

---
--- Creates a base transition with duration and incoming scene.
--- If back is true then the effect is reversed to appear as if the incoming
--- scene is being turned from left over the outgoing scene.
---
--- from left over the outgoing scene.
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@param backwards boolean @(bool) If back is true then the effect is reversed to appear as if the incoming scene is being turned
---@return boolean @(bool) True if initialize success.
function TransitionPageTurn:initWithDuration(t, scene, backwards)
end

---
--- Creates a base transition with duration and incoming scene.
--- If back is true then the effect is reversed to appear as if the incoming
--- scene is being turned from left over the outgoing scene.
---
--- from left over the outgoing scene.
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@param backwards boolean @(bool) If back is true then the effect is reversed to appear as if the incoming scene is being turned
---@return cc.TransitionPageTurn @(cocos2d::TransitionPageTurn*) An autoreleased TransitionPageTurn object.
function TransitionPageTurn:create(t, scene, backwards)
end

---
--- @addtogroup _2d
--- @{
---
---  @class TransitionProgress
--- @brief A base class of progress transition.
---@class cc.TransitionProgress:cc.TransitionScene
local TransitionProgress = {}
cc.TransitionProgress = TransitionProgress

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgress @(cocos2d::TransitionProgress*) An autoreleased TransitionProgress object.
function TransitionProgress:create(t, scene)
end

--- @class TransitionProgressRadialCCW
--- @brief TransitionRadialCCW transition.
---  A counter clock-wise radial transition to the next scene
---@class cc.TransitionProgressRadialCCW:cc.TransitionProgress
local TransitionProgressRadialCCW = {}
cc.TransitionProgressRadialCCW = TransitionProgressRadialCCW

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgressRadialCCW @(cocos2d::TransitionProgressRadialCCW*) An autoreleased TransitionProgressRadialCCW object.
function TransitionProgressRadialCCW:create(t, scene)
end

--- @class TransitionProgressRadialCW
--- @brief TransitionRadialCW transition.
---  A counter clock-wise radial transition to the next scene.
---@class cc.TransitionProgressRadialCW:cc.TransitionProgress
local TransitionProgressRadialCW = {}
cc.TransitionProgressRadialCW = TransitionProgressRadialCW

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgressRadialCW @(cocos2d::TransitionProgressRadialCW*) An autoreleased TransitionProgressRadialCW object.
function TransitionProgressRadialCW:create(t, scene)
end

--- @class TransitionProgressHorizontal
--- @brief TransitionProgressHorizontal transition.
---  A  clock-wise radial transition to the next scene
---@class cc.TransitionProgressHorizontal:cc.TransitionProgress
local TransitionProgressHorizontal = {}
cc.TransitionProgressHorizontal = TransitionProgressHorizontal

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgressHorizontal @(cocos2d::TransitionProgressHorizontal*) An autoreleased TransitionProgressHorizontal object.
function TransitionProgressHorizontal:create(t, scene)
end

--- @class TransitionProgressVertical
--- @brief TransitionProgressVertical transition.
---@class cc.TransitionProgressVertical:cc.TransitionProgress
local TransitionProgressVertical = {}
cc.TransitionProgressVertical = TransitionProgressVertical

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgressVertical @(cocos2d::TransitionProgressVertical*) An autoreleased TransitionProgressVertical object.
function TransitionProgressVertical:create(t, scene)
end

--- @class TransitionProgressInOut
--- @brief TransitionProgressInOut transition.
---@class cc.TransitionProgressInOut:cc.TransitionProgress
local TransitionProgressInOut = {}
cc.TransitionProgressInOut = TransitionProgressInOut

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgressInOut @(cocos2d::TransitionProgressInOut*) An autoreleased TransitionProgressInOut object.
function TransitionProgressInOut:create(t, scene)
end

--- @class TransitionProgressOutIn
--- @brief TransitionProgressOutIn transition.
---@class cc.TransitionProgressOutIn:cc.TransitionProgress
local TransitionProgressOutIn = {}
cc.TransitionProgressOutIn = TransitionProgressOutIn

--- Creates a transition with duration and incoming scene.
---
--- (static)
---@param t number @(float) Duration time, in seconds.
---@param scene cc.Scene @(cocos2d::Scene*) A given scene.
---@return cc.TransitionProgressOutIn @(cocos2d::TransitionProgressOutIn*) An autoreleased TransitionProgressOutIn object.
function TransitionProgressOutIn:create(t, scene)
end

---
--- Defines a camera .
---@class cc.Camera:cc.Node
local Camera = {}
cc.Camera = Camera

---
--- Apply the FBO, RenderTargets and viewport.
---@return self @(void)
function Camera:apply()
end

---@return self @(void)
function Camera:applyViewport()
end

---
--- Apply the zoom factor.
---
--- @since axmol-1.0.0b8
---@return self @(void)
function Camera:applyZoom()
end

---
--- Before rendering the scene with this camera, the background needs to be cleared.
--- It will clear the depth buffer with max depth by default.
--- Use setBackgroundBrush to modify this default behavior.
---@return self @(void)
function Camera:clearBackground()
end

---
--- Get clear brush
---@return cc.CameraBackgroundBrush @(cocos2d::CameraBackgroundBrush*)
function Camera:getBackgroundBrush()
end

--- get & set Camera flag
---@return cc.CameraFlag @(cocos2d::CameraFlag)
function Camera:getCameraFlag()
end

---
--- get depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with
--- CameraFlag::DEFAULT is 0, user defined camera is -1 by default
---@return signed char @(int8_t)
function Camera:getDepth()
end

---
--- Get object depth towards camera
---@param transform mat4_table @(cocos2d::Mat4)
---@return number @(float)
function Camera:getDepthInView(transform)
end

---
--- Gets the field of view of the camera if the projection mode is 3D.
---
--- @since axmol-1.0.0b8
---@return number @(float)
function Camera:getFOV()
end

---
--- Gets the frustum's far plane.
---@return number @(float)
function Camera:getFarPlane()
end

---
--- Gets the frustum's near plane.
---@return number @(float)
function Camera:getNearPlane()
end

---
--- Gets the camera's projection matrix.
---
---@return mat4_table @(const cocos2d::Mat4&) The camera projection matrix.
function Camera:getProjectionMatrix()
end

---
--- get rendered order
---@return number @(int)
function Camera:getRenderOrder()
end

---
--- Gets the camera's view matrix.
---
---@return mat4_table @(const cocos2d::Mat4&) The camera view matrix.
function Camera:getViewMatrix()
end

--- get view projection matrix
---@return mat4_table @(const cocos2d::Mat4&)
function Camera:getViewProjectionMatrix()
end

---
--- Gets the zoom multiplier of the camera.
---
--- @since axmol-1.0.0b8
---@return number @(float)
function Camera:getZoom()
end

--- Init default camera with director current projection,
--- !!!Note: Must invoke this function again when director projection or winsize changed
---@return self @(void)
function Camera:initDefault()
end

---@param zoomX number @(float)
---@param zoomY number @(float)
---@param nearPlane number @(float)
---@param farPlane number @(float)
---@return boolean @(bool)
function Camera:initOrthographic(zoomX, zoomY, nearPlane, farPlane)
end

---@param fieldOfView number @(float)
---@param aspectRatio number @(float)
---@param nearPlane number @(float)
---@param farPlane number @(float)
---@return boolean @(bool)
function Camera:initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
end

---@return boolean @(bool)
function Camera:isBrushValid()
end

---
--- Whether or not the viewprojection matrix was updated last frame.
---@return boolean @(bool) True if the viewprojection matrix was updated last frame.
function Camera:isViewProjectionUpdated()
end

---
--- Is this aabb visible in frustum
---@param aabb cc.AABB @(const cocos2d::AABB*)
---@return boolean @(bool)
function Camera:isVisibleInFrustum(aabb)
end

---
--- Make Camera looks at target
---
---@param target vec3_table @(cocos2d::Vec3) The target camera is point at
---@param up vec3_table @(cocos2d::Vec3) The up vector, usually it's Y axis
---@return self @(void)
function Camera:lookAt(target, up)
end

---
--- Make Camera looks at target
---
---@param target vec3_table @(cocos2d::Vec3) The target camera is point at
---@return self @(void)
function Camera:lookAt(target)
end

---@param src vec3_table @(cocos2d::Vec3)
---@return vec2_table @(cocos2d::Vec2)
function Camera:project(src)
end

---@param src vec3_table @(cocos2d::Vec3)
---@return vec2_table @(cocos2d::Vec2)
function Camera:projectGL(src)
end

--- set additional matrix for the projection matrix, it multiplies mat to projection matrix when called, used by
--- WP8
---@param mat mat4_table @(cocos2d::Mat4)
---@return self @(void)
function Camera:setAdditionalProjection(mat)
end

---
--- set the background brush. See CameraBackgroundBrush for more information.
---@param clearBrush cc.CameraBackgroundBrush @(cocos2d::CameraBackgroundBrush*) Brush used to clear the background
---@return self @(void)
function Camera:setBackgroundBrush(clearBrush)
end

---@param flag cc.CameraFlag @(cocos2d::CameraFlag)
---@return self @(void)
function Camera:setCameraFlag(flag)
end

---
--- set depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with
--- CameraFlag::DEFAULT is 0, user defined camera is -1 by default
---@param depth signed char @(int8_t)
---@return self @(void)
function Camera:setDepth(depth)
end

---
--- Sets the field of view of the camera if the projection mode is 3D.
---
--- @since axmol-1.0.0b8
---@param fov number @(float)
---@return self @(void)
function Camera:setFOV(fov)
end

---
--- Sets the frustum's far plane.
---
--- @since axmol-1.0.0b8
---@param farPlane number @(float)
---@return self @(void)
function Camera:setFarPlane(farPlane)
end

---
--- Gets the frustum's near plane.
---
--- @since axmol-1.0.0b8
---@param nearPlane number @(float)
---@return self @(void)
function Camera:setNearPlane(nearPlane)
end

---
--- Set the owner scene of the camera, this method shall not be invoked manually
---@param scene cc.Scene @(cocos2d::Scene*)
---@return self @(void)
function Camera:setScene(scene)
end

---
--- Sets the zoom multiplier of the camera.
--- This is designed to be used with 2D views only.
---
---
--- @since axmol-1.0.0b8
---@param factor number @(float) The zoom factor of the camera.
---@return self @(void)
function Camera:setZoom(factor)
end

--- create default camera, the camera type depends on Director::getProjection, the depth of the default camera is 0
--- (static)
---@return cc.Camera @(cocos2d::Camera*)
function Camera:create()
end

---
--- Creates an orthographic camera.
---
--- projection).
--- (static)
---@param zoomX number @(float) The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
---@param zoomY number @(float) The zoom factor along the Y-axis of the orthographic projection (the height of the ortho
---@param nearPlane number @(float) The near plane distance.
---@param farPlane number @(float) The far plane distance.
---@return cc.Camera @(cocos2d::Camera*)
function Camera:createOrthographic(zoomX, zoomY, nearPlane, farPlane)
end

---
--- Creates a perspective camera.
---
--- the viewport).
--- (static)
---@param fieldOfView number @(float) The field of view for the perspective camera (normally in the range of 40-60 degrees).
---@param aspectRatio number @(float) The aspect ratio of the camera (normally the width of the viewport divided by the height of
---@param nearPlane number @(float) The near plane distance.
---@param farPlane number @(float) The far plane distance.
---@return cc.Camera @(cocos2d::Camera*)
function Camera:createPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
end

---
--- Get the default camera of the current running scene.
--- (static)
---@return cc.Camera @(cocos2d::Camera*)
function Camera:getDefaultCamera()
end

--- (static)
---@return cc.Viewport @(const cocos2d::Viewport&)
function Camera:getDefaultViewport()
end

---
--- Get the visiting camera , the visiting camera shall be set on Scene::render
--- (static)
---@return cc.Camera @(const cocos2d::Camera*)
function Camera:getVisitingCamera()
end

--- (static)
---@param vp cc.Viewport @(cocos2d::Viewport)
---@return self @(void)
function Camera:setDefaultViewport(vp)
end

---
--- Defines a brush to clear the background of camera.
--- There are 4 types of brush. None brush do nothing, Depth brush clear background with given depth, Color brush clear
--- background with given color and depth, Skybox brush clear the background with a skybox. Camera uses depth brush by
--- default.
---@class cc.CameraBackgroundBrush:cc.Ref
local CameraBackgroundBrush = {}
cc.CameraBackgroundBrush = CameraBackgroundBrush

---
--- draw the background
---@param param1 cc.Camera @(cocos2d::Camera*)
---@return self @(void)
function CameraBackgroundBrush:drawBackground(param1)
end

---
--- get brush type
---@return cc.CameraBackgroundBrush.BrushType @(cocos2d::CameraBackgroundBrush::BrushType) BrushType
function CameraBackgroundBrush:getBrushType()
end

---@return boolean @(bool)
function CameraBackgroundBrush:init()
end

---@return boolean @(bool)
function CameraBackgroundBrush:isValid()
end

---
--- Creates a color brush
--- (static)
---@param color color4f_table @(cocos2d::Color4F) Color of brush
---@param depth number @(float) Depth used to clear depth buffer
---@return cc.CameraBackgroundColorBrush @(cocos2d::CameraBackgroundColorBrush*) Created brush
function CameraBackgroundBrush:createColorBrush(color, depth)
end

---
--- Creates a depth brush, which clears depth buffer with a given depth.
--- (static)
---@param depth number @(float) Depth used to clear depth buffer
---@return cc.CameraBackgroundDepthBrush @(cocos2d::CameraBackgroundDepthBrush*) Created brush
function CameraBackgroundBrush:createDepthBrush(depth)
end

---
--- Creates a depth brush, which clears depth buffer with a given depth.
--- (static)
---@return cc.CameraBackgroundDepthBrush @(cocos2d::CameraBackgroundDepthBrush*) Created brush
function CameraBackgroundBrush:createDepthBrush()
end

---
--- Creates a none brush, it does nothing when clear the background
--- (static)
---@return cc.CameraBackgroundBrush @(cocos2d::CameraBackgroundBrush*) Created brush.
function CameraBackgroundBrush:createNoneBrush()
end

--- Creates a Skybox brush with 6 textures.
--- @param positive_x texture for the right side of the texture cube face.
--- @param negative_x texture for the up side of the texture cube face.
--- @param positive_y texture for the top side of the texture cube face
--- @param negative_y texture for the bottom side of the texture cube face
--- @param positive_z texture for the forward side of the texture cube face.
--- @param negative_z texture for the rear side of the texture cube face.
--- @return  A new brush inited with given parameters.
--- (static)
---@param positive_x string @(std::string_view)
---@param negative_x string @(std::string_view)
---@param positive_y string @(std::string_view)
---@param negative_y string @(std::string_view)
---@param positive_z string @(std::string_view)
---@param negative_z string @(std::string_view)
---@return cc.CameraBackgroundSkyBoxBrush @(cocos2d::CameraBackgroundSkyBoxBrush*)
function CameraBackgroundBrush:createSkyboxBrush(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z)
end

---
--- Depth brush clear depth buffer with given depth
---@class cc.CameraBackgroundDepthBrush:cc.CameraBackgroundBrush
local CameraBackgroundDepthBrush = {}
cc.CameraBackgroundDepthBrush = CameraBackgroundDepthBrush

---
--- Set depth
---@param depth number @(float) Depth used to clear depth buffer
---@return self @(void)
function CameraBackgroundDepthBrush:setDepth(depth)
end

---
--- Create a depth brush
--- (static)
---@param depth number @(float) Depth used to clear the depth buffer
---@return cc.CameraBackgroundDepthBrush @(cocos2d::CameraBackgroundDepthBrush*) Created brush
function CameraBackgroundDepthBrush:create(depth)
end

---
--- Color brush clear buffer with given depth and color
---@class cc.CameraBackgroundColorBrush:cc.CameraBackgroundDepthBrush
local CameraBackgroundColorBrush = {}
cc.CameraBackgroundColorBrush = CameraBackgroundColorBrush

---
--- Set clear color
---@param color color4f_table @(cocos2d::Color4F) Color used to clear the color buffer
---@return self @(void)
function CameraBackgroundColorBrush:setColor(color)
end

---
--- Create a color brush
--- (static)
---@param color color4f_table @(cocos2d::Color4F) Color used to clear the color buffer
---@param depth number @(float) Depth used to clear the depth buffer
---@return cc.CameraBackgroundColorBrush @(cocos2d::CameraBackgroundColorBrush*) Created brush
function CameraBackgroundColorBrush:create(color, depth)
end

---
--- Skybox brush clear buffer with a skybox
---@class cc.CameraBackgroundSkyBoxBrush:cc.CameraBackgroundBrush
local CameraBackgroundSkyBoxBrush = {}
cc.CameraBackgroundSkyBoxBrush = CameraBackgroundSkyBoxBrush

---@return cc.TextureCube @(cocos2d::TextureCube*)
function CameraBackgroundSkyBoxBrush:getTexture()
end

---@return boolean @(bool)
function CameraBackgroundSkyBoxBrush:isActived()
end

---@param actived boolean @(bool)
---@return self @(void)
function CameraBackgroundSkyBoxBrush:setActived(actived)
end

---
--- Set skybox texture
---@param texture cc.TextureCube @(cocos2d::TextureCube*) Skybox texture
---@return self @(void)
function CameraBackgroundSkyBoxBrush:setTexture(texture)
end

---@param valid boolean @(bool)
---@return self @(void)
function CameraBackgroundSkyBoxBrush:setTextureValid(valid)
end

--- Creates a Skybox brush with 6 textures.
--- @param positive_x texture for the right side of the texture cube face.
--- @param negative_x texture for the up side of the texture cube face.
--- @param positive_y texture for the top side of the texture cube face
--- @param negative_y texture for the bottom side of the texture cube face
--- @param positive_z texture for the forward side of the texture cube face.
--- @param negative_z texture for the rear side of the texture cube face.
--- @return  A new brush inited with given parameters.
--- (static)
---@param positive_x string @(std::string_view)
---@param negative_x string @(std::string_view)
---@param positive_y string @(std::string_view)
---@param negative_y string @(std::string_view)
---@param positive_z string @(std::string_view)
---@param negative_z string @(std::string_view)
---@return cc.CameraBackgroundSkyBoxBrush @(cocos2d::CameraBackgroundSkyBoxBrush*)
function CameraBackgroundSkyBoxBrush:create(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z)
end

--- Creates a Skybox brush with 6 textures.
--- (static)
---@return cc.CameraBackgroundSkyBoxBrush @(cocos2d::CameraBackgroundSkyBoxBrush*)
function CameraBackgroundSkyBoxBrush:create()
end

--- Base class for Other grid.
---@class cc.GridBase:cc.Ref
local GridBase = {}
cc.GridBase = GridBase

---@return self @(void)
function GridBase:afterBlit()
end

---@param target cc.Node @(cocos2d::Node*)
---@return self @(void)
function GridBase:afterDraw(target)
end

--- @{
--- Interface for custom action when before or after draw.
--- @js NA
---@return self @(void)
function GridBase:beforeBlit()
end

--- @{
--- Init and reset the status when render effects by using the grid.
---@return self @(void)
function GridBase:beforeDraw()
end

--- Interface used to blit the texture with grid to screen.
---@return self @(void)
function GridBase:blit()
end

--- Interface, Calculate the vertices used for the blit.
---@return self @(void)
function GridBase:calculateVertexPoints()
end

---
--- @brief Get the effect grid rect.
---@return rect_table @(const cocos2d::Rect&) Return the effect grid rect.
function GridBase:getGridRect()
end

--- The size of the grid.
---@return vec2_table @(const cocos2d::Vec2&)
function GridBase:getGridSize()
end

--- Get number of times that the grid will be reused.
---@return number @(int)
function GridBase:getReuseGrid()
end

--- Pixels between the grids.
---@return vec2_table @(const cocos2d::Vec2&)
function GridBase:getStep()
end

---@param gridSize vec2_table @(cocos2d::Vec2)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param flipped boolean @(bool)
---@param rect rect_table @(cocos2d::Rect)
---@return boolean @(bool)
function GridBase:initWithSize(gridSize, texture, flipped, rect)
end

---@param gridSize vec2_table @(cocos2d::Vec2)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param flipped boolean @(bool)
---@return boolean @(bool)
function GridBase:initWithSize(gridSize, texture, flipped)
end

---@param gridSize vec2_table @(cocos2d::Vec2)
---@param rect rect_table @(cocos2d::Rect)
---@return boolean @(bool)
function GridBase:initWithSize(gridSize, rect)
end

--- @{
--- Init the Grid base.
--- @param gridSize the size of the grid.
--- @param texture The texture used for grab.
--- @param flipped whether or not the grab texture should be flip by Y or not.
--- @param rect The effective grid rect.
---@param gridSize vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function GridBase:initWithSize(gridSize)
end

--- @}*
--- @{
--- Getter and setter of the active state of the grid.
---@return boolean @(bool)
function GridBase:isActive()
end

--- is texture flipped.
---@return boolean @(bool)
function GridBase:isTextureFlipped()
end

--- Interface, Reuse the grid vertices.
---@return self @(void)
function GridBase:reuse()
end

--- Change projection to 2D for grabbing.
---@return self @(void)
function GridBase:set2DProjection()
end

---@param active boolean @(bool)
---@return self @(void)
function GridBase:setActive(active)
end

---
--- @brief Set the effect grid rect.
---@param rect rect_table @(cocos2d::Rect) The effect grid rect.
---@return self @(void)
function GridBase:setGridRect(rect)
end

--- Set the size of the grid.
---@param gridSize vec2_table @(cocos2d::Vec2)
---@return self @(void)
function GridBase:setGridSize(gridSize)
end

--- Set number of times that the grid will be reused.
---@param reuseGrid number @(int)
---@return self @(void)
function GridBase:setReuseGrid(reuseGrid)
end

--- Get the pixels between the grids.
---@param step vec2_table @(cocos2d::Vec2)
---@return self @(void)
function GridBase:setStep(step)
end

--- Set the texture flipped or not.
---@param flipped boolean @(bool)
---@return self @(void)
function GridBase:setTextureFlipped(flipped)
end

---
---  Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
---@class cc.Grid3D:cc.GridBase
local Grid3D = {}
cc.Grid3D = Grid3D

---@return boolean @(bool)
function Grid3D:getNeedDepthTestForBlit()
end

--- @{
--- Getter and Setter for depth test state when blit.
--- @js NA
---@param neededDepthTest boolean @(bool)
---@return self @(void)
function Grid3D:setNeedDepthTestForBlit(neededDepthTest)
end

--- create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param flipped boolean @(bool)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.Grid3D @(cocos2d::Grid3D*)
function Grid3D:create(gridSize, texture, flipped, rect)
end

--- create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param flipped boolean @(bool)
---@return cc.Grid3D @(cocos2d::Grid3D*)
function Grid3D:create(gridSize, texture, flipped)
end

--- create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.Grid3D @(cocos2d::Grid3D*)
function Grid3D:create(gridSize, rect)
end

--- create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@return cc.Grid3D @(cocos2d::Grid3D*)
function Grid3D:create(gridSize)
end

---
---  TiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
---  the tiles can be separated from the grid.
---@class cc.TiledGrid3D:cc.GridBase
local TiledGrid3D = {}
cc.TiledGrid3D = TiledGrid3D

--- Create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param flipped boolean @(bool)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.TiledGrid3D @(cocos2d::TiledGrid3D*)
function TiledGrid3D:create(gridSize, texture, flipped, rect)
end

--- Create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@param flipped boolean @(bool)
---@return cc.TiledGrid3D @(cocos2d::TiledGrid3D*)
function TiledGrid3D:create(gridSize, texture, flipped)
end

--- Create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@param rect rect_table @(cocos2d::Rect)
---@return cc.TiledGrid3D @(cocos2d::TiledGrid3D*)
function TiledGrid3D:create(gridSize, rect)
end

--- Create one Grid.
--- (static)
---@param gridSize vec2_table @(cocos2d::Vec2)
---@return cc.TiledGrid3D @(cocos2d::TiledGrid3D*)
function TiledGrid3D:create(gridSize)
end

---
--- @js NA
---@class cc.BaseLight:cc.Node
local BaseLight = {}
cc.BaseLight = BaseLight

--- intensity getter and setter
---@return number @(float)
function BaseLight:getIntensity()
end

--- light flag getter and setter
---@return cc.LightFlag @(cocos2d::LightFlag)
function BaseLight:getLightFlag()
end

---
--- Get the light type,light type MUST be one of LightType::DIRECTIONAL ,
--- LightType::POINT, LightType::SPOT, LightType::AMBIENT.
---@return cc.LightType @(cocos2d::LightType)
function BaseLight:getLightType()
end

---@return boolean @(bool)
function BaseLight:isEnabled()
end

---
--- light enabled getter and setter.
---@param enabled boolean @(bool)
---@return self @(void)
function BaseLight:setEnabled(enabled)
end

---@param intensity number @(float)
---@return self @(void)
function BaseLight:setIntensity(intensity)
end

---@param flag cc.LightFlag @(cocos2d::LightFlag)
---@return self @(void)
function BaseLight:setLightFlag(flag)
end

---
--- @js NA
---@class cc.DirectionLight:cc.BaseLight
local DirectionLight = {}
cc.DirectionLight = DirectionLight

---
--- Returns the Direction in parent.
---@return vec3_table @(cocos2d::Vec3)
function DirectionLight:getDirection()
end

---
--- Returns direction in world.
---@return vec3_table @(cocos2d::Vec3)
function DirectionLight:getDirectionInWorld()
end

---
--- Sets the Direction in parent.
---
---@param dir vec3_table @(cocos2d::Vec3) The Direction in parent.
---@return self @(void)
function DirectionLight:setDirection(dir)
end

---
--- Creates a direction light.
---
--- (static)
---@param direction vec3_table @(cocos2d::Vec3) The light's direction
---@param color color3b_table @(cocos2d::Color3B) The light's color.
---@return cc.DirectionLight @(cocos2d::DirectionLight*) The new direction light.
function DirectionLight:create(direction, color)
end

---
--- @js NA
---@class cc.PointLight:cc.BaseLight
local PointLight = {}
cc.PointLight = PointLight

--- get or set range
---@return number @(float)
function PointLight:getRange()
end

---@param range number @(float)
---@return self @(void)
function PointLight:setRange(range)
end

---
--- Creates a point light.
---
--- (static)
---@param position vec3_table @(cocos2d::Vec3) The light's position
---@param color color3b_table @(cocos2d::Color3B) The light's color.
---@param range number @(float) The light's range.
---@return cc.PointLight @(cocos2d::PointLight*) The new point light.
function PointLight:create(position, color, range)
end

---
--- @js NA
---@class cc.SpotLight:cc.BaseLight
local SpotLight = {}
cc.SpotLight = SpotLight

--- get cos innerAngle
---@return number @(float)
function SpotLight:getCosInnerAngle()
end

--- get cos outAngle
---@return number @(float)
function SpotLight:getCosOuterAngle()
end

---
--- Returns the Direction in parent.
---@return vec3_table @(cocos2d::Vec3)
function SpotLight:getDirection()
end

---
--- Returns direction in world.
---@return vec3_table @(cocos2d::Vec3)
function SpotLight:getDirectionInWorld()
end

---
--- Returns the inner angle the spot light (in radians).
---@return number @(float)
function SpotLight:getInnerAngle()
end

---
--- Returns the outer angle of the spot light (in radians).
---@return number @(float)
function SpotLight:getOuterAngle()
end

---
--- Returns the range of point or spot light.
---
---@return number @(float) The range of the point or spot light.
function SpotLight:getRange()
end

---
--- Sets the Direction in parent.
---
---@param dir vec3_table @(cocos2d::Vec3) The Direction in parent.
---@return self @(void)
function SpotLight:setDirection(dir)
end

---
--- Sets the inner angle of a spot light (in radians).
---
---@param angle number @(float) The angle of spot light (in radians).
---@return self @(void)
function SpotLight:setInnerAngle(angle)
end

---
--- Sets the outer angle of a spot light (in radians).
---
---@param outerAngle number @(float) The angle of spot light (in radians).
---@return self @(void)
function SpotLight:setOuterAngle(outerAngle)
end

---
--- Sets the range of point or spot light.
---
---@param range number @(float) The range of point or spot light.
---@return self @(void)
function SpotLight:setRange(range)
end

---
--- Creates a spot light.
---
--- (static)
---@param direction vec3_table @(cocos2d::Vec3) The light's direction
---@param position vec3_table @(cocos2d::Vec3) The light's position
---@param color color3b_table @(cocos2d::Color3B) The light's color.
---@param innerAngle number @(float) The light's inner angle (in radians).
---@param outerAngle number @(float) The light's outer angle (in radians).
---@param range number @(float) The light's range.
---@return cc.SpotLight @(cocos2d::SpotLight*) The new spot light.
function SpotLight:create(direction, position, color, innerAngle, outerAngle, range)
end

---
--- @js NA
---@class cc.AmbientLight:cc.BaseLight
local AmbientLight = {}
cc.AmbientLight = AmbientLight

---
--- Creates a ambient light.
---
--- (static)
---@param color color3b_table @(cocos2d::Color3B) The light's color.
---@return cc.AmbientLight @(cocos2d::AmbientLight*) The new ambient light.
function AmbientLight:create(color)
end

---
--- Defines the rendering state of the graphics device.
---@class cc.RenderState:cc.Ref
local RenderState = {}
cc.RenderState = RenderState

---
--- Binds the render state for this RenderState and any of its parents, top-down,
--- for the given pass.
---@param pass cc.Pass @(cocos2d::Pass*)
---@param param2 cc.MeshCommand @(cocos2d::MeshCommand*)
---@return self @(void)
function RenderState:bindPass(pass, param2)
end

---@return string @(std::string)
function RenderState:getName()
end

--- Technique
---@class cc.Technique:cc.Ref
local Technique = {}
cc.Technique = Technique

--- Adds a new pass to the Technique.
--- Order matters. First added, first rendered
---@param pass cc.Pass @(cocos2d::Pass*)
---@return self @(void)
function Technique:addPass(pass)
end

--- Returns a new clone of the Technique
---@return cc.Technique @(cocos2d::Technique*)
function Technique:clone()
end

--- Returns the name of the Technique
---@return string @(std::string)
function Technique:getName()
end

--- Returns the Pass at given index
---@param index number @(ssize_t)
---@return cc.Pass @(cocos2d::Pass*)
function Technique:getPassByIndex(index)
end

--- Returns the number of Passes in the Technique
---@return number @(ssize_t)
function Technique:getPassCount()
end

--- Returns the list of passes
---@return cc.Pass [] @(const cocos2d::Vector<cocos2d::Pass *>&)
function Technique:getPasses()
end

---@param material cc.Material @(cocos2d::Material*)
---@return self @(void)
function Technique:setMaterial(material)
end

--- (static)
---@param parent cc.Material @(cocos2d::Material*)
---@return cc.Technique @(cocos2d::Technique*)
function Technique:create(parent)
end

--- Creates a new Technique with a GLProgramState.
--- Method added to support legacy code
--- (static)
---@param parent cc.Material @(cocos2d::Material*)
---@param state ccb.ProgramState @(cocos2d::backend::ProgramState*)
---@return cc.Technique @(cocos2d::Technique*)
function Technique:createWithProgramState(parent, state)
end

--- Material
---@class cc.Material:cc.Ref
local Material = {}
cc.Material = Material

--- Adds a Technique into the Material
---@param technique cc.Technique @(cocos2d::Technique*)
---@return self @(void)
function Material:addTechnique(technique)
end

--- returns a clone (deep-copy) of the material
---@return cc.Material @(cocos2d::Material*)
function Material:clone()
end

---@param meshCommand cc.MeshCommand @(cocos2d::MeshCommand*)
---@param globalZOrder number @(float)
---@param vertexBuffer ccb.Buffer @(cocos2d::backend::Buffer*)
---@param indexBuffer ccb.Buffer @(cocos2d::backend::Buffer*)
---@param primitive ccb.PrimitiveType @(cocos2d::CustomCommand::PrimitiveType)
---@param indexFormat ccb.IndexFormat @(cocos2d::CustomCommand::IndexFormat)
---@param indexCount number @(unsigned int)
---@param modelView mat4_table @(cocos2d::Mat4)
---@return self @(void)
function Material:draw(meshCommand, globalZOrder, vertexBuffer, indexBuffer, primitive, indexFormat, indexCount, modelView)
end

--- returns the material name
---@return string @(std::string)
function Material:getName()
end

---
--- Get material primitive draw type
---@return ccb.PrimitiveType @(cocos2d::backend::PrimitiveType) Primitive draw type
function Material:getPrimitiveType()
end

---@return cc.RenderState @(cocos2d::RenderState*)
function Material:getRenderState()
end

--- Returns the Technique used by the Material
---@return cc.Technique @(cocos2d::Technique*)
function Material:getTechnique()
end

--- Returns a Technique by index.
--- returns `nullptr` if the index is invalid.
---@param index number @(ssize_t)
---@return cc.Technique @(cocos2d::Technique*)
function Material:getTechniqueByIndex(index)
end

--- Returns a Technique by its name.
--- returns `nullptr` if the Technique can't be found.
---@param name string @(std::string_view)
---@return cc.Technique @(cocos2d::Technique*)
function Material:getTechniqueByName(name)
end

--- Returns the number of Techniques in the Material.
---@return number @(ssize_t)
function Material:getTechniqueCount()
end

--- Returns the list of Techniques
---@return cc.Technique [] @(const cocos2d::Vector<cocos2d::Technique *>&)
function Material:getTechniques()
end

---
--- Is material in 2D render queue?
---@return boolean @(bool)
function Material:isForce2DQueue()
end

---
--- Is material transparent?
---@return boolean @(bool)
function Material:isTransparent()
end

---
--- Enable material 2D queue rendering.
---@param value boolean @(bool)
---@return self @(void)
function Material:setForce2DQueue(value)
end

--- sets the material name
---@param name string @(std::string_view)
---@return self @(void)
function Material:setName(name)
end

---
--- Set material primitive draw type
---@param primitive ccb.PrimitiveType @(cocos2d::backend::PrimitiveType) Primitive draw type
---@return self @(void)
function Material:setPrimitiveType(primitive)
end

--- Sets the current technique
---@param techniqueName string @(std::string_view)
---@return self @(void)
function Material:setTechnique(techniqueName)
end

---
--- Enable material transparent rendering.
--- WARNING: depth testing will not work.
---@param value boolean @(bool)
---@return self @(void)
function Material:setTransparent(value)
end

---
--- Creates a Material using the data from the Properties object defined at the specified URL,
--- where the URL is of the format "<file-path>.<extension>#<namespace-id><namespace-id>...<namespace-id>"
--- (and "#<namespace-id><namespace-id>...<namespace-id>" is optional).
---
---
--- (static)
---@param path string @(std::string_view)
---@return cc.Material @(cocos2d::Material*) A new Material or NULL if there was an error.
function Material:createWithFilename(path)
end

--- Creates a Material with a GLProgramState.
--- It will only contain one Technique and one Pass.
--- Added in order to support legacy code.
--- (static)
---@param programState ccb.ProgramState @(cocos2d::backend::ProgramState*)
---@return cc.Material @(cocos2d::Material*)
function Material:createWithProgramState(programState)
end


---@class cc.Pass:cc.Ref
local Pass = {}
cc.Pass = Pass

---
--- Returns a clone (deep-copy) of this instance
---@return cc.Pass @(cocos2d::Pass*)
function Pass:clone()
end

---@param meshCommand cc.MeshCommand @(cocos2d::MeshCommand*)
---@param globalZOrder number @(float)
---@param vertexBuffer ccb.Buffer @(cocos2d::backend::Buffer*)
---@param indexBuffer ccb.Buffer @(cocos2d::backend::Buffer*)
---@param primitive ccb.PrimitiveType @(cocos2d::CustomCommand::PrimitiveType)
---@param indexFormat ccb.IndexFormat @(cocos2d::MeshCommand::IndexFormat)
---@param indexCount number @(unsigned int)
---@param modelView mat4_table @(cocos2d::Mat4)
---@return self @(void)
function Pass:draw(meshCommand, globalZOrder, vertexBuffer, indexBuffer, primitive, indexFormat, indexCount, modelView)
end

---@return string @(std::string_view)
function Pass:getName()
end

--- Returns the ProgramState
---@return ccb.ProgramState @(cocos2d::backend::ProgramState*)
function Pass:getProgramState()
end

---
--- Returns the vertex attribute binding for this pass.
---
---@return cc.VertexAttribBinding @(cocos2d::VertexAttribBinding*) The vertex attribute binding for this pass.
function Pass:getVertexAttributeBinding()
end

---@param name string @(std::string_view)
---@return self @(void)
function Pass:setName(name)
end

---@param technique cc.Technique @(cocos2d::Technique*)
---@return self @(void)
function Pass:setTechnique(technique)
end

---@param slot number @(uint32_t)
---@param param2 ccb.TextureBackend @(cocos2d::backend::TextureBackend*)
---@return self @(void)
function Pass:setUniformNormTexture(slot, param2)
end

---@param slot number @(uint32_t)
---@param param2 ccb.TextureBackend @(cocos2d::backend::TextureBackend*)
---@return self @(void)
function Pass:setUniformTexture(slot, param2)
end

---
--- Sets a vertex attribute binding for this pass.
---
--- When a mesh binding is set, the VertexAttribBinding will be automatically
--- bound when the bind() method is called for the pass.
---
---@param binding cc.VertexAttribBinding @(cocos2d::VertexAttribBinding*) The VertexAttribBinding to set (or NULL to remove an existing binding).
---@return self @(void)
function Pass:setVertexAttribBinding(binding)
end

---@param modelView mat4_table @(cocos2d::Mat4)
---@return self @(void)
function Pass:updateMVPUniform(modelView)
end

--- (static)
---@param parent cc.Technique @(cocos2d::Technique*)
---@return cc.Pass @(cocos2d::Pass*)
function Pass:create(parent)
end

--- Creates a Pass with a GLProgramState.
--- (static)
---@param parent cc.Technique @(cocos2d::Technique*)
---@param programState ccb.ProgramState @(cocos2d::backend::ProgramState*)
---@return cc.Pass @(cocos2d::Pass*)
function Pass:createWithProgramState(parent, programState)
end


---@class cc.Renderer
local Renderer = {}
cc.Renderer = Renderer

---@param func function @(std::function<void()>) Required callback; nil is rejected.
---@param globalZOrder number @(float)
---@return self @(void)
function Renderer:addCallbackCommand(func, globalZOrder)
end

---@param func function @(std::function<void()>) Required callback; nil is rejected.
---@return self @(void)
function Renderer:addCallbackCommand(func)
end

--- Adds a `RenderComamnd` into the renderer specifying a particular render queue ID
---@param command cc.RenderCommand @(cocos2d::RenderCommand*)
---@param renderQueueID number @(int)
---@return self @(void)
function Renderer:addCommand(command, renderQueueID)
end

--- Adds a `RenderComamnd` into the renderer
---@param command cc.RenderCommand @(cocos2d::RenderCommand*)
---@return self @(void)
function Renderer:addCommand(command)
end

---@param number number @(ssize_t)
---@return self @(void)
function Renderer:addDrawnBatches(number)
end

---@param number number @(ssize_t)
---@return self @(void)
function Renderer:addDrawnVertices(number)
end

---@return self @(void)
function Renderer:beginRenderPass()
end

--- returns whether or not a rectangle is visible or not
---@param transform mat4_table @(cocos2d::Mat4)
---@param size vec2_table @(cocos2d::Vec2)
---@return boolean @(bool)
function Renderer:checkVisibility(transform, size)
end

--- Cleans all `RenderCommand`s in the queue
---@return self @(void)
function Renderer:clean()
end

---
--- Set clear values for each attachment.
--- @flags Flags to indicate which attachment clear value to be modified.
--- @color The clear color value.
--- @depth The clear depth value.
--- @stencil The clear stencil value.
---@param flags ccb.TargetBufferFlags @(cocos2d::ClearFlag)
---@param color color4f_table @(cocos2d::Color4F)
---@param depth number @(float)
---@param stencil number @(unsigned int)
---@param globalOrder number @(float)
---@return self @(void)
function Renderer:clear(flags, color, depth, stencil, globalOrder)
end

---@return self @(void)
function Renderer:clearDrawStats()
end

--- Creates a render queue and returns its Id
---@return number @(int)
function Renderer:createRenderQueue()
end

--- Begin a render pass.
---@return self @(void)
function Renderer:endRenderPass()
end

---
--- Get color clear value.
---@return color4f_table @(const cocos2d::Color4F&) Color clear value.
function Renderer:getClearColor()
end

---
--- Get depth clear value.
---@return number @(float) Depth clear value.
function Renderer:getClearDepth()
end

---
--- Get the clear flag.
---@return ccb.TargetBufferFlags @(cocos2d::ClearFlag) The clear flag.
function Renderer:getClearFlag()
end

---
--- Get the index when the stencil buffer is cleared.
---@return number @(unsigned int) The index used when the stencil buffer is cleared.
function Renderer:getClearStencil()
end

---
--- Get cull mode.
---@return ccb.CullMode @(cocos2d::CullMode) The cull mode.
function Renderer:getCullMode()
end

---@return ccb.RenderTarget @(cocos2d::backend::RenderTarget*)
function Renderer:getDefaultRenderTarget()
end

---
--- Get depth compare function.
---@return ccb.CompareFunction @(cocos2d::backend::CompareFunction) Depth compare function.
function Renderer:getDepthCompareFunction()
end

---
--- Get whether depth test state is enabled or disabled.
---@return boolean @(bool) true if depth test is enabled, otherwise false.
function Renderer:getDepthTest()
end

---
--- Get whether writing to depth buffer is enabled or not.
---@return boolean @(bool) true if enable writing into the depth buffer, false otherwise.
function Renderer:getDepthWrite()
end

---@return number @(ssize_t)
function Renderer:getDrawnBatches()
end

---@return number @(ssize_t)
function Renderer:getDrawnVertices()
end

--- Get a `GroupCommand` from a GroupCommand pool or creates a new command if the pool is empty
---@return cc.GroupCommand @(cocos2d::GroupCommand*)
function Renderer:getNextGroupCommand()
end

---@return ccb.RenderTarget @(cocos2d::backend::RenderTarget*)
function Renderer:getOffscreenRenderTarget()
end

---
--- Set render targets. If not set, will use default render targets. It will effect all commands.
--- @flags Flags to indicate which attachment to be replaced.
--- @colorAttachment The value to replace color attachment, only one color attachment supported now.
--- @depthAttachment The value to repalce depth attachment.
--- @stencilAttachment The value to replace stencil attachment. Depth attachment and stencil attachment
--- can be the same value.
---@return ccb.RenderTarget @(cocos2d::backend::RenderTarget*)
function Renderer:getRenderTarget()
end

---
--- Get the render target flag.
---@return ccb.TargetBufferFlags @(cocos2d::RenderTargetFlag) The render target flag.
function Renderer:getRenderTargetFlag()
end

---@return boolean @(bool)
function Renderer:getScissorTest()
end

--- Get the stencil test function.
---@return ccb.CompareFunction @(cocos2d::backend::CompareFunction)
function Renderer:getStencilCompareFunction()
end

--- Get the stencil action when both the stencil test and the depth test pass, or when the stencil test passes and
--- either there is no depth buffer or depth testing is not enabled.
---@return ccb.StencilOperation @(cocos2d::backend::StencilOperation)
function Renderer:getStencilDepthPassOperation()
end

--- Get the action to take when the stencil test fails.
---@return ccb.StencilOperation @(cocos2d::backend::StencilOperation)
function Renderer:getStencilFailureOperation()
end

--- Get the stencil action when the stencil test passes, but the depth test fails.
---@return ccb.StencilOperation @(cocos2d::backend::StencilOperation)
function Renderer:getStencilPassDepthFailureOperation()
end

---
--- Get the stencil readMask.
--- @see `setStencilCompareFunction(backend::CompareFunction func, unsigned int ref, unsigned int readMask)`
---@return number @(unsigned int) Stencil read mask.
function Renderer:getStencilReadMask()
end

---
--- Get stencil reference value set by `setStencilCompareFunction`.
--- @see `setStencilCompareFunction(backend::CompareFunction func, unsigned int ref, unsigned int readMask)`
---@return number @(unsigned int) Stencil reference value.
function Renderer:getStencilReferenceValue()
end

---
--- Get whether stencil test is enabled or not.
---@return boolean @(bool) true if stencil test is enabled, false otherwise.
function Renderer:getStencilTest()
end

---
--- Get the stencil write mask.
--- @see `setStencilWriteMask(unsigned int mask)`
---@return number @(unsigned int) Stencil write mask.
function Renderer:getStencilWriteMask()
end

---
--- Get winding mode.
---@return ccb.Winding @(cocos2d::Winding) The winding mode.
function Renderer:getWinding()
end

---@return self @(void)
function Renderer:init()
end

---@return cc.CallbackCommand @(cocos2d::CallbackCommand*)
function Renderer:nextCallbackCommand()
end

--- Pops a group from the render queue
---@return self @(void)
function Renderer:popGroup()
end

--- Pushes a group into the render queue
---@param renderQueueID number @(int)
---@return self @(void)
function Renderer:pushGroup(renderQueueID)
end

--- Renders into the GLView all the queued `RenderCommand` objects
---@return self @(void)
function Renderer:render()
end

---
--- Fixed-function state
---@param mode ccb.CullMode @(cocos2d::CullMode) Controls if primitives are culled when front facing, back facing, or not culled at all.
---@return self @(void)
function Renderer:setCullMode(mode)
end

---
--- Set depth compare function.
---@param func ccb.CompareFunction @(cocos2d::backend::CompareFunction) Specifies the value used for depth buffer comparisons.
---@return self @(void)
function Renderer:setDepthCompareFunction(func)
end

---
--- Enabledisable depth test.
---@param value boolean @(bool) true means enable depth test, otherwise false.
---@return self @(void)
function Renderer:setDepthTest(value)
end

---
--- Enabledisable to update depth buffer.
---@param value boolean @(bool) true means enable writing into the depth buffer, otherwise false.
---@return self @(void)
function Renderer:setDepthWrite(value)
end

---@param rt ccb.RenderTarget @(cocos2d::backend::RenderTarget*)
---@return self @(void)
function Renderer:setRenderTarget(rt)
end

---
--- Fixed-function state
---@param x number @(float)
---@param y number @(float)
---@param width number @(float)
---@param height number @(float) Specifies the height of the scissor box
---@return self @(void)
function Renderer:setScissorRect(x, y, width, height)
end

---
--- Enabledisable scissor test.
---@param enabled boolean @(bool) true if enable scissor test, false otherwise.
---@return self @(void)
function Renderer:setScissorTest(enabled)
end

---
--- Set front and back function and reference value for stencil testing.
--- @readMask Specifies a mask that is ANDed with both the reference value and the stored stencil value when the test
--- is done.
---@param func ccb.CompareFunction @(cocos2d::backend::CompareFunction) Specifies the stencil test function.
---@param ref number @(unsigned int) Specifies the reference value for the stencil test.
---@param readMask number @(unsigned int)
---@return self @(void)
function Renderer:setStencilCompareFunction(func, ref, readMask)
end

---
--- Set front and back stencil test actions.
--- when the stencil test passes and either there is no depth buffer or depth testing is not enabled.
---@param stencilFailureOp ccb.StencilOperation @(cocos2d::backend::StencilOperation) Specifies the action to take when the stencil test fails.
---@param depthFailureOp ccb.StencilOperation @(cocos2d::backend::StencilOperation) Specifies the stencil action when the stencil test passes, but the depth test fails.
---@param stencilDepthPassOp ccb.StencilOperation @(cocos2d::backend::StencilOperation) Specifies the stencil action when both the stencil test and the depth test pass, or
---@return self @(void)
function Renderer:setStencilOperation(stencilFailureOp, depthFailureOp, stencilDepthPassOp)
end

---
--- Enabledisable stencil test.
---@param value boolean @(bool) true means enable stencil test, otherwise false.
---@return self @(void)
function Renderer:setStencilTest(value)
end

---
--- Control the front and back writing of individual bits in the stencil planes.
---@param mask number @(unsigned int) Specifies a bit mask to enable and disable writing of individual bits in the stencil planes.
---@return self @(void)
function Renderer:setStencilWriteMask(mask)
end

---
--- Fixed-function state
---@param x number @(int) The x coordinate of the upper-left corner of the viewport.
---@param y number @(int) The y coordinate of the upper-left corner of the viewport.
---@param w number @(unsigned int) The width of the viewport, in pixels.
---@param h number @(unsigned int) The height of the viewport, in pixels.
---@return self @(void)
function Renderer:setViewPort(x, y, w, h)
end

---
--- Fixed-function state
---@param winding ccb.Winding @(cocos2d::Winding) The winding order of front-facing primitives.
---@return self @(void)
function Renderer:setWinding(winding)
end

--- @brief Singleton that handles the loading of textures.
--- Once the texture is loaded, the next time it will return.
--- A reference of the previously loaded texture reducing GPU & CPU memory.
---@class cc.TextureCache:cc.Ref
local TextureCache = {}
cc.TextureCache = TextureCache

---@param image cc.Image @(cocos2d::Image*)
---@param key string @(std::string_view)
---@param format ccb.PixelFormat @(cocos2d::PixelFormat)
---@return cc.Texture2D @(cocos2d::Texture2D*)
function TextureCache:addImage(image, key, format)
end

--- Returns a Texture2D object given an Image.
--- If the image was not previously loaded, it will create a new Texture2D object and it will return it.
--- Otherwise it will return a reference of a previously loaded image.
--- If "key" is nil, then a new texture will be created each time.
---@param image cc.Image @(cocos2d::Image*)
---@param key string @(std::string_view) The "key" parameter will be used as the "key" for the cache.
---@return cc.Texture2D @(cocos2d::Texture2D*)
function TextureCache:addImage(image, key)
end

---@param filepath string @(std::string_view)
---@param format ccb.PixelFormat @(cocos2d::PixelFormat)
---@return cc.Texture2D @(cocos2d::Texture2D*)
function TextureCache:addImage(filepath, format)
end

--- Returns a Texture2D object given an filename.
--- If the filename was not previously loaded, it will create a new Texture2D.
--- Object and it will return it. It will use the filename as a key.
--- Otherwise it will return a reference of a previously loaded image.
--- Supported image extensions: .png, .bmp, .jpeg, .pvr.
--- @param filepath The file path.
---@param filepath string @(std::string_view)
---@return cc.Texture2D @(cocos2d::Texture2D*)
function TextureCache:addImage(filepath)
end

--- Returns a Texture2D object given a file image.
--- If the file image was not previously loaded, it will create a new Texture2D object and it will return it.
--- Otherwise it will load a texture in a offthread, and when the image is loaded, the callback will be called with
--- the Texture2D as a parameter.
--- The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
--- Supported image extensions: .png, .jpg
--- @param filepath The file path.
--- @param callback A callback function would be invoked after the image is loaded.
--- @since v0.8
---
--- @remark Please don't invoke Texture2D::setDefaultAlphaPixelFormat in main GL thread before invoke this API.
---@param filepath string @(std::string_view)
---@param callback function @(std::function<void(cocos2d::Texture2D*)>)
---@return self @(void)
function TextureCache:addImageAsync(filepath, callback)
end

--- Output to CCLOG the current contents of this TextureCache.
--- This will attempt to calculate the size of each texture, and the total texture memory in use.
---
--- @since v1.0
---@return string @(std::string)
function TextureCache:getCachedTextureInfo()
end

---
--- @js NA
--- @lua NA
---@return string @(std::string)
function TextureCache:getDescription()
end

---
--- Get the file path of the texture
---
---
---@param texture cc.Texture2D @(cocos2d::Texture2D*) A Texture2D object pointer.
---@return string @(std::string) The full path of the file.
function TextureCache:getTextureFilePath(texture)
end

--- Returns an already created texture. Returns nil if the texture doesn't exist.
--- @param key It's the relatedabsolute path of the file image.
--- @since v0.99.5
---@param key string @(std::string_view)
---@return cc.Texture2D @(cocos2d::Texture2D*)
function TextureCache:getTextureForKey(key)
end

--- Reload texture from the image file.
--- If the file image hasn't loaded before, load it.
--- Otherwise the texture will be reloaded from the file image.
---@param fileName string @(std::string_view) It's the relatedabsolute path of the file image.
---@return boolean @(bool) True if the reloading is succeed, otherwise return false.
function TextureCache:reloadTexture(fileName)
end

--- Purges the dictionary of loaded textures.
--- Call this method if you receive the "Memory Warning".
--- In the short term: it will free some resources preventing your app from being killed.
--- In the medium term: it will allocate more resources.
--- In the long term: it will be the same.
---@return self @(void)
function TextureCache:removeAllTextures()
end

--- Deletes a texture from the cache given a texture.
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function TextureCache:removeTexture(texture)
end

--- Deletes a texture from the cache given a its key name.
--- @param key It's the relatedabsolute path of the file image.
--- @since v0.99.4
---@param key string @(std::string_view)
---@return self @(void)
function TextureCache:removeTextureForKey(key)
end

--- Removes unused textures.
--- Textures that have a retain count of 1 will be deleted.
--- It is convenient to call this method after when starting a new Scene.
--- @since v0.8
---@return self @(void)
function TextureCache:removeUnusedTextures()
end

--- Reload texture from a new file.
--- This function is mainly for editor, won't suggest use it in game for performance reason.
---
---
--- @since v3.10
---@param srcName string @(std::string_view) Original texture file name.
---@param dstName string @(std::string_view) New texture file name.
---@return self @(void)
function TextureCache:renameTextureWithKey(srcName, dstName)
end

--- Unbind all bound image asynchronous load callbacks.
--- @since v3.1
---@return self @(void)
function TextureCache:unbindAllImageAsync()
end

--- Unbind a specified bound image asynchronous callback.
--- In the case an object who was bound to an image asynchronous callback was destroyed before the callback is
--- invoked, the object always need to unbind this callback manually.
--- @since v3.1
---@param filename string @(std::string_view) It's the relatedabsolute path of the file image.
---@return self @(void)
function TextureCache:unbindImageAsync(filename)
end

--- Called by director, please do not called outside.
---@return self @(void)
function TextureCache:waitForQuit()
end

--- (static)
---@return string @(std::string)
function TextureCache:getETC1AlphaFileSuffix()
end

--- (static)
---@param suffix string @(std::string_view)
---@return self @(void)
function TextureCache:setETC1AlphaFileSuffix(suffix)
end

---
--- @class Device
--- @brief
---@class cc.Device
local Device = {}
cc.Device = Device

---
--- Gets the DPI of device
--- @return The DPI of device.
--- (static)
---@return number @(int)
function Device:getDPI()
end

---
--- To enable or disable accelerometer.
--- (static)
---@param isEnabled boolean @(bool)
---@return self @(void)
function Device:setAccelerometerEnabled(isEnabled)
end

---
--- Sets the interval of accelerometer.
--- (static)
---@param interval number @(float)
---@return self @(void)
function Device:setAccelerometerInterval(interval)
end

---
--- Controls whether the screen should remain on.
---
--- (static)
---@param keepScreenOn boolean @(bool) One flag indicating that the screen should remain on.
---@return self @(void)
function Device:setKeepScreenOn(keepScreenOn)
end

---
--- Vibrate for the specified amount of time.
--- If vibrate is not supported, then invoking this method has no effect.
--- Some platforms limit to a maximum duration of 5 seconds.
--- Duration is ignored on iOS due to API limitations.
--- (static)
---@param duration number @(float) The duration in seconds.
---@return self @(void)
function Device:vibrate(duration)
end


---@class cc.Application
local Application = {}
cc.Application = Application

---
--- @brief Get current language config
--- @return Current language config
---@return cc.LanguageType @(cocos2d::LanguageType)
function Application:getCurrentLanguage()
end

---
--- @brief Get current language iso 639-1 code
--- @return Current language iso 639-1 code
---@return string @(const char*)
function Application:getCurrentLanguageCode()
end

---
--- @brief Get target platform
---@return cc.ApplicationProtocol.Platform @(cocos2d::ApplicationProtocol::Platform)
function Application:getTargetPlatform()
end

---
--- @brief Get application version.
---@return string @(std::string)
function Application:getVersion()
end

---
--- @brief Open url in default browser
--- @param String with url to open.
--- @return true if the resource located by the URL was successfully opened; otherwise false.
---@param url string @(std::string_view)
---@return boolean @(bool)
function Application:openURL(url)
end

---
--- @brief    Callback by Director to limit FPS.
--- @param interval The time, expressed in seconds, between current frame and next.
---@param interval number @(float)
---@return self @(void)
function Application:setAnimationInterval(interval)
end

---
--- @brief    Get current application instance.
--- @return Current application instance pointer.
--- (static)
---@return cc.Application @(cocos2d::Application*)
function Application:getInstance()
end


---@class cc.GLViewImpl:cc.GLView
local GLViewImpl = {}
cc.GLViewImpl = GLViewImpl

--- (static)
---@param viewName string @(std::string_view)
---@return cc.GLViewImpl @(cocos2d::GLViewImpl*)
function GLViewImpl:createWithFullScreen(viewName)
end

--- Singleton that manages the Animations.
--- It saves in a cache the animations. You should use this class if you want to save your animations in a cache.
---
--- Before v0.99.5, the recommend way was to save them on the Sprite. Since v0.99.5, you should use this class instead.
---
--- @since v0.99.5
--- @js cc.animationCache
---@class cc.AnimationCache:cc.Ref
local AnimationCache = {}
cc.AnimationCache = AnimationCache

--- Adds a Animation with a name.
---
---@param animation cc.Animation @(cocos2d::Animation*) An animation.
---@param name string @(std::string_view) The name of animation.
---@return self @(void)
function AnimationCache:addAnimation(animation, name)
end

--- Adds an animation from a plist file.
--- Make sure that the frames were previously loaded in the SpriteFrameCache.
--- @since v1.1
--- @js addAnimations
--- @lua addAnimations
---@param plist string @(std::string_view) An animation from a plist file.
---@return self @(void)
function AnimationCache:addAnimations(plist)
end

--- Adds an animation from an NSDictionary.
--- Make sure that the frames were previously loaded in the SpriteFrameCache.
--- @since v1.1
--- @js NA
---@param dictionary tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) An NSDictionary.
---@param plist string @(std::string_view) The path of the relative file,it use to find the plist path for load SpriteFrames.
---@return self @(void)
function AnimationCache:addAnimationsWithDictionary(dictionary, plist)
end

--- Returns a Animation that was previously added.
--- If the name is not found it will return nil.
--- You should retain the returned copy if you are going to use it.
---
---@param name string @(std::string_view)
---@return cc.Animation @(cocos2d::Animation*) A Animation that was previously added. If the name is not found it will return nil.
function AnimationCache:getAnimation(name)
end

---@return boolean @(bool)
function AnimationCache:init()
end

--- Deletes a Animation from the cache.
---
---@param name string @(std::string_view) The name of animation.
---@return self @(void)
function AnimationCache:removeAnimation(name)
end

--- Returns the shared instance of the Animation cache
--- @js NA
--- (static)
---@return cc.AnimationCache @(cocos2d::AnimationCache*)
function AnimationCache:getInstance()
end

--- SpriteBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
--- (often known as "batch draw").
---
--- A SpriteBatchNode can reference one and only one texture (one image file, one texture atlas).
--- Only the Sprites that are contained in that texture can be added to the SpriteBatchNode.
--- All Sprites added to a SpriteBatchNode are drawn in one OpenGL ES draw call.
--- If the Sprites are not added to a SpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is
--- less efficient.
---
---  *
--- Limitations:
---  - The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is Sprite or any subclass of
--- Sprite. eg: particles, labels and layer can't be added to a SpriteBatchNode.
---  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of
--- the texture, and all the sprites share the same texture.
---
--- @since v0.7.1
---@class cc.SpriteBatchNode:cc.Node
local SpriteBatchNode = {}
cc.SpriteBatchNode = SpriteBatchNode

---@param child cc.Sprite @(cocos2d::Sprite*)
---@param z number @(int)
---@param aTag number @(int)
---@return cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*)
function SpriteBatchNode:addSpriteWithoutQuad(child, z, aTag)
end

--- Append the child.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) A Sprite.
---@return self @(void)
function SpriteBatchNode:appendChild(sprite)
end

--- Get the nearest index from the sprite in z.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) The parent sprite.
---@param z number @(int) Z order for drawing priority.
---@return number @(ssize_t) Index.
function SpriteBatchNode:atlasIndexForChild(sprite, z)
end

---
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function SpriteBatchNode:getBlendFunc()
end

--- Returns an array with the descendants (children, gran children, etc.).
--- This is specific to BatchNode. In order to use the children, use getChildren() instead.
---
---@return cc.Sprite [] @(const std::vector<cocos2d::Sprite *>&) An array with the descendants (children, gran children, etc.).
function SpriteBatchNode:getDescendants()
end

---@return cc.Texture2D @(cocos2d::Texture2D*)
function SpriteBatchNode:getTexture()
end

--- Returns the TextureAtlas object.
---
---@return cc.TextureAtlas @(cocos2d::TextureAtlas*) The TextureAtlas object.
function SpriteBatchNode:getTextureAtlas()
end

--- Get the Max image block index,in all child.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) The parent sprite.
---@return number @(ssize_t) Index.
function SpriteBatchNode:highestAtlasIndexInChild(sprite)
end

--- Increase the Atlas Capacity.
---@return self @(void)
function SpriteBatchNode:increaseAtlasCapacity()
end

--- initializes a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
--- The file will be loaded using the TextureMgr.
--- @js init
--- @lua init
---@param fileImage string @(std::string_view)
---@param capacity number @(ssize_t)
---@return boolean @(bool)
function SpriteBatchNode:initWithFile(fileImage, capacity)
end

--- initializes a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
--- The file will be loaded using the TextureMgr.
--- @js init
--- @lua init
---@param fileImage string @(std::string_view)
---@return boolean @(bool)
function SpriteBatchNode:initWithFile(fileImage)
end

--- initializes a SpriteBatchNode with a texture2d and capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
---@param tex cc.Texture2D @(cocos2d::Texture2D*)
---@param capacity number @(ssize_t)
---@return boolean @(bool)
function SpriteBatchNode:initWithTexture(tex, capacity)
end

--- initializes a SpriteBatchNode with a texture2d and capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
---@param tex cc.Texture2D @(cocos2d::Texture2D*)
---@return boolean @(bool)
function SpriteBatchNode:initWithTexture(tex)
end

--- Inserts a quad at a certain index into the texture atlas. The Sprite won't be added into the children array.
--- This method should be called only when you are dealing with very big AtlasSprite and when most of the Sprite
--- won't be updated. For example: a tile map (TMXMap) or a label with lots of characters (LabelBMFont).
---@param sprite cc.Sprite @(cocos2d::Sprite*)
---@param index number @(ssize_t)
---@return self @(void)
function SpriteBatchNode:insertQuadFromSprite(sprite, index)
end

--- Get the Min image block index,in all child.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) The parent sprite.
---@return number @(ssize_t) Index.
function SpriteBatchNode:lowestAtlasIndexInChild(sprite)
end

--- Rebuild index with a sprite all child.
---
---@param parent cc.Sprite @(cocos2d::Sprite*) The parent sprite.
---@param index number @(ssize_t) The child index.
---@return number @(ssize_t) Index.
function SpriteBatchNode:rebuildIndexInOrder(parent, index)
end

---
--- @js NA
---@param cleanup boolean @(bool)
---@return self @(void)
function SpriteBatchNode:removeAllChildrenWithCleanup(cleanup)
end

--- Removes a child given a certain index. It will also cleanup the running actions depending on the cleanup
--- parameter.
---
--- @warning Removing a child from a SpriteBatchNode is very slow.
---@param index number @(ssize_t) A certain index.
---@param doCleanup boolean @(bool) Whether or not to cleanup the running actions.
---@return self @(void)
function SpriteBatchNode:removeChildAtIndex(index, doCleanup)
end

--- Remove a sprite from Atlas.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) A Sprite.
---@return self @(void)
function SpriteBatchNode:removeSpriteFromAtlas(sprite)
end

---@param reorder boolean @(bool)
---@return self @(void)
function SpriteBatchNode:reorderBatch(reorder)
end

--- reserves capacity for the batch node.
--- If the current capacity is bigger, nothing happens.
--- otherwise, a new capacity is allocated
---@param newCapacity number @(ssize_t)
---@return self @(void)
function SpriteBatchNode:reserveCapacity(newCapacity)
end

---
--- *@code
--- When this function bound into js or lua,the parameter will be changed.
--- In js: var setBlendFunc(var src, var dst).
--- @endcode
--- @lua NA
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function SpriteBatchNode:setBlendFunc(blendFunc)
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function SpriteBatchNode:setTexture(texture)
end

--- Sets the TextureAtlas object.
---
---@param textureAtlas cc.TextureAtlas @(cocos2d::TextureAtlas*) The TextureAtlas object.
---@return self @(void)
function SpriteBatchNode:setTextureAtlas(textureAtlas)
end

--- Creates a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
--- The file will be loaded using the TextureMgr.
---
--- (static)
---@param fileImage string @(std::string_view) A file image (.png, .jpeg, .pvr, etc).
---@param capacity number @(ssize_t) The capacity of children.
---@return cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*) Return an autorelease object.
function SpriteBatchNode:create(fileImage, capacity)
end

--- Creates a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
--- The file will be loaded using the TextureMgr.
---
--- (static)
---@param fileImage string @(std::string_view) A file image (.png, .jpeg, .pvr, etc).
---@return cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*) Return an autorelease object.
function SpriteBatchNode:create(fileImage)
end

--- Creates a SpriteBatchNode with a texture2d and capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
---
--- (static)
---@param tex cc.Texture2D @(cocos2d::Texture2D*) A texture2d.
---@param capacity number @(ssize_t) The capacity of children.
---@return cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*) Return an autorelease object.
function SpriteBatchNode:createWithTexture(tex, capacity)
end

--- Creates a SpriteBatchNode with a texture2d and capacity of children.
--- The capacity will be increased in 33% in runtime if it runs out of space.
---
--- (static)
---@param tex cc.Texture2D @(cocos2d::Texture2D*) A texture2d.
---@return cc.SpriteBatchNode @(cocos2d::SpriteBatchNode*) Return an autorelease object.
function SpriteBatchNode:createWithTexture(tex)
end

--- @class ParallaxNode
--- @brief ParallaxNode: A node that simulates a parallax scroller
---
--- The children will be moved faster slower than the parent according the parallax ratio.
---
---@class cc.ParallaxNode:cc.Node
local ParallaxNode = {}
cc.ParallaxNode = ParallaxNode

--- Adds a child to the container with a local z-order, parallax ratio and position offset.
---
---@param child cc.Node @(cocos2d::Node*) A child node.
---@param z number @(int) Z order for drawing priority.
---@param parallaxRatio vec2_table @(cocos2d::Vec2) A given parallax ratio.
---@param positionOffset vec2_table @(cocos2d::Vec2) A given position offset.
---@return self @(void)
function ParallaxNode:addChild(child, z, parallaxRatio, positionOffset)
end

---@param cleanup boolean @(bool)
---@return self @(void)
function ParallaxNode:removeAllChildrenWithCleanup(cleanup)
end

--- Create a Parallax node.
---
--- (static)
---@return cc.ParallaxNode @(cocos2d::ParallaxNode*) An autoreleased ParallaxNode object.
function ParallaxNode:create()
end

--- @brief TMXObjectGroup represents the TMX object group.
--- @since v0.99.0
---@class cc.TMXObjectGroup:cc.Ref
local TMXObjectGroup = {}
cc.TMXObjectGroup = TMXObjectGroup

--- Get the group name.
---
---@return string @(std::string_view) The group name.
function TMXObjectGroup:getGroupName()
end

--- Return the dictionary for the specific object name.
--- It will return the 1st object found on the array for the given name.
---
---@param objectName string @(std::string_view)
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) Return the dictionary for the specific object name.
function TMXObjectGroup:getObject(objectName)
end

---@return cc.Value[] @(cocos2d::ValueVector&)
function TMXObjectGroup:getObjects()
end

--- Gets the array of the objects.
---
---@return cc.Value[] @(const cocos2d::ValueVector&) The array of the objects.
function TMXObjectGroup:getObjects()
end

--- Gets the offset position of child objects.
---
---@return vec2_table @(const cocos2d::Vec2&) The offset position of child objects.
function TMXObjectGroup:getPositionOffset()
end

---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap&)
function TMXObjectGroup:getProperties()
end

--- Gets the list of properties stored in a dictionary.
---
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(const cocos2d::ValueMap&) The list of properties stored in a dictionary.
function TMXObjectGroup:getProperties()
end

--- Return the value for the specific property name.
---
--- @js NA
---@param propertyName string @(std::string_view) The specific property name.
---@return cc.Value @(cocos2d::Value) Return the value for the specific property name.
function TMXObjectGroup:getProperty(propertyName)
end

--- Set the group name.
---
---@param groupName string @(std::string_view) A string,it is used to set the group name.
---@return self @(void)
function TMXObjectGroup:setGroupName(groupName)
end

--- Sets the array of the objects.
---
---@param objects cc.Value[] @(cocos2d::ValueVector) The array of the objects.
---@return self @(void)
function TMXObjectGroup:setObjects(objects)
end

--- Sets the offset position of child objects.
---
---@param offset vec2_table @(cocos2d::Vec2) The offset position of child objects.
---@return self @(void)
function TMXObjectGroup:setPositionOffset(offset)
end

--- Sets the list of properties.
---
---@param properties tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) The list of properties.
---@return self @(void)
function TMXObjectGroup:setProperties(properties)
end

--- @brief TMXLayerInfo contains the information about the layers like:
--- - Layer name
--- - Layer size
--- - Layer opacity at creation time (it can be modified at runtime)
--- - Whether the layer is visible (if it's not visible, then the CocosNode won't be created)
---
--- This information is obtained from the TMX file.
---@class cc.TMXLayerInfo:cc.Ref
local TMXLayerInfo = {}
cc.TMXLayerInfo = TMXLayerInfo

---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap&)
function TMXLayerInfo:getProperties()
end

---@param properties tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@return self @(void)
function TMXLayerInfo:setProperties(properties)
end

--- @brief TMXTilesetInfo contains the information about the tilesets like:
--- - Tileset name
--- - Tileset spacing
--- - Tileset margin
--- - size of the tiles
--- - Image used for the tiles
--- - Image size
---
--- This information is obtained from the TMX file.
---@class cc.TMXTilesetInfo:cc.Ref
local TMXTilesetInfo = {}
cc.TMXTilesetInfo = TMXTilesetInfo

---@param gid number @(uint32_t)
---@return rect_table @(cocos2d::Rect)
function TMXTilesetInfo:getRectForGID(gid)
end

--- @brief TMXMapInfo contains the information about the map like:
--- - Map orientation (hexagonal, isometric or orthogonal)
--- - Tile size
--- - Map size
---
--- And it also contains:
--- - Layers (an array of TMXLayerInfo objects)
--- - Tilesets (an array of TMXTilesetInfo objects)
--- - ObjectGroups (an array of TMXObjectGroupInfo objects)
---
--- This information is obtained from the TMX file.
---
---@class cc.TMXMapInfo
local TMXMapInfo = {}
cc.TMXMapInfo = TMXMapInfo

---@return string @(std::string_view)
function TMXMapInfo:getCurrentString()
end

---@return string @(std::string_view)
function TMXMapInfo:getExternalTilesetFileName()
end

--- map hexsidelength
---@return number @(int)
function TMXMapInfo:getHexSideLength()
end

--- layer attribs
---@return number @(int)
function TMXMapInfo:getLayerAttribs()
end

---@return cc.TMXLayerInfo [] @(cocos2d::Vector<cocos2d::TMXLayerInfo *>&)
function TMXMapInfo:getLayers()
end

--- Layers
---@return cc.TMXLayerInfo [] @(const cocos2d::Vector<cocos2d::TMXLayerInfo *>&)
function TMXMapInfo:getLayers()
end

--- map width & height
---@return vec2_table @(const cocos2d::Vec2&)
function TMXMapInfo:getMapSize()
end

---@return cc.TMXObjectGroup [] @(cocos2d::Vector<cocos2d::TMXObjectGroup *>&)
function TMXMapInfo:getObjectGroups()
end

--- ObjectGroups
---@return cc.TMXObjectGroup [] @(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&)
function TMXMapInfo:getObjectGroups()
end

--- map orientation
---@return number @(int)
function TMXMapInfo:getOrientation()
end

--- parent element
---@return number @(int)
function TMXMapInfo:getParentElement()
end

--- parent GID
---@return number @(int)
function TMXMapInfo:getParentGID()
end

---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap&)
function TMXMapInfo:getProperties()
end

--- properties
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(const cocos2d::ValueMap&)
function TMXMapInfo:getProperties()
end

--- map staggeraxis
---@return number @(int)
function TMXMapInfo:getStaggerAxis()
end

--- map stagger index
---@return number @(int)
function TMXMapInfo:getStaggerIndex()
end

---@return string @(std::string_view)
function TMXMapInfo:getTMXFileName()
end

---@return table<number, cc.Value> @(cocos2d::ValueMapIntKey&)
function TMXMapInfo:getTileProperties()
end

--- tiles width & height
---@return vec2_table @(const cocos2d::Vec2&)
function TMXMapInfo:getTileSize()
end

---@return cc.TMXTilesetInfo [] @(cocos2d::Vector<cocos2d::TMXTilesetInfo *>&)
function TMXMapInfo:getTilesets()
end

--- tilesets
---@return cc.TMXTilesetInfo [] @(const cocos2d::Vector<cocos2d::TMXTilesetInfo *>&)
function TMXMapInfo:getTilesets()
end

--- initializes a TMX format with a  tmx file
---@param tmxFile string @(std::string_view)
---@return boolean @(bool)
function TMXMapInfo:initWithTMXFile(tmxFile)
end

--- initializes a TMX format with an XML string and a TMX resource path
---@param tmxString string @(std::string_view)
---@param resourcePath string @(std::string_view)
---@return boolean @(bool)
function TMXMapInfo:initWithXML(tmxString, resourcePath)
end

--- is storing characters?
---@return boolean @(bool)
function TMXMapInfo:isStoringCharacters()
end

--- initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file
---@param xmlFilename string @(std::string_view)
---@return boolean @(bool)
function TMXMapInfo:parseXMLFile(xmlFilename)
end

---@param xmlString string @(std::string_view)
---@return boolean @(bool)
function TMXMapInfo:parseXMLString(xmlString)
end

---@param currentString string @(std::string_view)
---@return self @(void)
function TMXMapInfo:setCurrentString(currentString)
end

---@param hexSideLength number @(int)
---@return self @(void)
function TMXMapInfo:setHexSideLength(hexSideLength)
end

---@param layerAttribs number @(int)
---@return self @(void)
function TMXMapInfo:setLayerAttribs(layerAttribs)
end

---@param layers cc.TMXLayerInfo [] @(cocos2d::Vector<cocos2d::TMXLayerInfo *>)
---@return self @(void)
function TMXMapInfo:setLayers(layers)
end

---@param mapSize vec2_table @(cocos2d::Vec2)
---@return self @(void)
function TMXMapInfo:setMapSize(mapSize)
end

---@param groups cc.TMXObjectGroup [] @(cocos2d::Vector<cocos2d::TMXObjectGroup *>)
---@return self @(void)
function TMXMapInfo:setObjectGroups(groups)
end

---@param orientation number @(int)
---@return self @(void)
function TMXMapInfo:setOrientation(orientation)
end

---@param element number @(int)
---@return self @(void)
function TMXMapInfo:setParentElement(element)
end

---@param gid number @(int)
---@return self @(void)
function TMXMapInfo:setParentGID(gid)
end

---@param properties tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap)
---@return self @(void)
function TMXMapInfo:setProperties(properties)
end

---@param staggerAxis number @(int)
---@return self @(void)
function TMXMapInfo:setStaggerAxis(staggerAxis)
end

---@param staggerIndex number @(int)
---@return self @(void)
function TMXMapInfo:setStaggerIndex(staggerIndex)
end

---@param storingCharacters boolean @(bool)
---@return self @(void)
function TMXMapInfo:setStoringCharacters(storingCharacters)
end

---@param fileName string @(std::string_view)
---@return self @(void)
function TMXMapInfo:setTMXFileName(fileName)
end

---@param tileProperties table<number, cc.Value> @(cocos2d::ValueMapIntKey)
---@return self @(void)
function TMXMapInfo:setTileProperties(tileProperties)
end

---@param tileSize vec2_table @(cocos2d::Vec2)
---@return self @(void)
function TMXMapInfo:setTileSize(tileSize)
end

---@param tilesets cc.TMXTilesetInfo [] @(cocos2d::Vector<cocos2d::TMXTilesetInfo *>)
---@return self @(void)
function TMXMapInfo:setTilesets(tilesets)
end

--- creates a TMX Format with a tmx file
--- (static)
---@param tmxFile string @(std::string_view)
---@return cc.TMXMapInfo @(cocos2d::TMXMapInfo*)
function TMXMapInfo:create(tmxFile)
end

--- creates a TMX Format with an XML string and a TMX resource path
--- (static)
---@param tmxString string @(std::string_view)
---@param resourcePath string @(std::string_view)
---@return cc.TMXMapInfo @(cocos2d::TMXMapInfo*)
function TMXMapInfo:createWithXML(tmxString, resourcePath)
end

--- @brief TileMapAtlas is a subclass of AtlasNode.
---
--- It knows how to render a map based of tiles.
--- The tiles must be in a .PNG format while the map must be a .TGA file.
---
--- For more information regarding the format, please see this post:
--- http:www.cocos2d-iphone.orgarchives27
---
--- All features from AtlasNode are valid in TileMapAtlas
---
--- IMPORTANT:
--- This class is deprecated. It is maintained for compatibility reasons only.
--- You SHOULD not use this class.
--- Instead, use the newer TMX file format: TMXTiledMap
--- @js NA
---@class cc.TileMapAtlas:cc.AtlasNode
local TileMapAtlas = {}
cc.TileMapAtlas = TileMapAtlas

---
--- Returns a tile from position x,y.
--- *For the moment only channel R is used
---@param position vec2_table @(cocos2d::Vec2)
---@return color3b_table @(cocos2d::Color3B)
function TileMapAtlas:getTileAt(position)
end

--- initializes a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
--- The file will be loaded using the TextureMgr.
---@param tile string @(std::string_view)
---@param mapFile string @(std::string_view)
---@param tileWidth number @(int)
---@param tileHeight number @(int)
---@return boolean @(bool)
function TileMapAtlas:initWithTileFile(tile, mapFile, tileWidth, tileHeight)
end

--- dealloc the map from memory
---@return self @(void)
function TileMapAtlas:releaseMap()
end

--- sets a tile at position x,y.
--- For the moment only channel R is used
---@param tile color3b_table @(cocos2d::Color3B)
---@param position vec2_table @(cocos2d::Vec2)
---@return self @(void)
function TileMapAtlas:setTile(tile, position)
end

--- creates a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
--- The tile file will be loaded using the TextureMgr.
--- (static)
---@param tile string @(std::string_view)
---@param mapFile string @(std::string_view)
---@param tileWidth number @(int)
---@param tileHeight number @(int)
---@return cc.TileMapAtlas @(cocos2d::TileMapAtlas*)
function TileMapAtlas:create(tile, mapFile, tileWidth, tileHeight)
end

--- @brief FastTMXLayer represents the TMX layer.
---
--- It is a subclass of SpriteBatchNode. By default the tiles are rendered using a TextureAtlas.
--- If you modify a tile on runtime, then, that tile will become a Sprite, otherwise no Sprite objects are created.
--- The benefits of using Sprite objects as tiles are:
--- - tiles (Sprite) can be rotatedscaledmoved with a nice API.
---
--- If the layer contains a property named "cc_vertexz" with an integer (in can be positive or negative),
--- then all the tiles belonging to the layer will use that value as their OpenGL vertex Z for depth.
---
--- On the other hand, if the "cc_vertexz" property has the "automatic" value, then the tiles will use an automatic
---  vertex Z value.
--- Also before drawing the tiles, GL_ALPHA_TEST will be enabled, and disabled after drawing them. The used alpha func
---  will be:
---
--- glAlphaFunc( GL_GREATER, value ).
---
--- "value" by default is 0, but you can change it from Tiled by adding the "cc_alpha_func" property to the layer.
--- The value 0 should work for most cases, but if you have tiles that are semi-transparent, then you might want to use a
---  different
--- value, like 0.5.
---
--- For further information, please see the programming guide:
--- http:www.cocos2d-iphone.orgwikidoku.phpprog_guide:tiled_maps
---
--- @since v3.2
--- @js NA
---@class cc.FastTMXLayer:cc.Node
local FastTMXLayer = {}
cc.FastTMXLayer = FastTMXLayer

--- Get the tile layer name.
---
---@return string @(std::string_view) The tile layer name.
function FastTMXLayer:getLayerName()
end

--- Layer orientation, which is the same as the map orientation.
---
---@return number @(int) Layer orientation, which is the same as the map orientation.
function FastTMXLayer:getLayerOrientation()
end

--- Gets the size of the layer in tiles.
---
---@return vec2_table @(const cocos2d::Vec2&) The size of the layer in tiles.
function FastTMXLayer:getLayerSize()
end

--- Gets the size of the map's tile (could be different from the tile's size).
---
---@return vec2_table @(const cocos2d::Vec2&) The size of the map's tile (could be different from the tile's size).
function FastTMXLayer:getMapTileSize()
end

--- Returns the position in points of a given tile coordinate.
---
---@param tileCoordinate vec2_table @(cocos2d::Vec2) The tile Coordinate.
---@return vec2_table @(cocos2d::Vec2) The position in points of a given tile coordinate.
function FastTMXLayer:getPositionAt(tileCoordinate)
end

--- Properties from the layer. They can be added using Tiled.
---
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap&) Properties from the layer. They can be added using Tiled.
function FastTMXLayer:getProperties()
end

--- Properties from the layer. They can be added using Tiled.
---
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(const cocos2d::ValueMap&) Properties from the layer. They can be added using Tiled.
function FastTMXLayer:getProperties()
end

--- Return the value for the specific property name.
---
---@param propertyName string @(std::string_view) The value for the specific property name.
---@return cc.Value @(cocos2d::Value) The value for the specific property name.
function FastTMXLayer:getProperty(propertyName)
end

---@return cc.TMXTileAnimManager @(cocos2d::TMXTileAnimManager*)
function FastTMXLayer:getTileAnimManager()
end

--- Returns the tile (Sprite) at a given a tile coordinate.
--- The returned Sprite will be already added to the TMXLayer. Don't add it again.
--- The Sprite can be treated like any other Sprite: rotated, scaled, translated, opacity, color, etc.
--- You can remove either by calling:
--- - layer->removeChild(sprite, cleanup);
---
---@param tileCoordinate vec2_table @(cocos2d::Vec2)
---@return cc.Sprite @(cocos2d::Sprite*) Returns the tile (Sprite) at a given a tile coordinate.
function FastTMXLayer:getTileAt(tileCoordinate)
end

--- Tileset information for the layer.
---
---@return cc.TMXTilesetInfo @(cocos2d::TMXTilesetInfo*) Tileset information for the layer.
function FastTMXLayer:getTileSet()
end

---@return boolean @(bool)
function FastTMXLayer:hasTileAnimation()
end

---@param tilesetInfo cc.TMXTilesetInfo @(cocos2d::TMXTilesetInfo*)
---@param layerInfo cc.TMXLayerInfo @(cocos2d::TMXLayerInfo*)
---@param mapInfo cc.TMXMapInfo @(cocos2d::TMXMapInfo*)
---@return boolean @(bool)
function FastTMXLayer:initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo)
end

--- Removes a tile at given tile coordinate.
---
---@param tileCoordinate vec2_table @(cocos2d::Vec2) The tile Coordinate.
---@return self @(void)
function FastTMXLayer:removeTileAt(tileCoordinate)
end

--- Set the tile layer name.
---
---@param layerName string @(std::string_view) The new layer name.
---@return self @(void)
function FastTMXLayer:setLayerName(layerName)
end

--- Set Layer orientation, which is the same as the map orientation.
---
---@param orientation number @(int) Layer orientation, which is the same as the map orientation.
---@return self @(void)
function FastTMXLayer:setLayerOrientation(orientation)
end

--- Set the size of the layer in tiles.
---
---@param size vec2_table @(cocos2d::Vec2) The new size of the layer in tiles.
---@return self @(void)
function FastTMXLayer:setLayerSize(size)
end

--- Set the size of the map's tile.
---
---@param size vec2_table @(cocos2d::Vec2) The new size of the map's tile.
---@return self @(void)
function FastTMXLayer:setMapTileSize(size)
end

--- Set the properties to the layer.
---
---@param properties tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) The properties to the layer.
---@return self @(void)
function FastTMXLayer:setProperties(properties)
end

--- Sets the tile gid (gid = tile global id) at a given tile coordinate.
--- The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
--- If a tile is already placed at that position, then it will be removed.
--- Use withFlags if the tile flags need to be changed as well.
---
---@param gid number @(int) A integer value,it will be sets the tile gid.
---@param tileCoordinate vec2_table @(cocos2d::Vec2) The tile coordinate.
---@param flags cc.TMXTileFlags_ @(cocos2d::TMXTileFlags) A TMXTileFlags.
---@return self @(void)
function FastTMXLayer:setTileGID(gid, tileCoordinate, flags)
end

--- Sets the tile gid (gid = tile global id) at a given tile coordinate.
--- The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
--- If a tile is already placed at that position, then it will be removed.
---@param gid number @(int) The gid value.
---@param tileCoordinate vec2_table @(cocos2d::Vec2) The tile coordinate.
---@return self @(void)
function FastTMXLayer:setTileGID(gid, tileCoordinate)
end

--- Set the tileset information for the layer.
---
---@param info cc.TMXTilesetInfo @(cocos2d::TMXTilesetInfo*) The new tileset information for the layer.
---@return self @(void)
function FastTMXLayer:setTileSet(info)
end

--- Set an sprite to the tile,with the tile coordinate and gid.
---
---@param sprite cc.Sprite @(cocos2d::Sprite*) A Sprite.
---@param pos vec2_table @(cocos2d::Vec2) The tile coordinate.
---@param gid number @(uint32_t) The tile gid.
---@return self @(void)
function FastTMXLayer:setupTileSprite(sprite, pos, gid)
end

--- Creates the tiles.
---@return self @(void)
function FastTMXLayer:setupTiles()
end

--- Creates a FastTMXLayer with an tileset info, a layer info and a map info.
---
--- (static)
---@param tilesetInfo cc.TMXTilesetInfo @(cocos2d::TMXTilesetInfo*) An tileset info.
---@param layerInfo cc.TMXLayerInfo @(cocos2d::TMXLayerInfo*) A layer info.
---@param mapInfo cc.TMXMapInfo @(cocos2d::TMXMapInfo*) A map info.
---@return cc.FastTMXLayer @(cocos2d::FastTMXLayer*) Return an autorelease object.
function FastTMXLayer:create(tilesetInfo, layerInfo, mapInfo)
end

--- @brief TMXTileAnimTask represents the frame-tick task of an animated tile.
--- It is a assistant class for TMXTileAnimTicker.
---@class cc.TMXTileAnimTask:cc.Ref
local TMXTileAnimTask = {}
cc.TMXTileAnimTask = TMXTileAnimTask

---@return boolean @(bool)
function TMXTileAnimTask:isRunning()
end

--- start the animation task
---@return self @(void)
function TMXTileAnimTask:start()
end

--- stop the animation task
---@return self @(void)
function TMXTileAnimTask:stop()
end

--- @brief TMXTileAnimManager controls all tile animation of a layer.
---@class cc.TMXTileAnimManager:cc.Ref
local TMXTileAnimManager = {}
cc.TMXTileAnimManager = TMXTileAnimManager

--- get vector of tasks
---@return cc.TMXTileAnimTask [] @(const cocos2d::Vector<cocos2d::TMXTileAnimTask *>&)
function TMXTileAnimManager:getTasks()
end

--- start all tile animations
---@return self @(void)
function TMXTileAnimManager:startAll()
end

--- stop all tile animations
---@return self @(void)
function TMXTileAnimManager:stopAll()
end

--- (static)
---@param layer cc.FastTMXLayer @(cocos2d::FastTMXLayer*)
---@return cc.TMXTileAnimManager @(cocos2d::TMXTileAnimManager*)
function TMXTileAnimManager:create(layer)
end

--- @brief FastTMXTiledMap knows how to parse and render a TMX map.
---
--- It adds support for the TMX tiled map format used by http:www.mapeditor.org.
--- It supports isometric, hexagonal and orthogonal tiles.
--- It also supports object groups, objects, and properties.
---
--- Features:
--- - Each tile will be treated as an Sprite.
--- - The sprites are created on demand. They will be created only when you call "layer->tileAt(position)".
--- - Each tile can be rotated moved scaled tinted "opaqued", since each tile is a Sprite.
--- - Tiles can be addedremoved in runtime.
--- - The z-order of the tiles can be modified in runtime.
--- - Each tile has an anchorPoint of (0,0).
--- - The anchorPoint of the TMXTileMap is (0,0).
--- - The TMX layers will be added as a child.
--- - The TMX layers will be aliased by default.
--- - The tileset image will be loaded using the TextureCache.
--- - Each tile will have a unique tag.
--- - Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z.
--- - Each object group will be treated as an MutableArray.
--- - Object class which will contain all the properties in a dictionary.
--- - Properties can be assigned to the Map, Layer, Object Group, and Object.
---
--- Limitations:
--- - It only supports one tileset per layer.
--- - Embedded images are not supported.
--- - It only supports the XML format (the JSON format is not supported).
---
--- Technical description:
--- Each layer is created using an FastTMXLayer (subclass of SpriteBatchNode). If you have 5 layers, then 5 FastTMXLayer
---  will be created,
--- unless the layer visibility is off. In that case, the layer won't be created at all.
--- You can obtain the layers (FastTMXLayer objects) at runtime by:
--- - map->getChildByTag(tag_number); 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
--- - map->getLayer(name_of_the_layer);
---
--- Each object group is created using a TMXObjectGroup which is a subclass of MutableArray.
--- You can obtain the object groups at runtime by:
--- - map->getObjectGroup(name_of_the_object_group);
---
--- Each object is a TMXObject.
---
--- Each property is stored as a key-value pair in an MutableDictionary.
--- You can obtain the properties at runtime by:
---
--- map->getProperty(name_of_the_property);
--- layer->getProperty(name_of_the_property);
--- objectGroup->getProperty(name_of_the_property);
--- object->getProperty(name_of_the_property);
---
--- @since v3.2
--- @js NA
---@class cc.FastTMXTiledMap:cc.Node
local FastTMXTiledMap = {}
cc.FastTMXTiledMap = FastTMXTiledMap

--- Return the FastTMXLayer for the specific layer.
---
---@param layerName string @(std::string_view)
---@return cc.FastTMXLayer @(cocos2d::FastTMXLayer*) Return the FastTMXLayer for the specific layer.
function FastTMXTiledMap:getLayer(layerName)
end

---@return number @(int)
function FastTMXTiledMap:getLayerCount()
end

--- Get map orientation.
---
---@return number @(int) The map orientation.
function FastTMXTiledMap:getMapOrientation()
end

--- The map's size property measured in tiles.
---
---@return vec2_table @(const cocos2d::Vec2&) The map's size property measured in tiles.
function FastTMXTiledMap:getMapSize()
end

--- Return the TMXObjectGroup for the specific group.
---
---@param groupName string @(std::string_view)
---@return cc.TMXObjectGroup @(cocos2d::TMXObjectGroup*) Return the TMXObjectGroup for the specific group.
function FastTMXTiledMap:getObjectGroup(groupName)
end

---@return cc.TMXObjectGroup [] @(cocos2d::Vector<cocos2d::TMXObjectGroup *>&)
function FastTMXTiledMap:getObjectGroups()
end

--- Get object groups.
---
---@return cc.TMXObjectGroup [] @(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&) Object groups.
function FastTMXTiledMap:getObjectGroups()
end

--- Get properties.
---
---@return tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(const cocos2d::ValueMap&) Properties.
function FastTMXTiledMap:getProperties()
end

--- Return properties dictionary for tile GID.
---
---@param GID number @(int)
---@return cc.Value @(cocos2d::Value) Return properties dictionary for tile GID.
function FastTMXTiledMap:getPropertiesForGID(GID)
end

--- Return the value for the specific property name.
---
---@param propertyName string @(std::string_view)
---@return cc.Value @(cocos2d::Value) Return the value for the specific property name.
function FastTMXTiledMap:getProperty(propertyName)
end

---@return string @(std::string_view)
function FastTMXTiledMap:getResourceFile()
end

--- The tiles's size property measured in pixels.
---
---@return vec2_table @(const cocos2d::Vec2&) The tiles's size property measured in pixels.
function FastTMXTiledMap:getTileSize()
end

--- initializes a TMX Tiled Map with a TMX file
---@param tmxFile string @(std::string_view)
---@return boolean @(bool)
function FastTMXTiledMap:initWithTMXFile(tmxFile)
end

--- initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources
---@param tmxString string @(std::string_view)
---@param resourcePath string @(std::string_view)
---@return boolean @(bool)
function FastTMXTiledMap:initWithXML(tmxString, resourcePath)
end

--- Set map orientation.
---
---@param mapOrientation number @(int) The map orientation.
---@return self @(void)
function FastTMXTiledMap:setMapOrientation(mapOrientation)
end

--- Set the map's size property measured in tiles.
---
---@param mapSize vec2_table @(cocos2d::Vec2) The map's size property measured in tiles.
---@return self @(void)
function FastTMXTiledMap:setMapSize(mapSize)
end

--- Set object groups.
---
---@param groups cc.TMXObjectGroup [] @(cocos2d::Vector<cocos2d::TMXObjectGroup *>) An object groups.
---@return self @(void)
function FastTMXTiledMap:setObjectGroups(groups)
end

--- Set properties.
---
---@param properties tsl.robin_map<std.string, cc.Value, hlookup.string_hash, hlookup.equal_to> @(cocos2d::ValueMap) An ValueMap Properties.
---@return self @(void)
function FastTMXTiledMap:setProperties(properties)
end

--- Set all tile animations enabled or not.
--- animations are not enabled by default
---@param enabled boolean @(bool)
---@return self @(void)
function FastTMXTiledMap:setTileAnimEnabled(enabled)
end

--- Set the tiles's size property measured in pixels.
---
---@param tileSize vec2_table @(cocos2d::Vec2) The tiles's size property measured in pixels.
---@return self @(void)
function FastTMXTiledMap:setTileSize(tileSize)
end

--- Creates a TMX Tiled Map with a TMX file.
---
--- (static)
---@param tmxFile string @(std::string_view)
---@return cc.FastTMXTiledMap @(cocos2d::FastTMXTiledMap*) An autorelease object.
function FastTMXTiledMap:create(tmxFile)
end

--- Initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources.
---
--- (static)
---@param tmxString string @(std::string_view) A TMX formatted XML string.
---@param resourcePath string @(std::string_view) A path to TMX resources.
---@return cc.FastTMXTiledMap @(cocos2d::FastTMXTiledMap*) An autorelease object.
function FastTMXTiledMap:createWithXML(tmxString, resourcePath)
end

--- @class MotionStreak3D.
--- @brief Creates a trailing path. It is created from a line segment sweeping along the path.
---@class cc.MotionStreak3D:cc.Node
local MotionStreak3D = {}
cc.MotionStreak3D = MotionStreak3D

---
--- @js NA
--- @lua NA
---@return cc.BlendFunc @(const cocos2d::BlendFunc&)
function MotionStreak3D:getBlendFunc()
end

--- Get stroke.
---
---@return number @(float) float stroke.
function MotionStreak3D:getStroke()
end

---
--- Get the direction of sweeping line segment
---@return vec3_table @(const cocos2d::Vec3&)
function MotionStreak3D:getSweepAxis()
end

---@return cc.Texture2D @(cocos2d::Texture2D*)
function MotionStreak3D:getTexture()
end

--- initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture
---@param fade number @(float)
---@param minSeg number @(float)
---@param stroke number @(float)
---@param color color3b_table @(cocos2d::Color3B)
---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return boolean @(bool)
function MotionStreak3D:initWithFade(fade, minSeg, stroke, color, texture)
end

--- initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename
---@param fade number @(float)
---@param minSeg number @(float)
---@param stroke number @(float)
---@param color color3b_table @(cocos2d::Color3B)
---@param path string @(std::string_view)
---@return boolean @(bool)
function MotionStreak3D:initWithFade(fade, minSeg, stroke, color, path)
end

--- Is the starting position initialized or not.
---
---@return boolean @(bool) True if the starting position is initialized.
function MotionStreak3D:isStartingPositionInitialized()
end

--- Remove all living segments of the ribbon.
---@return self @(void)
function MotionStreak3D:reset()
end

---
--- @js NA
--- @lua NA
---@param blendFunc cc.BlendFunc @(cocos2d::BlendFunc)
---@return self @(void)
function MotionStreak3D:setBlendFunc(blendFunc)
end

--- Sets the starting position initialized or not.
---
---@param bStartingPositionInitialized boolean @(bool) True if initialized the starting position.
---@return self @(void)
function MotionStreak3D:setStartingPositionInitialized(bStartingPositionInitialized)
end

--- Set stroke.
---
---@param stroke number @(float) The width of stroke.
---@return self @(void)
function MotionStreak3D:setStroke(stroke)
end

---
--- Set the direction of sweeping line segment.
---@param sweepAxis vec3_table @(cocos2d::Vec3) Direction of sweeping line segment
---@return self @(void)
function MotionStreak3D:setSweepAxis(sweepAxis)
end

---@param texture cc.Texture2D @(cocos2d::Texture2D*)
---@return self @(void)
function MotionStreak3D:setTexture(texture)
end

--- Color used for the tint.
---
---@param colors color3b_table @(cocos2d::Color3B) The color used for the tint.
---@return self @(void)
function MotionStreak3D:tintWithColor(colors)
end

--- Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture.
---
--- (static)
---@param fade number @(float) The fade time, in seconds.
---@param minSeg number @(float) The minimum segments.
---@param stroke number @(float) The width of stroke.
---@param color color3b_table @(cocos2d::Color3B) The color of stroke.
---@param texture cc.Texture2D @(cocos2d::Texture2D*) The texture name of stoke.
---@return cc.MotionStreak3D @(cocos2d::MotionStreak3D*) An autoreleased MotionStreak3D object.
function MotionStreak3D:create(fade, minSeg, stroke, color, texture)
end

--- Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture
--- filename.
---
--- (static)
---@param fade number @(float) The fade time, in seconds.
---@param minSeg number @(float) The minimum segments.
---@param stroke number @(float) The width of stroke.
---@param color color3b_table @(cocos2d::Color3B) The color of stroke.
---@param path string @(std::string_view) The texture file name of stoke.
---@return cc.MotionStreak3D @(cocos2d::MotionStreak3D*) An autoreleased MotionStreak3D object.
function MotionStreak3D:create(fade, minSeg, stroke, color, path)
end


---@class cc.ComponentLua:cc.Component
local ComponentLua = {}
cc.ComponentLua = ComponentLua

--- (static)
---@param scriptFileName string @(std::string_view)
---@return cc.ComponentLua @(cocos2d::ComponentLua*)
function ComponentLua:create(scriptFileName)
end

