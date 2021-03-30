#include "pch.h"
#include "Logger.h"

namespace RenderEngine {

	Logger::Logger() {
		mFile = "logged_files/log.txt";
	}

	Logger& Logger::getInstance() 
	{
		static Logger sLogger;
		return sLogger;
	}

	void Logger::setOutputFile(const std::string& inFilename) 
	{
		mFile = inFilename;

		// Clear the file if it hasn't been written to yet
		if (std::find(mFilePaths.begin(), mFilePaths.end(), inFilename) == mFilePaths.end()) {
			mFilePaths.insert(inFilename);
			clearFileContents();
		}
	}

	void Logger::debug(const std::string& inFilePath, std::string& inModule, const std::string& inMessage) 
	{
		setOutputFile(inFilePath);
		logMessage(DEBUG, inModule, inMessage);
	}

	void Logger::info(const std::string& inFilePath, const std::string& inModule, const std::string& inMessage)
	{
		setOutputFile(inFilePath);
		logMessage(INFO, inModule, inMessage);
	}

	void Logger::warning(const std::string& FilePath, const std::string& inModule, const std::string& inMessage) 
	{
		setOutputFile(FilePath);
		logMessage(WARNING, inModule, inMessage);
	}

	void Logger::error(const std::string& inFilePath, const std::string& inModule, const std::string& inMessage) 
	{
		setOutputFile(inFilePath);
		logMessage(ERROR, inModule, inMessage);
	}

	void Logger::logMessage(const int& inPriority, const std::string& inModule, const std::string& inMessage) 
	{
		std::cout << inModule.c_str() << " : " << inMessage.c_str() << std::endl;
		mFilestream.open(mFile, std::ofstream::app);
		if (!mFilestream) {
			std::cout << "Error: Logger Can't Log To: " << mFile.c_str() << std::endl;
		}
		mFilestream << "(" << inModule.c_str() << "): " << inMessage.c_str() << std::endl;
		mFilestream.close();
	}

	void Logger::clearFileContents() 
	{
		mFilestream.open(mFile, std::ofstream::out);
		if (!mFilestream) {
			error(mFile, "Logger Dtor", std::string("Could not empty the contents of file: ") + mFile);
		}
		mFilestream.close();
	}

}
