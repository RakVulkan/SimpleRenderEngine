#include "pch.h"
#include "PointLight.h"

namespace RenderEngine {

	PointLight::PointLight(float lightIntensity, glm::vec3 &&lightColour, float attenuationRadius, glm::vec3 &&pos)
		: Light(lightIntensity, lightColour)
		, mAttenuationRadius(attenuationRadius)
		, mPosition(pos) {}

	void PointLight::setupUniforms(Shader *shader, int currentLightIndex) {
		shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].position").c_str(), mPosition);
		shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].intensity").c_str(), mIntensity);
		shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), mLightColour);
		shader->setUniform(("pointLights[" + std::to_string(currentLightIndex) + "].attenuationRadius").c_str(), mAttenuationRadius);
	}
}
