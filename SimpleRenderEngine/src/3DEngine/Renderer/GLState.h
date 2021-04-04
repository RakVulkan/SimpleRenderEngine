#pragma once

#include <3DEngine/Shader.h>
#include <Utilities/Singleton.h>

namespace RenderEngine {

	class GLState : Singleton {
	public:
		GLState();
		~GLState();

		static GLState* getInstance();

		void setDepthTest(bool choice);
		void setStencilTest(bool choice);
		void setBlend(bool choice);
		void setFaceCull(bool choice);
		void setMultisample(bool choice);
		void setUsesClipPlane(bool choice);

		void setDepthFunc(GLenum depthFunc);
		void setStencilFunc(GLenum testFunc, int stencilFragValue, unsigned int stencilBitmask);
		void setStencilOp(GLenum stencilFailOperation, GLenum depthFailOperation, GLenum depthPassOperation);
		void setStencilWriteMask(unsigned int bitmask);
		void setBlendFunc(GLenum src, GLenum dst);
		void setCullFace(GLenum faceToCull);
		void setClipPlane(glm::vec4 clipPlane);

		void switchShader(Shader *shader);
		void switchShader(unsigned int shaderID);

		inline bool getUsesClipPlane() { return mUsesClipPlane; }
		inline const glm::vec4& getActiveClipPlane() { return mActiveClipPlane; }
	private:
		// Toggles
		bool mDepthTest;
		bool mStencilTest;
		bool mBlend;
		bool mCull;
		bool mMultisample;
		bool mUsesClipPlane;

		// Depth State
		GLenum mDepthFunc;

		// Stencil State
		GLenum mStencilTestFunc;
		int mStencilFragValue;
		unsigned int mStencilFuncBitmask;

		GLenum mStencilFailOperation, mDepthFailOperation, mDepthPassOperation;
		unsigned int mStencilWriteBitmask;

		// Blend State
		GLenum mBlendSrc, mBlendDst;

		// Culling State
		GLenum mFaceToCull;

		// Clip Plane State
		glm::vec4 mActiveClipPlane;

		// Active binds
		unsigned int mActiveShaderID;
	};

}
