#pragma once

#include "Singleton.h"

namespace RenderEngine {

	class Logger : public Singleton 
	{
	private:
		Logger();		

	public:
		static Logger& getInstance();

		void debug(const std::string& inFilePath, std::string& inModule, const std::string& inMessage);
		void info(const std::string& inFilePath, const std::string& inModule, const std::string& inMessage);
		void warning(const std::string& FilePath, const std::string& inModule, const std::string& inMessage);
		void error(const std::string& inFilePath, const std::string& inModule, const std::string& inMessage);

	private:
		void logMessage(const int& inPriority, const std::string& inModule, const std::string& inMessage);
		void clearFileContents();
		void setOutputFile(const std::string& inFilename);

	private:
		std::set<std::string> mFilePaths;
		std::ofstream mFilestream;
		std::string mFile; 

		enum
		{
			DEBUG, INFO, WARNING, ERROR
		};
	};

}
