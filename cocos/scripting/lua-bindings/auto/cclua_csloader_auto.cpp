#include "cclua_csloader_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"

int lua_cocos2d_CSLoader_createNodeFromJson(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:createNodeFromJson");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::CSLoader::*)(std::string_view)>(&cocos2d::CSLoader::createNodeFromJson));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_createNodeWithFlatBuffersFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:createNodeWithFlatBuffersFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::CSLoader::*)(std::string_view)>(&cocos2d::CSLoader::createNodeWithFlatBuffersFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_createNodeWithFlatBuffersForSimulator(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:createNodeWithFlatBuffersForSimulator");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::CSLoader::*)(std::string_view)>(&cocos2d::CSLoader::createNodeWithFlatBuffersForSimulator));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_getJsonPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:getJsonPath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::CSLoader::*)()const>(&cocos2d::CSLoader::getJsonPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CSLoader_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:init");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::CSLoader::*)()>(&cocos2d::CSLoader::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CSLoader_isRecordJsonPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:isRecordJsonPath");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::CSLoader::*)()const>(&cocos2d::CSLoader::isRecordJsonPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CSLoader_loadNodeWithContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:loadNodeWithContent");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::CSLoader::*)(std::string_view)>(&cocos2d::CSLoader::loadNodeWithContent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_loadNodeWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:loadNodeWithFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::CSLoader::*)(std::string_view)>(&cocos2d::CSLoader::loadNodeWithFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_setJsonPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:setJsonPath");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CSLoader::*)(std::string)>(&cocos2d::CSLoader::setJsonPath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_setRecordJsonPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:setRecordJsonPath");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CSLoader::*)(bool)>(&cocos2d::CSLoader::setRecordJsonPath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_createNode_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CSLoader", "cc.CSLoader:createNode");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(*)(std::string_view)>(&cocos2d::CSLoader::createNode));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Node*(*)(std::string_view, const cocos2d::ccNodeLoadCallback&)>(&cocos2d::CSLoader::createNode)));
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_CSLoader_createNodeWithVisibleSize_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CSLoader", "cc.CSLoader:createNodeWithVisibleSize");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(*)(std::string_view)>(&cocos2d::CSLoader::createNodeWithVisibleSize));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Node*(*)(std::string_view, const cocos2d::ccNodeLoadCallback&)>(&cocos2d::CSLoader::createNodeWithVisibleSize)));
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_CSLoader_createTimeline_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CSLoader", "cc.CSLoader:createTimeline");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(*)(std::string_view)>(&cocos2d::CSLoader::createTimeline));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_CSLoader_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CSLoader", "cc.CSLoader:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CSLoader*(*)()>(&cocos2d::CSLoader::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_CSLoader_ccCSLoader(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CSLoader, "CSLoader", "cc.CSLoader",
		cocos2d::CSLoader, "",
		nullptr, nullptr);
	LUA_METHOD("createNodeFromJson", lua_cocos2d_CSLoader_createNodeFromJson);
	LUA_METHOD("createNodeWithFlatBuffersFile", lua_cocos2d_CSLoader_createNodeWithFlatBuffersFile);
	LUA_METHOD("createNodeWithFlatBuffersForSimulator", lua_cocos2d_CSLoader_createNodeWithFlatBuffersForSimulator);
	LUA_METHOD("getJsonPath", lua_cocos2d_CSLoader_getJsonPath);
	LUA_METHOD("init", lua_cocos2d_CSLoader_init);
	LUA_METHOD("isRecordJsonPath", lua_cocos2d_CSLoader_isRecordJsonPath);
	LUA_METHOD("loadNodeWithContent", lua_cocos2d_CSLoader_loadNodeWithContent);
	LUA_METHOD("loadNodeWithFile", lua_cocos2d_CSLoader_loadNodeWithFile);
	LUA_METHOD("setJsonPath", lua_cocos2d_CSLoader_setJsonPath);
	LUA_METHOD("setRecordJsonPath", lua_cocos2d_CSLoader_setRecordJsonPath);
	LUA_METHOD("createNode", lua_cocos2d_CSLoader_createNode_1);
	LUA_METHOD("createNodeWithVisibleSize", lua_cocos2d_CSLoader_createNodeWithVisibleSize_1);
	LUA_METHOD("createTimeline", lua_cocos2d_CSLoader_createTimeline_1);
	LUA_METHOD("getInstance", lua_cocos2d_CSLoader_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int register_all_cc_csloader_manual(lua_State* lua_S);

int register_all_cc_csloader(lua_State* lua_S)
{
	tolua_open(lua_S);
	luaReg_CSLoader_ccCSLoader(lua_S);
	return register_all_cc_csloader_manual(lua_S);
}
