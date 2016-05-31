#include "ModeInterface.h"
#include "InfoHarvester.h"
#include "EventMessengerService.h"
#include <boost\asio.hpp>


ModeInterface::ModeInterface(boost::shared_ptr<EventMessengerService> Messenger)
	: IOService(new boost::asio::io_service()),
	Harvester(new InfoHarvester())
{
	this->Messenger = Messenger;
}


ModeInterface::~ModeInterface()
{
}