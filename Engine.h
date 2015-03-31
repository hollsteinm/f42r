#ifndef ENGINE_H
#define ENGINE_H
#include "types.h"
#include <boost\shared_ptr.hpp>

class Engine
{
public:
	~Engine();
	static boost::shared_ptr<Engine> Create(int32 argc, char* argv[]);
	int32 Run();
private:
	Engine(int32 argc, char* argv[]);
	
	boost::shared_ptr<class CommandParser> Parser;
	boost::shared_ptr<class EventMessengerService> Messaging;
	SecureString commands;
};
#endif