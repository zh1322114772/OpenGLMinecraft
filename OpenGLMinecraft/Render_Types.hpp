#pragma once
#include "GLW_GLHeaders.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace renderer
{

	/// <summary>
	/// mouse event send from easy3D
	/// </summary>
	struct MouseEvent
	{
		bool buttonPressed[GLFW_MOUSE_BUTTON_LAST] = { false };
		glm::vec2 mousePosition;
		glm::vec2 mouseScroll;

	};

	/// <summary>
	/// keyboard event send from easy3D
	/// </summary>
	struct KeyboardEvent
	{
		bool keyPressed[GLFW_KEY_LAST] = { false };
		std::vector<unsigned int> charInputBuffer;
		int modKey = 0;
	};



	/// <summary>
	/// This class receives all callbacks from easy3D
	/// </summary>
	class Controller
	{
	public:
		
		/// <summary>
		/// this function will be called after Easy3D::start() is invoked
		/// </summary>
		virtual void onStart() = 0;

		/// <summary>
		/// this function will be called before Easy3D exits
		/// </summary>
		virtual void onExit() = 0;

		/// <summary>
		/// this function will be called after the controller is enabled
		/// </summary>
		virtual void onEnable() = 0;

		/// <summary>
		/// this function will be called before the controller is disabled
		/// </summary>
		virtual void onDisable() = 0;

		/// <summary>
		/// this function will be called when the game loop is ready to render a new frame
		/// </summary>
		/// <param name="delta_t">time interval between frames, in million second</param>
		virtual void onDraw(const double& delta_t) = 0;

		/// <summary>
		/// this function will be called when screen size is changed
		/// </summary>
		/// <param name="newWidth">new width</param>
		/// <param name="newHeight">new height</param>
		virtual void renderAreaChangedCallback(const int& newWidth, const int& newHeight) = 0;

		/// <summary>
		/// this function will be called before onDraw() is called to handle inputs
		/// </summary>
		/// <param name="keyboardEvent">keyboard event sent from Easy3D</param>
		/// <param name="mouseEvent">mouse event sent from Easy3D</param>
		/// <param name="delta_t">interval between two frames </param>
		virtual void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) = 0;

	};



}