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

GLuint compile_shader(GLenum type, const GLchar* source)
{
	// create shader object for the specified type
	GLuint shader = glCreateShader(type);
	// attach the shader source to the shader object
	glShaderSource(shader, 1, &source, nullptr);
	// compile shader
	glCompileShader(shader);
	// check for compilation errors
	GLint success;
	GLchar log[512];
	// retrieve the compilation status parameter from the shader object
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// retrieve the information log for the shader object
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " compilation failed" << std::endl;
		std::cout << log << std::endl;
		// free occupied memory
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

GLuint create_shader(const GLchar* vertex_source, const GLchar* fragment_source)
{
	// compile vertex and fragment shader
	GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
	GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
	// create program object
	GLuint program = glCreateProgram();
	// attach and link compiled shaders to program object
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	// check for linking errors
	GLint success;
	GLchar log[512];
	// retrieve the linking status parameter from the program object
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		// retrieve the information log for the program object
		glGetProgramInfoLog(program, 512, NULL, log);
		std::cout << "Linking failed" << std::endl;
		std::cout << log << std::endl;
		// free occupied memory
		glDeleteProgram(program);
		return 0;
	}
	// delete shader objects after linking
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return program;
}

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
	// read in vertex and fragment shader
	std::string vertex_source_str = read_binary_file(vertex_path);
	std::string fragment_source_str = read_binary_file(fragment_path);
	const GLchar* vertex_source = vertex_source_str.c_str();
	const GLchar* fragment_source = fragment_source_str.c_str();
	// create program object with given shaders
	program = create_shader(vertex_source, fragment_source);
}

void Shader::bind() const
{
	glUseProgram(program);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::del()
{
	glDeleteProgram(program);
}

void Shader::set_bool(const char* name, bool value) const
{
	bool uniform = glGetUniformLocation(program, name);
	glUniform1i(uniform, (int)value);
}

void Shader::set_int(const char* name, int value) const
{
	int uniform = glGetUniformLocation(program, name);
	glUniform1i(uniform, value);
}

void Shader::set_float(const char* name, float value) const
{
	float uniform = glGetUniformLocation(program, name);
	glUniform1f(uniform, value);
}

void Shader::set_mat4fv(const char* name, glm::mat4 value) const
{
	unsigned int uniform = glGetUniformLocation(program, name);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
}