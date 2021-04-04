#include "pch.h"
#include "Framebuffer.h"
#include <Utilities/Logger.h>

namespace RenderEngine 
{
	Framebuffer::Framebuffer(unsigned int inWidth, unsigned int inHeight, bool inIsMultisampled)
		: mFBO(0)
		, mWidth(inWidth)
		, mHeight(inHeight)
		, mIsMultisampled(inIsMultisampled)		
	{
		glGenFramebuffers(1, &mFBO);
	}

	Framebuffer::~Framebuffer() 
	{
		glDeleteFramebuffers(1, &mFBO);
	}

	Framebuffer& Framebuffer::addColorTexture(ColorAttachmentFormat inTextureFormat) 
	{		
		bind();
		Texture lColourTexture;
		TextureSettings lColourTextureSettings;
		lColourTextureSettings.TextureFormat = inTextureFormat;
		lColourTextureSettings.TextureWrapSMode = GL_CLAMP_TO_EDGE;
		lColourTextureSettings.TextureWrapTMode = GL_CLAMP_TO_EDGE;
		lColourTextureSettings.TextureMinificationFilterMode = GL_LINEAR;
		lColourTextureSettings.TextureMagnificationFilterMode = GL_LINEAR;
		lColourTexture.setTextureSettings(lColourTextureSettings);

		// Generate colour texture attachment		
		lColourTexture.generate2DTexture(mWidth, mHeight, GL_RGB);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, lColourTexture.getTextureId(), GL_TEXTURE_2D, 0);

		unbind();
		return *this;
	}

	Framebuffer& Framebuffer::addDepthStencilTexture(DepthStencilAttachmentFormat inTextureFormat) 
	{
		GLenum attachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
		if (inTextureFormat == NormalizedDepthOnly) {
			attachmentType = GL_DEPTH_ATTACHMENT;
		}

		bind();
		Texture lDepthStencilTexture;
		TextureSettings lDepthStencilSettings;
		lDepthStencilSettings.TextureFormat = inTextureFormat;
		lDepthStencilSettings.TextureWrapSMode = GL_CLAMP_TO_BORDER;
		lDepthStencilSettings.TextureWrapTMode = GL_CLAMP_TO_BORDER;
		lDepthStencilSettings.TextureMinificationFilterMode = GL_NEAREST;
		lDepthStencilSettings.TextureMagnificationFilterMode = GL_NEAREST;
	
		lDepthStencilTexture.generate2DTexture(mWidth, mHeight, GL_DEPTH_COMPONENT);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, lDepthStencilTexture.getTextureId(), 0);

		unbind();
		return *this;
	}	

	void Framebuffer::bind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void Framebuffer::unbind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::clear() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}
