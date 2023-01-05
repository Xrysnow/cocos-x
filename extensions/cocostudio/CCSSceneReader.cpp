/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.
Copyright (c) 2021 Bytedance Inc.

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

#include "CocoStudio.h"
#include "ui/CocosGUI.h"
#include "base/ObjectFactory.h"
#include "base/ccUtils.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;
using namespace ui;

namespace cocostudio
{

SceneReader* SceneReader::s_sharedReader = nullptr;

SceneReader::SceneReader() : _fnSelector(nullptr), _node(nullptr), _attachComponent(AttachComponentType::EMPTY_NODE)
{
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComAttribute));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComRender));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComAudio));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComController));
}

SceneReader::~SceneReader() {}

const char* SceneReader::sceneReaderVersion()
{
    return "1.0.0.0";
}

cocos2d::Node* SceneReader::createNodeWithSceneFile(
    std::string_view fileName,
    AttachComponentType attachComponent /*= AttachComponentType::EMPTY_NODE*/)
{
    std::string fileExtension = cocos2d::FileUtils::getInstance()->getFileExtension(fileName);
    if (fileExtension == ".json")
    {
        _node = nullptr;
        rapidjson::Document jsonDict;
        do
        {
            CC_BREAK_IF(!readJson(fileName, jsonDict));
            _node = createObject(jsonDict, nullptr, attachComponent);
            TriggerMng::getInstance()->parse(jsonDict);
        } while (0);

        return _node;
    }
    else if (fileExtension == ".csb")
    {
        do
        {
            std::string binaryFilePath = FileUtils::getInstance()->fullPathForFilename(fileName);
            auto fileData              = FileUtils::getInstance()->getDataFromFile(binaryFilePath);
            auto fileDataBytes         = fileData.getBytes();
            CC_BREAK_IF(fileData.isNull());
            CocoLoader tCocoLoader;
            if (tCocoLoader.ReadCocoBinBuff((char*)fileDataBytes))
            {
                stExpCocoNode* tpRootCocoNode = tCocoLoader.GetRootCocoNode();
                rapidjson::Type tType         = tpRootCocoNode->GetType(&tCocoLoader);
                if (rapidjson::kObjectType == tType)
                {
                    stExpCocoNode* tpChildArray = tpRootCocoNode->GetChildArray(&tCocoLoader);
                    CC_BREAK_IF(tpRootCocoNode->GetChildNum() == 0);
                    _node      = Node::create();
                    int nCount = 0;
                    std::vector<Component*> _vecComs;
                    ComRender* pRender = nullptr;
                    std::string key    = tpChildArray[15].GetName(&tCocoLoader);
                    if (key == "components")
                    {
                        nCount = tpChildArray[15].GetChildNum();
                    }
                    stExpCocoNode* pComponents = tpChildArray[15].GetChildArray(&tCocoLoader);
                    SerData* data              = new SerData();
                    for (int i = 0; i < nCount; i++)
                    {
                        stExpCocoNode* subDict = pComponents[i].GetChildArray(&tCocoLoader);
                        if (subDict == nullptr)
                        {
                            continue;
                        }
                        std::string key1    = subDict[1].GetName(&tCocoLoader);
                        const char* comName = subDict[1].GetValue(&tCocoLoader);
                        Component* pCom     = nullptr;
                        if (key1 == "classname" && comName != nullptr)
                        {
                            pCom = createComponent(comName);
                        }
                        if (pCom != nullptr)
                        {
                            data->_rData      = nullptr;
                            data->_cocoNode   = subDict;
                            data->_cocoLoader = &tCocoLoader;
                            if (pCom->serialize(data))
                            {
                                ComRender* pTRender = dynamic_cast<ComRender*>(pCom);
                                if (pTRender != nullptr)
                                {
                                    pRender = pTRender;
                                }
                                else
                                {
                                    _vecComs.emplace_back(pCom);
                                }
                            }
                            else
                            {
                                CC_SAFE_RELEASE_NULL(pCom);
                            }
                        }
                        if (_fnSelector != nullptr)
                        {
                            _fnSelector(pCom, (void*)(data));
                        }
                    }

                    setPropertyFromJsonDict(&tCocoLoader, tpRootCocoNode, _node);
                    for (std::vector<Component*>::iterator iter = _vecComs.begin(); iter != _vecComs.end(); ++iter)
                    {
                        _node->addComponent(*iter);
                    }

                    stExpCocoNode* pGameObjects = tpChildArray[11].GetChildArray(&tCocoLoader);
                    int length                  = tpChildArray[11].GetChildNum();
                    for (int i = 0; i < length; ++i)
                    {
                        createObject(&tCocoLoader, &pGameObjects[i], _node, attachComponent);
                    }
                    TriggerMng::getInstance()->parse(&tCocoLoader, tpChildArray);
                }
            }
        } while (0);
        return _node;
    }
    else
    {
        log("read file [%s] error!\n", fileName.data());
    }
    return nullptr;
}

