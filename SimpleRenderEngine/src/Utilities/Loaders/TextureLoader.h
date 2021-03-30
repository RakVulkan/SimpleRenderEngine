#pragma once

#include <pch.h>
#include <3DEngine/Texture/Texture.h>
#include <3DEngine/Texture/Cubemap.h>

namespace RenderEngine {

	class TextureLoader 
	{
	 public:
		static Texture* load2DTexture(const std::string& inPath, TextureSettings* inSettings = nullptr);
		static Cubemap* loadCubemapTexture(const std::string& inRight, const std::string& inLeft, const std::string& inTop, 
			const std::string& inBottom, const std::string& inBack, const std::string& inFront, CubemapSettings* inSettings = nullptr);

	 private:
		static std::unordered_map<std::string, Texture*> mTextureCache;
	};
}
