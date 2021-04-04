#include "pch.h"
#include "Cubemap.h"

namespace RenderEngine {
	
	Cubemap::Cubemap(const CubemapSettings &settings = CubemapSettings())
		: mCubemapID(0)
		, mFaceWidth(0)
		, mFaceHeight(0)
		, mFacesGenerated(0)
		, mCubemapSettings(settings) {}

	Cubemap::~Cubemap() {
		glDeleteTextures(1, &mCubemapID);
	}

	void Cubemap::applyCubemapSettings() {
		// Texture wrapping
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, mCubemapSettings.TextureWrapSMode);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, mCubemapSettings.TextureWrapTMode);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, mCubemapSettings.TextureWrapRMode);

		// Texture filtering
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mCubemapSettings.TextureMagnificationFilterMode);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mCubemapSettings.TextureMinificationFilterMode);
	}

	void Cubemap::generateCubemapFace(GLenum face, unsigned int faceWidth, unsigned int faceHeight, GLenum dataFormat, const unsigned char *data)
	{
		// Generate cubemap if this is the first face being generated
		if (mCubemapID == 0) {
			glGenTextures(1, &mCubemapID);

			mFaceWidth = faceWidth;
			mFaceHeight = faceHeight;

			// If GL_NONE is specified, set the texture format to the data format
			if (mCubemapSettings.TextureFormat == GL_NONE) {
				mCubemapSettings.TextureFormat = dataFormat;
			}
			// Check if the texture is SRGB, if so change the texture format
			if (mCubemapSettings.IsSRGB) {
				switch (dataFormat) {
				case GL_RGB: mCubemapSettings.TextureFormat = GL_SRGB; break;
				case GL_RGBA: mCubemapSettings.TextureFormat = GL_SRGB_ALPHA; break;
				}
			}
		}

		bind();

		glTexImage2D(face, 0, mCubemapSettings.TextureFormat, mFaceWidth, mFaceHeight, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		++mFacesGenerated;

		if (mFacesGenerated >= 6) {
			applyCubemapSettings();
		}

		unbind();
	}

	void Cubemap::bind(int unit) {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemapID);
	}

	void Cubemap::unbind() {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

}
