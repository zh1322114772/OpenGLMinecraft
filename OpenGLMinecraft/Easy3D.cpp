#include "Easy3D.hpp"
#include <iostream>
namespace renderer
{

	/// <summary>
	/// static variables
	/// </summary>
	GLFWwindow* Easy3D::windowHandle = nullptr;
	int Easy3D::windowHeight = -1;
	int Easy3D::windowWidth = -1;
	Scene* Easy3D::currentScene = nullptr;
	const char* Easy3D::title;
	bool Easy3D::printFPS = false;

	void Easy3D::mousePosChangedCallback(GLFWwindow* window, double xpos, double ypos) 
	{
	
	}

	void Easy3D::mouseEnterCallback(GLFWwindow* window, int message) 
	{
	
	}

	void Easy3D::mouseStatusChangedCallback(GLFWwindow* window, int buttonID, int action, int mods) 
	{
	
	}

	void Easy3D::frameBufferSizeChangedCallback(GLFWwindow* window, int width, int height) 
	{
		glViewport(0, 0, width, height);
		Easy3D::windowWidth = width;
		Easy3D::windowHeight = height;
		
	}

	void Easy3D::charInputCallback(GLFWwindow* window, unsigned int unicode) 
	{
	
	}

	void Easy3D::keyInputCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods) 
	{
	
	}

	void Easy3D::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) 
	{
	
	}

	void Easy3D::setGameWidnow(const char* windowTitle, const int& width, const int& height) 
	{
		//init window
		wrapperGL::GLWrapper::init(windowHandle, windowTitle, height, width);
		Easy3D::windowWidth = width;
		Easy3D::windowHeight = height;
		Easy3D::title = windowTitle;

		//set callbacks
		glfwSetFramebufferSizeCallback(windowHandle, Easy3D::frameBufferSizeChangedCallback);
		glfwSetCursorPosCallback(windowHandle, Easy3D::mousePosChangedCallback);
		glfwSetCursorEnterCallback(windowHandle, Easy3D::mouseEnterCallback);
		glfwSetMouseButtonCallback(windowHandle, Easy3D::mouseStatusChangedCallback);
		glfwSetCharCallback(windowHandle, Easy3D::charInputCallback);
		glfwSetKeyCallback(windowHandle, Easy3D::keyInputCallback);
		glfwSetScrollCallback(windowHandle, Easy3D::mouseScrollCallback);
	}

	void Easy3D::setScene(Scene* s) 
	{
		if (Easy3D::currentScene != nullptr) 
		{
			Easy3D::currentScene->onDisable();
			Easy3D::currentScene = s;
			Easy3D::currentScene->onEnable();
			Easy3D::currentScene->renderAreaChangedCallback(Easy3D::windowWidth, Easy3D::windowHeight);
		}
	}

	void Easy3D::showFPS(bool b) 
	{
		Easy3D::printFPS = b;
	}

	void Easy3D::start() 
	{
		glClearColor(0.2, 0.2, 0.2, 1.0);

		//delta t variables
		double currentTime;
		double currentTimeOld = glfwGetTime();
		double delta_t;

		//fps variables
		int frameCounter = 0;
		double oneSecond = 0;

		while (!glfwWindowShouldClose(windowHandle)) 
		{
			//compute delta t
			currentTime = glfwGetTime();
			delta_t = currentTime - currentTimeOld;
			currentTimeOld = currentTime;

			//draw content
			//Easy3D::currentScene->onDraw(delta_t);

			//show fps
			if (printFPS) 
			{
				if (oneSecond > 1.0) 
				{
					oneSecond = 0;
					glfwSetWindowTitle(Easy3D::windowHandle, (std::string(Easy3D::title) + " -FPS: " + std::to_string(frameCounter)).c_str());
					frameCounter = 0;
				}
				oneSecond += delta_t;
				frameCounter++;
			}

			//show content
			glfwSwapBuffers(windowHandle);
			glfwPollEvents();
		}
	}


}