
#include "TextureLoader.h"
#include "../Logger.h"

constexpr int CUBEMAP_FACE_COUNT = 6;

namespace RenderEngine {

	// Static declarations
	std::unordered_map<std::string, Texture*> TextureLoader::mTextureCache;

	Texture* TextureLoader::load2DTexture(const std::string& inPath, TextureSettings* inSettings) 
	{	
		auto iter = mTextureCache.find(inPath);
		if (iter != mTextureCache.end()) {
			return iter->second;
		}
	
		int width, height, numComponents;
		unsigned char* image = SOIL_load_image(inPath.c_str(), &width, &height, &numComponents, SOIL_LOAD_AUTO);
		if (!image) {
			Logger::getInstance().error("logged_files/texture_loading.txt", "texture load fail - path:", inPath);
			stbi_image_free(image);
			return nullptr;
		}

		GLenum dataFormat;
		switch (numComponents) {
		case 1: dataFormat = GL_RED;  break;
		case 3: dataFormat = GL_RGB;  break;
		case 4: dataFormat = GL_RGBA; break;
		}

		Texture *texture = nullptr;
		if (inSettings != nullptr) {
			texture = new Texture(*inSettings);
		}
		else {
			texture = new Texture();
		}

		texture->generate2DTexture(width, height, dataFormat, GL_UNSIGNED_BYTE, image);

		mTextureCache.insert(std::pair<std::string, Texture*>(inPath, texture));
		stbi_image_free(image);

		return mTextureCache[inPath];
	}

	Cubemap* TextureLoader::loadCubemapTexture(const std::string& inRight, const std::string& inLeft, const std::string& inTop,
		const std::string& inBottom, const std::string& inBack, const std::string& inFront, CubemapSettings* inSettings)
	{
		Cubemap *cubemap = new Cubemap();
		if (inSettings != nullptr)
			cubemap->setCubemapSettings(*inSettings);

		std::vector<std::string> faces = { inRight, inLeft, inTop, inBottom, inBack, inFront };

		// Textures for the cubemap
		int width, height, numComponents;
		for (unsigned int i = 0; i < CUBEMAP_FACE_COUNT; ++i) {
			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &numComponents, 0);

			if (data) {
				GLenum dataFormat;
				switch (numComponents) {
				case 1: dataFormat = GL_RED;  break;
				case 3: dataFormat = GL_RGB;  break;
				case 4: dataFormat = GL_RGBA; break;
				}

				cubemap->generateCubemapFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, width, height, dataFormat, data);
				stbi_image_free(data);
			}
			else {
				Logger::getInstance().error("logged_files/error.txt", "Cubemap initialization", "Couldn't load cubemap using 6 filepaths. Filepath error: " + faces[i]);
				stbi_image_free(data);
				return cubemap;
			}
		}
		
		return cubemap;
	}
}
