#include "GLWrapper.hpp"

int main(void) 
{
	GLFWwindow* window;
	int height = 1000;
	int width = 1000;
	wrapperGL::GLWrapper::init(window, "asd", height, width);
}