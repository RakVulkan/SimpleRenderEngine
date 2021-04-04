#pragma once

#include "RenderPassType.h"
#include <3DEngine/Scene3D/Scene3D.h>

namespace RenderEngine {

	class RenderPass {
	public:
		RenderPass(Scene3D* inScene);
		virtual ~RenderPass();
	protected:
		GLState* mGLState;
		Scene3D* mActiveScene;
	};

}
