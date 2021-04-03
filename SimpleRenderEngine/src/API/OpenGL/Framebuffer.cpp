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
		, mColourTexture()
		, mDepthStencilTexture()
		, mDepthStencilRBO(0)
	{
		glGenFramebuffers(1, &mFBO);
	}

	Framebuffer::~Framebuffer() 
	{
		glDeleteRenderbuffers(1, &mDepthStencilRBO);
		glDeleteFramebuffers(1, &mFBO);
	}

	void Framebuffer::createFramebuffer() 
	{
		bind();
		if (!mColourTexture.isGenerated()) {
			// Indicate that there won't be a colour buffer for this FBO
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}

		// Check if the creation failed
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Logger::getInstance().error("logged_files/error.txt", "Framebuffer initialization", "Could not initialize the framebuffer");
			return;
		}
		unbind();
	}

	Framebuffer& Framebuffer::addColorTexture(ColorAttachmentFormat inTextureFormat) 
	{		
		bind();

		TextureSettings colourTextureSettings;
		colourTextureSettings.TextureFormat = inTextureFormat;
		colourTextureSettings.TextureWrapSMode = GL_CLAMP_TO_EDGE;
		colourTextureSettings.TextureWrapTMode = GL_CLAMP_TO_EDGE;
		colourTextureSettings.TextureMinificationFilterMode = GL_LINEAR;
		colourTextureSettings.TextureMagnificationFilterMode = GL_LINEAR;
		mColourTexture.setTextureSettings(colourTextureSettings);

		// Generate colour texture attachment
		
		mColourTexture.generate2DTexture(mWidth, mHeight, GL_RGB);
		setColorAttachment(mColourTexture.getTextureId(), GL_TEXTURE_2D);

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

		TextureSettings depthStencilSettings;
		depthStencilSettings.TextureFormat = inTextureFormat;
		depthStencilSettings.TextureWrapSMode = GL_CLAMP_TO_BORDER;
		depthStencilSettings.TextureWrapTMode = GL_CLAMP_TO_BORDER;
		depthStencilSettings.TextureMinificationFilterMode = GL_NEAREST;
		depthStencilSettings.TextureMagnificationFilterMode = GL_NEAREST;
	
		mDepthStencilTexture.generate2DTexture(mWidth, mHeight, GL_DEPTH_COMPONENT);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, mDepthStencilTexture.getTextureId(), 0);		

		unbind();
		return *this;
	}

	Framebuffer& Framebuffer::addDepthStencilRBO(DepthStencilAttachmentFormat inTextureFormat) 
	{
		bind();

		GLenum attachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
		if (inTextureFormat == NormalizedDepthOnly) {
			attachmentType = GL_DEPTH_ATTACHMENT;
		}

		// Generate depth+stencil RBO attachment
		glGenRenderbuffers(1, &mDepthStencilRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, mDepthStencilRBO);
		
		glRenderbufferStorage(GL_RENDERBUFFER, inTextureFormat, mWidth, mHeight);

		// Attach depth+stencil attachment
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, mDepthStencilRBO);

		unbind();
		return *this;
	}

	void Framebuffer::setColorAttachment(unsigned int inTarget, unsigned int inTargetType, int inMipToWriteTo) 
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, inTargetType, inTarget, inMipToWriteTo);
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
