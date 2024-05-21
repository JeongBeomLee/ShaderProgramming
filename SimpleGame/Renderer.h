#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);

	void DrawTest();
	void DrawParticle();
	void DrawParticleCloud();
	void DrawFSSandbox();
	void DrawGridMesh();
	void DrawTextureSandBox();
	void DrawTexture(float x, float y, float sizeX, float sizeY, GLuint texID);
	void DrawGaussianBlur(GLuint texID, GLuint targetFBOID, GLuint shader);
	void DrawMergeBloomTexture(GLuint sceneTexID, GLuint bloomTexID, float exposure);
	
	GLuint CreatePngTexture(char* filePath, GLuint samplingMethod);

	void DrawTotal();
	void DrawAlphaClear(float r, float g, float b, float a);

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void CreateParticleCloud(int numParticles);
	void CreateGridMesh(int x, int y);
	void CreateFBOs();

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;

	GLuint m_TestVBO = 0 ;

	GLuint m_particleShader = 0;
	GLuint m_particleVBO = 0;
	float m_particleTime = 0;

	GLuint m_particleCloudShader = 0;
	GLuint m_particleCloudVBO = 0;
	GLuint m_particleCloudVertexCount = 0;

	GLuint m_FSSandboxShader = 0;
	GLuint m_FSSandboxVBO = 0;
	float m_FSSandboxTime = 0;

	GLuint m_GridMeshShader = 0;
	GLuint m_GridMeshVBO = 0;
	GLuint m_GirdMeshVertexCount = 0;
	float m_GridMeshTime = 0;

	GLuint m_RGBTexture;
	GLuint m_TextureSandBoxShader = 0;
	GLuint m_TextureSandBoxVBO = 0;
	GLuint m_TextureSandBoxCount = 0;
	float  m_TextureSandBoxTime = 0;

	GLuint m_NumberTexture[10];
	GLuint m_numbersTexture;
	GLuint m_ParticleTexture;

	GLuint m_TextureShader = 0;
	GLuint m_TextureVBO = 0;

	GLuint m_A_FBO;
	GLuint m_A_FBOTexture0;
	GLuint m_A_FBOTexture1;

	GLuint m_FullRectVBO = 0;
	GLuint m_AlphaClearShader = 0;

	GLuint m_HDRFBO = 0;
	GLuint m_HDRHighTexture = 0;
	GLuint m_HDRLowTexture = 0;

	GLuint m_PingpongFBO[2]{};
	GLuint m_PingpongTexture[2]{};
	GLuint m_HBlurShader = 0;
	GLuint m_VBlurShader = 0;

	GLuint m_MergeShader = 0;
};

