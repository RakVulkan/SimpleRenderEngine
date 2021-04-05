#include "pch.h"
#include "SpotLight.h"

namespace RenderEngine {

	SpotLight::SpotLight(float inLightIntensity, glm::vec3&& inLightColour, float inAttenuationRadius,
		glm::vec3&& inPos, glm::vec3&& inDir, float inCutOffAngle, float inOuterCutOffAngle)
		: Light(inLightIntensity, inLightColour)
		, mAttenuationRadius(inAttenuationRadius)
		, mPosition(inPos)
		, mDirection(inDir)
		, mCutOff(inCutOffAngle)
		, mOuterCutOff(inOuterCutOffAngle) 
	{
	}

	// Sets Uniforms for the Spot light properties
	void SpotLight::setupUniforms(Shader* inShader, int inCurrentLightIndex) 
	{
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].position").c_str(), mPosition);
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].direction").c_str(), mDirection);
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].intensity").c_str(), mIntensity);
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].lightColour").c_str(), mLightColour);
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].attenuationRadius").c_str(), mAttenuationRadius);
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].cutOff").c_str(), mCutOff);
		inShader->setUniform(("spotLights[" + std::to_string(inCurrentLightIndex) + "].outerCutOff").c_str(), mOuterCutOff);
	}
}
