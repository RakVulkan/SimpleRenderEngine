#pragma once

#include "Light.h"

namespace RenderEngine {
	
	// Forward declaration
	class LightManager;

	class DirectionalLight : public Light 
	{
		friend LightManager;
	public:
		DirectionalLight(float inLightIntensity, glm::vec3&& inLightColour, glm::vec3&& inDir);
		virtual void setupUniforms(Shader* inShader, int inCurrentLightIndex) override;

	private:
		glm::vec3 mDirection;
	};

}
