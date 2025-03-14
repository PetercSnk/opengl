#include "ebo.h"

EBO::EBO(GLsizeiptr size, const GLvoid* indices)
{
	// generates one buffer object
	glGenBuffers(1, &ebo);
	// binds buffer object to opengl's element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// copies index data into the currently bound buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void EBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::del()
{
	glDeleteBuffers(1, &ebo);
}