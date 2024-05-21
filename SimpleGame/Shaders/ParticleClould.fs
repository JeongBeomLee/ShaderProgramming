#version 330

layout(location=0) out vec4 FragColor0;	// HDRLow
layout(location=1) out vec4 FragColor1;	// HDRHigh

uniform sampler2D u_Texture;

in vec4 v_Color;
in vec2 v_TexPos;

void main()
{
	vec4 newColor = texture(u_Texture, v_TexPos);
	vec4 interColor = vec4(newColor.rgb * v_Color.rgb * 1, newColor.a);
	float brightness = dot(interColor.rgb, vec3(0.2126, 0.7152, 0.0722));	// ��Į�� �� ����
	FragColor0 = interColor;

	if (brightness > 1.0)	// ���� �κи� HDRHigh�� ����
	{
		FragColor1 = interColor;
	}
	else	// ��ο� �κ��� 0
		FragColor1 = vec4(0);
}
