--[[

Copyright (c) 2014-2017 Chukong Technologies Inc.
Copyright (c) 2022 Bytedance Inc.

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

]]

-- >= lua-5.4
if (math.pow == nil) then
    math.pow = function (x,y)
        return x ^ y
    end
end

-- < lua-5.4
if (unpack) then
    table.unpack = unpack
end

-- Keep method aliases within the directly registered cc table.
cc.Director.setDisplayStats = cc.Director.setStatsDisplay
cc.Sprite3D = cc.MeshRenderer

require "cc.cocos2d.Cocos2d"
require "cc.cocos2d.Cocos2dConstants"
require "cc.cocos2d.functions"

__G__TRACKBACK__ = function(msg)
    local msg = debug.traceback(msg, 3)
    print(msg)
    return msg
end

-- ui
if nil ~= ccui then
    require "cc.ui.GuiConstants"
end

-- extensions
require "cc.extension.ExtensionConstants"
-- network
require "cc.network.NetworkConstants"
-- Spine
if nil ~= sp then
    require "cc.spine.SpineConstants"
end

-- Lua extensions
require "cc.cocos2d.bitExtend"

-- physics3d
require "cc.physics3d.physics3d-constants"

if CC_USE_FRAMEWORK then
    require "cc.framework.init"
end
