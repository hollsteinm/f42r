#pragma once
#include "types.h"

namespace Mode{
	ENUM_2(Type, Client, Server, Client)
}

class ModeFactory
{
public:
	ModeFactory();
	~ModeFactory();

	static boost::shared_ptr<class ModeInterface> Get(boost::shared_ptr<class CommandParser> const Parser, boost::shared_ptr<class EventMessengerService> Messenger);
};