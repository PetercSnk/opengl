#include "shader.h"

std::string read_binary_file(const char* path)
{
	// open binary file with current get position pointer set to eof
	std::ifstream file(path, std::ios::binary | std::ios::ate | std::ios::in);
	// check if opened successfully, else print error
	if (file.is_open())
	{
		// placeholder for file content
		std::string content;
		// find size of file
		int size = file.tellg();
		// resize content 
		content.resize(size);
		// set current get position pointer to beginning of file
		file.seekg(0, std::ios::beg);
		// read file as block
		file.read(&content[0], size);
		// close file and return content
		file.close();
		return content;
	}
	else
	{
		perror("Failed to open file");
	}
}

unsigned int compile_shader(GLenum type, const char* source)
{
	// create shader object for the specified type
	unsigned int id = glCreateShader(type);
	// attach the shader source to the shader object
	glShaderSource(id, 1, &source, nullptr);
	// compile shader
	glCompileShader(id);
	// check for compilation errors
	int success;
	char log[512];
	// retrieve the compilation status parameter from the shader object
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// retrieve the information log for the shader object
		glGetShaderInfoLog(id, 512, NULL, log);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "compilation failed" << std::endl;
		std::cout << log << std::endl;
		// free occupied memory
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int create_shader(const char* vertex_shader_source, const char* fragment_shader_source)
{
	// compile both shaders
	unsigned int vertex_shader_id = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
	unsigned int fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
	// create program object
	unsigned int program_id = glCreateProgram();
	// attach and link compiled shaders to program object
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	// check for linking errors
	int success;
	char log[512];
	// retrieve the linking status parameter from the program object
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		// retrieve the information log for the program object
		glGetProgramInfoLog(program_id, 512, NULL, log);
		std::cout << "Linking failed" << std::endl;
		std::cout << log << std::endl;
		// free occupied memory
		glDeleteProgram(program_id);
		return 0;
	}
	// delete shader objects after linking
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	return program_id;
}