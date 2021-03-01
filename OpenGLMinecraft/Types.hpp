namespace renderer
{
	/// <summary>
	/// define the Scene class
	/// </summary>
	class Scene 
	{
	public:

		/// <summary>
		/// this function will be called after loaded to Easy3D
		/// </summary>
		virtual void onEnable() = 0;

		/// <summary>
		/// this function will be called before the Scene is closed
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
		/// this function will be called when cursor position is changed
		/// </summary>
		virtual void mousePositionChangedCallback() = 0;

		/// <summary>
		/// this function will be called when the state of the mouse button is changed
		/// </summary>
		virtual void mouseButtonStatusChangedCallback() = 0;

		/// <summary>
		/// this function will be called when the state of key is changed
		/// </summary>
		virtual void keyboardStatusChangedCallback() = 0;
	};



}