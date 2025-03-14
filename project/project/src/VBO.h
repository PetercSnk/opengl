#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
private:
	// vertex buffer object identifier
	GLuint vbo;
public:
	// generates and binds buffer object, then copies vertex data into it
	VBO(GLsizeiptr size, const GLvoid* vertices);
	// binds, unbinds, and deletes buffer object
	void bind() const;
	void unbind() const;
	void del();
};
#endif // !VBO_CLASS_H

