#include "shader.h"

std::string read_binary_file(const char* path)
{
	// opens binary file with current get position pointer set to eof
	std::ifstream file(path, std::ios::binary | std::ios::ate | std::ios::in);
	// checks if opened successfully, else print error
	if (file.is_open())
	{
		// placeholder for file content
		std::string content;
		// finds size of file
		int size = file.tellg();
		// resizes content 
		content.resize(size);
		// sets current get position pointer to beginning of file
		file.seekg(0, std::ios::beg);
		// reads file as block
		file.read(&content[0], size);
		// closes file and returns content
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
	// creates shader object for the specified type
	GLuint shader = glCreateShader(type);
	// attaches the shader source to the shader object
	glShaderSource(shader, 1, &source, nullptr);
	// compiles shader
	glCompileShader(shader);
	// checks for compilation errors
	GLint success;
	GLchar log[512];
	// retrieves the compilation status parameter from the shader object
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// retrieves the information log for the shader object
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " compilation failed" << std::endl;
		std::cout << log << std::endl;
		// frees occupied memory
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

GLuint create_shader(const GLchar* vertex_source, const GLchar* fragment_source)
{
	// compiles vertex and fragment shader
	GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
	GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
	// creates program object
	GLuint program = glCreateProgram();
	// attaches and links compiled shaders to program object
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	// checks for linking errors
	GLint success;
	GLchar log[512];
	// retrieves the linking status parameter from the program object
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		// retrieves the information log for the program object
		glGetProgramInfoLog(program, 512, NULL, log);
		std::cout << "Linking failed" << std::endl;
		std::cout << log << std::endl;
		// frees occupied memory
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
	// reads in vertex and fragment shaders
	std::string vertex_source_str = read_binary_file(vertex_path);
	std::string fragment_source_str = read_binary_file(fragment_path);
	const GLchar* vertex_source = vertex_source_str.c_str();
	const GLchar* fragment_source = fragment_source_str.c_str();
	// creates program object with given shaders
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

void Shader::set_int(const char* name, int value) const
{
	GLint uniform = glGetUniformLocation(program, name);
	glUniform1i(uniform, value);
}

void Shader::set_float(const char* name, float value) const
{
	GLint uniform = glGetUniformLocation(program, name);
	glUniform1f(uniform, value);
}

void Shader::set_mat4(const char* name, glm::mat4 value) const
{
	GLint uniform = glGetUniformLocation(program, name);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_vec3(const char* name, glm::vec3 value) const
{
	GLint uniform = glGetUniformLocation(program, name);
	glUniform3fv(uniform, 1, glm::value_ptr(value));
}