#pragma once

#include "Light.h"

namespace RenderEngine {

	class LightManager;

	class SpotLight : public Light {
		friend LightManager;
	public:
		SpotLight(float inLightIntensity, glm::vec3&& inLightColour, float inAttenuationRadius, 
			glm::vec3&& inPos, glm::vec3&& inDir, float inCutOffAngle, float inOuterCutOffAngle);
	
		virtual void setupUniforms(Shader* inShader, int inCurrentLightIndex) override;
	private:
		float mAttenuationRadius;
		glm::vec3 mPosition, mDirection;
		float mCutOff, mOuterCutOff;
	};

}
