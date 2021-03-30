#pragma once
#include <pch.h>

constexpr int MAX_KEYS = 1024;
constexpr int MAX_BUTTONS = 3;

namespace RenderEngine {

	class InputHandler {
	public:
		InputHandler();
		~InputHandler();

		void update();

		static bool isKeyPressed(unsigned int keycode);
		static float getKeyPressed(unsigned int inKeycode);
		static bool isMouseButtonPressed(unsigned int code);
		static bool getButton(int keyCode);
		static bool getButtonDown(int keyCode);

		void keyCallback(int key, int scancode, int action, int mods);
		void mouseButtonCallback(int button, int action, int mods);
		void cursorPositionCallback(double xpos, double ypos);
		void scrollCallback(double xoffset, double yoffset);	

		// Getters and setters
		static inline double getMouseX() { return sMouseX; }
		static inline double getMouseY() { return sMouseY; }
		static inline double getMouseXDelta() { return sMouseXDelta; }
		static inline double getMouseYDelta() { return sMouseYDelta; }
		static inline double getScrollXDelta() { return sScrollXDelta; }
		static inline double getScrollYDelta() { return sScrollYDelta; }
		static inline void getMousePosition(double &x, double &y) { x = sMouseX; y = sMouseY; }

		static inline void setMouseX(double value) { sMouseX = value; }
		static inline void setMouseY(double value) { sMouseY = value; }
		static inline void setMousePos(double xPos, double yPos) { sMouseX = xPos, sMouseY = yPos; }

	private:
		static bool sKeys[MAX_KEYS];
		static float sKeyPressed[MAX_KEYS];
		static bool sButtons[MAX_BUTTONS];
		static double sMouseX;  
		static double sMouseY; 
		static double sMouseXDelta;
		static double sMouseYDelta;
		static double sScrollXDelta;
		static double sScrollYDelta;
	};

}
