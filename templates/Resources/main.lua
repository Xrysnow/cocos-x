local director = cc.Director:getInstance()
local scene = cc.Scene:create()
local label = cc.Label:createWithSystemFont("Hello world!", "Arial", 28)
local origin = director:getVisibleOrigin()
local size = director:getVisibleSize()

label:setAnchorPoint({ x = 0, y = 1 })
label:setPosition(origin.x + 16, origin.y + size.y - 16)
scene:addChild(label)

local dialog = cc.FileDialog
if dialog.capabilities().openFiles then
    local caption = cc.Label:createWithSystemFont("Open a file", "Arial", 22)
    local item = cc.MenuItemLabel:create(caption)
    local menu = cc.Menu:create()
    menu:addChild(item)
    menu:setPosition(origin.x + size.x / 2, origin.y + size.y / 2)
    scene:addChild(menu)
    local request
    local pending
    item:registerScriptTapHandler(function()
        if pending then return end
        local token = {}
        pending = token
        local error
        local function finished(result)
            if pending ~= token then return end
            request, pending = nil, nil
            if result.status == "ok" then
                local document = result.documents[1]
                label:setString(document:tryGetLocalPath() or document:info().displayName)
            elseif result.error then label:setString(result.error.message) end
        end
        request, error = dialog.openFiles({}, function(result)
            if pending ~= token then return end
            request = nil
            if result.status == "ok" then
                request, error = dialog.importFile(result.documents[1], {}, finished)
                if not request then finished({error = error}) end
            else
                finished(result)
            end
        end)
        if not request then finished({error = error}) end
    end)
    scene:registerScriptHandler(function(event)
        if event == "exit" then
            pending = nil
            if request then request:cancel(); request = nil end
        end
    end)
end
director:runWithScene(scene)
return true
