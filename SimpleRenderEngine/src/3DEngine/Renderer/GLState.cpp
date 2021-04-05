#include "pch.h"
#include "GLState.h"

namespace RenderEngine {

	GLState::GLState() 
		: mActiveShaderID(0) 
	{
		// Initialize cache values to ensure garbage data doesn't mess with my GL state
		mDepthTest = false;
		mBlend = false;
		mCull = false;
		mFaceToCull = GL_BACK;
		setDepthTest(true);
		setFaceCull(true);
	}

	GLState::~GLState() 
	{
	}

	// Static function to get the instance of GLState. 
	GLState* GLState::getInstance() 
	{
		static GLState cache;
		return &cache;
	}

	// Enable the depth test based on input choice
	void GLState::setDepthTest(bool inChoice) 
	{
		if (mDepthTest != inChoice) {
			mDepthTest = inChoice;
			if (mDepthTest)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}
	}

	// Enable blending based on the input choice
	void GLState::setBlend(bool inChoice)
	{
		if (mBlend != inChoice) {
			mBlend = inChoice;
			if (mBlend)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}
	}

	// Enable culling based on the input choice
	void GLState::setFaceCull(bool inChoice)
	{
		if (mCull != inChoice) {
			mCull = inChoice;
			if (mCull)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
	}

	// Sets the depth function based on input depth function parameter
	void GLState::setDepthFunc(GLenum inDepthFunc) 
	{
		if (mDepthFunc != inDepthFunc) {
			mDepthFunc = inDepthFunc;
			glDepthFunc(inDepthFunc);
		}
	}

	// Sets the blending function
	void GLState::setBlendFunc(GLenum inSource, GLenum inDestination) 
	{
		if (mBlendSrc != inSource || mBlendDst != inDestination) {
			mBlendSrc = inSource;
			mBlendDst = inDestination;
			glBlendFunc(mBlendSrc, mBlendDst);
		}
	}

	// Sets the face(Either front face or back face) to cull based on the input face type
	void GLState::setCullFace(GLenum inFaceToCull) 
	{
		if (mFaceToCull != inFaceToCull) {
			mFaceToCull = inFaceToCull;
			glCullFace(mFaceToCull);
		}
	}

	// Switch the current active shader to new shader based on input shader type
	void GLState::switchShader(Shader* inShader) 
	{
		if (mActiveShaderID != inShader->getShaderID()) {
			mActiveShaderID = inShader->getShaderID();
			inShader->enable();
		}
	}

	// Swicth the current active shader to new shader based on the input shader ID
	void GLState::switchShader(unsigned int inShaderID) 
	{
		if (mActiveShaderID != inShaderID) {
			mActiveShaderID = inShaderID;
			glUseProgram(inShaderID);
		}
	}
}
