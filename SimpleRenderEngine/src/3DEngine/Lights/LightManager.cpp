#include "pch.h"
#include "LightManager.h"

namespace RenderEngine {

	LightManager::LightManager() 
	{
		init();
	}

	void LightManager::init() 
	{
		// Setup some lights for the scene
		DirectionalLight directionalLight1(2.0f, glm::vec3(3.25f, 3.25f, 3.25f), glm::vec3(-0.1f, -1.0f, -0.1f));
		directionalLight1.mIsStatic = true;
		addDirectionalLight(directionalLight1);

		SpotLight spotlight1(100.0f, glm::vec3(1.0f, 1.0f, 1.0f), 50.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
		spotlight1.mIsStatic = false;
		addSpotLight(spotlight1);

		PointLight pointLight1(10.0f, glm::vec3(1.0f, 0.0f, 1.0f), 30.0f, glm::vec3(120.0f, 84.0f, 122.0f));
		pointLight1.mIsStatic = false;
		addPointLight(pointLight1);

		PointLight pointLight2(10.0f, glm::vec3(1.0f, 0.25f, 0.0f), 30.0f, glm::vec3(120.0f, 77.0f, 100.0f));
		pointLight2.mIsStatic = true;
		addPointLight(pointLight2);
	}

	void LightManager::bindLightingUniforms(Shader* inShader) 
	{
		inShader->setUniform("numDirPointSpotLights", glm::ivec4(mDirectionalLights.size(), mPointLights.size(), mSpotLights.size(), 0));

		int lIndex = 0;
		for (auto iter = mDirectionalLights.begin(); iter != mDirectionalLights.end(); iter++) {
			iter->setupUniforms(inShader, lIndex++);
		}

		lIndex = 0;
		for (auto iter = mPointLights.begin(); iter != mPointLights.end(); iter++) {
			iter->setupUniforms(inShader, lIndex++);
		}

		lIndex = 0;
		for (auto iter = mSpotLights.begin(); iter != mSpotLights.end(); iter++) {
			iter->setupUniforms(inShader, lIndex++);
		}
	}

	void LightManager::bindStaticLightingUniforms(Shader* inShader) 
	{
		int lNumStaticDirLights = 0;
		for (auto iter = mDirectionalLights.begin(); iter != mDirectionalLights.end(); iter++) {
			if (iter->mIsStatic) 
				iter->setupUniforms(inShader, lNumStaticDirLights++);
		}

		int lNumStaticPointLights = 0;
		for (auto iter = mPointLights.begin(); iter != mPointLights.end(); iter++) {
			if (iter->mIsStatic)
				iter->setupUniforms(inShader, lNumStaticPointLights++);
		}

		int lNumStaticSpotLights = 0;
		for (auto iter = mSpotLights.begin(); iter != mSpotLights.end(); iter++) {
			if (iter->mIsStatic) 
				iter->setupUniforms(inShader, lNumStaticSpotLights++);
		}

		inShader->setUniform("numDirPointSpotLights", glm::ivec4(lNumStaticDirLights, lNumStaticPointLights, lNumStaticSpotLights, 0));
	}


	void LightManager::addDirectionalLight(DirectionalLight &directionalLight) {
		mDirectionalLights.push_back(directionalLight);
	}

	void LightManager::addPointLight(PointLight &pointLight) 
	{
		mPointLights.push_back(pointLight);
	}

	void LightManager::addSpotLight(SpotLight &spotLight) 
	{
		mSpotLights.push_back(spotLight);
	}


	// Setters
	void LightManager::setDirectionalLightDirection(unsigned int inIndex, const glm::vec3& inDir) 
	{
		mDirectionalLights[inIndex].mDirection = inDir;
	}

	void LightManager::setPointLightPosition(unsigned int inIndex, const glm::vec3& inPos) 
	{
		mPointLights[inIndex].mPosition = inPos;
	}

	void LightManager::setSpotLightPosition(unsigned int index, const glm::vec3 &pos) 
	{
		mSpotLights[index].mPosition = pos;
	}

	void LightManager::setSpotLightDirection(unsigned int inIndex, const glm::vec3& inDir) 
	{
		mSpotLights[inIndex].mDirection = inDir;
	}

	// Getters
	const glm::vec3& LightManager::getDirectionalLightDirection(unsigned int inIndex) 
	{
		return mDirectionalLights[inIndex].mDirection;
	}

}
