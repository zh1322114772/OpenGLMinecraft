#pragma once
#include "GLW_GLWrapper.hpp"
#include "GLW_GLShader.hpp"
#include "GLW_GlmHeaders.hpp"
#include <unordered_map>
#include "Render_Types.hpp"
#include <stdexcept>
#include <iostream>

namespace renderer 
{

	class Easy3D 
	{
	private:

		static char programStatus;

		// glfw window handle
		static GLFWwindow* windowHandle;

		//current window height
		static int windowHeight;

		//current window width
		static int windowWidth;

		//current controller that's in use
		static Controller* currentController;

		//total controller list
		static std::vector<Controller*> controllers;

		//window title
		static const char* title;

		//print fps flag
		static bool printFPS;

		//keyboard event
		static  KeyboardEvent keyboardEvent;

		//mouse event
		static MouseEvent mouseEvent;
		static glm::vec2 mousePosition;
		static glm::vec2 mousePositionOld;
		static glm::vec2 mouseOffsets;

		//mouse mode
		static bool mouseCenterMode;

		/**
		* glfw callback functions, for details see glfw3.h
		*/
		static void mousePosChangedCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseStatusChangedCallback(GLFWwindow* window, int buttonID, int action, int mods);
		static void frameBufferSizeChangedCallback(GLFWwindow* window, int width, int height);
		static void charInputCallback(GLFWwindow* window, unsigned int unicode);
		static void keyInputCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);
		static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	public:

		/// <summary>
		/// set game window
		/// </summary>
		/// <param name="windowTitle">game title</param>
		/// <param name="width">window width</param>
		/// <param name="height">window height</param>
		static void setGameWidnow(const char* windowTitle, const int width, const int height);
		
		/// <summary>
		/// set contorller
		/// </summary>
		/// <param name="id">controller id </param>
		static void setContorller(int id);

		/// <summary>
		/// add new contorller to easy3D
		/// </summary>
		/// <param name="c"></param>
		static int addController(Controller* c);

		/// <summary>
		/// show current fps
		/// </summary>
		/// <param name="b">either true or false</param>
		static void showFPS(bool b);

		/// <summary>
		/// set mouse to center mode
		/// </summary>
		/// <param name="b"></param>
		static void setMouseCenter(bool b);

		/// <summary>
		/// run game loop
		/// </summary>
		static void start();

		/// <summary>
		/// return current render area height
		/// </summary>
		/// <returns></returns>
		static int getRenderAreaHeight();

		/// <summary>
		/// return current render area width
		/// </summary>
		/// <returns></returns>
		static int getRenderAreaWidth();
	};

}
