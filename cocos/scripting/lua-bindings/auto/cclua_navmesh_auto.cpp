#include "cclua_navmesh_auto.hpp"
#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#include "lua_conversion/lua_conversion.hpp"
#include "navmesh/CCNavMesh.h"

int lua_cc_NavMeshAgent_completeOffMeshLink(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:completeOffMeshLink");
	LUA_TRY_INVOKE(0, &cc::NavMeshAgent::completeOffMeshLink);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getCurrentOffMeshLinkData_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getCurrentOffMeshLinkData");
	LUA_TRY_INVOKE_R(0, static_cast<cc::OffMeshLinkData(cc::NavMeshAgent::*)()>(&cc::NavMeshAgent::getCurrentOffMeshLinkData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getCurrentVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getCurrentVelocity");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getCurrentVelocity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getHeight");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getMaxAcceleration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getMaxAcceleration");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getMaxAcceleration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getMaxSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getMaxSpeed");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getMaxSpeed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getObstacleAvoidanceType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getObstacleAvoidanceType");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getObstacleAvoidanceType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getRadius");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getSeparationWeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getSeparationWeight");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getSeparationWeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getSyncFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getSyncFlag");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getSyncFlag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_getVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getVelocity");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getVelocity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_isOnOffMeshLink(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:isOnOffMeshLink");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::isOnOffMeshLink);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_move(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:move");
	LUA_TRY_INVOKE(2, &cc::NavMeshAgent::move);
	LUA_TRY_INVOKE(1, ([](cc::NavMeshAgent* obj,const cc::Vec3& arg0){{return obj->move(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_NavMeshAgent_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:pause");
	LUA_TRY_INVOKE(0, &cc::NavMeshAgent::pause);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:resume");
	LUA_TRY_INVOKE(0, &cc::NavMeshAgent::resume);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_setAutoOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setAutoOrientation");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setAutoOrientation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setAutoTraverseOffMeshLink(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setAutoTraverseOffMeshLink");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setAutoTraverseOffMeshLink);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setHeight");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setHeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setMaxAcceleration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setMaxAcceleration");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setMaxAcceleration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setMaxSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setMaxSpeed");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setMaxSpeed);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setObstacleAvoidanceType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setObstacleAvoidanceType");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setObstacleAvoidanceType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setOrientationRefAxes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setOrientationRefAxes");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setOrientationRefAxes);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setRadius");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setRadius);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setSeparationWeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setSeparationWeight");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setSeparationWeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_setSyncFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:setSyncFlag");
	LUA_TRY_INVOKE(1, &cc::NavMeshAgent::setSyncFlag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:stop");
	LUA_TRY_INVOKE(0, &cc::NavMeshAgent::stop);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_syncToAgent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:syncToAgent");
	LUA_TRY_INVOKE(0, &cc::NavMeshAgent::syncToAgent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_syncToNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:syncToNode");
	LUA_TRY_INVOKE(0, &cc::NavMeshAgent::syncToNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshAgent_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:create");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::NavMeshAgent>(*)(const cc::NavMeshAgentParam&)>(&cc::NavMeshAgent::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_NavMeshAgent_getNavMeshAgentComponentName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NavMeshAgent", "cc.NavMeshAgent:getNavMeshAgentComponentName");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshAgent::getNavMeshAgentComponentName);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_NavMesh_ccNavMeshAgent(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::NavMeshAgent, "NavMeshAgent", "cc.NavMeshAgent",
		cc::Component, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("completeOffMeshLink", lua_cc_NavMeshAgent_completeOffMeshLink);
	LUA_METHOD("getCurrentOffMeshLinkData", lua_cc_NavMeshAgent_getCurrentOffMeshLinkData_1);
	LUA_METHOD("getCurrentVelocity", lua_cc_NavMeshAgent_getCurrentVelocity);
	LUA_METHOD("getHeight", lua_cc_NavMeshAgent_getHeight);
	LUA_METHOD("getMaxAcceleration", lua_cc_NavMeshAgent_getMaxAcceleration);
	LUA_METHOD("getMaxSpeed", lua_cc_NavMeshAgent_getMaxSpeed);
	LUA_METHOD("getObstacleAvoidanceType", lua_cc_NavMeshAgent_getObstacleAvoidanceType);
	LUA_METHOD("getRadius", lua_cc_NavMeshAgent_getRadius);
	LUA_METHOD("getSeparationWeight", lua_cc_NavMeshAgent_getSeparationWeight);
	LUA_METHOD("getSyncFlag", lua_cc_NavMeshAgent_getSyncFlag);
	LUA_METHOD("getVelocity", lua_cc_NavMeshAgent_getVelocity);
	LUA_METHOD("isOnOffMeshLink", lua_cc_NavMeshAgent_isOnOffMeshLink);
	LUA_METHOD("move", lua_cc_NavMeshAgent_move);
	LUA_METHOD("pause", lua_cc_NavMeshAgent_pause);
	LUA_METHOD("resume", lua_cc_NavMeshAgent_resume);
	LUA_METHOD("setAutoOrientation", lua_cc_NavMeshAgent_setAutoOrientation);
	LUA_METHOD("setAutoTraverseOffMeshLink", lua_cc_NavMeshAgent_setAutoTraverseOffMeshLink);
	LUA_METHOD("setHeight", lua_cc_NavMeshAgent_setHeight);
	LUA_METHOD("setMaxAcceleration", lua_cc_NavMeshAgent_setMaxAcceleration);
	LUA_METHOD("setMaxSpeed", lua_cc_NavMeshAgent_setMaxSpeed);
	LUA_METHOD("setObstacleAvoidanceType", lua_cc_NavMeshAgent_setObstacleAvoidanceType);
	LUA_METHOD("setOrientationRefAxes", lua_cc_NavMeshAgent_setOrientationRefAxes);
	LUA_METHOD("setRadius", lua_cc_NavMeshAgent_setRadius);
	LUA_METHOD("setSeparationWeight", lua_cc_NavMeshAgent_setSeparationWeight);
	LUA_METHOD("setSyncFlag", lua_cc_NavMeshAgent_setSyncFlag);
	LUA_METHOD("stop", lua_cc_NavMeshAgent_stop);
	LUA_METHOD("syncToAgent", lua_cc_NavMeshAgent_syncToAgent);
	LUA_METHOD("syncToNode", lua_cc_NavMeshAgent_syncToNode);
	LUA_METHOD("create", lua_cc_NavMeshAgent_create_1);
	LUA_METHOD("getNavMeshAgentComponentName", lua_cc_NavMeshAgent_getNavMeshAgentComponentName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_NavMeshObstacle_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:getHeight");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshObstacle::getHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshObstacle_getRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:getRadius");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshObstacle::getRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshObstacle_getSyncFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:getSyncFlag");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshObstacle::getSyncFlag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshObstacle_initWith(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:initWith");
	LUA_TRY_INVOKE_R(2, &cc::NavMeshObstacle::initWith);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_NavMeshObstacle_setSyncFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:setSyncFlag");
	LUA_TRY_INVOKE(1, &cc::NavMeshObstacle::setSyncFlag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMeshObstacle_syncToNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:syncToNode");
	LUA_TRY_INVOKE(0, &cc::NavMeshObstacle::syncToNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshObstacle_syncToObstacle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:syncToObstacle");
	LUA_TRY_INVOKE(0, &cc::NavMeshObstacle::syncToObstacle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMeshObstacle_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:create");
	LUA_TRY_INVOKE_R(2, &cc::NavMeshObstacle::create);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cc_NavMeshObstacle_getNavMeshObstacleComponentName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NavMeshObstacle", "cc.NavMeshObstacle:getNavMeshObstacleComponentName");
	LUA_TRY_INVOKE_R(0, &cc::NavMeshObstacle::getNavMeshObstacleComponentName);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_NavMesh_ccNavMeshObstacle(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::NavMeshObstacle, "NavMeshObstacle", "cc.NavMeshObstacle",
		cc::Component, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("getHeight", lua_cc_NavMeshObstacle_getHeight);
	LUA_METHOD("getRadius", lua_cc_NavMeshObstacle_getRadius);
	LUA_METHOD("getSyncFlag", lua_cc_NavMeshObstacle_getSyncFlag);
	LUA_METHOD("initWith", lua_cc_NavMeshObstacle_initWith);
	LUA_METHOD("setSyncFlag", lua_cc_NavMeshObstacle_setSyncFlag);
	LUA_METHOD("syncToNode", lua_cc_NavMeshObstacle_syncToNode);
	LUA_METHOD("syncToObstacle", lua_cc_NavMeshObstacle_syncToObstacle);
	LUA_METHOD("create", lua_cc_NavMeshObstacle_create);
	LUA_METHOD("getNavMeshObstacleComponentName", lua_cc_NavMeshObstacle_getNavMeshObstacleComponentName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_NavMesh_addNavMeshAgent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:addNavMeshAgent");
	LUA_TRY_INVOKE(1, &cc::NavMesh::addNavMeshAgent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_addNavMeshObstacle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:addNavMeshObstacle");
	LUA_TRY_INVOKE(1, &cc::NavMesh::addNavMeshObstacle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_debugDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:debugDraw");
	LUA_TRY_INVOKE(1, &cc::NavMesh::debugDraw);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_isDebugDrawEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:isDebugDrawEnabled");
	LUA_TRY_INVOKE_R(0, &cc::NavMesh::isDebugDrawEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NavMesh_removeNavMeshAgent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:removeNavMeshAgent");
	LUA_TRY_INVOKE(1, &cc::NavMesh::removeNavMeshAgent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_removeNavMeshObstacle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:removeNavMeshObstacle");
	LUA_TRY_INVOKE(1, &cc::NavMesh::removeNavMeshObstacle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_setDebugDrawEnable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:setDebugDrawEnable");
	LUA_TRY_INVOKE(1, &cc::NavMesh::setDebugDrawEnable);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NavMesh", "cc.NavMesh:update");
	LUA_TRY_INVOKE(1, &cc::NavMesh::update);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NavMesh_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NavMesh", "cc.NavMesh:create");
	LUA_TRY_INVOKE_R(2, &cc::NavMesh::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_NavMesh_ccNavMesh(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::NavMesh, "NavMesh", "cc.NavMesh",
		cc::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addNavMeshAgent", lua_cc_NavMesh_addNavMeshAgent);
	LUA_METHOD("addNavMeshObstacle", lua_cc_NavMesh_addNavMeshObstacle);
	LUA_METHOD("debugDraw", lua_cc_NavMesh_debugDraw);
	LUA_METHOD("isDebugDrawEnabled", lua_cc_NavMesh_isDebugDrawEnabled);
	LUA_METHOD("removeNavMeshAgent", lua_cc_NavMesh_removeNavMeshAgent);
	LUA_METHOD("removeNavMeshObstacle", lua_cc_NavMesh_removeNavMeshObstacle);
	LUA_METHOD("setDebugDrawEnable", lua_cc_NavMesh_setDebugDrawEnable);
	LUA_METHOD("update", lua_cc_NavMesh_update);
	LUA_METHOD("create", lua_cc_NavMesh_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int register_all_cc_navmesh(lua_State* lua_S)
{
#include "base/ccConfig.h"
#if CC_USE_NAVMESH
	luaReg_NavMesh_ccNavMeshAgent(lua_S);
	luaReg_NavMesh_ccNavMeshObstacle(lua_S);
	luaReg_NavMesh_ccNavMesh(lua_S);
	return 0;
#else
	return 0;
#endif
}
