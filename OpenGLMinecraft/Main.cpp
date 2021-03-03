#include "Renderer.hpp"
#include "World3D.hpp"
#include <iostream>
#include <stdexcept>
int main(void) 
{
	try {
		renderer::Easy3D::setGameWidnow("Minecraft OpenGL", 1024, 768);
		renderer::Easy3D::showFPS(true);
		int id = renderer::Easy3D::addController(new renderer::controllers::World3D());
		renderer::Easy3D::setContorller(id);

		renderer::Easy3D::start();
	}
	catch (std::runtime_error e) 
	{
		std::cout << e.what() << std::endl;
	}
}