#include "Renderer.hpp"
#include "CLR_World3D.hpp"
#include "CLR_Loading.hpp"
#include "GLB_ControllerIDs.hpp"
#include <iostream>
#include <stdexcept>
#include "WorldTickClock.hpp"
#include "TKB_InputGetter.hpp"

int main(void) 
{

	try {
		renderer::Easy3D::setGameWidnow("Minecraft OpenGL", 1024, 768);

		//game tick clock
		tickerable::WorldTickClock clock(50);


		//init controllers
		global::Controllers::Loading = renderer::Easy3D::addController(new renderer::controllers::Loading());
		global::Controllers::World3D = renderer::Easy3D::addController(new renderer::controllers::World3D(&clock));

		//set init controller
		renderer::Easy3D::setContorller(global::Controllers::Loading);

		//start!! :)
		renderer::Easy3D::showFPS(true);
		renderer::Easy3D::start();
	}
	catch (std::runtime_error e) 
	{
		std::cout << e.what() << std::endl;
	}
}