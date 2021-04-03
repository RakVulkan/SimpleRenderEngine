#include "pch.h"
#include "Camera.h"
#include <Platform/InputHandler.h>

namespace RenderEngine {

	Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f)
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

	Camera::Camera(float xPos, float yPos, float zPos, float xUp, float yUp, float zUp, float yaw = -90.0f, float pitch = 0.0f)
		: mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mCurrentMovementSpeed(Camera_MAX_SPEED), mCurrentFOV(Camera_MAX_FOV)
	{
		mPosition = glm::vec3(xPos, yPos, zPos);
		mWorldUp = glm::vec3(xUp, yUp, zUp);
		mCurrentYaw = yaw;
		mCurrentPitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	glm::mat4 Camera::getProjectionMatrix() {
		return glm::perspective(glm::radians(mCurrentFOV), (float)Window::getRenderResolutionWidth() / (float)Window::getRenderResolutionHeight(), NEAR_PLANE, FAR_PLANE);
	}

	void Camera::processInput(float deltaTime) {
		// Movement speed
		if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
			mCurrentMovementSpeed = Camera_MAX_SPEED * 4.0f;
		else if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_ALT))
			mCurrentMovementSpeed = Camera_MAX_SPEED / 4.0f;
		else
			mCurrentMovementSpeed = Camera_MAX_SPEED;

		// Camera movement
		glm::vec3 direction = glm::vec3(0.0f);
		if (InputHandler::isKeyPressed(GLFW_KEY_W))
			direction += mFront;
		if (InputHandler::isKeyPressed(GLFW_KEY_S))
			direction -= mFront;
		if (InputHandler::isKeyPressed(GLFW_KEY_A))
			direction -= mRight;
		if (InputHandler::isKeyPressed(GLFW_KEY_D))
			direction += mRight;
		if (InputHandler::isKeyPressed(GLFW_KEY_SPACE))
			direction += mWorldUp;
		if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
			direction -= mWorldUp;

		processCameraMovement(direction, deltaTime);


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

	void Camera::processCameraMovement(glm::vec3 &direction, float deltaTime) {
		float velocity = mCurrentMovementSpeed * deltaTime;
		mPosition += direction * velocity;
	}

	void Camera::processCameraRotation(double xOffset, double yOffset, GLboolean constrainPitch = true) {

		mCurrentYaw += (float)xOffset;
		mCurrentPitch += (float)yOffset;

		// Constrain the pitch
		if (constrainPitch) {
			if (mCurrentPitch > 89.0f) {
				mCurrentPitch = 89.0f;
			}
			else if (mCurrentPitch < -89.0f) {
				mCurrentPitch = -89.0f;
			}
		}

		updateCameraVectors();
	}

	void Camera::processCameraFOV(double offset) {
		if (offset != 0.0 && mCurrentFOV >= 1.0 && mCurrentFOV <= Camera_MAX_FOV) {
			mCurrentFOV -= static_cast<float>(offset);
		}
		if (mCurrentFOV < 1.0f) {
			mCurrentFOV = 1.0f;
		}
		else if (mCurrentFOV > Camera_MAX_FOV) {
			mCurrentFOV = Camera_MAX_FOV;
		}
	}

	void Camera::updateCameraVectors() {
		mFront.x = cos(glm::radians(mCurrentYaw)) * cos(glm::radians(mCurrentPitch));
		mFront.y = sin(glm::radians(mCurrentPitch));
		mFront.z = sin(glm::radians(mCurrentYaw)) * cos(glm::radians(mCurrentPitch));
		mFront = glm::normalize(mFront);

		mRight = glm::normalize(glm::cross(mFront, mWorldUp));
		mUp = glm::normalize(glm::cross(mRight, mFront));
	}

}
