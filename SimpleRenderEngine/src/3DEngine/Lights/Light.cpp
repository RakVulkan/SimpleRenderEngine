#include "pch.h"
#include "Light.h"

namespace RenderEngine {

	Light::Light(float inLightIntensity, glm::vec3& inLightColour) 
		: mIntensity(inLightIntensity)
		, mLightColour(inLightColour)
		, mIsStatic(false) 
	{
	}
}
