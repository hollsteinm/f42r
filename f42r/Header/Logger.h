#ifndef LOGGER_H
#define LOGGER_H
#include "types.h"

#include <boost\filesystem.hpp>
#include <ostream>
#include <boost\thread.hpp>

namespace times
{
	string date_as_string(bool local);
	string date_as_string();
	string date_as_file_string();
};

namespace Log
{
	ENUM_3(MethodType, silent, console, file, console)
	ENUM_4(TraceType, info, warn, error, debug, info)
	ENUM_4(ConfigType, nolog, development, production, testing, nolog)
};

class Logger
{
public:
	~Logger();

	static boost::shared_ptr<Logger> Create(boost::shared_ptr<class CommandParser> Parser);

	Logger& Log(Log::TraceType trace, string msg);

	Logger& Info(string message);
	Logger& Warn(string message);
	Logger& Erro(string message);
	Logger& Dbug(string message);

	const Log::MethodType GetLogMethod() const;

protected:
	///Silent Logger Constructor
	Logger();
	///Console Logger Constructor
	Logger(Log::ConfigType Config);
	///File output log Constructor
	Logger(Log::ConfigType Config, string Location);


private:
	void Write(string message);
	void WriteFile(string message);
	void WriteCon(string message);

	Log::MethodType method;
	Log::ConfigType config;

	string filepath;
	std::ofstream os;
	boost::filesystem::path path;

	boost::mutex con_mutex;
	boost::mutex fil_mutex;
};
#endif