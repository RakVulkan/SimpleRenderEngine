#pragma once

#include <3DEngine/Shader.h>

namespace RenderEngine {

	class Light {
	public:
		Light(float inLightIntensity, glm::vec3& inLightColour);

		virtual void setupUniforms(Shader* inShader, int inCurrentLightIndex) = 0;
	protected:
		float mIntensity;
		glm::vec3 mLightColour;

		bool mIsStatic; 
	};

}
