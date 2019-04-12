#include "game.h"
#include "game_functions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


glm::mat4x4 make_matrix(int width, int height)
{
	float mat[16] =
	{
		2 / float(width), 0.f, 0.f, 0.f,
		0, -2 / float(height), 0.f, 0.f,
		0.f, 0.f, 1.f / window_manager::MAX_Z, 0.f,
		-1.0f, 1.0f, 0.f, 1.f
	};

	return glm::make_mat4x4(mat);
}


game::game(const std::string & name, int width, int height, glm::vec3 bg_color):
	name(name),
	bg_color(bg_color),
	window(create_window(name, width, height), glfwDestroyWindow),
	shader(nullptr),
	renderer(nullptr),
	projection(make_matrix(width, height)),
	wm(nullptr)
{
	glew_init(width, height);

	shader = std::make_shared<shader_program>(
		"shaders/defVS.glsl",
		"shaders/defFS.glsl"
		);

	renderer = std::make_unique<window_renderer>(shader);

	bind_projection();


	glfwSetWindowUserPointer(window.get(), this);

	glEnable(GL_DEPTH_TEST);


	glfwSetKeyCallback(window.get(), [](GLFWwindow* w, int key, int scancode, int action, int mode)
	{
		game * self = static_cast<game *>(glfwGetWindowUserPointer(w));
		self->on_key(key, scancode, action, mode);
	});


	glfwSetWindowSizeCallback(window.get(), [](GLFWwindow* w, int width, int height)
	{
		game * self = static_cast<game *>(glfwGetWindowUserPointer(w));
		self->on_window_size(width, height);
	});
}


void game::on_key(int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window.get(), GL_TRUE);
}


void game::on_window_size(int width, int height)
{
	glViewport(0, 0, width, height);

	projection = make_matrix(width, height);

	bind_projection();
}


void game::use_window_manager(std::shared_ptr<window_manager> wm)
{
	this->wm = wm;
}


game::~game()
{
	glfwTerminate();
}


void game::run()
{
	while (!glfwWindowShouldClose(window.get()))
	{
		glfwPollEvents();
		this->update();
		glfwSwapBuffers(window.get());
	}
}


void game::update()
{
	using win_t = ::window;

	glClearColor(bg_color.r, bg_color.g, bg_color.g, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (wm == nullptr)
	{
		std::cerr << "wm not found!\n";
		return;
	}

	for (auto & pair : *wm)
		renderer->draw_window(pair.second);
}


void game::bind_projection()
{
	shader->use();
	GLint projection_loc = shader->get_uniform_loc("projection");
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));
	glUseProgram(0);
}
