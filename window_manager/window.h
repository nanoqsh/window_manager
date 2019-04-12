#pragma once

#include "window_manager.h"
#include <glm/vec3.hpp>


class window
{
private:
	window(
		unsigned id,
		int x_pos,
		int y_pos,
		unsigned z_index,
		int width,
		int height,
		bool is_active,
		glm::vec3 bg_color
		);

public:
	~window();

	void set_position(int x, int y);
	void set_z_index(unsigned index);
	void set_active(bool state);
	bool get_active_state() const;
	void set_size(int width, int height);
	unsigned get_id() const;

	int get_x() const;
	int get_y() const;
	unsigned get_z_index() const;
	int get_width() const;
	int get_height() const;

	void set_bg_color(const glm::vec3 & color);
	const glm::vec3 & get_bg_color() const;

private:
	unsigned id;
	int x_pos;
	int y_pos;
	unsigned z_index;
	int width;
	int height;
	bool is_active;
	glm::vec3 bg_color;

	friend class window_manager;
};
