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
 

const char* CC3D_positionTexture_vert = R"(

#if __VERSION__ >= 300

layout(location=0) in vec4 a_position;
layout(location=1) in vec2 a_texCoord;

layout(std140, binding=0) uniform VSBlock
{
    mat4 u_MVPMatrix;
};

layout(location=0) out vec2 TextureCoordOut;

#else

attribute vec4 a_position;
attribute vec2 a_texCoord;

uniform mat4 u_MVPMatrix;

varying vec2 TextureCoordOut;

#endif

void main(void)
{
    gl_Position = u_MVPMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}
)";

const char* CC3D_skinPositionTexture_vert = R"(

const int SKINNING_JOINT_COUNT = 60;

#if __VERSION__ >= 300

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_blendWeight;
layout(location=2) in vec4 a_blendIndex;
layout(location=3) in vec2 a_texCoord;

layout(std140, binding=0) uniform VSBlock
{
    vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];
    mat4 u_MVPMatrix;
};

layout(location=0) out vec2 TextureCoordOut;

#else

attribute vec3 a_position;
attribute vec4 a_blendWeight;
attribute vec4 a_blendIndex;
attribute vec2 a_texCoord;

uniform vec4 u_matrixPalette[SKINNING_JOINT_COUNT * 3];
uniform mat4 u_MVPMatrix;

varying vec2 TextureCoordOut;
#endif

vec4 getPosition()
{
    float blendWeight = a_blendWeight[0];

    int matrixIndex = int (a_blendIndex[0]) * 3;
    vec4 matrixPalette1 = u_matrixPalette[matrixIndex] * blendWeight;
    vec4 matrixPalette2 = u_matrixPalette[matrixIndex + 1] * blendWeight;
    vec4 matrixPalette3 = u_matrixPalette[matrixIndex + 2] * blendWeight;


    blendWeight = a_blendWeight[1];
    if (blendWeight > 0.0)
    {
        matrixIndex = int(a_blendIndex[1]) * 3;
        matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
        matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
        matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;

        blendWeight = a_blendWeight[2];
        if (blendWeight > 0.0)
        {
            matrixIndex = int(a_blendIndex[2]) * 3;
            matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
            matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
            matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;

            blendWeight = a_blendWeight[3];
            if (blendWeight > 0.0)
            {
                matrixIndex = int(a_blendIndex[3]) * 3;
                matrixPalette1 += u_matrixPalette[matrixIndex] * blendWeight;
                matrixPalette2 += u_matrixPalette[matrixIndex + 1] * blendWeight;
                matrixPalette3 += u_matrixPalette[matrixIndex + 2] * blendWeight;
            }
        }
    }

    vec4 _skinnedPosition;
    vec4 position = vec4(a_position, 1.0);
    _skinnedPosition.x = dot(position, matrixPalette1);
    _skinnedPosition.y = dot(position, matrixPalette2);
    _skinnedPosition.z = dot(position, matrixPalette3);
    _skinnedPosition.w = position.w;

    return _skinnedPosition;
}

void main()
{
    vec4 position = getPosition();
    gl_Position = u_MVPMatrix * position;

    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}

)";