bool SceneReader::readJson(std::string_view fileName, rapidjson::Document& doc)
{
    bool ret = false;
    do
    {
        std::string jsonpath   = FileUtils::getInstance()->fullPathForFilename(fileName);
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
        doc.Parse<0>(contentStr.c_str());
        CC_BREAK_IF(doc.HasParseError());
        ret = true;
    } while (0);
    return ret;
}

Node* SceneReader::nodeByTag(Node* parent, int tag)
{
    if (parent == nullptr)
    {
        return nullptr;
    }
    Node* _retNode               = nullptr;
    Vector<Node*>& Children      = parent->getChildren();
    Vector<Node*>::iterator iter = Children.begin();
    while (iter != Children.end())
    {
        Node* pNode = *iter;
        if (pNode != nullptr && pNode->getTag() == tag)
        {
            _retNode = pNode;
            break;
        }
        else
        {
            _retNode = nodeByTag(pNode, tag);
            if (_retNode != nullptr)
            {
                break;
            }
        }
        ++iter;
    }
    return _retNode;
}

cocos2d::Component* SceneReader::createComponent(std::string_view classname)
{
    std::string name = this->getComponentClassName(classname);
    Ref* object      = ObjectFactory::getInstance()->createObject(name);

    return dynamic_cast<Component*>(object);
}
std::string SceneReader::getComponentClassName(std::string_view name)
{
    std::string comName;
    if (name == "CCSprite" || name == "CCTMXTiledMap" || name == "CCParticleSystemQuad" || name == "CCArmature" ||
        name == "GUIComponent")
    {
        comName = "ComRender";
    }
    else if (name == ComAudio::COMPONENT_NAME || name == "CCBackgroundAudio")
    {
        comName = "ComAudio";
    }
    else if (name == ComController::COMPONENT_NAME)
    {
        comName = "ComController";
    }
    else if (name == ComAttribute::COMPONENT_NAME)
    {
        comName = "ComAttribute";
    }
    else if (name == "CCScene")
    {
        comName = "Scene";
    }
    else
    {
        CCASSERT(false, "Unregistered Component!");
    }

    return comName;
}

