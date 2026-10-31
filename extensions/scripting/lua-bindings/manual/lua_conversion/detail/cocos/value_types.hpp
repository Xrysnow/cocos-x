#pragma once
#include "../conversion.hpp"
#include "object.hpp"
#include "cocos2d.h"
#include <new>

namespace lua
{
	template<>
	struct to_native<cocos2d::Vec2> {
		static bool F(lua_State* L, int lo, cocos2d::Vec2* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::Vec2 v;
			bool ok = true;
			ok &= luaval_field_to_native(L, lo, "x", &v.x, fName) || luaval_field_to_native(L, lo, "width", &v.x, fName);
			ok &= luaval_field_to_native(L, lo, "y", &v.y, fName) || luaval_field_to_native(L, lo, "height", &v.y, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT2(cocos2d::Vec2, x, y);

	LUA_TO_NATIVE_STRUCT3(cocos2d::Vec3, x, y, z);

	LUA_TO_LUA_STRUCT3(cocos2d::Vec3, x, y, z);

	LUA_TO_NATIVE_STRUCT4(cocos2d::Vec4, x, y, z, w);

	LUA_TO_LUA_STRUCT4(cocos2d::Vec4, x, y, z, w);

	LUA_TO_NATIVE_STRUCT2(cocos2d::BlendFunc, src, dst);

	LUA_TO_LUA_STRUCT2(cocos2d::BlendFunc, src, dst);

	LUA_TO_NATIVE_STRUCT3(cocos2d::Color3B, r, g, b);

	LUA_TO_LUA_STRUCT3(cocos2d::Color3B, r, g, b);

	// Per VM; shared by its coroutines.
	using color4b_userdata_converter = bool (*)(lua_State*, int, cocos2d::Color4B*);

	inline void* _color4b_userdata_converter_key() {
		static char key;
		return &key;
	}

	// A converter returns false for unrecognized userdata. nullptr removes the adapter.
	inline void set_color4b_userdata_converter(lua_State* L, color4b_userdata_converter converter) {
		if (!L) return;
		lua_pushlightuserdata(L, _color4b_userdata_converter_key());
		if (converter)
			new (lua_newuserdata(L, sizeof(converter))) color4b_userdata_converter(converter);
		else
			lua_pushnil(L);
		lua_rawset(L, LUA_REGISTRYINDEX);
	}

	inline color4b_userdata_converter _get_color4b_userdata_converter(lua_State* L) {
		lua_pushlightuserdata(L, _color4b_userdata_converter_key());
		lua_rawget(L, LUA_REGISTRYINDEX);
		const auto converter = lua_type(L, -1) == LUA_TUSERDATA
			&& lua_objlen(L, -1) == sizeof(color4b_userdata_converter)
			? *static_cast<color4b_userdata_converter*>(lua_touserdata(L, -1)) : nullptr;
		lua_pop(L, 1);
		return converter;
	}

	template<>
	struct to_native<cocos2d::Color4B> {
		static bool F(lua_State* L, int lo, cocos2d::Color4B* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (lua_type(L, lo) == LUA_TUSERDATA) {
				const auto converter = _get_color4b_userdata_converter(L);
				if (!converter) return false;
				cocos2d::Color4B value;
				const bool ok = converter(L, lo, &value);
				lua_settop(L, top);
				if (ok) *outValue = value;
				return ok;
			}
			if (!is_indexable(L, lo))
				return false;
			cocos2d::Color4B v;
			bool ok = luaval_field_to_native(L, lo, "r", &v.r, fName) &&
				luaval_field_to_native(L, lo, "g", &v.g, fName) &&
				luaval_field_to_native(L, lo, "b", &v.b, fName) &&
				luaval_field_to_native(L, lo, "a", &v.a, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT4(cocos2d::Color4B, r, g, b, a);

	LUA_TO_NATIVE_STRUCT4(cocos2d::Color4F, r, g, b, a);

	LUA_TO_LUA_STRUCT4(cocos2d::Color4F, r, g, b, a);

	LUA_TO_NATIVE_STRUCT4(cocos2d::Quaternion, x, y, z, w);

	LUA_TO_LUA_STRUCT4(cocos2d::Quaternion, x, y, z, w);

	LUA_TO_NATIVE_STRUCT2(cocos2d::MeshVertexAttrib, type, vertexAttrib);

	LUA_TO_LUA_STRUCT2(cocos2d::MeshVertexAttrib, type, vertexAttrib);

	LUA_TO_NATIVE_STRUCT3(cocos2d::V3F_C4B_T2F, vertices, colors, texCoords);

	LUA_TO_LUA_STRUCT3(cocos2d::V3F_C4B_T2F, vertices, colors, texCoords);

	LUA_TO_NATIVE_STRUCT4(cocos2d::V3F_C4B_T2F_Quad, tl, tr, bl, br);

	LUA_TO_LUA_STRUCT4(cocos2d::V3F_C4B_T2F_Quad, tl, tr, bl, br);

	LUA_TO_NATIVE_STRUCT4(cocos2d::Viewport, x, y, w, h);

	LUA_TO_LUA_STRUCT4(cocos2d::Viewport, x, y, w, h);

	LUA_TO_NATIVE_STRUCT4(cocos2d::backend::AttributeBindInfo, attributeName, location, size, type);

	LUA_TO_LUA_STRUCT4(cocos2d::backend::AttributeBindInfo, attributeName, location, size, type);

	template<>
	struct to_native<cocos2d::Rect> {
		static bool F(lua_State* L, int lo, cocos2d::Rect* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::Rect v;
			bool ok = luaval_field_to_native(L, lo, "x", &v.origin.x, fName) &&
				luaval_field_to_native(L, lo, "y", &v.origin.y, fName) &&
				luaval_field_to_native(L, lo, "width", &v.size.width, fName) &&
				luaval_field_to_native(L, lo, "height", &v.size.height, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	template<>
	struct to_lua<cocos2d::Rect> {
		static void F(lua_State* L, const cocos2d::Rect& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 4);
			native_to_luaval_field(L, -1, "x", inValue.origin.x);
			native_to_luaval_field(L, -1, "y", inValue.origin.y);
			native_to_luaval_field(L, -1, "width", inValue.size.width);
			native_to_luaval_field(L, -1, "height", inValue.size.height);
		}
	};

	template<>
	struct to_native<cocos2d::AffineTransform> {
		static bool F(lua_State* L, int lo, cocos2d::AffineTransform* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			cocos2d::AffineTransform v{};
			bool ok = luaval_field_to_native(L, lo, "a", &v.a, fName) &&
				luaval_field_to_native(L, lo, "b", &v.b, fName) &&
				luaval_field_to_native(L, lo, "c", &v.c, fName) &&
				luaval_field_to_native(L, lo, "d", &v.d, fName) &&
				luaval_field_to_native(L, lo, "tx", &v.tx, fName) &&
				luaval_field_to_native(L, lo, "ty", &v.ty, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT6(cocos2d::AffineTransform, a, b, c, d, tx, ty);

	template<>
	struct to_native<cocos2d::FontDefinition> {
		static bool F(lua_State* L, int lo, cocos2d::FontDefinition* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			cocos2d::FontDefinition v;
			luaval_field_to_native(L, lo, "fontName", &v._fontName, fName);
			luaval_field_to_native(L, lo, "fontSize", &v._fontSize, fName);
			luaval_field_to_native(L, lo, "fontAlignmentH", &v._alignment, fName);
			luaval_field_to_native(L, lo, "fontAlignmentV", &v._vertAlignment, fName);
			luaval_field_to_native(L, lo, "fontFillColor", &v._fontFillColor, fName);
			luaval_field_to_native(L, lo, "fontDimensions", &v._dimensions, fName);
			luaval_field_to_native(L, lo, "shadowEnabled", &v._shadow._shadowEnabled, fName);
			luaval_field_to_native(L, lo, "strokeEnabled", &v._stroke._strokeEnabled, fName);
			if (v._shadow._shadowEnabled)
			{
				luaval_field_to_native(L, lo, "shadowOffset", &v._shadow._shadowOffset, fName);
				luaval_field_to_native(L, lo, "shadowBlur", &v._shadow._shadowBlur, fName);
				luaval_field_to_native(L, lo, "shadowOpacity", &v._shadow._shadowOpacity, fName);
			}
			if (v._stroke._strokeEnabled)
			{
				luaval_field_to_native(L, lo, "strokeColor", &v._stroke._strokeColor, fName);
				luaval_field_to_native(L, lo, "strokeSize", &v._stroke._strokeSize, fName);
			}
			*outValue = v;
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::FontDefinition> {
		static void F(lua_State* L, const cocos2d::FontDefinition& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 13);
			native_to_luaval_field(L, -1, "fontName", inValue._fontName);
			native_to_luaval_field(L, -1, "fontSize", inValue._fontSize);
			native_to_luaval_field(L, -1, "fontAlignmentH", inValue._alignment);
			native_to_luaval_field(L, -1, "fontAlignmentV", inValue._vertAlignment);
			native_to_luaval_field(L, -1, "fontFillColor", inValue._fontFillColor);
			native_to_luaval_field(L, -1, "fontDimensions", inValue._dimensions);
			native_to_luaval_field(L, -1, "shadowEnabled", inValue._shadow._shadowEnabled);
			native_to_luaval_field(L, -1, "shadowOffset", inValue._shadow._shadowOffset);
			native_to_luaval_field(L, -1, "shadowBlur", inValue._shadow._shadowBlur);
			native_to_luaval_field(L, -1, "shadowOpacity", inValue._shadow._shadowOpacity);
			native_to_luaval_field(L, -1, "strokeEnabled", inValue._stroke._strokeEnabled);
			native_to_luaval_field(L, -1, "strokeColor", inValue._stroke._strokeColor);
			native_to_luaval_field(L, -1, "strokeSize", inValue._stroke._strokeSize);
		}
	};

	template<>
	struct to_native<cocos2d::TTFConfig> {
		static bool F(lua_State* L, int lo, cocos2d::TTFConfig* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			cocos2d::TTFConfig v;
			luaval_field_to_native(L, lo, "fontFilePath", &v.fontFilePath, fName);
			luaval_field_to_native(L, lo, "fontSize", &v.fontSize, fName);
			luaval_field_to_native(L, lo, "glyphs", &v.glyphs, fName);
			luaval_field_to_native(L, lo, "customGlyphs", &v.customGlyphs, fName);
			luaval_field_to_native(L, lo, "distanceFieldEnabled", &v.distanceFieldEnabled, fName);
			luaval_field_to_native(L, lo, "outlineSize", &v.outlineSize, fName);
			*outValue = v;
			return true;
		}
	};

	LUA_TO_LUA_STRUCT6(cocos2d::TTFConfig, fontFilePath, fontSize, glyphs, customGlyphs, distanceFieldEnabled, outlineSize);

	template<>
	struct to_native<cocos2d::Mat4> {
		static bool F(lua_State* L, int lo, cocos2d::Mat4* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			if (lua_objlen(L, lo) != 16) return false;
			cocos2d::Mat4 result;
			for (int i = 0; i < 16; ++i)
			{
				if (!luaval_field_to_native(L, lo, i + 1, &result.m[i], fName))
					return false;
			}
			*outValue = result;
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::Mat4> {
		static void F(lua_State* L, const cocos2d::Mat4& inValue) {
			if (!L) return;
			native_array_to_luaval(L, inValue.m, 16);
		}
	};

	template<>
	struct to_native<cocos2d::Texture2D::TexParams> {
		static bool F(lua_State* L, int lo, cocos2d::Texture2D::TexParams* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::Texture2D::TexParams v;
			bool ok = luaval_field_to_native(L, lo, "minFilter", &v.minFilter, fName) &&
				luaval_field_to_native(L, lo, "magFilter", &v.magFilter, fName);
			ok = ok && (luaval_field_to_native(L, lo, "wrapS", &v.sAddressMode, fName) || luaval_field_to_native(L, lo, "sAddressMode", &v.sAddressMode, fName));
			ok = ok && (luaval_field_to_native(L, lo, "wrapT", &v.tAddressMode, fName) || luaval_field_to_native(L, lo, "tAddressMode", &v.tAddressMode, fName));
			if (ok) *outValue = v;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT4(cocos2d::Texture2D::TexParams, minFilter, magFilter, sAddressMode, tAddressMode);

	template<>
	struct to_native<cocos2d::backend::UniformLocation> {
		static bool F(lua_State* L, int lo, cocos2d::backend::UniformLocation* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::backend::UniformLocation v;
			bool ok = luaval_field_to_native(L, lo, "shaderStage", &v.shaderStage, fName);
			if (ok)
			{
				lua_pushliteral(L, "location");
				lua_gettable(L, lo);
				ok = luaval_to_native_array(L, -1, v.location, 2, fName);
				lua_pop(L, 1);
			}
			if (ok) *outValue = v;
			return ok;
		}
	};

	template<>
	struct to_lua<cocos2d::backend::UniformLocation> {
		static void F(lua_State* L, const cocos2d::backend::UniformLocation& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 2);
			native_to_luaval_field(L, -1, "shaderStage", inValue.shaderStage);
			lua_pushstring(L, "location");
			native_array_to_luaval(L, inValue.location, 2);
			lua_settable(L, -3);
		}
	};

	template<>
	struct to_native<cocos2d::backend::BlendDescriptor> {
		static bool F(lua_State* L, int lo, cocos2d::backend::BlendDescriptor* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::backend::BlendDescriptor v;
			luaval_field_to_native(L, lo, "writeMask", &v.writeMask, fName);
			luaval_field_to_native(L, lo, "blendEnabled", &v.blendEnabled, fName);
			luaval_field_to_native(L, lo, "rgbBlendOperation", &v.rgbBlendOperation, fName);
			luaval_field_to_native(L, lo, "alphaBlendOperation", &v.alphaBlendOperation, fName);
			luaval_field_to_native(L, lo, "sourceRGBBlendFactor", &v.sourceRGBBlendFactor, fName);
			luaval_field_to_native(L, lo, "destinationRGBBlendFactor", &v.destinationRGBBlendFactor, fName);
			luaval_field_to_native(L, lo, "sourceAlphaBlendFactor", &v.sourceAlphaBlendFactor, fName);
			luaval_field_to_native(L, lo, "destinationAlphaBlendFactor", &v.destinationAlphaBlendFactor, fName);
			*outValue = v;
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::backend::BlendDescriptor> {
		static void F(lua_State* L, const cocos2d::backend::BlendDescriptor& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 4);
			native_to_luaval_field(L, -1, "writeMask", inValue.writeMask);
			native_to_luaval_field(L, -1, "blendEnabled", inValue.blendEnabled);
			native_to_luaval_field(L, -1, "rgbBlendOperation", inValue.rgbBlendOperation);
			native_to_luaval_field(L, -1, "alphaBlendOperation", inValue.alphaBlendOperation);
			native_to_luaval_field(L, -1, "sourceRGBBlendFactor", inValue.sourceRGBBlendFactor);
			native_to_luaval_field(L, -1, "destinationRGBBlendFactor", inValue.destinationRGBBlendFactor);
			native_to_luaval_field(L, -1, "sourceAlphaBlendFactor", inValue.sourceAlphaBlendFactor);
			native_to_luaval_field(L, -1, "destinationAlphaBlendFactor", inValue.destinationAlphaBlendFactor);
		}
	};
}
