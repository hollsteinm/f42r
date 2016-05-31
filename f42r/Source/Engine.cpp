#include "Engine.h"
#include "CommandParser.h"
#include "ModeFactory.h"
#include "ModeInterface.h"
#include <boost\shared_ptr.hpp>
#include "EventMessengerService.h"

Engine::Engine(int32 argc, char* argv[])
{
	for (int32 i = 0; i < argc; ++i)
		commands.append(argv[i]);
	Parser = boost::shared_ptr<CommandParser>(new CommandParser());
	Messaging = boost::shared_ptr<EventMessengerService>(new EventMessengerService());
}

boost::shared_ptr<Engine> Engine::Create(int32 argc, char* argv[])
{
	return boost::shared_ptr<Engine>(new Engine(argc, argv));
}

Engine::~Engine()
{
}

int32 Engine::Run()
{
	if (Parser->Parse(commands)){
		return ModeFactory::Get(Parser, Messaging)->Run(Parser);
	}
	return 0;
}