#include "pch.h"
#include "DynamicLightManager.h"

namespace RenderEngine {

	DynamicLightManager::DynamicLightManager() {
		init();
	}

	void DynamicLightManager::init() {
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

	void DynamicLightManager::bindLightingUniforms(Shader *shader) {
		shader->setUniform("numDirPointSpotLights", glm::ivec4(mDirectionalLights.size(), mPointLights.size(), mSpotLights.size(), 0));

		int i = 0;
		for (auto iter = mDirectionalLights.begin(); iter != mDirectionalLights.end(); iter++) {
			iter->setupUniforms(shader, i++);
		}

		i = 0;
		for (auto iter = mPointLights.begin(); iter != mPointLights.end(); iter++) {
			iter->setupUniforms(shader, i++);
		}

		i = 0;
		for (auto iter = mSpotLights.begin(); iter != mSpotLights.end(); iter++) {
			iter->setupUniforms(shader, i++);
		}
	}

	void DynamicLightManager::bindStaticLightingUniforms(Shader *shader) {
		int numStaticDirLights = 0;
		for (auto iter = mDirectionalLights.begin(); iter != mDirectionalLights.end(); iter++) {
			if (iter->mIsStatic) 
				iter->setupUniforms(shader, numStaticDirLights++);
		}

		int numStaticPointLights = 0;
		for (auto iter = mPointLights.begin(); iter != mPointLights.end(); iter++) {
			if (iter->mIsStatic)
				iter->setupUniforms(shader, numStaticPointLights++);
		}

		int numStaticSpotLights = 0;
		for (auto iter = mSpotLights.begin(); iter != mSpotLights.end(); iter++) {
			if (iter->mIsStatic) 
				iter->setupUniforms(shader, numStaticSpotLights++);
		}

		shader->setUniform("numDirPointSpotLights", glm::ivec4(numStaticDirLights, numStaticPointLights, numStaticSpotLights, 0));
	}


	void DynamicLightManager::addDirectionalLight(DirectionalLight &directionalLight) {
		mDirectionalLights.push_back(directionalLight);
	}

	void DynamicLightManager::addPointLight(PointLight &pointLight) {
		mPointLights.push_back(pointLight);
	}

	void DynamicLightManager::addSpotLight(SpotLight &spotLight) {
		mSpotLights.push_back(spotLight);
	}


	// Setters
	void DynamicLightManager::setDirectionalLightDirection(unsigned int index, const glm::vec3 &dir) {
		mDirectionalLights[index].mDirection = dir;
	}

	void DynamicLightManager::setPointLightPosition(unsigned int index, const glm::vec3 &pos) {
		mPointLights[index].mPosition = pos;
	}

	void DynamicLightManager::setSpotLightPosition(unsigned int index, const glm::vec3 &pos) {
		mSpotLights[index].mPosition = pos;
	}
	void DynamicLightManager::setSpotLightDirection(unsigned int index, const glm::vec3 &dir) {
		mSpotLights[index].mDirection = dir;
	}

	// Getters
	const glm::vec3& DynamicLightManager::getDirectionalLightDirection(unsigned int index) {
		return mDirectionalLights[index].mDirection;
	}

}
