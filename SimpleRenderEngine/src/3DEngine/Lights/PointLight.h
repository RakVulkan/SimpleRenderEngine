#pragma once

#include "Light.h"

namespace RenderEngine {

	class LightManager;

	class PointLight : public Light {
		friend LightManager;
	public:
		PointLight(float inLightIntensity, glm::vec3&& inLightColour, float inAttenuationRadius, glm::vec3&& inPos);

		virtual void setupUniforms(Shader* inShader, int inCurrentLightIndex) override;
	private:
		float mAttenuationRadius;
		glm::vec3 mPosition;
	};

}
