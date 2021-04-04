#include "pch.h"
#include "Material.h"
#include <Platform/Window.h>

namespace RenderEngine {

	Material::Material(Texture* inAlbedoMap, Texture* inNormalMap, Texture* inMetallicMap, 
		Texture* inRoughnessMap, Texture* inAmbientOcclusionMap)
		: mAlbedoMap(inAlbedoMap)
		, mNormalMap(inNormalMap)
		, mMetallicMap(inMetallicMap)
		, mRoughnessMap(inRoughnessMap)
		, mAmbientOcclusionMap(inAmbientOcclusionMap)
	{
	}

	Material::~Material()
	{
		if (mAlbedoMap) {
			delete mAlbedoMap;
			mAlbedoMap = nullptr;
		}

		if (mNormalMap) {
			delete mNormalMap;
			mNormalMap = nullptr;
		}

		if (mMetallicMap) {
			delete mMetallicMap;
			mMetallicMap = nullptr;
		}

		if (mRoughnessMap) {
			delete mRoughnessMap;
			mRoughnessMap = nullptr;
		}

		if (mAmbientOcclusionMap) {
			delete mAmbientOcclusionMap;
			mAmbientOcclusionMap = nullptr;
		}
	}

	void Material::BindMaterialInformation(Shader *shader) const 
	{
		int lCurrentTextureUnit = 4;

		shader->setUniform("material.texture_albedo", lCurrentTextureUnit);
		if (mAlbedoMap) {
			mAlbedoMap->bind(lCurrentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultAlbedo()->bind(lCurrentTextureUnit++);
		}

		shader->setUniform("material.texture_normal", lCurrentTextureUnit);
		if (mNormalMap) {
			mNormalMap->bind(lCurrentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultNormal()->bind(lCurrentTextureUnit++);
		}

		shader->setUniform("material.texture_metallic", lCurrentTextureUnit);
		if (mMetallicMap) {
			mMetallicMap->bind(lCurrentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultMetallic()->bind(lCurrentTextureUnit++);
		}

		shader->setUniform("material.texture_roughness", lCurrentTextureUnit);
		if (mRoughnessMap) {
			mRoughnessMap->bind(lCurrentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultRoughness()->bind(lCurrentTextureUnit++);
		}

		shader->setUniform("material.texture_ao", lCurrentTextureUnit);
		if (mAmbientOcclusionMap) {
			mAmbientOcclusionMap->bind(lCurrentTextureUnit++);
		}
		else {
			TextureLoader::getDefaultAO()->bind(lCurrentTextureUnit++);
		}
	}
}
