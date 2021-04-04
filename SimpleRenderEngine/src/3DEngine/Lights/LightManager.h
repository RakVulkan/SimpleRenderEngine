#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

namespace RenderEngine {

	class LightManager 
	{
	public:
		LightManager();

		void bindLightingUniforms(Shader* inShader);
		void bindStaticLightingUniforms(Shader* inShader);

		void addDirectionalLight(DirectionalLight& inDirectionalLight);
		void addPointLight(PointLight& inPointLight);
		void addSpotLight(SpotLight& inSpotLight);

		// Control functions for directional lights
		void setDirectionalLightDirection(unsigned int inIndex, const glm::vec3& inDir);

		// Control functions for point lights
		void setPointLightPosition(unsigned int inIndex, const glm::vec3& inPos);

		// Control functions for spot lights
		void setSpotLightPosition(unsigned int inIndex, const glm::vec3& inPos);
		void setSpotLightDirection(unsigned int inIndex, const glm::vec3& inDir);		
		const glm::vec3& getDirectionalLightDirection(unsigned int inIndex);

	private:
		void init();		
		std::vector<DirectionalLight> mDirectionalLights;
		std::vector<PointLight> mPointLights;
		std::vector<SpotLight> mSpotLights;
	};
}
