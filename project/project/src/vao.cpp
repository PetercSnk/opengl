#include "vao.h"

VAO::VAO()
{
	// generates one vertex array object
	glGenVertexArrays(1, &vao);
}

void VAO::link_attrib(VBO& vbo, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, GLvoid* offset)
{
	vbo.bind();
	// specifies how opengl should interpret vertex data
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	// enables the vertex attribute
	glEnableVertexAttribArray(index);
	vbo.unbind();
}

void VAO::bind() const
{
	glBindVertexArray(vao);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::del()
{
	glDeleteVertexArrays(1, &vao);
}