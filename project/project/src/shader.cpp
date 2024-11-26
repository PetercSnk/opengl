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

unsigned int compile_shader(GLenum type, const char* shader)
{
	// create shader object for the specified type
	unsigned int id = glCreateShader(type);
	// attach the shader source to the shader object
	glShaderSource(id, 1, &shader, nullptr);
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
		// free occupied memory, effectively undoing the effects of the call to glCreateShader
		glDeleteShader(id);
		return 0;
	}
	return id;
}