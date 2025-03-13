#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "vbo.h"

class VAO
{
private:
	// vertex array object identifier
	GLuint vao;
public:
	// generates vertex array object
	VAO();
	// links vertex attributes
	void link_attrib(VBO& vbo, GLuint location, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, GLvoid* offset);
	// binds, unbinds, and deletes array object
	void bind() const;
	void unbind() const;
	void del();
	
};
#endif // !VAO_CLASS_H
