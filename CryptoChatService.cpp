#include "CryptoChatService.h"
#include "ParserKeys.h"
#include "SecureClientTCP.h"
#include "CommandParser.h"
#include <boost\thread.hpp>
#include <iostream>

CryptoChatService::CryptoChatService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger)
	: ServiceInterface<SecureClientTCP>(Parser, Messenger)
{
	Meta.emplace(std::pair<string, string>(CLASS, MESSAGE_CLASS));
	Meta.emplace(std::pair<string, string>(SERVICE, Identifier()));
	if (Parser->HasKey(SESSION_IDENTITY) && Meta.find(SESSION_IDENTITY) == Meta.cend())
	{
		Meta.emplace(std::pair<string, string>(SESSION_IDENTITY, Parser->GetValue(SESSION_IDENTITY)));
	}
}

CryptoChatService::~CryptoChatService()
{
}

string CryptoChatService::Identifier()
{
	return ServiceName::Client::to_string(ServiceName::Client::CryptoChat);
}

void CryptoChatService::NetworkReadCallback(std::map<string, string> meta, string message)
{
	if (meta.find(CLASS) != meta.cend() && meta.find(SESSION_IDENTITY) != meta.cend()){
		if (boost::iequals(meta[CLASS], MESSAGE_CLASS)){
			std::cout << meta[SESSION_IDENTITY] << ":\t" << message << std::endl;
		}
	}
	else
	{
		for (auto kvp : meta)
		{
			std::cout << kvp.first << ":" << kvp.second << std::endl;
		}
		std::cout << message << std::endl;
	}
	Remote->ReadAsync();
}

void CryptoChatService::NetworkWriteCallback(const boost::system::error_code& errorCode, size bytesTransferred)
{
	boost::thread([this] () {
		static const size bufferSize = 1024;
		char buffer[bufferSize];
		std::cin.getline(buffer, bufferSize);
		string msg(buffer);
		Remote->WriteAsync(msg, Meta);
	});
}