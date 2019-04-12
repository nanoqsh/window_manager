#pragma once

#include <GL/glew.h>
#include <string>


class shader_program
{
public:
	shader_program(const std::string & vs_path, const std::string & fs_path);
	shader_program(const shader_program & other) = delete;
	shader_program & operator=(const shader_program & other) = delete;
	~shader_program();

	void use();
	GLint get_attribute_loc(const std::string & name) const;
	GLint get_uniform_loc(const std::string & name) const;

private:
	GLuint shader;

};
