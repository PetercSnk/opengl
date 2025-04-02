#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <string>

// reads a binary file and returns contents as a string
std::string read_binary_file(const char* path);
// creates a shader object and returns identifier
GLuint compile_shader(GLenum type, const GLchar* source);
// creates a program object and returns identifier
GLuint create_shader(const GLchar* vertex_source, const GLchar* fragment_source);

class Shader
{
private:
	// program object identifier
	GLuint program;
public:
	// reads, compiles, and creates shaders
	Shader(const char* vertex_path, const char* fragment_path);
	// binds, unbinds, and deletes program object
	void bind() const;
	void unbind() const;
	void del();
	// set uniforms
	void set_int(const char* name, int value) const;
	void set_float(const char* name, float value) const;
	void set_mat4(const char* name, glm::mat4 value) const;
	void set_vec3(const char* name, glm::vec3 value) const;
};
#endif // !SHADER_CLASS_H

