#include "pch.h"
#include "Camera.h"
#include <Platform/InputHandler.h>

namespace RenderEngine {

	Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = -90.0f, float pitch = 0.0f)
		: mFront(glm::vec3(0.0f, 0.0f, -1.0f))
		, mCurrentMovementSpeed(Camera_MAX_SPEED)
		, mCurrentFOV(Camera_MAX_FOV)
	{
		mPosition = position;
		mWorldUp = up;
		mUp = up;
		mCurrentYaw = yaw;
		mCurrentPitch = pitch;
		updateCameraVectors();		
	}

	Camera::Camera(float inXPos, float inYPos, float inZPos, float inXUp, float inYUp, float inZUp, float inYaw = -90.0f, float inPitch = 0.0f)
		: mFront(glm::vec3(0.0f, 0.0f, -1.0f))
		, mCurrentMovementSpeed(Camera_MAX_SPEED)
		, mCurrentFOV(Camera_MAX_FOV)
	{
		mPosition = glm::vec3(inXPos, inYPos, inZPos);
		mWorldUp = glm::vec3(inXUp, inYUp, inZUp);
		mCurrentYaw = inYaw;
		mCurrentPitch = inPitch;
		updateCameraVectors();
	}

	glm::mat4 Camera::getViewMatrix() 
	{
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	glm::mat4 Camera::getProjectionMatrix() 
	{
		return glm::perspective(glm::radians(mCurrentFOV), (float)Window::getRenderResolutionWidth() / (float)Window::getRenderResolutionHeight(), NEAR_PLANE, FAR_PLANE);
	}

	void Camera::processInput(float inDeltaTime) 
	{		 
		// Movement speed
		if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
			mCurrentMovementSpeed = Camera_MAX_SPEED * 4.0f;
		else if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_ALT))
			mCurrentMovementSpeed = Camera_MAX_SPEED / 4.0f;
		else
			mCurrentMovementSpeed = Camera_MAX_SPEED;

		// Camera movement
		glm::vec3 lDirection = glm::vec3(0.0f);
		if (InputHandler::isKeyPressed(GLFW_KEY_W))
			lDirection += mFront;
		if (InputHandler::isKeyPressed(GLFW_KEY_S))
			lDirection -= mFront;
		if (InputHandler::isKeyPressed(GLFW_KEY_A))
			lDirection -= mRight;
		if (InputHandler::isKeyPressed(GLFW_KEY_D))
			lDirection += mRight;
		if (InputHandler::isKeyPressed(GLFW_KEY_SPACE))
			lDirection += mWorldUp;
		if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
			lDirection -= mWorldUp;

		processCameraMovement(lDirection, inDeltaTime);


		// Camera FOV
		float scrollDelta = glm::clamp((float)InputHandler::getScrollYDelta() * 4.0f, -4.0f, 4.0f);
		processCameraFOV(scrollDelta);

		// Camera rotation
		float mouseXDelta = (float)(InputHandler::getMouseXDelta()) * Camera_ROTATION_SENSITIVITY;
		float mouseYDelta = (float)(-InputHandler::getMouseYDelta()) * Camera_ROTATION_SENSITIVITY;
		processCameraRotation(mouseXDelta, mouseYDelta, true);
	}

	void Camera::invertPitch()
	{
		mCurrentPitch = -mCurrentPitch;
		updateCameraVectors();
	}

	void Camera::processCameraMovement(glm::vec3& inDirection, float inDeltaTime) 
	{
		float velocity = mCurrentMovementSpeed * inDeltaTime;
		mPosition += inDirection * velocity;
	}

	void Camera::processCameraRotation(double inXOffset, double inYOffset, GLboolean inConstrainPitch = true) 
	{
		mCurrentYaw += static_cast<float>(inXOffset);
		mCurrentPitch += static_cast<float>(inYOffset);

		// Constrain the pitch
		if (inConstrainPitch) {
			if (mCurrentPitch > 89.0f) {
				mCurrentPitch = 89.0f;
			}
			else if (mCurrentPitch < -89.0f) {
				mCurrentPitch = -89.0f;
			}
		}

		updateCameraVectors();
	}

	void Camera::processCameraFOV(double inOffset) 
	{
		if (inOffset != 0.0 && mCurrentFOV >= 1.0 && mCurrentFOV <= Camera_MAX_FOV) {
			mCurrentFOV -= static_cast<float>(inOffset);
		}
		if (mCurrentFOV < 1.0f) {
			mCurrentFOV = 1.0f;
		}
		else if (mCurrentFOV > Camera_MAX_FOV) {
			mCurrentFOV = Camera_MAX_FOV;
		}
	}

	void Camera::updateCameraVectors() 
	{
		mFront.x = cos(glm::radians(mCurrentYaw)) * cos(glm::radians(mCurrentPitch));
		mFront.y = sin(glm::radians(mCurrentPitch));
		mFront.z = sin(glm::radians(mCurrentYaw)) * cos(glm::radians(mCurrentPitch));
		mFront = glm::normalize(mFront);

		mRight = glm::normalize(glm::cross(mFront, mWorldUp));
		mUp = glm::normalize(glm::cross(mRight, mFront));
	}
}
