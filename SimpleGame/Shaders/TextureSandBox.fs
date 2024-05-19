#version 330

layout(location=0) out vec4 FragColor;
in vec2 v_TexPos;

uniform sampler2D uTexSampler;
uniform sampler2D u_NumberTexture[10];
uniform sampler2D u_NumbersTexture;

//float C_PI  = 3.141592 ;
uniform float u_Time;

void P2(){
	float tx = v_TexPos.x;
	float ty = 1 - abs(v_TexPos.y * 2 - 1);
	vec2 newTexPos =vec2(tx,ty);
		FragColor = texture(uTexSampler,newTexPos);

}

void P3(){
	vec2 newTexPos;
	float tx = fract(v_TexPos.x *3);
	float ty = v_TexPos.y / 3 + floor(v_TexPos.x * 3)/3;

	newTexPos = vec2(tx,ty);

	FragColor = texture(uTexSampler,newTexPos);

}

void homework(){

	vec2 newTexPos;
	float tx = v_TexPos.x;
	float ty = ((2.f - floor(v_TexPos.y * 3)) / 3) + fract(v_TexPos.y * 3) / 3 ;
	newTexPos = vec2(tx,ty);
	FragColor = texture(uTexSampler,newTexPos);

}
void homework2(){
	vec2 newTexPos;
	float tx = fract(v_TexPos.x * 2);
	float ty =  fract(v_TexPos.y * 2)+0.5f*floor(v_TexPos.x * 2);

	newTexPos = vec2(tx,ty);
	FragColor = texture(uTexSampler,newTexPos);
}

void P5(){

	vec2 newTexPos;
	float padding = 0.2 + u_Time;
	float tx = fract(padding * (floor( v_TexPos.y * 2 ) + 1  )) +  v_TexPos.x * 2;
	float ty = fract(v_TexPos.y*2);

	newTexPos = vec2(tx,ty);

	FragColor = texture(uTexSampler,newTexPos);

}
void P6(){
	
	vec2 newTexPos;

	float tx = v_TexPos.x;
	 
	float ty =  v_TexPos.y;

	newTexPos = vec2(tx,ty);

	int texID = int(u_Time) % 10 ;
	FragColor = texture(u_NumberTexture[texID],newTexPos);
}

void P7(){

	vec2 newTexPos;
	float xResol = 5;
	float yResol = 2;
	float id = 5;
	float indexX = float(int(id) % int(xResol));
	float indexY = floor(id/xResol);
	float tx = v_TexPos.x / xResol + indexX*(1/xResol); // 0 - 0.2f
	float ty =  v_TexPos.y / yResol + indexY *(1/yResol); // 0 - 0.5f

	newTexPos = vec2(tx,ty);

	FragColor = texture(u_NumbersTexture,newTexPos);

}

void main()
{
	//homework();
	
	 P6();
}
