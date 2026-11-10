/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include <functional>
#include "base/ObjectFactory.h"

NS_CC_BEGIN

ObjectFactory::TInfo::TInfo() : _class(""), _fun(nullptr), _func(nullptr) {}

ObjectFactory::TInfo::TInfo(std::string_view type, Instance ins) : _class(type), _fun(ins), _func(nullptr)
{
    ObjectFactory::getInstance()->registerType(*this);
}

ObjectFactory::TInfo::TInfo(std::string_view type, InstanceFunc ins) : _class(type), _fun(nullptr), _func(ins)
{
    ObjectFactory::getInstance()->registerType(*this);
}

ObjectFactory::TInfo::TInfo(const TInfo& t)
{
    _class = t._class;
    _fun   = t._fun;
    _func  = t._func;
    _registrationOwner = t._registrationOwner;
}

ObjectFactory::TInfo::~TInfo()
{
    _class = "";
    _fun   = nullptr;
    _func  = nullptr;
}

ObjectFactory::TInfo& ObjectFactory::TInfo::operator=(const TInfo& t)
{
    _class = t._class;
    _fun   = t._fun;
    _func  = t._func;
    _registrationOwner = t._registrationOwner;
    return *this;
}

ObjectFactory* ObjectFactory::_sharedFactory = nullptr;

ObjectFactory::ObjectFactory() {}

ObjectFactory::~ObjectFactory()
{
    // Reentrant cleanup can only reach a new singleton, never these buckets.
    FactoryMap registrations;
    registrations.swap(_typeMap);
}

ObjectFactory* ObjectFactory::getInstance()
{
    if (nullptr == _sharedFactory)
    {
        _sharedFactory = new ObjectFactory();
    }
    return _sharedFactory;
}

void ObjectFactory::destroyInstance()
{
    auto factory = _sharedFactory;
    _sharedFactory = nullptr;
    delete factory;
}

Ref* ObjectFactory::createObject(std::string_view name)
{
    Ref* o = nullptr;
    do
    {
        // const TInfo t = _typeMap[name.data];
        auto it = _typeMap.find(name);
        if (it == _typeMap.end())
            break;
        // A factory callback may replace its own entry or destroy the factory.
        const auto t = it->second;
        if (t._fun != nullptr)
        {
            o = t._fun();
        }
        else if (t._func != nullptr)
        {
            o = t._func();
        }
    } while (0);

    return o;
}

void ObjectFactory::registerType(const TInfo& t)
{
    auto it = _typeMap.find(t._class);
    if (it != _typeMap.end() && !it->second._registrationOwner.expired())
    {
        const TInfo previous(it->second);
        TInfo replacement(t);
        replacement._registrationOwner.reset();
        it.value() = replacement;
    }
    else
    {
        _typeMap.emplace(t._class, t);
    }
}

ObjectFactory::TInfo ObjectFactory::registerOwnedType(const TInfo& t, const std::shared_ptr<void>& owner)
{
    TInfo registration(t);
    registration._registrationOwner = owner;
    TInfo previous;
    auto it = _typeMap.find(registration._class);
    if (it == _typeMap.end())
    {
        _typeMap.emplace(registration._class, registration);
    }
    else
    {
        previous = it->second;
        it.value() = registration;
    }
    return previous;
}

void ObjectFactory::removeOwnedType(std::string_view name, const std::shared_ptr<void>& owner)
{
    // Cleanup must neither recreate a destroyed factory nor remove a newer entry.
    if (_sharedFactory)
    {
        auto it = _sharedFactory->_typeMap.find(name);
        if (it != _sharedFactory->_typeMap.end() && it->second._registrationOwner.lock() == owner)
        {
            // Last captures may destroy either singleton; release after erase.
            const TInfo previous(it->second);
            _sharedFactory->_typeMap.erase(it);
        }
    }
}

NS_CC_END
