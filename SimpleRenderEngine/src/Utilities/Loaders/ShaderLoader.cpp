#include "pch.h"
#include "ShaderLoader.h"

namespace RenderEngine {

	// Static declarations
	std::unordered_map<std::size_t, Shader*> ShaderLoader::sShaderCache;
	std::hash<std::string> ShaderLoader::sHasher;

	Shader* ShaderLoader::loadShader(const std::string& inPath) 
	{
		std::size_t hash = sHasher(inPath);

		// Check the cache
		auto iter = sShaderCache.find(hash);
		if (iter != sShaderCache.end()) {
			return iter->second;
		}

		// Load the shader
		Shader *shader = new Shader(inPath);

		sShaderCache.insert(std::pair<std::size_t, Shader*>(hash, shader));
		return sShaderCache[hash];
	}

}
