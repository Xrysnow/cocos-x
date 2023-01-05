

#include "WidgetReader/TextAtlasReader/TextAtlasReader.h"

#include "ui/UITextAtlas.h"
#include "platform/CCFileUtils.h"

#include "CocoLoader.h"
#include "CSParseBinary_generated.h"
#include "FlatBuffersSerialize.h"

#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
static const char* P_StringValue     = "stringValue";
static const char* P_CharMapFileData = "charMapFileData";
static const char* P_ItemWidth       = "itemWidth";
static const char* P_ItemHeight      = "itemHeight";
static const char* P_StartCharMap    = "startCharMap";

static TextAtlasReader* instanceTextAtlasReader = nullptr;

IMPLEMENT_CLASS_NODE_READER_INFO(TextAtlasReader)

TextAtlasReader::TextAtlasReader() {}

TextAtlasReader::~TextAtlasReader() {}

TextAtlasReader* TextAtlasReader::getInstance()
{
    if (!instanceTextAtlasReader)
    {
        instanceTextAtlasReader = new TextAtlasReader();
    }
    return instanceTextAtlasReader;
}

void TextAtlasReader::destroyInstance()
{
    CC_SAFE_DELETE(instanceTextAtlasReader);
}

void TextAtlasReader::setPropsFromBinary(cocos2d::ui::Widget* widget, CocoLoader* cocoLoader, stExpCocoNode* cocoNode)
{
    this->beginSetBasicProperties(widget);

    TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);

    stExpCocoNode* stChildArray = cocoNode->GetChildArray(cocoLoader);
    // Widget::TextureResType type;
    // std::string charMapFileName;
    std::string stringValue;
    std::string startCharMap;
    float itemWidth;
    float itemHeight;

    int resourceType = 0;
    std::string charMapFile;
    for (int i = 0; i < cocoNode->GetChildNum(); ++i)
    {
        std::string key   = stChildArray[i].GetName(cocoLoader);
        std::string value = stChildArray[i].GetValue(cocoLoader);

        // read all basic properties of widget
        CC_BASIC_PROPERTY_BINARY_READER
        // read all color related properties of widget
        CC_COLOR_PROPERTY_BINARY_READER

        else if (key == P_StringValue) { stringValue = value; }
        else if (key == P_CharMapFileData)
        {
            stExpCocoNode* backGroundChildren = stChildArray[i].GetChildArray(cocoLoader);
            std::string resType               = backGroundChildren[2].GetValue(cocoLoader);

            Widget::TextureResType imageFileNameType = (Widget::TextureResType)valueToInt(resType);

            charMapFile = this->getResourcePath(cocoLoader, &stChildArray[i], imageFileNameType);
        }
        else if (key == P_ItemWidth) { itemWidth = valueToFloat(value); }
        else if (key == P_ItemHeight) { itemHeight = valueToFloat(value); }
        else if (key == P_StartCharMap) { startCharMap = value; }
    }  // end of for loop

    if (resourceType == 0)
    {
        labelAtlas->setProperty(stringValue, charMapFile, itemWidth, itemHeight, startCharMap);
    }
    this->endSetBasicProperties(widget);
}

void TextAtlasReader::setPropsFromJsonDictionary(Widget* widget, const rapidjson::Value& options)
{
    WidgetReader::setPropsFromJsonDictionary(widget, options);

    std::string_view jsonPath = GUIReader::getInstance()->getFilePath();

    TextAtlas* labelAtlas = static_cast<TextAtlas*>(widget);
    //        bool sv = DICTOOL->checkObjectExist_json(options, P_StringValue);
    //        bool cmf = DICTOOL->checkObjectExist_json(options, P_CharMapFile);
    //        bool iw = DICTOOL->checkObjectExist_json(options, P_ItemWidth);
    //        bool ih = DICTOOL->checkObjectExist_json(options, P_ItemHeight);
    //        bool scm = DICTOOL->checkObjectExist_json(options, P_StartCharMap);

    const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, P_CharMapFileData);
    int cmfType                     = DICTOOL->getIntValue_json(cmftDic, P_ResourceType);
    switch (cmfType)
    {
    case 0:
    {
        std::string tp_c{jsonPath};
        const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, P_Path);
        const char* cmf_tp  = tp_c.append(cmfPath).c_str();
        labelAtlas->setProperty(DICTOOL->getStringValue_json(options, P_StringValue, "12345678"), cmf_tp,
                                DICTOOL->getIntValue_json(options, P_ItemWidth, 24),
                                DICTOOL->getIntValue_json(options, P_ItemHeight, 32),
                                DICTOOL->getStringValue_json(options, P_StartCharMap));
        break;
    }
    case 1:
        CCLOG("Wrong res type of LabelAtlas!");
        break;
    default:
        break;
    }

    WidgetReader::setColorPropsFromJsonDictionary(widget, options);
}

