#include "pch.h"
#include "PointLight.h"

namespace RenderEngine {

	PointLight::PointLight(float inLightIntensity, glm::vec3&& inLightColour, float inAttenuationRadius, glm::vec3&& inPos)
		: Light(inLightIntensity, inLightColour)
		, mAttenuationRadius(inAttenuationRadius)
		, mPosition(inPos) 
	{
	}

	// Sets Uniforms for the point light properties
	void PointLight::setupUniforms(Shader* inShader, int inCurrentLightIndex) 
	{
		inShader->setUniform(("pointLights[" + std::to_string(inCurrentLightIndex) + "].position").c_str(), mPosition);
		inShader->setUniform(("pointLights[" + std::to_string(inCurrentLightIndex) + "].intensity").c_str(), mIntensity);
		inShader->setUniform(("pointLights[" + std::to_string(inCurrentLightIndex) + "].lightColour").c_str(), mLightColour);
		inShader->setUniform(("pointLights[" + std::to_string(inCurrentLightIndex) + "].attenuationRadius").c_str(), mAttenuationRadius);
	}
}
