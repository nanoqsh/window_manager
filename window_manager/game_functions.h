#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>


GLFWwindow * create_window(std::string name, int width, int height);

void glew_init(int width, int height);
