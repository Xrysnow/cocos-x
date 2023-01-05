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
 
const char* label_distanceNormal_frag = R"(

#ifdef GL_ES
precision lowp float;
#endif

#if __VERSION__ >= 300

layout(std140, binding=1) uniform FSBlock
{
    vec4 u_textColor;
};
layout(binding=2) uniform sampler2D u_texture;
layout(location=0) in vec4 v_fragmentColor;
layout(location=1) in vec2 v_texCoord;
layout(location=0) out vec4 cc_FragColor;

#else

uniform vec4 u_textColor;
uniform sampler2D u_texture;
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

#endif

void main()
{
    // the texture use single channel 8-bit output for distance_map
#if __VERSION__ >= 300
    vec4 color = texture(u_texture, v_texCoord);
    float dist = color.r; // R8_NORM
#else
    vec4 color = texture2D(u_texture, v_texCoord);
    float dist = color.a;
#endif
    //TODO: Implementation 'fwidth' for glsl 1.0
    //float width = fwidth(dist);
    //assign width for constant will lead to a little bit fuzzy,it's temporary measure.
    float width = 0.04;
    float alpha = smoothstep(0.5-width, 0.5+width, dist) * u_textColor.a;
#if __VERSION__ >= 300
    cc_FragColor = v_fragmentColor * vec4(u_textColor.rgb,alpha);
#else
    gl_FragColor = v_fragmentColor * vec4(u_textColor.rgb,alpha);
#endif
}
)";
