local director = cc.Director:getInstance()
local scene = cc.Scene:create()
local label = cc.Label:createWithSystemFont("Hello world!", "Arial", 28)
local origin = director:getVisibleOrigin()
local size = director:getVisibleSize()

label:setAnchorPoint({ x = 0, y = 1 })
label:setPosition(origin.x + 16, origin.y + size.y - 16)
scene:addChild(label)

director:runWithScene(scene)
return true
