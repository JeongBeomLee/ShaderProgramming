#version 330

layout(location=0) out vec4 FragColor;


in vec4 v_Color;

void main()
{
	FragColor = v_Color;
	//FragColor = vec4(1,1,1,1);

}
