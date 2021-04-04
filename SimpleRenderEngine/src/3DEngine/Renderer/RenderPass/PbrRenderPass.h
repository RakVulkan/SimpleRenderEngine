#pragma once

#include <3DEngine/Renderer/RenderPass/RenderPass.h>
#include <3DEngine/Shader.h>
#include <3DEngine/Scene3D/Scene3D.h>

namespace RenderEngine {

	class PbrRenderPass : public RenderPass {
	public:
		PbrRenderPass(Scene3D* inScene, bool inIsMultisampled);
		PbrRenderPass(Scene3D* inScene, Framebuffer* inCustomFramebuffer);
		virtual ~PbrRenderPass() override;

		void RunPbrRenderPass(ICamera* inCamera);

	private:
		bool mAllocatedFramebuffer;
		Framebuffer* mFramebuffer;
		Shader* mModelShader;
	};

}
