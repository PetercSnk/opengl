#pragma once
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
private:
	// texture identifier
	GLuint texture;
public:
	// generates a texture from image data
	Texture(const char* texture_path, GLenum format, GLenum wrapping, GLenum filtering);
	// binds texture to texture unit
	void bind(GLenum texture_unit) const;
};
#endif // !TEXTURE_CLASS_H