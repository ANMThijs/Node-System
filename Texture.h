#pragma once
#include <gl/glew.h>
#include <FreeImage.h>

class Texture
{
public:
	Texture();
	~Texture();
	
	void LoadTex(const char* File);

	FIBITMAP* GetBMP(const char* File);

	void Render();

	GLuint tex;
	int width, height, bpp;
};

