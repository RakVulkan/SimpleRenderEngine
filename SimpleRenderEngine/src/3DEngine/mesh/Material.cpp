#include "pch.h"
#include "Material.h"

#include <Platform/Window.h>

namespace RenderEngine {

	Material::Material(Texture *albedoMap, Texture *normalMap, Texture *metallicMap, Texture *roughnessMap, Texture *ambientOcclusionMap, Texture *displacementMap)
		: mAlbedoMap(albedoMap)
		, mNormalMap(normalMap)
		, mMetallicMap(metallicMap)
		, mRoughnessMap(roughnessMap)
		, mAmbientOcclusionMap(ambientOcclusionMap)
	{
	}

	void Material::BindMaterialInformation(Shader *shader) const 
	{
		int currentTextureUnit = 4;

		shader->setUniform("material.texture_albedo", currentTextureUnit);
		if (mAlbedoMap) {
			mAlbedoMap->bind(currentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultAlbedo()->bind(currentTextureUnit++);
		}

		shader->setUniform("material.texture_normal", currentTextureUnit);
		if (mNormalMap) {
			mNormalMap->bind(currentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultNormal()->bind(currentTextureUnit++);
		}

		shader->setUniform("material.texture_metallic", currentTextureUnit);
		if (mMetallicMap) {
			mMetallicMap->bind(currentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultMetallic()->bind(currentTextureUnit++);
		}

		shader->setUniform("material.texture_roughness", currentTextureUnit);
		if (mRoughnessMap) {
			mRoughnessMap->bind(currentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultRoughness()->bind(currentTextureUnit++);
		}

		shader->setUniform("material.texture_ao", currentTextureUnit);
		if (mAmbientOcclusionMap) {
			mAmbientOcclusionMap->bind(currentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultAO()->bind(currentTextureUnit++);
		}

	}
}
