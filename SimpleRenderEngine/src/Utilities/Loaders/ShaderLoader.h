#pragma once

#include <3DEngine/Shader.h>

namespace RenderEngine {

	class ShaderLoader {
	public:
		static Shader* loadShader(const std::string& inPath);
	private:
		static std::unordered_map<std::size_t, Shader*> sShaderCache;
		static std::hash<std::string> sHasher;
	};

}
