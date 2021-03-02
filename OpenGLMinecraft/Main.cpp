#include "Easy3D.hpp"

int main(void) 
{

	renderer::Easy3D::setGameWidnow("Minecraft OpenGL", 1024, 768);
	renderer::Easy3D::showFPS(true);

	renderer::Easy3D::start();
}