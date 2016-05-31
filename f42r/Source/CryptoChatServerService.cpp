#include "CryptoChatServerService.h"
#include "SecureServerTCP.h"
#include "ParserKeys.h"
#include "NetworkDefinitions.h"
#include "InfoHarvester.h"
#include "NetworkEvent.h"
#include "Logger.h"
#include "EventMessengerService.h"
#include <iostream>

CryptoChatServerService::CryptoChatServerService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger)
	: ServiceInterface<SecureServerTCP>(Parser, Messenger)
{
}

CryptoChatServerService::~CryptoChatServerService()
{
}

string CryptoChatServerService::Identifier()
{
	return ServiceName::Server::to_string(ServiceName::Server::CryptoChat);
}

void CryptoChatServerService::NetworkReadCallback(std::map<string, string> meta, string message)
{
	if (meta.find(CLASS) != meta.cend())
	{
		if (boost::iequals(meta[CLASS], NetworkProtocol::to_string(NetworkProtocol::Checkin)))
		{
			for (auto kvp : meta)
			{
				Log->Info(kvp.first + ':' + kvp.second);
			}
			if (meta.find(SESSION_IDENTITY) != meta.cend())
			{
				Log->Info(meta[SESSION_IDENTITY]);
			}
		}
		if (boost::iequals(meta[CLASS], MESSAGE_CLASS))
		{
			Messenger->Signal(NetworkEvent(message, meta, NetworkProtocol::Message));
		}
	}
}

void CryptoChatServerService::NetworkWriteCallback(const boost::system::error_code& errorCode, size bytesTransferred)
{

}