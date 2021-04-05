#include "pch.h"
#include "Skybox.h"
#include <Utilities/Loaders/ShaderLoader.h>

namespace RenderEngine {

	// Takes list of skybox textures path and create the cubemap texture
	Skybox::Skybox(const std::vector<std::string>& inFilePaths) 
	{
		mSkyboxShader = ShaderLoader::loadShader(std::string("src/Shaders/Skybox.glsl"));

		CubemapSettings lSrgbCubeMapSettings;
		lSrgbCubeMapSettings.IsSRGB = true;
		mSkyboxCubemap = TextureLoader::loadCubemapTexture(inFilePaths[0], inFilePaths[1], inFilePaths[2], inFilePaths[3], inFilePaths[4], inFilePaths[5], &lSrgbCubeMapSettings);

		// Get the current OpenGL global state
		mGLState = GLState::getInstance();
	}

	Skybox::~Skybox()
	{
		if (mSkyboxShader) {
			delete mSkyboxShader;
			mSkyboxShader = nullptr;
		}
		if (mSkyboxCubemap) {
			delete mSkyboxCubemap;
			mSkyboxCubemap = nullptr;
		}
	}

	// Render the skybox
	void Skybox::Draw(ICamera* inCamera) 
	{
		mGLState->switchShader(mSkyboxShader);

		// Pass the texture to the shader
		mSkyboxCubemap->bind(0);
		mSkyboxShader->setUniform("skyboxCubemap", 0);

		mSkyboxShader->setUniform("view", inCamera->getViewMatrix());
		mSkyboxShader->setUniform("projection", inCamera->getProjectionMatrix());

		// Since the vertex shader is gonna make the depth value 1.0, and the default value in the depth buffer is 1.0 so this is needed to draw the sky  box
		mGLState->setDepthTest(true);
		mGLState->setFaceCull(true);
		mGLState->setCullFace(GL_FRONT);
		mGLState->setDepthFunc(GL_LEQUAL);
		
		mCubeObject.Draw();

		// set back the opengl state
		mGLState->setCullFace(GL_BACK);
		mGLState->setDepthFunc(GL_LESS);

		mSkyboxCubemap->unbind();
	}
}
