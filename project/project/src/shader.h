#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <string>

// reads a binary file and returns contents as a string
std::string read_binary_file(const char* path);
// creates a shader object and returns identifier
static unsigned int compile_shader(GLenum type, const char* source);
// creates a program object and returns identifier
static unsigned int create_shader(const char* vertex_source, const char* fragment_source);

class Shader
{
public:
	// program object identifier
	unsigned int program;
	// reads, compiles, and creates shaders
	Shader(const char* vertex_path, const char* fragment_path);
	// binds, unbinds, and deletes program object
	void bind() const;
	void unbind() const;
	void del();
	// set uniforms
	void set_bool(const char* name, bool value) const;
	void set_int(const char* name, int value) const;
	void set_float(const char* name, float value) const;
};
#endif // !SHADER_CLASS_H

