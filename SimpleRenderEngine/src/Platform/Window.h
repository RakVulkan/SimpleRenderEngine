#pragma once
#include "pch.h"
#include "../Utilities/Logger.h"
#include <Platform/InputHandler.h>

namespace RenderEngine {

	static InputHandler gInputHandler;

	class Window {
	public:
		Window(const char* inWindowTitle, const int inWidth, const int inHeight);
		~Window();

		void update();
		bool closed() const;
		static void clear();
		static void bind();

		inline int getWidth() const { return sWidth; }
		inline int getHeight() const { return sHeight; }

	private:
		bool init();

		void setFullscreenResolution();

		// Callback Functions
		static friend void error_callback(int error, const char* description);
		static friend void window_resize_callback(GLFWwindow *inWindow, const int inWidth, const int inHeight);
		static friend void framebuffer_resize_callback(GLFWwindow *window, int width, int height);
		static friend void key_callback(GLFWwindow* inWindow, int inKey, int inScancode, int inAction, int inMods);
		static friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);		
		
	private:
		const char *mWindowTitle;
		GLFWwindow *mWindow;
		static int sWidth;  
		static int sHeight;
	};

}
