#ifndef SERVER_MODE
#define SERVER_MODE
#include "ModeInterface.h"
#include "ServiceInterface.h"
#include "NetworkDefinitions.h"
class ServerMode : public ModeInterface
{
public:
	ServerMode(boost::shared_ptr<class EventMessengerService> Messenger);
	~ServerMode();

	virtual int32 Run(boost::shared_ptr<class CommandParser> const Parser) override;
private:
	boost::shared_ptr<class SecureServerTCP> Server;
	boost::shared_ptr<ServiceInterface<class SecureServerTCP>> Service;

	void Initialize(boost::shared_ptr<class CommandParser> const Parser);
};
#endif