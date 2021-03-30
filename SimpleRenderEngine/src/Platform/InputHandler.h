#pragma once
#include <pch.h>

constexpr int MAX_KEYS = 1024;
constexpr int MAX_BUTTONS = 3;

namespace RenderEngine {

	class InputHandler 
	{
	public:
		InputHandler();
		~InputHandler();

		void update();

		static bool isKeyPressed(unsigned int inKeycode);
		static float getKeyPressed(unsigned int inKeycode);
		static bool isMouseButtonPressed(unsigned int inCode);
		static bool getButton(int inKeycode);
		static bool getButtonDown(int inKeycode);

		void keyCallback(int inKey, int inScancode, int inAction, int inMods);
		void mouseButtonCallback(int inButton, int inAction, int inMods);
		void cursorPositionCallback(double inXpos, double inYpos);
		void scrollCallback(double inXoffset, double inYoffset);	

		// Getters and setters
		inline double getMouseX() const { return sMouseX; }
		inline double getMouseY() const { return sMouseY; }
		inline double getMouseXDelta() const { return sMouseXDelta; }
		inline double getMouseYDelta() const { return sMouseYDelta; }
		inline double getScrollXDelta() const { return sScrollXDelta; }
		inline double getScrollYDelta() const { return sScrollYDelta; }
		inline void getMousePosition(double& x, double& y) const { x = sMouseX; y = sMouseY; }

		inline void setMouseX(double value) const { sMouseX = value; }
		inline void setMouseY(double value) const { sMouseY = value; }
		inline void setMousePos(double xPos, double yPos) const { sMouseX = xPos, sMouseY = yPos; }

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
