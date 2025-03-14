#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
private:
	// element buffer object identifier
	GLuint ebo;
public:
	// generates and binds buffer object, then copies index data into it
	EBO(GLsizeiptr size, const GLvoid* indices);
	// binds, unbinds, and deletes buffer object
	void bind() const;
	void unbind() const;
	void del();
};
#endif // !EBO_CLASS_H
