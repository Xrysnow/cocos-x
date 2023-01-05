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
 

const char* CC3D_particleTexture_frag = R"(

#if __VERSION__ >= 300
layout(std140, binding=1) uniform FSBlock
{
    vec4 u_color;
};
layout(location=0) in mediump vec2 TextureCoordOut;
layout(location=1) in mediump vec4 ColorOut;
layout(binding=2) uniform sampler2D u_texture;
layout(location = 0) out vec4 cc_FragColor;
#else
uniform vec4 u_color;
varying mediump vec2 TextureCoordOut;
varying mediump vec4 ColorOut;
uniform sampler2D u_texture;
#endif

void main(void)
{
#if __VERSION__ >= 300
    cc_FragColor = texture(u_texture, TextureCoordOut) * ColorOut * u_color;
#else
    gl_FragColor = texture2D(u_texture, TextureCoordOut) * ColorOut * u_color;
#endif
}
)";

const char* CC3D_particleColor_frag = R"(

#if __VERSION__ >= 300
layout(std140, binding=1) uniform FSBlock
{
    vec4 u_color;
};
layout(location=1) in mediump vec4 ColorOut;
layout(location=0) out vec4 cc_FragColor;
#else
uniform vec4 u_color;
varying mediump vec4 ColorOut;
#endif

void main(void)
{
#if __VERSION__ >= 300
    cc_FragColor = ColorOut * u_color;
#else
    gl_FragColor = ColorOut * u_color;
#endif
}
)";
