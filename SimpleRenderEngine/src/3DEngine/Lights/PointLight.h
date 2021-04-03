#pragma once

#include "Light.h"

namespace RenderEngine {

	class DynamicLightManager;

	class PointLight : public Light {
		friend DynamicLightManager;
	public:
		PointLight(float lightIntensity, glm::vec3 &&lightColour, float attenuationRadius, glm::vec3 &&pos);

		virtual void setupUniforms(Shader *shader, int currentLightIndex) override;
	private:
		float mAttenuationRadius;
		glm::vec3 mPosition;
	};

}
