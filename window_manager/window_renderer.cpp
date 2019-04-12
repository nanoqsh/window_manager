#include "window_renderer.h"

#include "game.h"


const glm::vec3 window_renderer::HEADER_COLOR = glm::vec3(0.1f, 0.1f, 0.1f);
const int window_renderer::HEADER_HEIGHT = 32;


window_renderer::window_renderer(std::shared_ptr<shader_program> shader):
	shader(shader)
{
	bg_color_location = shader->get_uniform_loc("bg_color");

	GLint position_location = shader->get_attribute_loc("position");

	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 3, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(position_location);
	glVertexAttribPointer(
		position_location,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GLfloat),
		(const void *)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


window_renderer::~window_renderer()
{
}


void window_renderer::set_bg_color(const glm::vec3 & color)
{
	glUniform3f(bg_color_location, color.r, color.g, color.b);
}


void window_renderer::draw_quad(float x0, float y0, float x1, float y1, float z)
{
	glBindVertexArray(vao);

	GLfloat vertices[4][3] =
	{
		x0, y1, z,
		x1, y1, z,
		x0, y0, z,
		x1, y0, z
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
}


void window_renderer::draw_window(const window & win)
{
	if (!win.get_active_state())
		return;

	shader->use();

	float x = (float)win.get_x();
	float y = (float)win.get_y();
	float width = (float)win.get_width();
	float height = (float)win.get_height();
	float z = float(window_manager::MAX_Z - win.get_z_index() - 1);

	set_bg_color(HEADER_COLOR);
	draw_quad(x, y, x + width, y + std::fminf(height, HEADER_HEIGHT), z);

	set_bg_color(win.get_bg_color());
	draw_quad(x, y, x + width, y + height, z);
}
