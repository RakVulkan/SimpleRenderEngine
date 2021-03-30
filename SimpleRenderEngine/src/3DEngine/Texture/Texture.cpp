#include "pch.h"
#include "Texture.h"
#include "../../Utilities/Logger.h"

namespace RenderEngine 
{
	Texture::Texture()
	{
	}
	Texture::Texture(const Texture& texture) : mTextureId(0), mTextureTarget(texture.getTextureTarget()), mWidth(texture.getWidth()), mHeight(texture.getHeight()), mTextureSettings(texture.getTextureSettings()) 
	{
		glGenTextures(1, &mTextureId);
		bind();

		glTexImage2D(mTextureTarget, 0, mTextureSettings.TextureFormat, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		applyTextureSettings();
		glCopyImageSubData(texture.getTextureId(), texture.getTextureTarget(), 0, 0, 0, 0, mTextureId, mTextureTarget, 0, 0, 0, 0, mWidth, mHeight, 1);

		unbind();
	}

	Texture::Texture(TextureSettings &settings) : mTextureId(0), mTextureTarget(0), mWidth(0), mHeight(0), mTextureSettings(settings) {}

	Texture::~Texture() {
		glDeleteTextures(1, &mTextureId);
	}

	void Texture::applyTextureSettings() 
	{
		// Texture wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureSettings.TextureWrapSMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureSettings.TextureWrapTMode);

		// Texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureSettings.TextureMinificationFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureSettings.TextureMagnificationFilterMode);	
	}

	void Texture::generate2DTexture(unsigned int inWidth, unsigned int inHeight, GLenum inDataFormat, GLenum inPixelDataType, const void* inData) 
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

		glTexImage2D(GL_TEXTURE_2D, 0, mTextureSettings.TextureFormat, inWidth, inHeight, 0, inDataFormat, inPixelDataType, inData);
		applyTextureSettings();

		unbind();
	}

	void Texture::bind(int inUnit) 
	{
		glActiveTexture(GL_TEXTURE0 + inUnit);
		glBindTexture(mTextureTarget, mTextureId);
	}

	void Texture::unbind() {
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
		// If mag filter mode exceeds GL_Linear (bilinear) report an error because it is useless to perform more expensive filtering with magnification
		if (inTextureFilterMode > GL_LINEAR)
			Logger::getInstance().warning("logged_files/textures.txt", "Texture Filter Tuning", "Texture's magnification filter exceeded bilinear filtering which won't result in any visual improvements and will just cost more");

		if (mTextureSettings.TextureMagnificationFilterMode == inTextureFilterMode)
			return;

		mTextureSettings.TextureMagnificationFilterMode = inTextureFilterMode;
		if (isGenerated()) {
			glTexParameteri(mTextureTarget, GL_TEXTURE_MAG_FILTER, mTextureSettings.TextureMagnificationFilterMode);
		}
	}
}
