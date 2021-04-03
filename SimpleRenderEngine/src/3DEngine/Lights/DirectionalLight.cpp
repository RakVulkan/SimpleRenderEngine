#include "pch.h"
#include "DirectionalLight.h"

namespace RenderEngine {

	DirectionalLight::DirectionalLight(float lightIntensity, glm::vec3 &&lightColour, glm::vec3 &&dir)
		: Light(lightIntensity, lightColour)
		, mDirection(dir) 
	{
	}

	void DirectionalLight::setupUniforms(Shader *shader, int currentLightIndex) {
		shader->setUniform(("dirLights[" + std::to_string(currentLightIndex) + "].direction").c_str(), mDirection);
		shader->setUniform(("dirLights[" + std::to_string(currentLightIndex) + "].intensity").c_str(), mIntensity);
		shader->setUniform(("dirLights[" + std::to_string(currentLightIndex) + "].lightColour").c_str(), mLightColour);
	}

}
