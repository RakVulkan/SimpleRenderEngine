#pragma once

#include <3DEngine/texture/Cubemap.h>
#include <3DEngine/texture/Texture.h>

namespace RenderEngine {

	class TextureLoader {
	public:
		static void initializeDefaultTextures();
	
		static Texture* load2DTexture(std::string&& inPath, TextureSettings* inSettings = nullptr);
		static Cubemap* loadCubemapTexture(const std::string& inRight, const std::string& inLeft, 
			const std::string& inTop, const std::string& inBottom, const std::string& inBack, const std::string& inFront, CubemapSettings* inSettings = nullptr);


		inline static Texture* getDefaultAlbedo() { return sDefaultAlbedo; }
		inline static Texture* getDefaultNormal() { return sDefaultNormal; }
		inline static Texture* getDefaultMetallic() { return sDefaultMetallic; }
		inline static Texture* getDefaultRoughness() { return sDefaultRoughness; }
		inline static Texture* getDefaultAO() { return sDefaultAo; }

	private:
		static std::unordered_map<std::string, Texture*> sTextureCache;
		
		// Default Textures
		static Texture* sDefaultAlbedo;
		static Texture* sDefaultNormal;
		static Texture* sDefaultRoughness;
		static Texture*	sDefaultMetallic;
		static Texture* sDefaultAo;
	};

}
