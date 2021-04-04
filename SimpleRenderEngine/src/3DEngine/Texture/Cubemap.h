#pragma once

namespace RenderEngine {

	struct CubemapSettings 
	{
		// Texture format
		GLenum TextureFormat = GL_NONE; 

		// For Gamma correction
		bool IsSRGB = false;

		// Texture wrapping options
		GLenum TextureWrapSMode = GL_CLAMP_TO_EDGE;
		GLenum TextureWrapTMode = GL_CLAMP_TO_EDGE;
		GLenum TextureWrapRMode = GL_CLAMP_TO_EDGE;

		// Texture filtering options
		GLenum TextureMinificationFilterMode = GL_LINEAR; 
		GLenum TextureMagnificationFilterMode = GL_LINEAR; 		
	};

	class Cubemap {
	public:		
	//	Cubemap();
		Cubemap(const CubemapSettings& inSettings);
		~Cubemap();

		void generateCubemapFace(GLenum inFace, unsigned int inFaceWidth, unsigned int inFaceHeight, GLenum inDataFormat, 
			const unsigned char* inData);

		void bind(int unit = 0);
		void unbind();
		inline void setCubemapSettings(CubemapSettings inSettings) { mCubemapSettings = inSettings; }
		unsigned int getCubemapID() const { return mCubemapID; }
		inline unsigned int getFaceWidth() { return mFaceWidth; }
		inline unsigned int getFaceHeight() { return mFaceHeight; }

	private:
		void applyCubemapSettings();

	private:
		unsigned int mCubemapID;
		unsigned int mFaceWidth, mFaceHeight;
		unsigned int mFacesGenerated;
		CubemapSettings mCubemapSettings;
	};

}
