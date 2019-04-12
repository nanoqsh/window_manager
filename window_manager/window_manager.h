#pragma once

#include <map>
#include <memory>
#include <glm/vec3.hpp>


class window;

class window_manager
{
public:
	window_manager();
	window_manager(const window_manager & other) = delete;
	window_manager & operator=(const window_manager & other) = delete;
	~window_manager();

	unsigned create_window(
		int x,
		int y,
		int width,
		int height,
		unsigned z_index,
		glm::vec3 bg_color = glm::vec3(0.0f, 0.0f, 0.0f)
		);

	using winmap = std::map<unsigned, window>;

	void delete_window(unsigned id);
	winmap::const_iterator begin() const;
	winmap::const_iterator end() const;

	static const int MAX_Z = 1000;

private:
	winmap windows;
	unsigned id_counter;

};
