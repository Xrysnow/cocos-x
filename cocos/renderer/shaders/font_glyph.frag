const char* fontGlyph_frag = R"(
#ifdef GL_ES
precision highp float;
#endif
layout(std140, binding=1) uniform FSBlock
{
    vec4 u_textColor;
    vec4 u_glyphParams;
};
layout(binding=2) uniform sampler2D u_texture;
layout(location=0) in vec4 v_fragmentColor;
layout(location=1) in vec2 v_texCoord;
layout(location=0) out vec4 cc_FragColor;
void main()
{
    vec3 sampleValue=texture(u_texture,v_texCoord).rgb;
    float d=sampleValue.r;
    if (u_glyphParams.x>1.5)
        d=max(min(sampleValue.r,sampleValue.g),min(max(sampleValue.r,sampleValue.g),sampleValue.b));
    float coverage=d;
    if (u_glyphParams.x>0.5)
    {
        float aa=max(fwidth(d)*0.5,0.5/255.0);
        float threshold=0.5-u_glyphParams.y;
        coverage=smoothstep(threshold-aa,threshold+aa,d);
        if (u_glyphParams.z>0.5) coverage=smoothstep(0.01,0.5,d);
    }
    vec4 color=v_fragmentColor*u_textColor;
    color.a*=coverage;
    if (u_glyphParams.w>0.5) color.rgb*=color.a;
    cc_FragColor=color;
}
)";