Node* SceneReader::createObject(const rapidjson::Value& dict,
                                cocos2d::Node* parent,
                                AttachComponentType attachComponent)
{
    const char* className = DICTOOL->getStringValue_json(dict, "classname");
    if (strcmp(className, "CCNode") == 0)
    {
        Node* gb = nullptr;
        if (nullptr == parent)
        {
            gb = Node::create();
        }

        std::vector<Component*> vecComs;
        ComRender* render = nullptr;
        int count         = DICTOOL->getArrayCount_json(dict, "components");
        for (int i = 0; i < count; i++)
        {
            const rapidjson::Value& subDict = DICTOOL->getSubDictionary_json(dict, "components", i);
            if (!DICTOOL->checkObjectExist_json(subDict))
            {
                break;
            }
            const char* comName = DICTOOL->getStringValue_json(subDict, "classname");
            Component* com      = this->createComponent(comName);
            SerData* data       = new SerData();
            if (com != nullptr)
            {
                data->_rData      = &subDict;
                data->_cocoNode   = nullptr;
                data->_cocoLoader = nullptr;
                if (com->serialize(data))
                {
                    ComRender* tRender = dynamic_cast<ComRender*>(com);
                    if (tRender == nullptr)
                    {
                        vecComs.emplace_back(com);
                    }
                    else
                    {
                        render = tRender;
                    }
                }
            }
            CC_SAFE_DELETE(data);
            if (_fnSelector != nullptr)
            {
                _fnSelector(com, data);
            }
        }

        if (parent != nullptr)
        {
            if (render == nullptr || attachComponent == AttachComponentType::EMPTY_NODE)
            {
                gb = Node::create();
                if (render != nullptr)
                {
                    vecComs.emplace_back(render);
                }
            }
            else
            {
                gb = render->getNode();
                gb->retain();
                render->setNode(nullptr);
            }
            parent->addChild(gb);
        }

        setPropertyFromJsonDict(dict, gb);
        for (std::vector<Component*>::iterator iter = vecComs.begin(); iter != vecComs.end(); ++iter)
        {
            gb->addComponent(*iter);
        }

        int length = DICTOOL->getArrayCount_json(dict, "gameobjects");
        for (int i = 0; i < length; ++i)
        {
            const rapidjson::Value& subDict = DICTOOL->getSubDictionary_json(dict, "gameobjects", i);
            if (!DICTOOL->checkObjectExist_json(subDict))
            {
                break;
            }
            createObject(subDict, gb, attachComponent);
        }

        if (dict.HasMember("CanvasSize"))
        {
            const rapidjson::Value& canvasSizeDict = DICTOOL->getSubDictionary_json(dict, "CanvasSize");
            if (DICTOOL->checkObjectExist_json(canvasSizeDict))
            {
                int width  = DICTOOL->getIntValue_json(canvasSizeDict, "_width");
                int height = DICTOOL->getIntValue_json(canvasSizeDict, "_height");
                gb->setContentSize(Size(width, height));
            }
        }

        return gb;
    }

    return nullptr;
}

cocos2d::Node* SceneReader::createObject(CocoLoader* cocoLoader,
                                         stExpCocoNode* cocoNode,
                                         cocos2d::Node* parent,
                                         AttachComponentType attachComponent)
{
    stExpCocoNode* pNodeArray = cocoNode->GetChildArray(cocoLoader);
    std::string Key           = pNodeArray[1].GetName(cocoLoader);
    const char* className     = Key == "classname" ? pNodeArray[1].GetValue(cocoLoader) : "";
    if (strcmp(className, "CCNode") == 0)
    {
        Node* gb = nullptr;
        std::vector<Component*> _vecComs;
        ComRender* pRender = nullptr;
        int count          = 0;
        std::string key    = pNodeArray[13].GetName(cocoLoader);
        if (key == "components")
        {
            count = pNodeArray[13].GetChildNum();
        }
        stExpCocoNode* pComponents = pNodeArray[13].GetChildArray(cocoLoader);
        SerData* data              = new SerData();
        for (int i = 0; i < count; ++i)
        {
            stExpCocoNode* subDict = pComponents[i].GetChildArray(cocoLoader);
            if (subDict == nullptr)
            {
                continue;
            }
            std::string key1    = subDict[1].GetName(cocoLoader);
            const char* comName = subDict[1].GetValue(cocoLoader);
            Component* pCom     = nullptr;
            if (key1 == "classname" && comName != nullptr)
            {
                pCom = createComponent(comName);
            }
            if (pCom != nullptr)
            {
                data->_rData      = nullptr;
                data->_cocoNode   = subDict;
                data->_cocoLoader = cocoLoader;
                if (pCom->serialize(data))
                {
                    ComRender* pTRender = dynamic_cast<ComRender*>(pCom);
                    if (pTRender != nullptr)
                    {
                        pRender = pTRender;
                    }
                    else
                    {
                        _vecComs.emplace_back(pCom);
                    }
                }
                else
                {
                    CC_SAFE_RELEASE_NULL(pCom);
                }
            }
            if (_fnSelector != nullptr)
            {
                _fnSelector(pCom, (void*)(data));
            }
        }
        CC_SAFE_DELETE(data);

        if (parent != nullptr)
        {
            if (pRender == nullptr || attachComponent == AttachComponentType::EMPTY_NODE)
            {
                gb = Node::create();
                if (pRender != nullptr)
                {
                    _vecComs.emplace_back(pRender);
                }
            }
            else
            {
                gb = pRender->getNode();
                gb->retain();
                pRender->setNode(nullptr);
                CC_SAFE_RELEASE_NULL(pRender);
            }
            parent->addChild(gb);
        }
        setPropertyFromJsonDict(cocoLoader, cocoNode, gb);
        for (std::vector<Component*>::iterator iter = _vecComs.begin(); iter != _vecComs.end(); ++iter)
        {
            gb->addComponent(*iter);
        }

        stExpCocoNode* pGameObjects = pNodeArray[12].GetChildArray(cocoLoader);
        if (pGameObjects != nullptr)
        {
            int length = pNodeArray[12].GetChildNum();
            for (int i = 0; i < length; ++i)
            {
                createObject(cocoLoader, &pGameObjects[i], gb, attachComponent);
            }
        }
        return gb;
    }
    return nullptr;
}

