#include "window.h"


window::window(
	unsigned id,
	int x_pos,
	int y_pos,
	unsigned z_index,
	int width,
	int height,
	bool is_active,
	glm::vec3 bg_color
	):
	id(id),
	x_pos(x_pos),
	y_pos(y_pos),
	z_index(z_index),
	width(width),
	height(height),
	is_active(is_active),
	bg_color(bg_color)
{
}


window::~window()
{
}


void window::set_position(int x, int y)
{
	x_pos = x;
	y_pos = y;
}


void window::set_z_index(unsigned index)
{
	z_index = index;
}


void window::set_active(bool state)
{
	is_active = state;
}


bool window::get_active_state() const
{
	return is_active;
}


void window::set_size(int width, int height)
{
	this->width = width;
	this->height = height;
}


unsigned window::get_id() const
{
	return id;
}


void window::set_bg_color(const glm::vec3 & color)
{
	bg_color = color;
}


const glm::vec3 & window::get_bg_color() const
{
	return bg_color;
}


int window::get_x() const
{
	return x_pos;
}


int window::get_y() const
{
	return y_pos;
}


unsigned window::get_z_index() const
{
	return z_index;
}


int window::get_width() const
{
	return width;
}


int window::get_height() const
{
	return height;
}
