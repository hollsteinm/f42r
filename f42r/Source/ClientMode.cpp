#include "ClientMode.h"
#include "CommandParser.h"
#include <boost\shared_ptr.hpp>
#include "SecureClientTCP.h"
#include "ParserKeys.h"
#include "InfoHarvester.h"
#include "NetworkDefinitions.h"
#include "ServiceProvider.h"
#include "ServiceInterface.h"
#include "EventMessengerService.h"
#include "Logger.h"
#include "NetworkEvent.h"
#include <boost\bind.hpp>
#include <iostream>

ClientMode::ClientMode(boost::shared_ptr<EventMessengerService> Messenger)
	: ModeInterface(Messenger)
{
}

ClientMode::~ClientMode()
{
}

void ClientMode::Initialize(boost::shared_ptr<CommandParser> Parser)
{
	Service = ServiceProvider::CreateClientService(Parser, Messenger);
	Log = boost::shared_ptr<Logger>(Logger::Create(Parser));
	Service->Initialize(Log);
}

int32 ClientMode::Run(boost::shared_ptr<CommandParser> const Parser)
{
	ConnectionType::Type Type;
	ConnectionType::parse(Parser->GetValue(CLIENT_CONNECTION_TYPE), &Type);
	Initialize(Parser);

	switch (Type)
	{
	case ConnectionType::Basic:
		BasicMode(Parser);
		break;
	case ConnectionType::HTTPS:
		HTTPSMode(Parser);
		break;
	default:
		return 1;
	}
	IOService->run();
	return 0;
}

void ClientMode::BasicMode(boost::shared_ptr<CommandParser> Parser)
{
	Remote = boost::shared_ptr<SecureClientTCP>(
		new SecureClientTCP(
		IOService,
		Parser->GetValue(VERIFY_FILE),
		boost::bind(&ServiceInterface<SecureClientTCP>::NetworkReadCallback, Service, _1, _2),
		boost::bind(&ServiceInterface<SecureClientTCP>::NetworkWriteCallback, Service, _1, _2)
		));

	if (Remote->Connect(Parser->GetValue(HOST), Parser->GetValue(PORT)))
	{
		std::map<string, string> meta;
		meta.emplace(std::pair<string, string>(CLASS, NetworkProtocol::to_string(NetworkProtocol::Checkin)));
		meta.emplace(std::pair<string, string>(SERVICE, Service->Identifier()));
		meta.emplace(std::pair<string, string>(SESSION_IDENTITY, Parser->GetValue(SESSION_IDENTITY)));

		for (auto pair : Harvester->GetAllInfoPairs())
		{
			meta.emplace(std::pair<string, string>(pair.first, pair.second));
		}
		Remote->WriteAsync(NetworkProtocol::to_string(NetworkProtocol::Checkin), meta);
		Remote->ReadAsync();
		Service->PostInitialize(Remote);
	}
}

void ClientMode::HTTPSMode(boost::shared_ptr<CommandParser> Parser)
{
	(void*)(0);
}
