#include "pch.h"
#include "Texture.h"
#include <Utilities/Logger.h>

namespace RenderEngine {

	Texture::Texture()
	{
	}

	// Creates texture copy from another texture
	Texture::Texture(const Texture& inTexture) 
		: mTextureId(0)
		, mTextureTarget(inTexture.getTextureTarget())
		, mWidth(inTexture.getWidth())
		, mHeight(inTexture.getHeight())
		, mTextureSettings(inTexture.getTextureSettings())
	{
		glGenTextures(1, &mTextureId);
		bind();

		glTexImage2D(mTextureTarget, 0, mTextureSettings.TextureFormat, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		applyTextureSettings();
		glCopyImageSubData(inTexture.getTextureId(), inTexture.getTextureTarget(), 0, 0, 0, 0, mTextureId,
			mTextureTarget, 0, 0, 0, 0, mWidth, mHeight, 1);

		unbind();
	}

	// Create texture based on texture settings
	Texture::Texture(TextureSettings& inSettings) 
		: mTextureId(0)
		, mTextureTarget(0)
		, mWidth(0), mHeight(0)
		, mTextureSettings(inSettings)
	{
	}

	Texture::~Texture() 
	{
		glDeleteTextures(1, &mTextureId);
	}

	// Sets all texture parameters such as texture wrapping, texture filtering and mipmapping
	void Texture::applyTextureSettings() 
	{
		// Texture wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureSettings.TextureWrapSMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureSettings.TextureWrapTMode);

		// Texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureSettings.TextureMinificationFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureSettings.TextureMagnificationFilterMode);

		// Mipmapping
		if (mTextureSettings.HasMips) {
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, mTextureSettings.MipBias);
		}
	}

	// Generates 2D textures based on input resolution  and image data
	void Texture::generate2DTexture(unsigned int inWidth, unsigned int inHeight, GLenum inDataFormat, 
		GLenum inPixelDataType, const void* inData) 
	{
		mTextureTarget = GL_TEXTURE_2D;
		mWidth = inWidth;
		mHeight = inHeight;

		// If GL_NONE is specified, set the texture format to the data format
		if (mTextureSettings.TextureFormat == GL_NONE) {
			mTextureSettings.TextureFormat = inDataFormat;
		}
		// Check if the texture is SRGB, if so change the texture format
		if (mTextureSettings.IsSRGB) {
			switch (inDataFormat) {
			case GL_RGB: mTextureSettings.TextureFormat = GL_SRGB; break;
			case GL_RGBA: mTextureSettings.TextureFormat = GL_SRGB_ALPHA; break;
			}
		}

		glGenTextures(1, &mTextureId);
		bind();

		glTexImage2D(GL_TEXTURE_2D, 0, mTextureSettings.TextureFormat, inWidth, inHeight, 0, 
				inDataFormat, inPixelDataType, inData);
		applyTextureSettings();

		unbind();
	}

	// Bind the current active texture
	void Texture::bind(int inUnit) 
	{
		glActiveTexture(GL_TEXTURE0 + inUnit);
		glBindTexture(mTextureTarget, mTextureId);
	}

	void Texture::unbind() 
	{
		glBindTexture(mTextureTarget, 0);
	}

	void Texture::setTextureWrapS(GLenum inTextureWrapMode) 
	{
		if (mTextureSettings.TextureWrapSMode == inTextureWrapMode)
			return;

		mTextureSettings.TextureWrapSMode = inTextureWrapMode;
		if (isGenerated()) {
			glTexParameteri(mTextureTarget, GL_TEXTURE_WRAP_S, mTextureSettings.TextureWrapSMode);
		}
	}

	void Texture::setTextureWrapT(GLenum inTextureWrapMode)
	{
		if (mTextureSettings.TextureWrapTMode == inTextureWrapMode)
			return;

		mTextureSettings.TextureWrapTMode = inTextureWrapMode;
		if (isGenerated()) {
			glTexParameteri(mTextureTarget, GL_TEXTURE_WRAP_T, mTextureSettings.TextureWrapTMode);
		}
	}

	void Texture::setTextureMinFilter(GLenum inTextureFilterMode) 
	{
		if (mTextureSettings.TextureMinificationFilterMode == inTextureFilterMode)
			return;

		mTextureSettings.TextureMinificationFilterMode = inTextureFilterMode;
		if (isGenerated()) {
			glTexParameteri(mTextureTarget, GL_TEXTURE_MIN_FILTER, mTextureSettings.TextureMinificationFilterMode);
		}
	}

	void Texture::setTextureMagFilter(GLenum inTextureFilterMode)
	{		
		if (mTextureSettings.TextureMagnificationFilterMode == inTextureFilterMode)
			return;

		mTextureSettings.TextureMagnificationFilterMode = inTextureFilterMode;
		if (isGenerated()) {
			glTexParameteri(mTextureTarget, GL_TEXTURE_MAG_FILTER, mTextureSettings.TextureMagnificationFilterMode);
		}
	}
}
