#include "ServiceProvider.h"
#include "ServiceInterface.h"
#include "CommandParser.h"
#include "ParserKeys.h"
#include "CryptoChatService.h"
#include "SecureServerTCP.h"
#include "CryptoChatServerService.h"
#include "EventMessengerService.h"

ServiceProvider::ServiceProvider()
{
}

ServiceProvider::~ServiceProvider()
{
}

boost::shared_ptr<ServiceInterface<SecureClientTCP>> ServiceProvider::CreateClientService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<EventMessengerService> Messenger)
{
	ServiceName::Client::Type type;
	ServiceName::Client::parse(Parser->GetValue(SERVICE), &type);
	switch (type)
	{
	case ServiceName::Client::CryptoChat:
		boost::shared_ptr<ServiceInterface<SecureClientTCP>>(new CryptoChatService(Parser, Messenger));
	case ServiceName::Client::Reserved_1:
	case ServiceName::Client::Reserved_2:
	case ServiceName::Client::Reserved_3:
	case ServiceName::Client::Reserved_4:
	case ServiceName::Client::Reserved_5:
	case ServiceName::Client::Reserved_6:
	case ServiceName::Client::Reserved_7:
	case ServiceName::Client::Reserved_8:
	case ServiceName::Client::Dynamic:
	default:
		return boost::shared_ptr<ServiceInterface<SecureClientTCP>>(new CryptoChatService(Parser, Messenger));
	}
}

boost::shared_ptr<ServiceInterface<class SecureServerTCP>> ServiceProvider::CreateServerService(boost::shared_ptr<class CommandParser> Parser,boost::shared_ptr<EventMessengerService> Messenger)
{
	ServiceName::Server::Type type;
	ServiceName::Server::parse(Parser->GetValue(SERVICE), &type);
	switch (type)
	{
	case ServiceName::Client::CryptoChat:
		boost::shared_ptr<ServiceInterface<SecureServerTCP>>(new CryptoChatServerService(Parser, Messenger));
	case ServiceName::Client::Reserved_1:
	case ServiceName::Client::Reserved_2:
	case ServiceName::Client::Reserved_3:
	case ServiceName::Client::Reserved_4:
	case ServiceName::Client::Reserved_5:
	case ServiceName::Client::Reserved_6:
	case ServiceName::Client::Reserved_7:
	case ServiceName::Client::Reserved_8:
	case ServiceName::Client::Dynamic:
	default:
		return boost::shared_ptr<ServiceInterface<SecureServerTCP>>(new CryptoChatServerService(Parser, Messenger));
	}
}