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
 

const char * cameraClear_vert = R"(

#if __VERSION__ >= 300

layout(location=0) in vec4 a_position;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texCoord;
layout(std140, binding=0) uniform VSBlock
{
    float depth;
};
#ifdef GL_ES
layout(location=0) out mediump vec2 v_texCoord;
layout(location=1) out mediump vec4 v_color;
#else
layout(location=0) out vec2 v_texCoord;
layout(location=1) out vec4 v_color;
#endif

#else

attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;
uniform float depth;
#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec4 v_color;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

#endif

void main()
{
    gl_Position = a_position;
    gl_Position.z = depth;
    gl_Position.w = 1.0;
    v_texCoord = a_texCoord;
    v_color = a_color;
}

)";