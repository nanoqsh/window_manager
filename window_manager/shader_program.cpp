#include "shader_program.h"
#include "read_file.h"

#include <iostream>


const unsigned LOG_SIZE = 512;


GLuint read_shader(const std::string & path, GLenum type)
{
	GLuint shader = glCreateShader(type);

	const std::string s = read_file(path);
	const char * st = s.c_str();

	glShaderSource(shader, 1, &st, nullptr);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[LOG_SIZE];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, LOG_SIZE, nullptr, infoLog);
		std::cerr << infoLog << '\n';
	}

	return shader;
}


shader_program::shader_program(const std::string & vs_path, const std::string & fs_path)
{
	GLint vs = read_shader(vs_path, GL_VERTEX_SHADER);
	GLint fs = read_shader(fs_path, GL_FRAGMENT_SHADER);

	shader = glCreateProgram();
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);
	glLinkProgram(shader);

	GLint success;
	GLchar infoLog[LOG_SIZE];

	glGetProgramiv(shader, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shader, LOG_SIZE, nullptr, infoLog);
		std::cerr << infoLog << '\n';
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}


shader_program::~shader_program()
{
	glUseProgram(0);
	glDeleteProgram(shader);
}


void shader_program::use()
{
	glUseProgram(shader);
}


GLint shader_program::get_attribute_loc(const std::string & name) const
{
	return glGetAttribLocation(shader, name.c_str());
}


GLint shader_program::get_uniform_loc(const std::string & name) const
{
	return glGetUniformLocation(shader, name.c_str());
}
