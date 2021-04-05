#include "pch.h"
#include "SceneObjectRenderer.h"
#include <3DEngine/Renderer/RenderPass/RenderPassType.h>
namespace RenderEngine {

	SceneObjectRenderer::SceneObjectRenderer(Camera* inCamera)
		: mCamera(inCamera)
	{
		// Configure OpenGL state
		mGLState = GLState::getInstance();
		mGLState->setDepthTest(true);
		mGLState->setBlend(false);
		mGLState->setFaceCull(true);
	}

	SceneObjectRenderer::~SceneObjectRenderer()
	{ 	
		for (auto lOpaqueObject : mOpaqueObjectsRenderQueue) {
			delete lOpaqueObject;
			lOpaqueObject = nullptr;
		}

		for (auto lTransparentObject : mTransparentObjectsRenderQueue) {
			delete lTransparentObject;
			lTransparentObject = nullptr;
		}
	}

	void SceneObjectRenderer::addOpaqueObject(RenderableSceneObject* inOpaqueObject) 
	{
		mOpaqueObjectsRenderQueue.push_back(inOpaqueObject);
	}

	void SceneObjectRenderer::addTransparentObject(RenderableSceneObject* inTransparentObject) 
	{
		mTransparentObjectsRenderQueue.push_back(inTransparentObject);
	}

	void SceneObjectRenderer::setupOpaqueObjectsRenderState()
	{
		mGLState->setDepthTest(true);
		mGLState->setBlend(false);
		mGLState->setFaceCull(true);
		mGLState->setCullFace(GL_BACK);
	}
	
	void SceneObjectRenderer::setupTransparentObjectsRenderState()
	{
		mGLState->setDepthTest(true);
		mGLState->setBlend(true);
		mGLState->setFaceCull(false);
	}

	void SceneObjectRenderer::renderOpaqueObjects(Shader* inShader, RenderPassType inRenderPassType) 
	{
		mGLState->switchShader(inShader);

		// Render opaque objects
		while (!mOpaqueObjectsRenderQueue.empty()) {
			RenderableSceneObject* lCurrentSceneObject = mOpaqueObjectsRenderQueue.front();

			setupModelMatrix(lCurrentSceneObject, inShader, inRenderPassType);
			lCurrentSceneObject->draw(inShader, inRenderPassType);

			mOpaqueObjectsRenderQueue.pop_front();
		}
	}

	void SceneObjectRenderer::renderTransparentObjects(Shader* inShader, RenderPassType inRenderPassType) 
	{
		mGLState->switchShader(inShader);

		// Sort then render transparent objects (from back to front, does not account for rotations or scaling)
		std::sort(mTransparentObjectsRenderQueue.begin(), mTransparentObjectsRenderQueue.end(),
			[this](RenderableSceneObject *a, RenderableSceneObject *b) -> bool
		{
			return glm::length2(mCamera->getPosition() - a->getPosition()) > glm::length2(mCamera->getPosition() - b->getPosition());
		});
		while (!mTransparentObjectsRenderQueue.empty()) {
			RenderableSceneObject *current = mTransparentObjectsRenderQueue.front();

			mGLState->setBlend(true);
			mGLState->setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			setupModelMatrix(current, inShader, inRenderPassType);
			current->draw(inShader, inRenderPassType);

			mTransparentObjectsRenderQueue.pop_front();
		}
	}

	void SceneObjectRenderer::setupModelMatrix(RenderableSceneObject* inRenderableObject, Shader* inShader, RenderPassType inRenderTypePass)
	{
		glm::mat4 lModelMatrix(1);
		glm::mat4 lTranslateMatrix = glm::translate(glm::mat4(1.0f), inRenderableObject->getPosition());
		glm::mat4 lRotateMatrix = glm::toMat4(inRenderableObject->getOrientation());
		glm::mat4 lScaleMatrix = glm::scale(glm::mat4(1.0f), inRenderableObject->getScale());
	
		lModelMatrix = lTranslateMatrix * lRotateMatrix * lScaleMatrix;

		inShader->setUniform("model", lModelMatrix);

		if (inRenderTypePass == RenderPassType::MaterialRequired) {
			glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(lModelMatrix)));
			inShader->setUniform("normalMatrix", normalMatrix);
		}
	}
}
