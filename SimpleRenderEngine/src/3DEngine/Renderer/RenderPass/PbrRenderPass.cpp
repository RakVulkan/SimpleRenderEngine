#include "pch.h"
#include "PbrRenderPass.h"

#include <Utilities/Loaders/ShaderLoader.h>

namespace RenderEngine {

	PbrRenderPass::PbrRenderPass(Scene3D *scene, bool inIsMultisampled)
		: RenderPass(scene)
		, mAllocatedFramebuffer(true)
	{
		mModelShader = ShaderLoader::loadShader(std::string("src/Shaders/PBR_Model.glsl"));	

		mFramebuffer = new Framebuffer(Window::getRenderResolutionWidth(), Window::getRenderResolutionHeight(), inIsMultisampled);
		mFramebuffer->addColorTexture(FloatingPoint16).addDepthStencilTexture(NormalizedDepthStencil);
	}

	PbrRenderPass::PbrRenderPass(Scene3D* inScene, Framebuffer* CustomFramebuffer) 
		: RenderPass(inScene)
		, mAllocatedFramebuffer(false)
		, mFramebuffer(CustomFramebuffer)
	{
		mModelShader = ShaderLoader::loadShader(std::string("src/Shaders/PBR_Model.glsl"));
	}

	PbrRenderPass::~PbrRenderPass() 
	{
		if (mFramebuffer) {
			delete mFramebuffer;
			mFramebuffer = nullptr;
		}

		if (mModelShader) {
			delete mModelShader;
			mModelShader = nullptr;
		}
	}

	void PbrRenderPass::RunPbrRenderPass(ICamera* inCamera)
	{		
		Window::bind();
		Window::clear();
		glViewport(0, 0, mFramebuffer->getWidth(), mFramebuffer->getHeight());	

		// Setup
		SceneObjectRenderer *lSceneObjectRenderer = mActiveScene->getSceneObjectRenderer();
		LightManager *lLightManager = mActiveScene->getDynamicLightManager();
		Skybox *skybox = mActiveScene->getSkybox();

		// View setup + lighting setup
		auto lightBindFunction = &LightManager::bindLightingUniforms;

		mGLState->switchShader(mModelShader);
		(lLightManager->*lightBindFunction) (mModelShader);
		mModelShader->setUniform("viewPos", inCamera->getPosition());
		mModelShader->setUniform("view", inCamera->getViewMatrix());
		mModelShader->setUniform("projection", inCamera->getProjectionMatrix());

		// Setup model renderer	
		mActiveScene->addSceneObjectsToRenderer();	
	
		lSceneObjectRenderer->setupOpaqueObjectsRenderState();
		lSceneObjectRenderer->renderOpaqueObjects(mModelShader, RenderPassType:: MaterialRequired);
	
		// Render skybox
		skybox->Draw(inCamera);

		// Render transparent objects
		mGLState->switchShader(mModelShader);

		lSceneObjectRenderer->setupTransparentObjectsRenderState();
		lSceneObjectRenderer->renderTransparentObjects(mModelShader, RenderPassType::MaterialRequired);
	}
}
