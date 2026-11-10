/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "scripting/lua-bindings/manual/cocostudio/CustomGUIReader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

USING_NS_CC;

namespace cocostudio
{

CustomGUIReader* CustomGUIReader::create(std::string_view className,
                                         CreateFunction createFunc,
                                         SetPropsFunction setPropsFunc)
{
    auto reader = new CustomGUIReader();
    if (!reader->init(className, std::move(createFunc), std::move(setPropsFunc)))
    {
        reader->release();
        return nullptr;
    }
    reader->autorelease();
    return reader;
}

Ref* CustomGUIReader::createInstance()
{
    const auto callbacks = _callbacks;
    return callbacks ? callbacks->create() : nullptr;
}

bool CustomGUIReader::init(std::string_view className, CreateFunction createFunc, SetPropsFunction setPropsFunc)
{
    if (_callbacks || !createFunc || !setPropsFunc)
    {
        return false;
    }
    auto callbacks = std::make_shared<Callbacks>(Callbacks{std::move(createFunc), std::move(setPropsFunc)});
    _callbacks = callbacks;
    // The factory owns the callback state, never a borrowed reader pointer.
    GUIReader::getInstance()->registerTypeAndCallBack(
        className, ObjectFactory::InstanceFunc([callbacks]() { return callbacks->create(); }), this,
        parseselector(CustomGUIReader::setCustomProps));
    return true;
}

void CustomGUIReader::setCustomProps(std::string_view classType,
                                     cocos2d::Ref* widget,
                                     const rapidjson::Value& customOptions)
{
    const auto callbacks = _callbacks;
    if (callbacks && widget)
    {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        customOptions.Accept(writer);

        callbacks->setProps(classType, widget, std::string_view(buffer.GetString(), buffer.GetSize()));
    }
}
}  // namespace cocostudio
