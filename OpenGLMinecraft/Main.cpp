#include "Renderer.hpp"
#include "CLR_World3D.hpp"
#include "CLR_Loading.hpp"
#include "CFG_ControllerIDs.hpp"
#include <iostream>
#include <stdexcept>

int main(void) 
{

	try {
		renderer::Easy3D::setGameWidnow("Minecraft OpenGL", 1024, 768);

		//init controllers
		game::config::ControllerIDs::Loading = renderer::Easy3D::addController(new renderer::controllers::Loading());
		game::config::ControllerIDs::World3D = renderer::Easy3D::addController(new renderer::controllers::World3D());


		//set init controller
		renderer::Easy3D::setContorller(game::config::ControllerIDs::Loading);

		//start!! :)
		renderer::Easy3D::showFPS(true);
		renderer::Easy3D::start();
	}
	catch (std::runtime_error e) 
	{
		std::cout << e.what() << std::endl;
	}
}