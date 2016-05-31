#ifndef SERVER_CRYPTO_CHAT_H
#define SERVER_CRYPTO_CHAT_H
#include "ServiceInterface.h"
#include "NetworkDefinitions.h"
class CryptoChatServerService :
	public ServiceInterface < class SecureServerTCP >
{
public:
	CryptoChatServerService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger);
	~CryptoChatServerService();

	virtual string Identifier() override;

	virtual void NetworkReadCallback(std::map<string, string> meta, string message) override;
	virtual void NetworkWriteCallback(const boost::system::error_code& errorCode, size bytesTransferred) override;
};
#endif