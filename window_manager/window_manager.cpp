#include "window_manager.h"

#include <iostream>
#include "window.h"
#include "game.h"


window_manager::window_manager():
	windows(),
	id_counter(0)
{
}


window_manager::~window_manager()
{
}


unsigned window_manager::create_window(
	int x,
	int y,
	int width,
	int height,
	unsigned z_index,
	glm::vec3 bg_color
	)
{
	unsigned id = id_counter;

	if (z_index >= window_manager::MAX_Z)
	{
		std::cerr << "z_index can't be more than " << (window_manager::MAX_Z - 1) << "\n";
		return 0;
	}

	window win(
		id,
		x,
		y,
		z_index,
		width,
		height,
		true,
		bg_color
		);

	auto res = windows.insert(std::make_pair(id, win));
	
	if (!res.second)
	{
		std::cerr << "window with id " << id << " already exists!\n";
		return 0;
	}

	id_counter++;
	return id;
}


void window_manager::delete_window(unsigned id)
{
	size_t res = windows.erase(id);

	if (res == 0)
		std::cerr << "window with id " << id << " not found\n";
}


window_manager::winmap::const_iterator window_manager::begin() const
{
	return windows.begin();
}


window_manager::winmap::const_iterator window_manager::end() const
{
	return windows.end();
}
