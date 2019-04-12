#include "game_functions.h"

#include <iostream>


GLFWwindow * create_window(std::string name, int width, int height)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow * window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window!\n";
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return window;
}


void glew_init(int width, int height)
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to init GLEW!\n";
		exit(2);
	}

	glViewport(0, 0, width, height);
}
