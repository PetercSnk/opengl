#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <string>

// reads a binary file and returns its contents as a string
std::string read_binary_file(const char* path);
// creates a shader object and returns an identifier by which it can be referenced
static unsigned int compile_shader(GLenum type, const char* source);
// creates a program object and returns an identifier by which it can be referenced
static unsigned int create_shader(const char* vertex_source, const char* fragment_source);

class Shader
{
public:
	// program object identifier
	unsigned int program;
	// constructor reads, compiles, and creates shaders
	Shader(const char* vertex_path, const char* fragment_path);
	// binds program object
	void bind() const;
	// unbinds program object
	void unbind() const;
	// deletes program object
	void del();
	// set boolean uniform
	void set_bool(const char* name, bool value) const;
	// set integer uniform
	void set_int(const char* name, int value) const;
	// set float uniform
	void set_float(const char* name, float value) const;
};
#endif // !SHADER_CLASS_H

