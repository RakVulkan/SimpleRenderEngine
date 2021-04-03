#pragma once

#include "Light.h"

namespace RenderEngine {

	class DynamicLightManager;

	class SpotLight : public Light {
		friend DynamicLightManager;
	public:
		SpotLight(float lightIntensity, glm::vec3 &&lightColour, float attenuationRadius, glm::vec3 &&pos, glm::vec3 &&dir, float cutOffAngle, float outerCutOffAngle);
	
		virtual void setupUniforms(Shader *shader, int currentLightIndex) override;
	private:
		float mAttenuationRadius;
		glm::vec3 mPosition, mDirection;
		float mCutOff, mOuterCutOff;
	};

}
