#include "game.h"

#include <glm/vec3.hpp>
#include <iostream>
#include <memory>

#include "window_manager.h"
#include "window.h"


int main()
{
	auto wm = std::make_shared<window_manager>();

	unsigned win1 = wm->create_window(
		50,							// x position
		50,							// y position
		500,						// width 
		200,						// height
		1,							// layer in range [0; 999]
		glm::vec3(0.1f, 0.3f, 0.5f)	// color
		);

	unsigned win2 = wm->create_window(100, 150, 600, 150, 0, glm::vec3(0.4f, 0.2f, 0.2f));
	unsigned win3 = wm->create_window(250, 200, 400, 200, 3, glm::vec3(0.2f, 0.4f, 0.2f));
	unsigned win4 = wm->create_window(700, 500, 100, 100, 999, glm::vec3(0.6f, 0.4f, 0.2f));


	glm::vec3 bg_color(0.2f, 0.2f, 0.4f);

	// create game object with title, width, height and background color
	game g("window manager", 1000, 600, bg_color);

	g.use_window_manager(wm);
	g.run();

	return 0;
}
