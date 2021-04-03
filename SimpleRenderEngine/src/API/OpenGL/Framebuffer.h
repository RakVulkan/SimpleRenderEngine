#pragma once

#include <Utilities/Loaders/TextureLoader.h>

namespace RenderEngine 
{
	enum ColorAttachmentFormat 
	{
		NormalizedSingleChannel8 = GL_RED,
		Normalized8 = GL_RGBA8,
		Normalized16 = GL_RGBA16,
		FloatingPoint16 = GL_RGBA16F,
		FloatingPoint32 = GL_RGBA32F
	};

	enum DepthStencilAttachmentFormat 
	{
		NormalizedDepthOnly = GL_DEPTH_COMPONENT,
		NormalizedDepthStencil = GL_DEPTH24_STENCIL8,
		FloatingPointDepthStencil = GL_DEPTH32F_STENCIL8
	};

	class Framebuffer 
	{
	public:
		Framebuffer(unsigned int inWidth, unsigned int inHeight, bool inIsMultisampled);
		virtual ~Framebuffer();
	
		void createFramebuffer();
		Framebuffer& addColorTexture(ColorAttachmentFormat inTextureFormat);
		Framebuffer& addDepthStencilTexture(DepthStencilAttachmentFormat inTextureFormat);
		Framebuffer& addDepthStencilRBO(DepthStencilAttachmentFormat inRboFormat);

		void bind();
		void unbind();

		void setColorAttachment(unsigned int inTarget, unsigned int inTargetType, int inMipToWriteTo = 0);
		void clear();

		inline unsigned int getFramebuffer() const { return mFBO; }
		inline unsigned int getWidth() const { return mWidth; }
		inline unsigned int getHeight() const { return mHeight; }
		inline bool isMultisampled() const { return mIsMultisampled; }

		inline Texture* getColourTexture() { return &mColourTexture; }
		inline Texture* getDepthStencilTexture() { return &mDepthStencilTexture; }
		inline unsigned int getDepthStencilRBO() { return mDepthStencilRBO; }

	protected:
		unsigned int mFBO;
		unsigned int mWidth;
		unsigned int mHeight;
		bool mIsMultisampled;
		
		// Render Target Attachments
		Texture mColourTexture;
		Texture mDepthStencilTexture;
		unsigned int mDepthStencilRBO;
	};
}
