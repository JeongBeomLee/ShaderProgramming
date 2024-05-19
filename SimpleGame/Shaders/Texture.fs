#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;

in vec2 v_TexPos;

void main()
{
	FragColor = texture( u_Texture ,v_TexPos);
	//FragColor =vec4(1,0,0,1);

}
