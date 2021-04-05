#include "pch.h"
#include "DirectionalLight.h"

namespace RenderEngine {

	DirectionalLight::DirectionalLight(float inLightIntensity, glm::vec3&& inLightColour, glm::vec3&& inDir)
		: Light(inLightIntensity, inLightColour)
		, mDirection(inDir)
	{
	}

	// Sets uniforms for the directional light properties
	void DirectionalLight::setupUniforms(Shader* inShader, int inCurrentLightIndex) 
	{
		inShader->setUniform(("dirLights[" + std::to_string(inCurrentLightIndex) + "].direction").c_str(), mDirection);
		inShader->setUniform(("dirLights[" + std::to_string(inCurrentLightIndex) + "].intensity").c_str(), mIntensity);
		inShader->setUniform(("dirLights[" + std::to_string(inCurrentLightIndex) + "].lightColour").c_str(), mLightColour);
	}
}
