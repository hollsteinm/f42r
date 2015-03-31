#ifndef SERVICE_PROVIDER_H
#define SERVICE_PROVIDER_H
#include "types.h"
#include <boost\shared_ptr.hpp>
#include "ServiceInterface.h"
#include "NetworkDefinitions.h"
class ServiceProvider
{
public:
	ServiceProvider();
	~ServiceProvider();

	static boost::shared_ptr<ServiceInterface<class SecureClientTCP>> CreateClientService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger);
	static boost::shared_ptr<ServiceInterface<class SecureServerTCP>> CreateServerService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger);
};
#endif