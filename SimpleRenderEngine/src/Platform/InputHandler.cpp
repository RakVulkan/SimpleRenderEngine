#include "InputHandler.h"
#include "..\Utilities\Logger.h"

namespace RenderEngine {

	// Static declarations
	bool InputHandler::sKeys[MAX_KEYS];
	float InputHandler::sKeyPressed[MAX_KEYS];
	bool InputHandler::sButtons[MAX_BUTTONS];
	double InputHandler::sMouseX;
	double InputHandler::sMouseY; 
	double InputHandler::sMouseXDelta;
    double InputHandler::sMouseYDelta;
	double InputHandler::sScrollXDelta;
	double InputHandler::sScrollYDelta;

	InputHandler::InputHandler() 
	{
		sScrollXDelta = sScrollYDelta = 0;
		sMouseXDelta = sMouseYDelta = 0;

		memset(sKeys, 0, sizeof(bool) * MAX_KEYS);
		memset(sKeyPressed, 0, sizeof(float) * MAX_KEYS);
		memset(sButtons, 0, sizeof(bool) * MAX_BUTTONS);
	}

	InputHandler::~InputHandler() 
	{
	}

	void InputHandler::update() 
	{
		sMouseXDelta = sMouseYDelta = 0;
		sScrollXDelta = 0; sScrollYDelta = 0;	
	}

	bool InputHandler::isKeyPressed(unsigned int inKeycode) 
	{
		if (inKeycode < 0 || inKeycode >= MAX_KEYS) {
			Logger::getInstance().error("logged_files/input_errors.txt", "Input Check", "Key checked is out of bounds (ie not supported)");
			return false;
		}
		else {
			return sKeys[inKeycode];
		}
	}

	float InputHandler::getKeyPressed(unsigned int inKeycode) 
	{
		if (inKeycode < 0 || inKeycode >= MAX_KEYS) {
			Logger::getInstance().error("logged_files/input_errors.txt", "Input Check", "Key checked is out of bounds (ie not supported)");
			return 0.0f;
		}

		return sKeyPressed[inKeycode];
	}

	bool InputHandler::isMouseButtonPressed(unsigned int inCode) 
	{
		if (inCode < 0 || inCode >= MAX_BUTTONS) {
			Logger::getInstance().error("logged_files/input_errors.txt", "Input Check", "Mouse button checked is out of bounds (ie not supported)");
			return false;
		}

		return sButtons[inCode];
	}

	void InputHandler::keyCallback(int inKey, int inScancode, int inAction) 
	{
		sKeys[inKey] = inAction != GLFW_RELEASE;
		sKeyPressed[inKey] = sKeys[inKey];
	}

	void InputHandler::mouseButtonCallback(int inButton, int inAction) 
	{
		sButtons[inButton] = inAction != GLFW_RELEASE;
	}

	void InputHandler::cursorPositionCallback(double inXpos, double inYpos) 
	{
		sMouseXDelta = inXpos - sMouseX;
		sMouseYDelta = inYpos - sMouseY;
		sMouseX = inXpos;
		sMouseY = inYpos;
	}

	void InputHandler::scrollCallback(double inXoffset, double inYoffset) 
	{
		sScrollXDelta = inXoffset;
		sScrollYDelta = inYoffset;
	}
}

