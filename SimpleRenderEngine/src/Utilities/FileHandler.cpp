#include "pch.h"
#include "FileHandler.h"
#include "Logger.h"

namespace RenderEngine {

	std::string FileHandler::readFile(const std::string& inFilepath) {
		std::ifstream lIstream(inFilepath, std::ios::in, std::ios::binary);
		std::string lResult;

		if (lIstream) {
			lResult = std::string((std::istreambuf_iterator<char>(lIstream)),
				(std::istreambuf_iterator<char>()));
			lIstream.close();
		}
		else {
			Logger::getInstance().warning("logged_files/error.txt", "Could Not Read File", inFilepath);
		}

		return lResult;
	}
}
