#ifndef MODE_INTERFACE_H
#define MODE_INTERFACE_H
#include "types.h"
#include <boost\shared_ptr.hpp>
#include <boost\asio.hpp>
class ModeInterface
{
public:
	virtual ~ModeInterface();

	virtual int32 Run(boost::shared_ptr<class CommandParser> const Parser) = 0;

protected:
	ModeInterface(boost::shared_ptr<class EventMessengerService> Messenger);
	boost::shared_ptr<boost::asio::io_service> IOService;
	boost::shared_ptr<class InfoHarvester> Harvester;
	boost::shared_ptr<class Logger> Log;
	boost::shared_ptr<class EventMessengerService> Messenger;
};
#endif