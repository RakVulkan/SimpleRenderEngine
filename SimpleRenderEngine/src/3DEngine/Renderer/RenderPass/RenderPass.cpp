#include "pch.h"
#include "RenderPass.h"

namespace RenderEngine {

	RenderPass::RenderPass(Scene3D* inScene) : mActiveScene(inScene) {
		mGLState = GLState::getInstance();
	}

	RenderPass::~RenderPass() {}
}
