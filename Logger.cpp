#include "CommandParser.h"
#include "Logger.h"
#include "ParserKeys.h"
#include <iostream>

string times::date_as_string(bool local)
{
	std::time_t now = std::time(0);
	tm * t = new tm();
	char buff[80];
	time(&now);
	if (local)
	{
		localtime_s(t, &now);
	}
	else
	{
		gmtime_s(t, &now);
	}
	strftime(buff, 80, "%c", t);
	delete t;
	return string(buff);

}

string times::date_as_string()
{
	return date_as_string(true);
}

string times::date_as_file_string()
{
	std::time_t now = std::time(0);
	tm * local = new tm();
	char buff[80];
	time(&now);
	localtime_s(local, &now);
	strftime(buff, 80, "_%Y_%m_%d.log.txt", local);
	delete local;
	return string(buff);
}

Logger::Logger()
{
	method = Log::silent;
	config = Log::nolog;
}

Logger::Logger(Log::ConfigType Config)
{
	method = Log::console;
	this->config = Config;
}

Logger::Logger(Log::ConfigType Config, string Locatn)
	: path(Locatn.c_str())
{
	try{
		if (!boost::filesystem::exists(path))
		{
			boost::filesystem::create_directory(path);
		}
		if (boost::filesystem::is_regular_file(path))
			os.open(path.c_str(), std::ios::out | std::ios::app);
		else
		{
			string finalLocatn;
			if (Locatn[Locatn.size() - 1] != '\\')
			{
				finalLocatn = Locatn + "\\" + times::date_as_file_string();
			}
			else
			{
				finalLocatn = Locatn + times::date_as_file_string();
			}
			path = finalLocatn;
			os.open(path.c_str(), std::ios::out | std::ios::app);
		}
	}
	catch (const boost::filesystem::filesystem_error& er)
	{
		WriteCon(er.what());
	}
	this->config = Config;
	method = Log::file;
}

Logger::~Logger()
{
}

boost::shared_ptr<Logger> Logger::Create(boost::shared_ptr<CommandParser> Parser)
{
	Log::MethodType method = Log::console;
	Log::ConfigType config = Log::development;
	if (Parser->HasKey(LOG_METHOD))
		parse(Parser->GetValue(LOG_METHOD), &method);
	if (Parser->HasKey(LOG_CONFIG))
		parse(Parser->GetValue(LOG_CONFIG), &config);
	switch (method)
	{
	case Log::silent:
		return boost::shared_ptr<Logger>(new Logger());
	case Log::console:
		return boost::shared_ptr<Logger>(new Logger(config));
	case Log::file:
		return boost::shared_ptr<Logger>(new Logger(config, string(Parser->GetValue(LOG_FILEPATH))));
	default:
		return boost::shared_ptr<Logger>(new Logger(config));
	}
}

Logger& Logger::Log(Log::TraceType trace, string msg)
{
	string message = "[" + times::date_as_string() + "][" + to_string(trace) + "]:\t" + msg;
	switch (config)
	{
	case Log::nolog:
		break;
	case Log::development:
		Write(message);
		break;
	case Log::production:
		switch (trace)
		{
		case Log::info:
		case Log::error:
			Write(message);
			break;
		default:
			break;
		}
		break;
	case Log::testing:
		switch (trace)
		{
		case Log::info:
		case Log::warn:
		case Log::error:
			Write(message);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return *this;
}

Logger& Logger::Info(string message)
{
	return Log(Log::info, message);
}

Logger& Logger::Warn(string message)
{
	return Log(Log::warn, message);
}

Logger& Logger::Erro(string message)
{
	return Log(Log::error, message);
}

Logger& Logger::Dbug(string message)
{
	return Log(Log::debug, message);
}

void Logger::Write(string message)
{
	switch (method)
	{
	case Log::silent:
		break;
	case Log::console:
		WriteCon(message);
		break;
	case Log::file:
		WriteFile(message);
		break;
	default:
		WriteCon(message);
		break;
	}
}

void Logger::WriteFile(string message)
{
	fil_mutex.lock();
	if (!os.is_open())
		os.open(path.c_str(), std::ios::out | std::ios::app);

	string finalMessage = message + "\r\n";
	os.write(finalMessage.c_str(), finalMessage.size());
	fil_mutex.unlock();
}

void Logger::WriteCon(string message)
{
	con_mutex.lock();
	std::cout << message << std::endl;
	con_mutex.unlock();
}

const Log::MethodType Logger::GetLogMethod() const
{
	return method;
}