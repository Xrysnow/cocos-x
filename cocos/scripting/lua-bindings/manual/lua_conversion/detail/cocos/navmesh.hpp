#pragma once
#include "../record.hpp"
#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#include "navmesh/CCNavMeshAgent.h"

namespace lua
{
    template<> struct to_native<cocos2d::NavMeshAgentParam> {
        static bool F(lua_State* L, int lo, cocos2d::NavMeshAgentParam* outValue, const char* fName = "") {
            LUA_CHECK_TO_NATIVE;
            if (!record_detail::fields(L, lo, {"radius", "height", "maxAcceleration", "maxSpeed",
                "collisionQueryRange", "pathOptimizationRange", "separationWeight", "updateFlags",
                "obstacleAvoidanceType", "queryFilterType"})) return false;
            cocos2d::NavMeshAgentParam value;
            if (!record_detail::number(L, lo, "radius", &value.radius, fName) ||
                !record_detail::number(L, lo, "height", &value.height, fName) ||
                !record_detail::number(L, lo, "maxAcceleration", &value.maxAcceleration, fName) ||
                !record_detail::number(L, lo, "maxSpeed", &value.maxSpeed, fName) ||
                !record_detail::number(L, lo, "collisionQueryRange", &value.collisionQueryRange, fName) ||
                !record_detail::number(L, lo, "pathOptimizationRange", &value.pathOptimizationRange, fName) ||
                !record_detail::number(L, lo, "separationWeight", &value.separationWeight, fName) ||
                !record_detail::number(L, lo, "updateFlags", &value.updateFlags, fName) ||
                !record_detail::number(L, lo, "obstacleAvoidanceType", &value.obstacleAvoidanceType, fName) ||
                !record_detail::number(L, lo, "queryFilterType", &value.queryFilterType, fName)) return false;
            constexpr unsigned flags = DT_CROWD_ANTICIPATE_TURNS | DT_CROWD_OBSTACLE_AVOIDANCE |
                DT_CROWD_SEPARATION | DT_CROWD_OPTIMIZE_VIS | DT_CROWD_OPTIMIZE_TOPO;
            if (value.radius < 0 || value.height <= 0 || value.maxAcceleration < 0 || value.maxSpeed < 0 ||
                value.collisionQueryRange <= 0 || value.pathOptimizationRange <= 0 || value.separationWeight < 0 ||
                (value.updateFlags & ~flags) != 0 || value.obstacleAvoidanceType >= DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS ||
                value.queryFilterType >= DT_CROWD_MAX_QUERY_FILTER_TYPE) return false;
            *outValue = value;
            return true;
        }
    };

    template<> struct to_lua<cocos2d::OffMeshLinkData> {
        static void F(lua_State* L, const cocos2d::OffMeshLinkData& inValue) {
            if (!L) return;
            const auto value = inValue;
            lua_createtable(L, 0, 2);
            native_to_luaval_field(L, -1, "startPosition", value.startPosition);
            native_to_luaval_field(L, -1, "endPosition", value.endPosition);
        }
    };
}
#endif
