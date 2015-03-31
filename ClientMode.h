#pragma once
#include "ModeInterface.h"
#include "ServiceInterface.h"

namespace ConnectionType
{
	ENUM_2(Type, Basic, HTTPS, HTTPS)
}

class ClientMode :
	public ModeInterface
{
public:
	ClientMode(boost::shared_ptr<class EventMessengerService> Messenger);
	~ClientMode();
	virtual int32 Run(boost::shared_ptr<class CommandParser> const Parser) override;

private:
	boost::shared_ptr<class SecureClientTCP> Remote;
	boost::shared_ptr<ServiceInterface<class SecureClientTCP>> Service;

	void BasicMode(boost::shared_ptr<class CommandParser> Parser);
	void HTTPSMode(boost::shared_ptr<class CommandParser> Parser);
	void Initialize(boost::shared_ptr<class CommandParser> Parser);
};