/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

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
 

const char* CC2D_quadTexture_frag = R"(

#if __VERSION__ >= 300

layout(std140, binding=1) uniform FSBlock
{
    vec4 u_color;
};
layout(binding=2) uniform sampler2D u_texture;
#ifdef GL_ES
    layout(location=0) in mediump vec4 ColorOut;
    layout(location=1) in mediump vec2 TextureCoordOut;
#else
    layout(location=0) in vec4 ColorOut;
    layout(location=1) in vec2 TextureCoordOut;
#endif
layout(location=0) out vec4 cc_FragColor;
#define texture2D texture
#define gl_FragColor cc_FragColor

#else

#ifdef GL_ES
    varying mediump vec2 TextureCoordOut;
    varying mediump vec4 ColorOut;
#else
    varying vec4 ColorOut;
    varying vec2 TextureCoordOut;
#endif
uniform vec4 u_color;
uniform sampler2D u_texture;

#endif

void main(void)
{
    gl_FragColor = texture2D(u_texture, TextureCoordOut) * ColorOut * u_color;
}
)";

const char* CC2D_quadColor_frag = R"(

#if __VERSION__ >= 300

layout(std140, binding=1) uniform FSBlock
{
    vec4 u_color;
};
#ifdef GL_ES
    layout(location=0) in mediump vec4 ColorOut;
#else
    layout(location=0) in vec4 ColorOut;
#endif
layout(location=0) out vec4 cc_FragColor;
#define gl_FragColor cc_FragColor

#else

#ifdef GL_ES
    varying mediump vec4 ColorOut;
#else
    varying vec4 ColorOut;
#endif
uniform vec4 u_color;

#endif

void main(void)
{
    gl_FragColor = ColorOut * u_color;
}
)";
