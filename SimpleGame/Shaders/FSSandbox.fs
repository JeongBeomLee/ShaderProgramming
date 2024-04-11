#version 330

layout(location=0) out vec4 FragColor;

uniform float u_Time;

in vec4 v_Color;

const float c_PI = 3.14159265359;

void FilledCircle()
{
	vec4 newColor = vec4(1, 1, 1, 1);
	float r = 0.5;
	vec2 center = vec2(0.5, 0.5);
	float dist = distance(center, v_Color.rg);

	if (dist < r)
	{
		newColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		newColor = vec4(0.0, 0.0, 0.0, 1.0);
	}

	FragColor = newColor;
}

void Circle()
{
	vec4 newColor = vec4(1, 1, 1, 1);
	float r = 0.5;
	float width = 0.05;
	vec2 center = vec2(0.5, 0.5);
	float dist = distance(center, v_Color.rg);

	if (dist < r && dist > r - width)
	{
		newColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		newColor = vec4(0.0, 0.0, 0.0, 1.0);
	}

	FragColor = newColor;
}

void Circles()
{
	float circleCount = 10;
	vec2 circleCenter = vec2(0.5, 0.5);
	float dist = distance(v_Color.rg, circleCenter);
	float input = circleCount * c_PI * 4 * dist - u_Time * 10;	// 시험문제 (circleCount만큼 원을 그리고 싶다. 식을 적어라.)
	float sinValue = pow(sin(input), 16);

	FragColor = vec4(sinValue);
}

void main()
{
	//FilledCircle();
	//Circle();
	Circles();
}
