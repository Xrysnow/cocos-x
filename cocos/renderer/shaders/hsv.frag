
const char* hsv_frag = R"(
#ifdef GL_ES
precision mediump float;
#endif

#if __VERSION__ >= 300

layout(std140, binding=1) uniform FSBlock
{
    mat3 u_mix_hsv;
    vec3 u_filter_rgb;
};
layout(binding=2) uniform sampler2D u_texture;
layout(location=0) in vec4 v_fragmentColor;
layout(location=1) in vec2 v_texCoord;
layout(location=0) out vec4 cc_FragColor;
#define texture2D texture
#define gl_FragColor cc_FragColor

#else

varying vec2 v_texCoord;  
varying vec4 v_fragmentColor;
uniform sampler2D u_texture;
// HSV matrix
uniform mat3 u_mix_hsv;
// filter color RGB values
uniform vec3 u_filter_rgb;

#endif

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() 
{ 
    vec4 pixColor = texture2D(u_texture, v_texCoord);  // * v_fragmentColor; 
    vec3 rgbColor = u_mix_hsv * pixColor.rgb;
    float sum = pixColor.r + pixColor.g + pixColor.b;
    float rv = pixColor.r / sum;
    float gv = pixColor.g / sum;
    float bv = pixColor.b / sum;
    if(  (rv < u_filter_rgb.r && gv < u_filter_rgb.g && bv < u_filter_rgb.b) || pixColor.a < 0.1)
    { // color filters, resume to original color
        rgbColor = pixColor.rgb;
        rgbColor.r *= v_fragmentColor.a;
        rgbColor.g *= v_fragmentColor.a;
        rgbColor.b *= v_fragmentColor.a;
    }
    rgbColor.rgb = rgbColor.rgb * v_fragmentColor.rgb;
    gl_FragColor = vec4(rgbColor, pixColor.a * v_fragmentColor.a); 
} 
)";
