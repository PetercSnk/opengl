#pragma once
#ifndef SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <string>

// reads a binary file and returns its contents as a string
std::string read_binary_file(const char* path);
// compiles a shader and returns its reference identifier
static unsigned int compile_shader(GLenum type, const char* shader);
// creates a program object and returns its reference identifier
static unsigned int create_shader(const char* vertex_shader, const char* fragment_shader);

class Shader
{
public:
	// program object identifier
	unsigned int id;
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

