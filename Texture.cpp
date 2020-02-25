#include "Texture.h"

Texture::Texture() {
	this->tex = 0;
}

Texture::~Texture() {

}

void Texture::LoadTex(const char* File) {
	FIBITMAP* dib = GetBMP(File);

	GLenum Format = 0;

	if (this->bpp == 32) Format = GL_BGRA;
	if (this->bpp == 24) Format = GL_BGR;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (GLEW_EXT_texture_filter_anisotropic) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_BGR, GL_UNSIGNED_BYTE, FreeImage_GetBits(dib));

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	FreeImage_Unload(dib);
}

FIBITMAP* Texture::GetBMP(const char* File) {
	FIBITMAP* dib = FreeImage_Load(FIF_JPEG, File);

	this->width = FreeImage_GetWidth(dib);
	this->height = FreeImage_GetHeight(dib);

	this->bpp = FreeImage_GetBPP(dib);

	return dib;
}

void Texture::Render() {
	glBindTexture(GL_TEXTURE_2D, this->tex);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-150.0f, -150.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(150.0f, -150.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(150.0f, 150.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-150.0f, 150.0f);
	glEnd();
}