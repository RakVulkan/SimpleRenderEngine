#pragma once
#include <pch.h>
namespace RenderEngine { 

	class FileHandler {
	public:
		static std::string readFile(const std::string& inFilepath);
	};

} 