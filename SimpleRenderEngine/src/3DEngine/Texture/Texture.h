#pragma once

namespace RenderEngine {

	struct TextureSettings 
	{
		// Texture format. If set to GL_NONE, the data format will be used
		GLenum TextureFormat = GL_NONE; 

		// IsSRGB will let the loader know that the texture needs to be "linearlized" before it is sampled in the shaders (ie the texture is in a non liner space)
		bool IsSRGB = false;

		// Texture wrapping options
		GLenum TextureWrapSMode = GL_REPEAT;
		GLenum TextureWrapTMode = GL_REPEAT;


		// Texture filtering options
		// Filtering mode when the texture moves further away and multiple texels map to one pixel (trilinear for best quality)
		GLenum TextureMinificationFilterMode = GL_LINEAR_MIPMAP_LINEAR; 

		// Filtering mode when the texture gets closer and multiple pixels map to a single texel (Never needs to be more than bilinear because that is as accurate as it gets in this sitation)
		GLenum TextureMagnificationFilterMode = GL_LINEAR; 

		// Specified independent of texture min and mag filtering, should be a power of 2 (1.0 means the usual isotropic texture filtering is used which means anisotropic filtering isn't used)
		float TextureAnisotropyLevel = ANISOTROPIC_FILTERING_LEVEL; 

		// Mip options
		bool HasMips = true;
		int MipBias = 0; 
	};

	class Texture {
	public:
		Texture();

		// Copies another texture and its settings
		Texture(const Texture& inTexture); 

		// If nothing is supplied, it will construct default settings
		Texture(TextureSettings& inSettings);
		~Texture();

		// Generation functions
		void generate2DTexture(unsigned int inWidth, unsigned int inHeight, GLenum inDataFormat, 
			GLenum inPixelDataType = GL_UNSIGNED_BYTE, const void* inData = nullptr);
		
		void bind(int inUnit = 0);
		void unbind();

		// Texture Tuning Functions (Works for pre-generation and post-generation)
		void setTextureWrapS(GLenum inTextureWrapMode);
		void setTextureWrapT(GLenum inTextureWrapMode);
		void setTextureMinFilter(GLenum inTextureFilterMode);
		void setTextureMagFilter(GLenum inTextureFilterMode);
	
		inline void setTextureSettings(TextureSettings inSettings) { mTextureSettings = inSettings; }
		inline void setTextureFormat(GLenum inFormat) { mTextureSettings.TextureFormat = inFormat; }

	
		inline unsigned int getTextureId() const { return mTextureId; }
		inline unsigned int getTextureTarget() const { return mTextureTarget; }
		inline bool isGenerated() const { return mTextureId != 0; }
		inline unsigned int getWidth() const { return mWidth; }
		inline unsigned int getHeight() const { return mHeight; }
		inline const TextureSettings& getTextureSettings() const { return mTextureSettings; }

	private:
		void applyTextureSettings();

	private:
		unsigned int mTextureId;
		GLenum mTextureTarget;
		unsigned int mWidth, mHeight;
		TextureSettings mTextureSettings;
	};

}
