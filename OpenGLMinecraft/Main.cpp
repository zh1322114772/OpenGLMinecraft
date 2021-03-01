#include "Easy3D.hpp"

int main(void) 
{
	int x = 1000;
	int y = 700;
	renderer::Easy3D::setGameWidnow("Minecraft OpenGL", x, y);

	renderer::Easy3D::showFPS(true);

	renderer::Easy3D::start();
}