Offset<Table> TextAtlasReader::createOptionsWithFlatBuffers(pugi::xml_node objectData,
                                                            flatbuffers::FlatBufferBuilder* builder)
{
    auto temp          = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
    auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);

    std::string path;
    std::string plistFile;
    int resourceType = 0;

    std::string stringValue = "0123456789";
    int itemWidth           = 0;
    int itemHeight          = 0;
    std::string startCharMap;

    // attributes
    auto attribute = objectData.first_attribute();
    while (attribute)
    {
        std::string_view name  = attribute.name();
        std::string_view value = attribute.value();

        if (name == "LabelText")
        {
            stringValue = value;
        }
        else if (name == "CharWidth")
        {
            itemWidth = atoi(value.data());
        }
        else if (name == "CharHeight")
        {
            itemHeight = atoi(value.data());
        }
        else if (name == "StartChar")
        {
            startCharMap = value;
        }

        attribute = attribute.next_attribute();
    }

    // child elements
    auto child = objectData.first_child();
    while (child)
    {
        std::string_view name = child.name();

        if (name == "LabelAtlasFileImage_CNB")
        {
            std::string texture;
            std::string texturePng;

            attribute = child.first_attribute();

            while (attribute)
            {
                name              = attribute.name();
                std::string_view value = attribute.value();

                if (name == "Path")
                {
                    path = value;
                }
                else if (name == "Type")
                {
                    resourceType = 0;
                }
                else if (name == "Plist")
                {
                    plistFile = value;
                    texture   = value;
                }

                attribute = attribute.next_attribute();
            }
        }

        child = child.next_sibling();
    }

    auto options = CreateTextAtlasOptions(
        *builder, widgetOptions,
        CreateResourceData(*builder, builder->CreateString(path), builder->CreateString(plistFile), resourceType),
        builder->CreateString(stringValue), builder->CreateString(startCharMap), itemWidth, itemHeight);

    return *(Offset<Table>*)(&options);
}

void TextAtlasReader::setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* textAtlasOptions)
{
    TextAtlas* labelAtlas = static_cast<TextAtlas*>(node);
    auto options          = (TextAtlasOptions*)textAtlasOptions;

    auto cmftDic = (options->charMapFileData());
    int cmfType  = cmftDic->resourceType();
    switch (cmfType)
    {
    case 0:
    {
        std::string cmfPath = cmftDic->path()->c_str();

        bool fileExist = false;
        std::string errorFilePath;

        if (FileUtils::getInstance()->isFileExist(cmfPath))
        {
            fileExist = true;

            std::string stringValue = options->stringValue()->c_str();
            int itemWidth           = options->itemWidth();
            int itemHeight          = options->itemHeight();
            labelAtlas->setProperty(stringValue, cmfPath, itemWidth, itemHeight, options->startCharMap()->c_str());
        }
        else
        {
            errorFilePath = cmfPath;
            fileExist     = false;
        }
        break;
    }

    case 1:
        CCLOG("Wrong res type of LabelAtlas!");
        break;

    default:
        break;
    }

    auto widgetReader = WidgetReader::getInstance();
    widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());

    labelAtlas->ignoreContentAdaptWithSize(true);
}

Node* TextAtlasReader::createNodeWithFlatBuffers(const flatbuffers::Table* textAtlasOptions)
{
    TextAtlas* textAtlas = TextAtlas::create();

    setPropsWithFlatBuffers(textAtlas, (Table*)textAtlasOptions);

    return textAtlas;
}

}  // namespace cocostudio
