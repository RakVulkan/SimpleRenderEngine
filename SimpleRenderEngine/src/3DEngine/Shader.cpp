#include "pch.h"
#include "Shader.h"

namespace RenderEngine {

	Shader::Shader(const std::string& inPath) 
		: mShaderFilePath(inPath)
	{
		std::string shaderBinary = FileHandler::readFile(mShaderFilePath);
		auto shaderSources = preProcessShaderBinary(shaderBinary);
		compile(shaderSources);
	}

	Shader::~Shader() 
	{
		glDeleteProgram(mShaderID);
	}

	void Shader::enable() const 
	{
		glUseProgram(mShaderID);
	}

	void Shader::disable() const 
	{
		glUseProgram(0);
	}

	void Shader::setUniform(const char* inName, float inValue) 
	{
		glUniform1f(getUniformLocation(inName), inValue);
	}

	void Shader::setUniform(const char* inName, int inValue) 
	{
		glUniform1i(getUniformLocation(inName), inValue);
	}

	void Shader::setUniform(const char* inName, const glm::vec2& inVector) 
	{
		glUniform2f(getUniformLocation(inName), inVector.x, inVector.y);
	}

	void Shader::setUniform(const char* inName, const glm::ivec2& inVector) 
	{
		glUniform2i(getUniformLocation(inName), inVector.x, inVector.y);
	}

	void Shader::setUniform(const char* inName, const glm::vec3& inVector) 
	{
		glUniform3f(getUniformLocation(inName), inVector.x, inVector.y, inVector.z);
	}

	void Shader::setUniform(const char* inName, const glm::ivec3& inVector) 
	{
		glUniform3i(getUniformLocation(inName), inVector.x, inVector.y, inVector.z);
	}

	void Shader::setUniform(const char* inName, const glm::vec4& inVector) 
	{
		glUniform4f(getUniformLocation(inName), inVector.x, inVector.y, inVector.z, inVector.w);
	}

	void Shader::setUniform(const char* inName, const glm::ivec4& inVector) 
	{
		glUniform4i(getUniformLocation(inName), inVector.x, inVector.y, inVector.z, inVector.w);
	}

	void Shader::setUniform(const char* inName, const glm::mat3& inMatrix) 
	{
		glUniformMatrix3fv(glGetUniformLocation(mShaderID, inName), 1, GL_FALSE, glm::value_ptr(inMatrix));
	}

	void Shader::setUniform(const char* inName, const glm::mat4& inMatrix) 
	{
		glUniformMatrix4fv(glGetUniformLocation(mShaderID, inName), 1, GL_FALSE, glm::value_ptr(inMatrix));
	}
	
	int Shader::getUniformLocation(const char* inName)
	{
		return glGetUniformLocation(mShaderID, inName);
	}

	GLenum Shader::shaderTypeFromString(const std::string &type) 
	{
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment") {
			return GL_FRAGMENT_SHADER;
		}

		return 0;
	}

	std::unordered_map<GLenum, std::string> Shader::preProcessShaderBinary(std::string &source) 
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char *shaderTypeToken = "#shader-type";
		size_t shaderTypeTokenLength = strlen(shaderTypeToken);
		size_t pos = source.find(shaderTypeToken);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			size_t begin = pos + shaderTypeTokenLength + 1;
			std::string shaderType = source.substr(begin, eol - begin);
			
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(shaderTypeToken, nextLinePos);
			shaderSources[shaderTypeFromString(shaderType)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void Shader::compile(const std::unordered_map<GLenum, std::string> &shaderSources) 
	{
		mShaderID = glCreateProgram();

		// Attach different components of the shader (vertex, fragment, geometry, hull, domain, or compute)
		for (auto &item : shaderSources) {
			GLenum type = item.first;
			const std::string &source = item.second;

			GLuint shader = glCreateShader(type);
			const GLchar *shaderSource = source.c_str();
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			// Check to see if compiling was successful
			GLint wasCompiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &wasCompiled);
			if (wasCompiled == GL_FALSE || source.empty()) {
				int length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				if (length > 0) {
					std::vector<char> error(length);
					glGetShaderInfoLog(shader, length, &length, &error[0]);
					std::string errorString(error.begin(), error.end());

					Logger::getInstance().error("logged_files/shader_compile_error.txt", mShaderFilePath, errorString);
				}
				else {
					Logger::getInstance().error("logged_files/shader_compile_error.txt", mShaderFilePath, "unknown error");
				}
				glDeleteShader(shader);
				break;
			}

			glAttachShader(mShaderID, shader);
			glDeleteShader(shader);
		}

		// Validate shader
		glLinkProgram(mShaderID);
		glValidateProgram(mShaderID);
	}

}