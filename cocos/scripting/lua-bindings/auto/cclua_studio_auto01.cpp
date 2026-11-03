#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_BaseData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BaseData", "ccs.BaseData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BaseData*(*)()>(&cocostudio::BaseData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBaseData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::BaseData, "BaseData", "ccs.BaseData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_BaseData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_DisplayData_copy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayData", "ccs.DisplayData:copy");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayData::*)(cocostudio::DisplayData*)>(&cocostudio::DisplayData::copy));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.DisplayData", "ccs.DisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayData*(*)()>(&cocostudio::DisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::DisplayData, "DisplayData", "ccs.DisplayData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("copy", lua_cocostudio_DisplayData_copy);
	LUA_METHOD("create", lua_cocostudio_DisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_SpriteDisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.SpriteDisplayData", "ccs.SpriteDisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::SpriteDisplayData*(*)()>(&cocostudio::SpriteDisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsSpriteDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::SpriteDisplayData, "SpriteDisplayData", "ccs.SpriteDisplayData",
		cocostudio::DisplayData, "ccs.DisplayData",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_SpriteDisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureDisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureDisplayData", "ccs.ArmatureDisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureDisplayData*(*)()>(&cocostudio::ArmatureDisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmatureDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureDisplayData, "ArmatureDisplayData", "ccs.ArmatureDisplayData",
		cocostudio::DisplayData, "ccs.DisplayData",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ArmatureDisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ParticleDisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ParticleDisplayData", "ccs.ParticleDisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ParticleDisplayData*(*)()>(&cocostudio::ParticleDisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsParticleDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ParticleDisplayData, "ParticleDisplayData", "ccs.ParticleDisplayData",
		cocostudio::DisplayData, "ccs.DisplayData",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ParticleDisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_BoneData_addDisplayData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneData", "ccs.BoneData:addDisplayData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::BoneData::*)(cocostudio::DisplayData*)>(&cocostudio::BoneData::addDisplayData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_BoneData_getDisplayData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneData", "ccs.BoneData:getDisplayData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::DisplayData*(cocostudio::BoneData::*)(int)>(&cocostudio::BoneData::getDisplayData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_BoneData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneData", "ccs.BoneData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::BoneData::*)()>(&cocostudio::BoneData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_BoneData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BoneData", "ccs.BoneData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BoneData*(*)()>(&cocostudio::BoneData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBoneData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::BoneData, "BoneData", "ccs.BoneData",
		cocostudio::BaseData, "ccs.BaseData",
		nullptr, nullptr);
	LUA_METHOD("addDisplayData", lua_cocostudio_BoneData_addDisplayData);
	LUA_METHOD("getDisplayData", lua_cocostudio_BoneData_getDisplayData);
	LUA_METHOD("init", lua_cocostudio_BoneData_init);
	LUA_METHOD("create", lua_cocostudio_BoneData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureData_addBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:addBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureData::*)(cocostudio::BoneData*)>(&cocostudio::ArmatureData::addBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ArmatureData::*)()>(&cocostudio::ArmatureData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureData*(*)()>(&cocostudio::ArmatureData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmatureData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureData, "ArmatureData", "ccs.ArmatureData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addBoneData", lua_cocostudio_ArmatureData_addBoneData);
	LUA_METHOD("init", lua_cocostudio_ArmatureData_init);
	LUA_METHOD("create", lua_cocostudio_ArmatureData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_FrameData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.FrameData", "ccs.FrameData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::FrameData*(*)()>(&cocostudio::FrameData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsFrameData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::FrameData, "FrameData", "ccs.FrameData",
		cocostudio::BaseData, "ccs.BaseData",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_FrameData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
