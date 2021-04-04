#pragma once

#include <3DEngine/Shader.h>
#include <3DEngine/Texture/Texture.h>
#include <Utilities/Loaders/TextureLoader.h>

namespace RenderEngine {

	class Material {
	public:
		Material(Texture* inAlbedoMap = nullptr, Texture* inNormalMap = nullptr, Texture* inMetallicMap = nullptr, 
			Texture* inRoughnessMap = nullptr, Texture* inAmbientOcclusionMap = nullptr);
		~Material();
		
		void BindMaterialInformation(Shader* inShader) const;

		inline void setAlbedoMap(Texture* inTexture) { mAlbedoMap = inTexture; }
		inline void setNormalMap(Texture* inTexture) { mNormalMap = inTexture; }
		inline void setMetallicMap(Texture* inTexture) { mMetallicMap = inTexture; }
		inline void setRoughnessMap(Texture* inTexture) { mRoughnessMap = inTexture; }
		inline void setAmbientOcclusionMap(Texture* inTexture) { mAmbientOcclusionMap = inTexture; }
		
	private:
		Texture *mAlbedoMap, *mNormalMap, *mMetallicMap, *mRoughnessMap, *mAmbientOcclusionMap;
	};
}