void SceneReader::setTarget(const std::function<void(cocos2d::Ref* obj, void* doc)>& selector)
{
    _fnSelector = selector;
}

Node* SceneReader::getNodeByTag(int nTag)
{
    if (_node == nullptr)
    {
        return nullptr;
    }
    if (_node->getTag() == nTag)
    {
        return _node;
    }
    return nodeByTag(_node, nTag);
}

void SceneReader::setPropertyFromJsonDict(const rapidjson::Value& root, cocos2d::Node* node)
{
    float x = DICTOOL->getFloatValue_json(root, "x");
    float y = DICTOOL->getFloatValue_json(root, "y");
    node->setPosition(x, y);

    const bool bVisible = (DICTOOL->getIntValue_json(root, "visible", 1) != 0);
    node->setVisible(bVisible);

    int nTag = DICTOOL->getIntValue_json(root, "objecttag", -1);
    node->setTag(nTag);

    int nZorder = DICTOOL->getIntValue_json(root, "zorder");
    node->setLocalZOrder(nZorder);

    float fScaleX = DICTOOL->getFloatValue_json(root, "scalex", 1.0);
    float fScaleY = DICTOOL->getFloatValue_json(root, "scaley", 1.0);
    node->setScaleX(fScaleX);
    node->setScaleY(fScaleY);

    float fRotationZ = DICTOOL->getFloatValue_json(root, "rotation");
    node->setRotation(fRotationZ);

    const char* sName = DICTOOL->getStringValue_json(root, "name", "");
    node->setName(sName);
}

void SceneReader::setPropertyFromJsonDict(CocoLoader* cocoLoader, stExpCocoNode* cocoNode, cocos2d::Node* node)
{
    stExpCocoNode* stChildArray = cocoNode->GetChildArray(cocoLoader);

    for (int i = 0; i < cocoNode->GetChildNum(); ++i)
    {
        std::string key   = stChildArray[i].GetName(cocoLoader);
        std::string value = stChildArray[i].GetValue(cocoLoader);

        if (key == "x")
        {
            node->setPositionX(utils::atof(value.data()));
        }
        else if (key == "y")
        {
            node->setPositionY(utils::atof(value.data()));
        }
        else if (key == "visible")
        {
            node->setVisible(atoi(value.data()) != 0);
        }
        else if (key == "objecttag")
        {
            node->setTag(atoi(value.data()));
        }
        else if (key == "zorder")
        {
            node->setLocalZOrder(atoi(value.data()));
        }
        else if (key == "scalex")
        {
            node->setScaleX(utils::atof(value.data()));
        }
        else if (key == "scaley")
        {
            node->setScaleY(atof(value.data()));
        }
        else if (key == "rotation")
        {
            node->setRotation(utils::atof(value.data()));
        }
        else if (key == "name")
        {
            node->setName(value);
        }
    }
}

SceneReader* SceneReader::getInstance()
{
    if (s_sharedReader == nullptr)
    {
        s_sharedReader = new SceneReader();
    }
    return s_sharedReader;
}

void SceneReader::destroyInstance()
{
    DictionaryHelper::destroyInstance();
    TriggerMng::destroyInstance();
    // CocosDenshion::SimpleAudioEngine::end();
    CC_SAFE_DELETE(s_sharedReader);
}

}  // namespace cocostudio
