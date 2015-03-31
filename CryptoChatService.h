#ifndef CRYPTO_CHAT_SERVICE_H
#define CRYPTO_CHAT_SERVICE_H
#include "ServiceInterface.h"

class CryptoChatService :
	public ServiceInterface<class SecureClientTCP>
{
public:
	CryptoChatService(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger);
	~CryptoChatService();

	virtual string Identifier() override;

	virtual void NetworkReadCallback(std::map<string, string> meta, string message) override;
	virtual void NetworkWriteCallback(const boost::system::error_code& errorCode, size bytesTransferred) override;

private:
	std::map<string, string> Meta;
};
#endif