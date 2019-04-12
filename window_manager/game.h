#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "shader_program.h"
#include "window_renderer.h"
#include "window_manager.h"


class game
{
public:
	game(const std::string & name, int width, int height, glm::vec3 bg_color);
	game(const game & other) = delete;
	game & operator=(const game & other) = delete;
	~game();

	void run();
	void on_key(int key, int scancode, int action, int mode);
	void on_window_size(int width, int height);

	void use_window_manager(std::shared_ptr<window_manager> wm);

private:
	void update();
	void bind_projection();

	std::string name;
	glm::vec3 bg_color;
	std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window;
	std::shared_ptr<shader_program> shader;

	std::unique_ptr<window_renderer> renderer;
	glm::mat4x4 projection;

	std::shared_ptr<window_manager> wm;

};
