#include "Window.h"

namespace RenderEngine {

	// Static declarations	
	int Window::sWidth; 
	int Window::sHeight;

	Window::Window(const char* inWindowTitle, const int inWidth, const int inHeight)
	{
		mWindowTitle = inWindowTitle;
		sWidth = inWidth;
		sHeight = inHeight;

		if (!init()) {
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not initialize window class");
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}
	}

	Window::~Window() 
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::update() 
	{	
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << error << std::endl;
		}

		// Input handling
		gInputHandler.update();
	
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}

	void Window::clear() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::bind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool Window::closed() const 
	{
		return glfwWindowShouldClose(mWindow);
	}

	// Usefull for creating the output window based on primary montior's resolution 
	void Window::setFullscreenResolution() 
	{
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		sWidth = mode->width;
		sHeight = mode->height;
	}

	// Callback functions
	static void error_callback(int error, const char* description) 
	{
		std::cout << "Error:" << std::endl << description << std::endl;
	}

	static void window_resize_callback(GLFWwindow *inOutWindow, int inWidth, int inHeight) 
	{
		Window* lWindow = (Window*)glfwGetWindowUserPointer(inOutWindow);
		if (inWidth == 0 || inHeight == 0) {
			lWindow->sWidth = WINDOW_WIDTH;
			lWindow->sHeight = WINDOW_HEIGHT;
		}
		else {
			lWindow->sWidth = inWidth;
			lWindow->sHeight = inHeight;
		}
		glViewport(0, 0, lWindow->sWidth, lWindow->sHeight);
	}

	static void framebuffer_resize_callback(GLFWwindow *inOutWindow, const int inWidth, const int inHeight) 
	{
		glViewport(0, 0, inWidth, inHeight);
	}

	static void key_callback(GLFWwindow *inOutWindow, int inKey, int inScancode, int inAction, int inMods) 
	{		
		gInputHandler.keyCallback(inKey, inScancode, inAction);
	}

	static void mouse_button_callback(GLFWwindow* inWindow, int inButton, int inAction, int inMods) 
	{
		gInputHandler.mouseButtonCallback(inButton, inAction);
	}

	static void cursor_position_callback(GLFWwindow* inWindow, double inXpos, double inYpos) 
	{
		gInputHandler.cursorPositionCallback(inXpos, inYpos);
	}
	
	static void scroll_callback(GLFWwindow* inWindow, double inXoffset, double inYoffset) 
	{
		gInputHandler.scrollCallback(inXoffset, inYoffset);
	}

	static void GLAPIENTRY DebugMessageCallback(GLenum inSource, GLenum inType, GLuint inId, GLenum inSeverity, 
		GLsizei inLength, const GLchar* inMessage, const void* inUserParam) 
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(inType == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			inType, inSeverity, inMessage);
	}

	bool Window::init()
	{
		glewExperimental = true;

		if (!glfwInit()) {
			std::cout << "GLFW Failed To Initialize" << std::endl;
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not initialize the GLFW window");
			return false;
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		// Window hints
		glfwWindowHint(GLFW_DOUBLEBUFFER, true);

		// Create the window and OpenGL context
		if (FULLSCREEN_MODE) {
			setFullscreenResolution();
			mWindow = glfwCreateWindow(sWidth, sHeight, mWindowTitle, glfwGetPrimaryMonitor(), NULL);
		}
		else {
			mWindow = glfwCreateWindow(sWidth, sHeight, mWindowTitle, NULL, NULL);
		}

		if (!mWindow) {
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not create the GLFW window");
			std::cout << "GLFW Window Couldn't Be Created" << std::endl;
			return false;
		}

		double currMouseX, currMouseY;
		glfwGetCursorPos(mWindow, &currMouseX, &currMouseY);
		gInputHandler.setMousePos(currMouseX, currMouseY);

		// Set up contexts and callbacks
		glfwMakeContextCurrent(mWindow);
		glfwSetWindowUserPointer(mWindow, this);
		glfwSetErrorCallback(error_callback);
		glfwSetWindowSizeCallback(mWindow, window_resize_callback);
		glfwSetFramebufferSizeCallback(mWindow, framebuffer_resize_callback);
		glfwSetKeyCallback(mWindow, key_callback);
		glfwSetMouseButtonCallback(mWindow, mouse_button_callback);
		glfwSetCursorPosCallback(mWindow, cursor_position_callback);
		glfwSetScrollCallback(mWindow, scroll_callback);

		// Check to see if v-sync was enabled and act accordingly
		if (VSYNC) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		// Initialize GLEW (allows us to use newer versions of OpenGL)
		if (glewInit() != GLEW_OK) {
			std::cout << "Could not Initialize GLEW" << std::endl;
			Logger::getInstance().error("logged_files/window_creation.txt", "Window Initialization", "Could not initialize the GLEW");
			return 0;
		}
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		// Setup default OpenGL viewport
		glViewport(0, 0, sWidth, sHeight);

		// Everything was successful so return true
		return 1;
	}

}
