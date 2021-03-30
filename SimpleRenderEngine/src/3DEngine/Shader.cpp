#include "pch.h"
#include "Shader.h"
#include <Utilities/Logger.h>

namespace RenderEngine {

	Shader::Shader(const std::string &path) 
		: mShaderFilePath(path) 
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

	void Shader::setUniform(const char* name, float value) 
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform(const char* name, int value) 
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform(const char* inName, const glm::vec2& inVector) 
	{
		glUniform2f(getUniformLocation(inName), inVector.x, inVector.y);
	}

	void Shader::setUniform(const char* name, const glm::vec3& vector) 
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform(const char* name, const glm::mat3& matrix) {
		glUniformMatrix3fv(glGetUniformLocation(mShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setUniform(const char* name, const glm::mat4& matrix) {
		glUniformMatrix4fv(glGetUniformLocation(mShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}	

	int Shader::getUniformLocation(const char* inName) const 
	{
		return glGetUniformLocation(mShaderID, inName);
	}

	GLenum Shader::shaderTypeFromString(const std::string& inType) 
	{   		
		if (inType == "vertex") {
			return GL_VERTEX_SHADER;
		}
		else if (inType == "fragment") {
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