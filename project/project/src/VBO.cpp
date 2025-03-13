#include "vbo.h"

VBO::VBO(unsigned int size, const float* vertices)
{
	// generates one buffer object
	glGenBuffers(1, &vbo);
	// binds buffer object to opengl's array buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// copies vertex data into the currently bound buffer object
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::del()
{
	glDeleteBuffers(1, &vbo);
}