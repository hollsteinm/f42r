#include "ServerMode.h"
#include "CommandParser.h"
#include <boost\shared_ptr.hpp>
#include "SecureServerTCP.h"
#include "ParserKeys.h"
#include "ServiceProvider.h"
#include "Logger.h"
#include "EventMessengerService.h"
#include <iostream>

ServerMode::ServerMode(boost::shared_ptr<EventMessengerService> Messenger)
	: ModeInterface(Messenger)
{
}

ServerMode::~ServerMode()
{
}

void ServerMode::Initialize(boost::shared_ptr<CommandParser> const Parser)
{
	Log = boost::shared_ptr<Logger>(Logger::Create(Parser));

	Service = ServiceProvider::CreateServerService(Parser, Messenger);
	Service->Initialize(Log);
}

int32 ServerMode::Run(boost::shared_ptr<CommandParser> const Parser)
{
	bool valid = Parser->HasKey(PORT) & Parser->HasKey(CHAIN_FILE) & Parser->HasKey(DH_FILE) & Parser->HasKey(KEY_FILE) & Parser->HasKey(PASSWORD);
	if (valid)
	{
		Initialize(Parser);

		Server = boost::shared_ptr<SecureServerTCP>(
			new SecureServerTCP(
			IOService,
			atoi(Parser->GetValue(PORT).c_str()),
			Parser->GetValue(CHAIN_FILE),
			Parser->GetValue(KEY_FILE),
			Parser->GetValue(DH_FILE),
			Parser->GetValue(PASSWORD),
			boost::bind(&ServiceInterface<SecureServerTCP>::NetworkReadCallback, Service, _1, _2),
			boost::bind(&ServiceInterface<SecureServerTCP>::NetworkWriteCallback, Service, _1, _2),
			Messenger,
			Log
		));

		Service->PostInitialize(Server);
		IOService->run();
	}
	return 0;
}
