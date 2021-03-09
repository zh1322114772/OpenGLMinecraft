#include "Renderer.hpp"

namespace renderer
{

	/// <summary>
	/// init static variables
	/// </summary>
	GLFWwindow* Easy3D::windowHandle = nullptr;
	int Easy3D::windowHeight = -1;
	int Easy3D::windowWidth = -1;
	Controller* Easy3D::currentController = nullptr;
	const char* Easy3D::title;
	bool Easy3D::printFPS = false;
	KeyboardEvent Easy3D::keyboardEvent;
	MouseEvent Easy3D::mouseEvent;
	glm::vec2 Easy3D::mousePosition;
	glm::vec2 Easy3D::mousePositionOld;
	glm::vec2 Easy3D::mouseOffsets;
	bool Easy3D::mouseCenterMode = false;
	std::vector<Controller*> Easy3D::controllers;
	char Easy3D::programStatus = 0;

	void Easy3D::mousePosChangedCallback(GLFWwindow* window, double xpos, double ypos)
	{
		static bool firstTimeActivate = true;

		if (firstTimeActivate) 
		{
			//first time callback, initialize mouse position old
			mousePositionOld.x = xpos;
			mousePositionOld.y = ypos;
			firstTimeActivate = false;
		}

		mousePosition.x = xpos;
		mousePosition.y = ypos;
	}

	void Easy3D::mouseStatusChangedCallback(GLFWwindow* window, int buttonID, int action, int mods)
	{
		mouseEvent.buttonPressed[buttonID] = action;
	}

	void Easy3D::frameBufferSizeChangedCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Easy3D::windowWidth = width;
		Easy3D::windowHeight = height;
		currentController->renderAreaChangedCallback(width, height);
	}

	void Easy3D::charInputCallback(GLFWwindow* window, unsigned int unicode)
	{
		keyboardEvent.charInputBuffer.push_back(unicode);
	}

	void Easy3D::keyInputCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
	{
		keyboardEvent.keyPressed[keyCode] = action;
		keyboardEvent.modKey = mods;

		//if esc is pressed
		if (keyboardEvent.keyPressed[GLFW_KEY_ESCAPE]) 
		{
			glfwSetWindowShouldClose(windowHandle, true);
		}
	}

	void Easy3D::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		mouseEvent.mouseScroll.x = xOffset;
		mouseEvent.mouseScroll.y = yOffset;
	}

	void Easy3D::setGameWidnow(const char* windowTitle, const int width, const int height)
	{
		//init window
		wrapperGL::GLWrapper::init(windowHandle, windowTitle, height, width);
		Easy3D::windowWidth = width;
		Easy3D::windowHeight = height;
		Easy3D::title = windowTitle;

		//set callbacks
		glfwSetFramebufferSizeCallback(windowHandle, Easy3D::frameBufferSizeChangedCallback);
		glfwSetCursorPosCallback(windowHandle, Easy3D::mousePosChangedCallback);
		glfwSetMouseButtonCallback(windowHandle, Easy3D::mouseStatusChangedCallback);
		glfwSetCharCallback(windowHandle, Easy3D::charInputCallback);
		glfwSetKeyCallback(windowHandle, Easy3D::keyInputCallback);
		glfwSetScrollCallback(windowHandle, Easy3D::mouseScrollCallback);

		//set default controller
		class SimpleController : public Controller
		{
		public:
			void onStart() override {}
			void onExit() override {}
			void onEnable() override {}
			void onDisable() override {}
			void onDraw(const double& delta_t) override {}
			void renderAreaChangedCallback(const int& newWidth, const int& newHeight) override {}
			void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) override {}
		};


		currentController = new SimpleController();
		Easy3D::controllers.push_back(currentController);

		//set program state
		Easy3D::programStatus = 1;
	}

	void Easy3D::setContorller(int id)
	{
		if (id < controllers.size())
		{
			currentController->onDisable();
			currentController = controllers[id];
			currentController->onEnable();
		}
		else
		{
			throw std::runtime_error("this id doesn't exist");
		}
	}

	int Easy3D::addController(Controller* c)
	{
		if (Easy3D::programStatus != 1)
		{
			//must be status 1
			throw std::runtime_error("please call this function before Start() and after setGameWindow()");
		}

		controllers.push_back(c);
		return controllers.size() - 1;
	}

	void Easy3D::showFPS(bool b)
	{
		Easy3D::printFPS = b;
	}

	void Easy3D::setMouseCenter(bool b) 
	{
		mouseCenterMode = b;
		wrapperGL::GLWrapper::setCursorCenter(windowHandle, b);

	}

	int Easy3D::getRenderAreaHeight() 
	{
		return windowHeight;
	}

	int Easy3D::getRenderAreaWidth() 
	{
		return windowWidth;
	}


	void Easy3D::start()
	{

		if (!Easy3D::programStatus)
		{
			//init before start
			throw std::runtime_error("please call setGameWindow() first");
		}

		//init all controllers
		for (auto c = controllers.begin(); c < controllers.end(); c++)
		{
			(*c)->onStart();
			(*c)->renderAreaChangedCallback(windowWidth, windowHeight);
		}

		Easy3D::programStatus++;
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

			//input process
			if (mouseCenterMode)
			{
				mouseEvent.mousePosition = mousePosition - mousePositionOld;
			}
			else
			{
				mouseEvent.mousePosition = mousePosition;
			}
			mousePositionOld = mousePosition;

			//controller input process
			Easy3D::currentController->inputProcess(keyboardEvent, mouseEvent, delta_t);
			keyboardEvent.charInputBuffer.clear();

			//draw content
			Easy3D::currentController->onDraw(delta_t);

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
			glfwPollEvents();
			glfwSwapBuffers(windowHandle);
		}

		//call onExits
		for (auto c = controllers.begin(); c < controllers.end(); c++)
		{
			(*c)->onDisable();
			(*c)->onExit();
			delete (*c);
		}

		glfwTerminate();
	}


}