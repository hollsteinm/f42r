#include "ModeFactory.h"
#include "CommandParser.h"
#include "DefinedModes.h"
#include "EventMessengerService.h"
#include "ParserKeys.h"
#include <boost\shared_ptr.hpp>

ModeFactory::ModeFactory()
{
}

ModeFactory::~ModeFactory()
{
}

boost::shared_ptr<ModeInterface> ModeFactory::Get(boost::shared_ptr<CommandParser> const Parser, boost::shared_ptr<EventMessengerService> Messenger)
{
	Mode::Type type;
	Mode::parse(Parser->GetValue(MODE), &type);
	switch (type)
	{
	case Mode::Client:
		return boost::shared_ptr<ModeInterface>(new ClientMode(Messenger));
	case Mode::Server:
		return boost::shared_ptr<ModeInterface>(new ServerMode(Messenger));
	default:
		return boost::shared_ptr<ModeInterface>();
	}
}