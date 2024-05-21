#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_TexPos;

uniform sampler2D u_TexSamplerScene;
uniform sampler2D u_TexSamplerBloom;
uniform float u_Exposure;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(u_TexSamplerScene, v_TexPos).rgb;      
    vec3 bloomColor = texture(u_TexSamplerBloom, v_TexPos).rgb;
    hdrColor += bloomColor; 

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * u_Exposure);

    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
} 
