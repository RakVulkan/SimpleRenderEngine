#include "pch.h"
#include "GLState.h"

namespace RenderEngine {

	GLState::GLState() : mActiveShaderID(0) {
		// Initialize cache values to ensure garbage data doesn't mess with my GL state
		mDepthTest = false;
		mStencilTest = false;
		mBlend = false;
		mCull = false;
		mFaceToCull = GL_BACK;
		mMultisample = false;
		mUsesClipPlane = false;
		setDepthTest(true);
		setFaceCull(true);
		setClipPlane(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	GLState::~GLState() {

	}

	GLState* GLState::getInstance() {
		static GLState cache;
		return &cache;
	}

	void GLState::setDepthTest(bool choice) {
		if (mDepthTest != choice) {
			mDepthTest = choice;
			if (mDepthTest)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}
	}

	void GLState::setStencilTest(bool choice) {
		if (mStencilTest != choice) {
			mStencilTest = choice;
			if (mStencilTest)
				glEnable(GL_STENCIL_TEST);
			else
				glDisable(GL_STENCIL_TEST);
		}
	}

	void GLState::setBlend(bool choice) {
		if (mBlend != choice) {
			mBlend = choice;
			if (mBlend)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}
	}

	void GLState::setFaceCull(bool choice) {
		if (mCull != choice) {
			mCull = choice;
			if (mCull)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
	}

	void GLState::setMultisample(bool choice) {
		if (mMultisample != choice) {
			mMultisample = choice;
			if (mMultisample)
				glEnable(GL_MULTISAMPLE);
			else
				glDisable(GL_MULTISAMPLE);
		}
	}

	void GLState::setUsesClipPlane(bool choice)
	{
		if (mUsesClipPlane != choice)
		{
			mUsesClipPlane = choice;
			if (mUsesClipPlane)
				glEnable(GL_CLIP_DISTANCE0);
			else
				glDisable(GL_CLIP_DISTANCE0);
		}
	}

	void GLState::setDepthFunc(GLenum depthFunc) {
		if (mDepthFunc != depthFunc) {
			mDepthFunc = depthFunc;
			glDepthFunc(mDepthFunc);
		}
	}

	void GLState::setStencilFunc(GLenum testFunc, int stencilFragValue, unsigned int stencilBitmask) {
		if (mStencilTestFunc != testFunc || mStencilFragValue != stencilFragValue || mStencilFuncBitmask != stencilBitmask) {
			mStencilTestFunc = testFunc; 
			mStencilFragValue = stencilFragValue; 
			mStencilFuncBitmask = stencilBitmask;

			glStencilFuncSeparate(GL_FRONT_AND_BACK, mStencilTestFunc, mStencilFragValue, mStencilFuncBitmask);
		}
	}

	void GLState::setStencilOp(GLenum stencilFailOperation, GLenum depthFailOperation, GLenum depthPassOperation) {
		if (mStencilFailOperation != stencilFailOperation || mDepthFailOperation != depthFailOperation || mDepthPassOperation != depthPassOperation) {
			mStencilFailOperation = stencilFailOperation;
			mDepthFailOperation = depthFailOperation;
			mDepthPassOperation = depthPassOperation;

			glStencilOpSeparate(GL_FRONT_AND_BACK, mStencilFailOperation, mDepthFailOperation, mDepthPassOperation);
		}
	}

	void GLState::setStencilWriteMask(unsigned int bitmask) {
		if (mStencilWriteBitmask != bitmask) {
			mStencilWriteBitmask = bitmask;
			glStencilMaskSeparate(GL_FRONT_AND_BACK, mStencilWriteBitmask);
		}
	}

	void GLState::setBlendFunc(GLenum src, GLenum dst) {
		if (mBlendSrc != src || mBlendDst != dst) {
			mBlendSrc = src;
			mBlendDst = dst;
			glBlendFunc(mBlendSrc, mBlendDst);
		}
	}

	void GLState::setCullFace(GLenum faceToCull) {
		if (mFaceToCull != faceToCull) {
			mFaceToCull = faceToCull;
			glCullFace(mFaceToCull);
		}
	}

	void GLState::setClipPlane(glm::vec4 clipPlane)
	{
		mActiveClipPlane = clipPlane;
	}

	void GLState::switchShader(Shader *shader) {
		if (mActiveShaderID != shader->getShaderID()) {
			mActiveShaderID = shader->getShaderID();
			shader->enable();
		}
	}

	void GLState::switchShader(unsigned int shaderID) {
		if (mActiveShaderID != shaderID) {
			mActiveShaderID = shaderID;
			glUseProgram(shaderID);
		}
	}

}
