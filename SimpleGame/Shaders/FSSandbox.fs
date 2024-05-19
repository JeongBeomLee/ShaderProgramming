#version 330

layout(location=0) out vec4 FragColor;

uniform float u_Time;

in vec4 v_Color;

const float c_PI = 3.14;

void FilledCircle(){
	vec4 newColor =vec4(1,1,1,1);
	float r = 0.5f;
	vec2 center = vec2(0.5f,0.5f);
	float dist  = distance(v_Color.rg,center );
	if( dist  < r ){
	newColor = vec4(1,1,1,1);

	}
	else{
	newColor = vec4(0.0f,0.0f,0.0f,1.0f);

	}

	FragColor = newColor;
}
void Circle(){

vec4 newColor = vec4(1,1,1,1);
float r = 0.5f;
float  width = 0.05f;
vec2 center = vec2(0.5f,0.5f);
float dist = distance(v_Color.rg , center);
if(dist > r - width && dist < r)	
{
	newColor = vec4(1,1,1,1);
}
else{
	newColor = vec4(0,0,0,0);
}
FragColor = newColor;
}


void Circles(){
	float circleCount = 10;
	vec2 circleCenter = vec2(0.5,0.5);
	float maxDist = 0.5f;

	float dist = distance(v_Color.rg , circleCenter);
	float input = circleCount*c_PI* 4* dist - u_Time * 20.0; 
	float sinValue = pow(sin(input),16);
	FragColor = vec4(sinValue);
 
}

void SinGraph(){

	vec2 newTexPos = vec2(v_Color.r  * 2 * c_PI, v_Color.g * 2 - 1);
	float period = 3;
	float speed = 10;
	float amp = 0.2f;
	//float sinValue = amp * sin(newTexPos.x*period - u_Time *speed) - amp * sin( - u_Time*speed); //다른 방법을 취함
	float sinValue = v_Color.r * amp * sin(newTexPos.x*period - u_Time * speed);
	float width = 0.5;
	width = width*(1.f - v_Color.r * 0.5f);

	if(sinValue < newTexPos.y + width && sinValue > newTexPos.y-width){
		
		FragColor = vec4((sinValue+1)/2);

	}
	else{

		discard;

	}

}

void DrawSin()
{

	float height = sin(v_Color.r*2*c_PI);
	float bold = 0.01f;
	float std  =  v_Color.g * 2 - 1;

	if(height + bold > std&&height- bold < std){
		FragColor = vec4(1);
	}
	else{
			discard;
	}
}

void main()
{
	//FilledCircle();
	//Circle();
	//Circles();
	//SinGraph();
	DrawSin();
}
