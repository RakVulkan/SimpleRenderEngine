#include "pch.h"
#include "SpotLight.h"

namespace RenderEngine {

	SpotLight::SpotLight(float lightIntensity, glm::vec3 &&lightColour, float attenuationRadius, glm::vec3 &&pos, glm::vec3 &&dir, float cutOffAngle, float outerCutOffAngle)
		: Light(lightIntensity, lightColour)
		, mAttenuationRadius(attenuationRadius)
		, mPosition(pos), mDirection(dir)
		, mCutOff(cutOffAngle)
		, mOuterCutOff(outerCutOffAngle) {}

	void SpotLight::setupUniforms(Shader *shader, int currentLightIndex) {
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].position").c_str(), mPosition);
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].direction").c_str(), mDirection);
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].intensity").c_str(), mIntensity);
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), mLightColour);
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].attenuationRadius").c_str(), mAttenuationRadius);
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].cutOff").c_str(), mCutOff);
		shader->setUniform(("spotLights[" + std::to_string(currentLightIndex) + "].outerCutOff").c_str(), mOuterCutOff);
	}

}
