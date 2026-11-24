/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Brian Chapados
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

const char* positionTextureColorAlphaTest_frag = R"(
#ifdef GL_ES
precision lowp float;
#endif

layout(std140, binding=1) uniform FSBlock
{
    float u_alpha_value;
};
layout(binding=2) uniform sampler2D u_texture;

layout(location=0) in vec4 v_fragmentColor;
layout(location=1) in vec2 v_texCoord;
layout(location=0) out vec4 cc_FragColor;

void main()
{
    vec4 texColor = texture(u_texture, v_texCoord);
    if ( texColor.a <= u_alpha_value )
        discard;
    cc_FragColor = texColor * v_fragmentColor;
}
)";
