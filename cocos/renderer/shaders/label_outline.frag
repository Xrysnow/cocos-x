/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

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
 
/*
 * LICENSE ???
 */
const char* labelOutline_frag = R"(
#ifdef GL_ES
precision lowp float;
#endif

#if __VERSION__ >= 300

layout(std140, binding=1) uniform FSBlock
{
    vec4 u_effectColor;
    vec4 u_textColor;
    #ifdef GL_ES
    lowp int u_effectType; // 0: None (Draw text), 1: Outline, 2: Shadow
    #else
    int u_effectType;
    #endif
};
layout(binding=2) uniform sampler2D u_texture;

layout(location=0) in vec4 v_fragmentColor;
layout(location=1) in vec2 v_texCoord;
layout(location=0) out vec4 cc_FragColor;

#else

uniform vec4 u_effectColor;
uniform vec4 u_textColor;
#ifdef GL_ES
uniform lowp int u_effectType; // 0: None (Draw text), 1: Outline, 2: Shadow
#else
uniform int u_effectType;
#endif
uniform sampler2D u_texture;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

#endif


void main()
{
#if __VERSION__ >= 300
    vec4 sample_ = texture(u_texture, v_texCoord);
#else
    vec4 sample_ = texture2D(u_texture, v_texCoord);
#endif
    // fontAlpha == 1 means the area of solid text (without edge)
    // fontAlpha == 0 means the area outside text, including outline area
    // fontAlpha == (0, 1) means the edge of text
    float fontAlpha = sample_.a;

    // outlineAlpha == 1 means the area of 'solid text' and 'solid outline'
    // outlineAlpha == 0 means the transparent area outside text and outline
    // outlineAlpha == (0, 1) means the edge of outline
    float outlineAlpha = sample_.r;

    vec4 fragColor;
    if (u_effectType == 0) // draw text
    {
        fragColor = v_fragmentColor * vec4(u_textColor.rgb, u_textColor.a * fontAlpha);
    }
    else if (u_effectType == 1) // draw outline
    {
        // multipy (1.0 - fontAlpha) to make the inner edge of outline smoother and make the text itself transparent.
        fragColor = v_fragmentColor * vec4(u_effectColor.rgb, u_effectColor.a * outlineAlpha * (1.0 - fontAlpha));
    }
    else // draw shadow
    {
        fragColor = v_fragmentColor * vec4(u_effectColor.rgb, u_effectColor.a * outlineAlpha);
    }
#if __VERSION__ >= 300
    cc_FragColor = fragColor;
#else
    gl_FragColor = fragColor;
#endif
}
)";
