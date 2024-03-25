#include "stdafx.h"
#include "Renderer.h"
#include "Dependencies\freeglut.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs", "./Shaders/Particle.fs");

	//Create VBOs
	CreateVertexBufferObjects();

	//Create Particle Cloud
	CreateParticleCloud(1000);

	if (m_SolidRectShader > 0 && m_ParticleVBO > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float size = 0.05f;
	float particleVerts[]
		=
	{
		// �ﰢ��1
		-size, -size, 0.f,
		size, -size, 0.f,
		size, size, 0.f,

		// �ﰢ��2
		-size, -size, 0.f,
		size, size, 0.f,
		-size, size, 0.f
	};

	glGenBuffers(1, &m_ParticleVBO);	// VBO 1�� ����, VBO�� ID�� m_ParticleVBO�� ����
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);	// VBO�� ���ε�(�� �����ʹ� array �����̴� ��� �˷���)
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleVerts), particleVerts, GL_STATIC_DRAW);	// Bind�� VBO�� �����͸� ����(GPU)

	// CPU �޸𸮿� ���� �����͸� ����
	float vertices[]
		=
	{
		0.f, 0.f, 0.f, 
		1.f, 0.f, 0.f, 
		1.f, 1.f, 0.f
	};

	// GPU �޸𸮿� ���� �����͸� ����
	glGenBuffers(1, &m_TestVBO);	// VBO ����, VBO�� ID�� m_TestVBO�� ����
	glBindBuffer(GL_ARRAY_BUFFER, m_TestVBO);	// VBO�� ���ε�(�� �����ʹ� array �����̴� ��� �˷���)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Bind�� VBO�� �����͸� ����(GPU)
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

void Renderer::DrawTest()
{
	//Program select
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_TestVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::DrawParticle()
{
	GLuint shader = m_ParticleShader;
	glUseProgram(shader);

	GLint timeLocation = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeLocation, m_ParticleTime);
	m_ParticleTime += 0.0064;

	GLint periodLocation = glGetUniformLocation(shader, "u_Period");
	glUniform1f(periodLocation, 1.0f);

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::DrawParticleCloud()
{
	GLuint shader = m_ParticleShader;
	glUseProgram(shader);

	GLint timeLocation = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeLocation, m_ParticleTime);
	m_ParticleTime += 0.0064;

	GLint periodLocation = glGetUniformLocation(shader, "u_Period");
	glUniform1f(periodLocation, 1.0f);

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, m_ParticleCloudVertexCount);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::CreateParticleCloud(int numParticles)
{
	float centerX, centerY;
	centerX = 0.f;
	centerY = 0.f;

	float size = 0.01f;
	int particleCount = numParticles;
	int vertexCount = particleCount * 6;
	int floatCount = vertexCount * 3;

	float* vertices = nullptr;
	vertices = new float[floatCount];

	int index = 0;
	for (int i = 0; i < particleCount; ++i) {
		centerX = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		centerY = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;

		// Triangle 1
		vertices[index++] = centerX - size;
		vertices[index++] = centerY - size;
		vertices[index++] = 0.f;

		vertices[index++] = centerX + size;
		vertices[index++] = centerY + size;
		vertices[index++] = 0.f;

		vertices[index++] = centerX - size;
		vertices[index++] = centerY + size;
		vertices[index++] = 0.f;
		
		// Triangle 2
		vertices[index++] = centerX - size;
		vertices[index++] = centerY - size;
		vertices[index++] = 0.f;

		vertices[index++] = centerX + size;
		vertices[index++] = centerY - size;
		vertices[index++] = 0.f;

		vertices[index++] = centerX + size;
		vertices[index++] = centerY + size;
		vertices[index++] = 0.f;
	}

	glGenBuffers(1, &m_ParticleCloudVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCount, vertices, GL_STATIC_DRAW);
	m_ParticleCloudVertexCount = vertexCount;

	delete[] vertices;
}
