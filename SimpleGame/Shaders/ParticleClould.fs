#version 330

layout(location=0) out vec4 FragColor0;
layout(location=1) out vec4 FragColor1;

uniform sampler2D u_Texture;

in vec4 v_Color;
in vec2 v_TexPos;

void main()
{
	FragColor0 = texture( u_Texture ,v_TexPos.xy );
    FragColor1 = vec4(v_TexPos, 0.0, 1.0);
}
