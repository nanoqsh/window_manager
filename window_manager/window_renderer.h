#pragma once

#include "shader_program.h"
#include "window.h"
#include <memory>
#include <GL/glew.h>
#include <glm/vec3.hpp>


class window_renderer
{
public:
	window_renderer(std::shared_ptr<shader_program> shader);
	window_renderer(const window_renderer & other) = delete;
	window_renderer & operator=(const window_renderer & other) = delete;
	~window_renderer();

	void draw_window(const window & win);

private:
	void set_bg_color(const glm::vec3 & color);
	void draw_quad(float x, float y, float width, float height, float z);

	GLuint vbo;
	GLuint vao;
	std::shared_ptr<shader_program> shader;
	GLint bg_color_location;

	static const glm::vec3 HEADER_COLOR;
	static const int HEADER_HEIGHT;

};
