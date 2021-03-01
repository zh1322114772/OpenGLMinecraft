#pragma once
#include "GLWrapper.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include "Types.hpp"

namespace renderer 
{



	class Easy3D 
	{
	private:
		static GLFWwindow* windowHandle;
		static int windowHeight;
		static int windowWidth;
		static Scene* currentScene;
		static const char* title;
		static bool printFPS;

		/**
		* glfw callback functions, for details see glfw3.h
		*/
		static void mousePosChangedCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseEnterCallback(GLFWwindow* window, int message);
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
		static void setGameWidnow(const char* windowTitle, const int& width, const int& height);
		
		/// <summary>
		/// set new Scene to easy3D
		/// </summary>
		/// <param name="s"></param>
		static void setScene(Scene* s);

		/// <summary>
		/// show current fps
		/// </summary>
		/// <param name="b">either true or false</param>
		static void showFPS(bool b);

		/// <summary>
		/// run game loop
		/// </summary>
		static void start();
	};





}
