#pragma once
#include "../conversion.hpp"
#include "../record.hpp"
#include "object.hpp"
#include "../value_userdata.hpp"
#include "renderer/backend/VertexLayout.h"
#include "cocos2d.h"
#include <new>

namespace lua
{
	template<> struct value_type<cc::backend::VertexLayout> : std::true_type {};
	template<> struct value_type<cc::GlyphTicket> : std::true_type {};
	template<>
	struct to_native<cc::Vec2> {
		static bool F(lua_State* L, int lo, cc::Vec2* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::Vec2 v;
			bool ok = true;
			ok &= luaval_field_to_native(L, lo, "x", &v.x, fName) || luaval_field_to_native(L, lo, "width", &v.x, fName);
			ok &= luaval_field_to_native(L, lo, "y", &v.y, fName) || luaval_field_to_native(L, lo, "height", &v.y, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT2(cc::Vec2, x, y);

	LUA_TO_NATIVE_STRUCT3(cc::Vec3, x, y, z);

	LUA_TO_LUA_STRUCT3(cc::Vec3, x, y, z);

	LUA_TO_NATIVE_STRUCT4(cc::Vec4, x, y, z, w);

	LUA_TO_LUA_STRUCT4(cc::Vec4, x, y, z, w);

	LUA_TO_NATIVE_STRUCT2(cc::BlendFunc, src, dst);

	LUA_TO_LUA_STRUCT2(cc::BlendFunc, src, dst);

	LUA_TO_NATIVE_STRUCT3(cc::Color3B, r, g, b);

	LUA_TO_LUA_STRUCT3(cc::Color3B, r, g, b);

	// Per VM; shared by its coroutines.
	using color4b_userdata_converter = bool (*)(lua_State*, int, cc::Color4B*);

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
	struct to_native<cc::Color4B> {
		static bool F(lua_State* L, int lo, cc::Color4B* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (lua_type(L, lo) == LUA_TUSERDATA) {
				const auto converter = _get_color4b_userdata_converter(L);
				if (!converter) return false;
				cc::Color4B value;
				const bool ok = converter(L, lo, &value);
				lua_settop(L, top);
				if (ok) *outValue = value;
				return ok;
			}
			if (!is_indexable(L, lo))
				return false;
			cc::Color4B v;
			bool ok = luaval_field_to_native(L, lo, "r", &v.r, fName) &&
				luaval_field_to_native(L, lo, "g", &v.g, fName) &&
				luaval_field_to_native(L, lo, "b", &v.b, fName) &&
				luaval_field_to_native(L, lo, "a", &v.a, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT4(cc::Color4B, r, g, b, a);

	LUA_TO_NATIVE_STRUCT4(cc::Color4F, r, g, b, a);

	LUA_TO_LUA_STRUCT4(cc::Color4F, r, g, b, a);

	LUA_TO_NATIVE_STRUCT4(cc::HSV, h, s, v, a);

	LUA_TO_LUA_STRUCT4(cc::HSV, h, s, v, a);

	template<>
	struct to_native<cc::ccBezierConfig> {
		static bool F(lua_State* L, int lo, cc::ccBezierConfig* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::ccBezierConfig value{};
			bool ok;
			// Match BezierBy/BezierTo::create's {control1, control2, end} convention.
			if (lua_istable(L, lo) && lua_objlen(L, lo) == 3)
				ok = luaval_field_to_native(L, lo, 1, &value.controlPoint_1, fName) &&
					luaval_field_to_native(L, lo, 2, &value.controlPoint_2, fName) &&
					luaval_field_to_native(L, lo, 3, &value.endPosition, fName);
			else
				ok = luaval_field_to_native(L, lo, "controlPoint_1", &value.controlPoint_1, fName) &&
					luaval_field_to_native(L, lo, "controlPoint_2", &value.controlPoint_2, fName) &&
					luaval_field_to_native(L, lo, "endPosition", &value.endPosition, fName);
			if (ok) *outValue = value;
			return ok;
		}
	};

	LUA_TO_LUA_STRUCT3(cc::ccBezierConfig, controlPoint_1, controlPoint_2, endPosition);

	LUA_TO_NATIVE_STRUCT4(cc::Quaternion, x, y, z, w);

	LUA_TO_LUA_STRUCT4(cc::Quaternion, x, y, z, w);

	LUA_TO_NATIVE_STRUCT2(cc::MeshVertexAttrib, type, vertexAttrib);

	LUA_TO_LUA_STRUCT2(cc::MeshVertexAttrib, type, vertexAttrib);

	LUA_TO_NATIVE_STRUCT3(cc::V3F_C4B_T2F, vertices, colors, texCoords);

	LUA_TO_LUA_STRUCT3(cc::V3F_C4B_T2F, vertices, colors, texCoords);

	LUA_TO_NATIVE_STRUCT4(cc::V3F_C4B_T2F_Quad, tl, tr, bl, br);

	LUA_TO_LUA_STRUCT4(cc::V3F_C4B_T2F_Quad, tl, tr, bl, br);

	LUA_TO_NATIVE_STRUCT4(cc::Viewport, x, y, w, h);

	LUA_TO_LUA_STRUCT4(cc::Viewport, x, y, w, h);

	LUA_TO_NATIVE_STRUCT4(cc::ScissorRect, x, y, width, height);

	LUA_TO_LUA_STRUCT4(cc::ScissorRect, x, y, width, height);

	LUA_TO_NATIVE_STRUCT4(cc::backend::AttributeBindInfo, attributeName, location, size, type);

	LUA_TO_LUA_STRUCT4(cc::backend::AttributeBindInfo, attributeName, location, size, type);

	template<>
	struct to_native<cc::Rect> {
		static bool F(lua_State* L, int lo, cc::Rect* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::Rect v;
			bool ok = luaval_field_to_native(L, lo, "x", &v.origin.x, fName) &&
				luaval_field_to_native(L, lo, "y", &v.origin.y, fName) &&
				luaval_field_to_native(L, lo, "width", &v.size.width, fName) &&
				luaval_field_to_native(L, lo, "height", &v.size.height, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	template<>
	struct to_lua<cc::Rect> {
		static void F(lua_State* L, const cc::Rect& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 4);
			native_to_luaval_field(L, -1, "x", inValue.origin.x);
			native_to_luaval_field(L, -1, "y", inValue.origin.y);
			native_to_luaval_field(L, -1, "width", inValue.size.width);
			native_to_luaval_field(L, -1, "height", inValue.size.height);
		}
	};

	template<>
	struct to_native<cc::AffineTransform> {
		static bool F(lua_State* L, int lo, cc::AffineTransform* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			cc::AffineTransform v{};
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

	LUA_TO_LUA_STRUCT6(cc::AffineTransform, a, b, c, d, tx, ty);

	template<>
	struct to_native<cc::FontDefinition> {
		static bool F(lua_State* L, int lo, cc::FontDefinition* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			cc::FontDefinition v;
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
	struct to_lua<cc::FontDefinition> {
		static void F(lua_State* L, const cc::FontDefinition& inValue) {
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
	struct to_native<cc::TTFConfig> {
		static bool F(lua_State* L, int lo, cc::TTFConfig* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			cc::TTFConfig v;
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

	LUA_TO_LUA_STRUCT6(cc::TTFConfig, fontFilePath, fontSize, glyphs, customGlyphs, distanceFieldEnabled, outlineSize);

	template<>
	struct to_native<cc::FontConfig> {
		static bool F(lua_State* L, int lo, cc::FontConfig* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			if (lo < 0 && lo > LUA_REGISTRYINDEX) lo += lua_gettop(L) + 1;
			cc::FontConfig value;
			if (!luaval_field_to_native(L, lo, "name", &value.name, fName)) return false;
			lua_pushliteral(L, "size");
			lua_rawget(L, lo);
			const bool validSize = lua_isnil(L, -1) || luaval_to_native(L, -1, &value.size, fName);
			lua_pop(L, 1);
			if (!validSize) return false;
			*outValue = std::move(value);
			return true;
		}
	};
	LUA_TO_LUA_STRUCT(cc::FontMetrics, ascent, descent, lineHeight);
	LUA_TO_LUA_STRUCT(cc::GlyphProgress, status, total, ready, failed);
	LUA_TO_LUA_STRUCT(cc::FontCacheStats, livePages, retiringPages, queuedGlyphs, runningGlyphs,
		textureBytes, stagingBytes, cacheHits, deduplicatedRequests, evictions, capacityMisses);

	template<>
	struct to_native<cc::Mat4> {
		static bool F(lua_State* L, int lo, cc::Mat4* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			if (lua_objlen(L, lo) != 16) return false;
			cc::Mat4 result;
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
	struct to_lua<cc::Mat4> {
		static void F(lua_State* L, const cc::Mat4& inValue) {
			if (!L) return;
			native_array_to_luaval(L, inValue.m, 16);
		}
	};

	template<>
	struct to_native<cc::backend::SamplerDescriptor> {
		static bool F(lua_State* L, int lo, cc::backend::SamplerDescriptor* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!record_detail::fields(L, lo, {"minFilter", "magFilter", "sAddressMode", "tAddressMode"})) return false;
			using Filter = cc::backend::SamplerFilter;
			using Address = cc::backend::SamplerAddressMode;
			const std::initializer_list<Filter> filters = {Filter::NEAREST, Filter::NEAREST_MIPMAP_NEAREST,
				Filter::NEAREST_MIPMAP_LINEAR, Filter::LINEAR, Filter::LINEAR_MIPMAP_LINEAR,
				Filter::LINEAR_MIPMAP_NEAREST, Filter::DONT_CARE};
			const std::initializer_list<Address> addresses = {Address::REPEAT, Address::MIRROR_REPEAT,
				Address::CLAMP_TO_EDGE, Address::DONT_CARE};
			cc::backend::SamplerDescriptor value;
			if (!record_detail::enumeration(L, lo, "minFilter", &value.minFilter, filters, fName) ||
				!record_detail::enumeration(L, lo, "magFilter", &value.magFilter, filters, fName) ||
				!record_detail::enumeration(L, lo, "sAddressMode", &value.sAddressMode, addresses, fName) ||
				!record_detail::enumeration(L, lo, "tAddressMode", &value.tAddressMode, addresses, fName)) return false;
			*outValue = value;
			return true;
		}
	};

	// Texture2D::TexParams is the same native type and uses the same canonical record.
	LUA_TO_LUA_STRUCT4(cc::backend::SamplerDescriptor, minFilter, magFilter, sAddressMode, tAddressMode);

	template<>
	struct to_native<cc::backend::UniformLocation> {
		static bool F(lua_State* L, int lo, cc::backend::UniformLocation* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::backend::UniformLocation v;
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
	struct to_lua<cc::backend::UniformLocation> {
		static void F(lua_State* L, const cc::backend::UniformLocation& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 2);
			native_to_luaval_field(L, -1, "shaderStage", inValue.shaderStage);
			lua_pushstring(L, "location");
			native_array_to_luaval(L, inValue.location, 2);
			lua_settable(L, -3);
		}
	};

	template<>
	struct to_native<cc::backend::BlendDescriptor> {
		static bool F(lua_State* L, int lo, cc::backend::BlendDescriptor* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::backend::BlendDescriptor v;
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
	struct to_lua<cc::backend::BlendDescriptor> {
		static void F(lua_State* L, const cc::backend::BlendDescriptor& inValue) {
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
