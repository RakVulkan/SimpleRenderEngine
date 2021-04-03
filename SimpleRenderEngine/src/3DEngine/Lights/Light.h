#pragma once

#include <3DEngine/Shader.h>

namespace RenderEngine {

	class Light {
	public:
		Light(float lightIntensity, glm::vec3 &lightColour);

		virtual void setupUniforms(Shader *shader, int currentLightIndex) = 0;
	protected:
		float mIntensity;
		glm::vec3 mLightColour;

		bool mIsStatic; // Should be true if the light will never have any of it's properties changed
	};

}
