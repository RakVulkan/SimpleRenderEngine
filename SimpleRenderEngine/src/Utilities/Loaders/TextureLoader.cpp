#include "pch.h"
#include "TextureLoader.h"
#include <Utilities/Logger.h>

constexpr int CUBE_MAP_FACE_COUNT = 6;
namespace RenderEngine {

	// Static declarations
	std::unordered_map<std::string, Texture*> TextureLoader::mTextureCache;
	Texture* TextureLoader::sDefaultAlbedo;
	Texture* TextureLoader::sDefaultNormal;
	Texture* TextureLoader::sDefaultRoughness; 
	Texture* TextureLoader::sDefaultMetallic;
	Texture* TextureLoader::sDefaultAo;

	Texture* TextureLoader::load2DTexture(std::string&& inPath, TextureSettings* inSettings) 
	{
		// Check the cache
		auto iter = mTextureCache.find(inPath);
		if (iter != mTextureCache.end()) {
			return iter->second;
		}

		// Load the texture
		int lWidth, lHeight, lNumComponents;

		unsigned char* image = SOIL_load_image(inPath.c_str(), &lWidth, &lHeight, &lNumComponents, SOIL_LOAD_AUTO);
		if (!image) {
			Logger::getInstance().error("logged_files/texture_loading.txt", "texture load fail - path:", inPath);
			stbi_image_free(image);
			return nullptr;
		}

		GLenum dataFormat;
		switch (lNumComponents) {
		case 1: dataFormat = GL_RED;  break;
		case 3: dataFormat = GL_RGB;  break;
		case 4: dataFormat = GL_RGBA; break;
		}

		Texture *lTexture = nullptr;
		if (inSettings != nullptr) {
			lTexture = new Texture(*inSettings);
		}
		else {
			lTexture = new Texture();
		}

		lTexture->generate2DTexture(lWidth, lHeight, dataFormat, GL_UNSIGNED_BYTE, image);

		mTextureCache.insert(std::pair<std::string, Texture*>(inPath, lTexture));
		
		stbi_image_free(image);

		return mTextureCache[inPath];
	}

	Cubemap* TextureLoader::loadCubemapTexture(const std::string& inRight, const std::string& inLeft, const std::string& inTop,
		const std::string& inBottom, const std::string& inBack, const std::string& inFront, CubemapSettings* inSettings) 
	{
		Cubemap *lCubemap = new Cubemap(*inSettings);
		if (inSettings != nullptr)
			lCubemap->setCubemapSettings(*inSettings);

		std::vector<std::string> lFaces = { inRight, inLeft, inTop, inBottom, inBack, inFront };

		// Load the textures for the cubemap
		int width, height, numComponents;
		for (unsigned int i = 0; i < CUBE_MAP_FACE_COUNT; ++i) {
			unsigned char* lData = stbi_load(lFaces[i].c_str(), &width, &height, &numComponents, 0);

			if (lData) {
				GLenum lDataFormat;
				switch (numComponents) {
				case 1: lDataFormat = GL_RED;  break;
				case 3: lDataFormat = GL_RGB;  break;
				case 4: lDataFormat = GL_RGBA; break;
				}

				lCubemap->generateCubemapFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, width, height, lDataFormat, lData);
				stbi_image_free(lData);
			}
			else {
				Logger::getInstance().error("logged_files/error.txt", "Cubemap initialization", "Couldn't load cubemap using 6 filepaths. Filepath error: " + lFaces[i]);
				stbi_image_free(lData);
				return lCubemap;
			}
		}
		
		return lCubemap;
	}

	void TextureLoader::initializeDefaultTextures() 
	{
		// Setup texture and minimal filtering because they are 1x1 textures so they require none
		TextureSettings lSrgbTextureSettings;
		lSrgbTextureSettings.IsSRGB = true;

		sDefaultAlbedo = load2DTexture(std::string("resources/textures/Default/defaultAlbedo.png"), &lSrgbTextureSettings);
		sDefaultAlbedo->bind();
		sDefaultAlbedo->setTextureMinFilter(GL_NEAREST);
		sDefaultAlbedo->setTextureMagFilter(GL_NEAREST);

		sDefaultNormal = load2DTexture(std::string("resources/textures/Default/defaultNormal.png"));
		sDefaultNormal->bind();
		sDefaultNormal->setTextureMinFilter(GL_NEAREST);
		sDefaultNormal->setTextureMagFilter(GL_NEAREST);

		sDefaultRoughness = load2DTexture(std::string("resources/textures/Default/white.png"));
		sDefaultRoughness->bind();
		sDefaultRoughness->setTextureMinFilter(GL_NEAREST);
		sDefaultRoughness->setTextureMagFilter(GL_NEAREST);

		sDefaultMetallic = load2DTexture(std::string("resources/textures/Default/black.png"));
		sDefaultMetallic->bind();
		sDefaultMetallic->setTextureMinFilter(GL_NEAREST);
		sDefaultMetallic->setTextureMagFilter(GL_NEAREST);

		sDefaultAo = load2DTexture(std::string("resources/textures/Default/black.png"));
		sDefaultAo->bind();
		sDefaultAo->setTextureMinFilter(GL_NEAREST);
		sDefaultAo->setTextureMagFilter(GL_NEAREST);
	}
}
