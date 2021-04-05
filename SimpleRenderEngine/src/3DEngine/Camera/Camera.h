#pragma once

#include <3DEngine/camera/ICamera.h>
#include <Platform/Window.h>

namespace RenderEngine {

	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UPWARDS,
		DOWNWARDS
	};

	class Camera : public ICamera {

#define Camera_MAX_SPEED 40.0f
#define Camera_ROTATION_SENSITIVITY 0.1f
#define Camera_MAX_FOV 90.0f

	public:
		Camera(glm::vec3 inPosition, glm::vec3 inUp, float inYaw, float inPitch);
		Camera(float inXPos, float inYPos, float inZPos, float inXUp, float inYUp, float inZUp, float inYaw, float inPitch);

		virtual glm::mat4 getViewMatrix() override;
		virtual glm::mat4 getProjectionMatrix() override;

		void processInput(float deltaTime);

		inline virtual void setPosition(const glm::vec3& inPosition) override { mPosition = inPosition; };
		virtual void invertPitch() override;

		// Getters
		inline virtual const glm::vec3& getPosition() const override { return mPosition; }
		inline virtual const glm::vec3& getFront() const override { return mFront; }
		inline virtual const glm::vec3& getUp() const override { return mUp; }

	private:
		void updateCameraVectors();
		void processCameraMovement(glm::vec3& inDirection, float inDeltaTime);
		void processCameraRotation(double inXOffset, double inYOffset, GLboolean inConstrainPitch);
		void processCameraFOV(double inYOffset);

	private:
		// Camera Attributes
		glm::vec3 mPosition;
		glm::vec3 mFront;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;

		// Euler Angles
		float mCurrentYaw;
		float mCurrentPitch;
		float mCurrentMovementSpeed;
		float mCurrentFOV;
	};
}
