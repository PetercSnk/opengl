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
// compiles a shader and returns its reference identifier
static unsigned int compile_shader(GLenum type, const char* source);
// creates a program object, attaches and links shaders then returns its reference identifier
static unsigned int create_shader(const char* vertex_source, const char* fragment_source);

class Shader
{
public:
	// program object identifier
	unsigned int program;
	// constructor reads and builds shaders
	Shader(const char* vertex_path, const char* fragment_path);
	// binds program object
	void bind() const;
	// unbinds program object
	void unbind() const;
	// deletes program object
	void del();
};
#endif // !SHADER_CLASS_H

