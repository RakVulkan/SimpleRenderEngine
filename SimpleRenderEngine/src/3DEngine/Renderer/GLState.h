#pragma once

#include <3DEngine/Shader.h>
#include <Utilities/Singleton.h>

namespace RenderEngine {
	
	// This class holds the OpenGL pipeline state information. This class is derived from singleton as only once instance 
	// of the OpenGL state should be there always
	class GLState : Singleton {
	public:
		GLState();
		~GLState();

		static GLState* getInstance();

		void setDepthTest(bool inChoice);
		void setBlend(bool inChoice);
		void setFaceCull(bool inChoice);

		void setDepthFunc(GLenum inDepthFunc);
		void setBlendFunc(GLenum inSource, GLenum inDestination);
		void setCullFace(GLenum inFaceToCull);

		void switchShader(Shader* inShader);
		void switchShader(unsigned int inShaderID);

	private:

		// Toggles
		bool mDepthTest;
		bool mBlend;
		bool mCull;

		// Depth State
		GLenum mDepthFunc;

		// Blend State
		GLenum mBlendSrc, mBlendDst;

		// Culling State
		GLenum mFaceToCull;

		// Active binds
		unsigned int mActiveShaderID;
	};

}
