#include "pch.h"
#include "Renderer.h"

namespace RenderEngine
{
	Renderer::Renderer(Scene3D* inScene) 
		: mActiveScene(inScene)
		, mPbrRenderPass(inScene, false)
	{
		mGLState = GLState::getInstance();
	}

	void Renderer::init() 
	{
		// State that should never change
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void Renderer::render() 
	{	
		mPbrRenderPass.RunPbrRenderPass(mActiveScene->getCamera());	
	}
}
