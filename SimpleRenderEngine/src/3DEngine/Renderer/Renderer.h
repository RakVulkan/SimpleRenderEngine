#pragma once

#include <3DEngine/Renderer/RenderPass/PbrRenderPass.h>
#include <3DEngine/Scene3D/Scene3D.h>
#include <3DEngine/Renderer/GLState.h>

namespace RenderEngine
{

	class Renderer
	{
	public:
		Renderer(Scene3D* inScene);

		void init();
		void render();
	private:
		GLState* mGLState;
		Scene3D* mActiveScene;
		PbrRenderPass mPbrRenderPass;
	};

}
