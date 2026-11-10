#pragma once
#include "value_types.hpp"
#include "renderer/backend/Texture.h"
#include "renderer/backend/DepthStencilState.h"

namespace lua
{
	namespace render_detail
	{
		template<typename T>
		bool optional_field(lua_State* L, int lo, const char* key, T* outValue, const char* fName)
		{
			lua_getfield(L, lo, key);
			const bool ok = lua_isnil(L, -1) || luaval_to_native(L, -1, outValue, fName);
			lua_pop(L, 1);
			return ok;
		}
	}

	template<>
	struct to_native<cocos2d::backend::TextureDescriptor> {
		static bool F(lua_State* L, int lo, cocos2d::backend::TextureDescriptor* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::backend::TextureDescriptor value;
			if (!render_detail::optional_field(L, lo, "textureType", &value.textureType, fName) ||
				!render_detail::optional_field(L, lo, "textureFormat", &value.textureFormat, fName) ||
				!render_detail::optional_field(L, lo, "textureUsage", &value.textureUsage, fName) ||
				!render_detail::optional_field(L, lo, "width", &value.width, fName) ||
				!render_detail::optional_field(L, lo, "height", &value.height, fName) ||
				!render_detail::optional_field(L, lo, "depth", &value.depth, fName) ||
				!render_detail::optional_field(L, lo, "samplerDescriptor", &value.samplerDescriptor, fName)) return false;
			*outValue = value;
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::backend::TextureDescriptor> {
		static void F(lua_State* L, const cocos2d::backend::TextureDescriptor& inValue) {
			if (!L) return;
			const auto value = inValue;
			lua_createtable(L, 0, 7);
			native_to_luaval_field(L, -1, "textureType", value.textureType);
			native_to_luaval_field(L, -1, "textureFormat", value.textureFormat);
			native_to_luaval_field(L, -1, "textureUsage", value.textureUsage);
			native_to_luaval_field(L, -1, "width", value.width);
			native_to_luaval_field(L, -1, "height", value.height);
			native_to_luaval_field(L, -1, "depth", value.depth);
			native_to_luaval_field(L, -1, "samplerDescriptor", value.samplerDescriptor);
		}
	};

	template<>
	struct to_native<cocos2d::backend::StencilDescriptor> {
		static bool F(lua_State* L, int lo, cocos2d::backend::StencilDescriptor* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::backend::StencilDescriptor value;
			if (!render_detail::optional_field(L, lo, "stencilFailureOperation", &value.stencilFailureOperation, fName) ||
				!render_detail::optional_field(L, lo, "depthFailureOperation", &value.depthFailureOperation, fName) ||
				!render_detail::optional_field(L, lo, "depthStencilPassOperation", &value.depthStencilPassOperation, fName) ||
				!render_detail::optional_field(L, lo, "stencilCompareFunction", &value.stencilCompareFunction, fName) ||
				!render_detail::optional_field(L, lo, "readMask", &value.readMask, fName) ||
				!render_detail::optional_field(L, lo, "writeMask", &value.writeMask, fName)) return false;
			*outValue = value;
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::backend::StencilDescriptor> {
		static void F(lua_State* L, const cocos2d::backend::StencilDescriptor& inValue) {
			if (!L) return;
			const auto value = inValue;
			lua_createtable(L, 0, 6);
			native_to_luaval_field(L, -1, "stencilFailureOperation", value.stencilFailureOperation);
			native_to_luaval_field(L, -1, "depthFailureOperation", value.depthFailureOperation);
			native_to_luaval_field(L, -1, "depthStencilPassOperation", value.depthStencilPassOperation);
			native_to_luaval_field(L, -1, "stencilCompareFunction", value.stencilCompareFunction);
			native_to_luaval_field(L, -1, "readMask", value.readMask);
			native_to_luaval_field(L, -1, "writeMask", value.writeMask);
		}
	};

	template<>
	struct to_native<cocos2d::backend::DepthStencilDescriptor> {
		static bool F(lua_State* L, int lo, cocos2d::backend::DepthStencilDescriptor* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::backend::DepthStencilDescriptor value;
			if (!render_detail::optional_field(L, lo, "depthCompareFunction", &value.depthCompareFunction, fName) ||
				!render_detail::optional_field(L, lo, "backFaceStencil", &value.backFaceStencil, fName) ||
				!render_detail::optional_field(L, lo, "frontFaceStencil", &value.frontFaceStencil, fName) ||
				!render_detail::optional_field(L, lo, "flags", &value.flags, fName)) return false;
			*outValue = value;
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::backend::DepthStencilDescriptor> {
		static void F(lua_State* L, const cocos2d::backend::DepthStencilDescriptor& inValue) {
			if (!L) return;
			const auto value = inValue;
			lua_createtable(L, 0, 4);
			native_to_luaval_field(L, -1, "depthCompareFunction", value.depthCompareFunction);
			native_to_luaval_field(L, -1, "backFaceStencil", value.backFaceStencil);
			native_to_luaval_field(L, -1, "frontFaceStencil", value.frontFaceStencil);
			native_to_luaval_field(L, -1, "flags", value.flags);
		}
	};
}
