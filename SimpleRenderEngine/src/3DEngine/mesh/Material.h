#pragma once

#include <3DEngine/Shader.h>
#include <3DEngine/Texture/Texture.h>
#include <Utilities/Loaders/TextureLoader.h>

namespace RenderEngine {

	class Material {
	public:
		Material(Texture *albedoMap = nullptr, Texture *normalMap = nullptr, Texture *metallicMap = nullptr, Texture *roughnessMap = nullptr, 
				 Texture *ambientOcclusionMap = nullptr, Texture *displacementMap = nullptr);

		// Assumes the shader is already bound
		void BindMaterialInformation(Shader *shader) const;

		inline void setAlbedoMap(Texture *texture) { mAlbedoMap = texture; }
		inline void setNormalMap(Texture *texture) { mNormalMap = texture; }
		inline void setMetallicMap(Texture *texture) { mMetallicMap = texture; }
		inline void setRoughnessMap(Texture *texture) { mRoughnessMap = texture; }
		inline void setAmbientOcclusionMap(Texture *texture) { mAmbientOcclusionMap = texture; }		
		
	private:
		Texture *mAlbedoMap, *mNormalMap, *mMetallicMap, *mRoughnessMap, *mAmbientOcclusionMap;

	};

}
