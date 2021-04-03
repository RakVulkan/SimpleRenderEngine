#include "pch.h"
#include "Light.h"

namespace RenderEngine {

	Light::Light(float lightIntensity, glm::vec3 &lightColour) 
		: mIntensity(lightIntensity)
		, mLightColour(lightColour)
		, mIsStatic(false) 
	{
	}
}
