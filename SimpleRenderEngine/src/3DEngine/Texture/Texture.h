#pragma once

namespace RenderEngine {

	struct TextureSettings 
	{	
		GLenum TextureFormat = GL_NONE; 
		bool IsSRGB = false;

		// Texture wrapping options
		GLenum TextureWrapSMode = GL_REPEAT;
		GLenum TextureWrapTMode = GL_REPEAT;

		// Texture filtering options
		GLenum TextureMinificationFilterMode = GL_LINEAR_MIPMAP_LINEAR; 
		GLenum TextureMagnificationFilterMode = GL_LINEAR; 	
	};

	class Texture {
	public:
		Texture();
		Texture(const Texture& texture); 
		Texture(TextureSettings& inSettings); 
		~Texture();

		void generate2DTexture(unsigned int inWidth, unsigned int inHeight, GLenum inDataFormat, GLenum inPixelDataType = GL_UNSIGNED_BYTE, const void* inData = nullptr);
		void bind(int unit = 0);
		void unbind();
		
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
		unsigned int mWidth;
		unsigned int mHeight;
		TextureSettings mTextureSettings;
	};

}
