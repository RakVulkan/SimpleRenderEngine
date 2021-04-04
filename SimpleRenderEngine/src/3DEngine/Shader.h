#pragma once

#include <Utilities/FileHandler.h>
#include <Utilities/Logger.h>
namespace RenderEngine {

	class Shader {
	public:
		Shader(const std::string& inPath);
		~Shader();

		void enable() const;
		void disable() const;

		void setUniform(const char* inName, float inValue);
		void setUniform(const char* inName, int inValue);
		void setUniform(const char* inName, const glm::vec2& inVector);
		void setUniform(const char* inName, const glm::ivec2& inVector);
		void setUniform(const char* inName, const glm::vec3& inVector);
		void setUniform(const char* inName, const glm::ivec3& inVector);
		void setUniform(const char* inName, const glm::vec4& inVector);
		void setUniform(const char* inName, const glm::ivec4& inVector);
		void setUniform(const char* inName, const glm::mat3& inMatrix);
		void setUniform(const char* inName, const glm::mat4& inMatrix);

		inline unsigned int getShaderID() { return mShaderID; }
	private:
		int getUniformLocation(const char* inName);

		static GLenum shaderTypeFromString(const std::string& inType);
		std::unordered_map<GLenum, std::string> preProcessShaderBinary(std::string& inSource);
		void compile(const std::unordered_map<GLenum, std::string>& inShaderSources);
	private:
		unsigned int mShaderID;
		std::string mShaderFilePath;
	};
}
