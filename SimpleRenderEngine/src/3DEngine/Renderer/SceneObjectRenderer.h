#pragma once

#include "GLState.h"

#include <3DEngine/Scene3D/RenderableSceneObject.h>
#include <3DEngine/camera/Camera.h>
#include <3DEngine/mesh/Model.h>
#include <3DEngine/mesh/common/Quad.h>
#include <3DEngine/mesh/common/Cube.h>
#include <3DEngine/Renderer/renderpass/RenderPassType.h>

namespace RenderEngine {

	class SceneObjectRenderer {
	public:
		SceneObjectRenderer(Camera* inCamera);
		~SceneObjectRenderer();

		void addOpaqueObject(RenderableSceneObject* inOpaqueObject);
		void addTransparentObject(RenderableSceneObject* inTransparentObject);
		
		void setupOpaqueObjectsRenderState();
		void setupTransparentObjectsRenderState();

		void renderOpaqueObjects(Shader* inShader, RenderPassType inRenderPassType);
		void renderTransparentObjects(Shader* inShader, RenderPassType inRenderPassType);

	private:
		void setupModelMatrix(RenderableSceneObject* inRenderableObject, Shader* inShader, RenderPassType inRenderTypePass);

		std::deque<RenderableSceneObject*> mOpaqueObjectsRenderQueue;
		std::deque<RenderableSceneObject*> mTransparentObjectsRenderQueue;

		Camera* mCamera;
		GLState* mGLState;
	};

}
