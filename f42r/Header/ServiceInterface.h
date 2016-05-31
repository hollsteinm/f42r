#ifndef SERVICE_INTERFACE_H
#define SERVICE_INTERFACE_H
#include "types.h"
#include <boost\shared_ptr.hpp>
#include <boost\system\system_error.hpp>
#include <map>

template<class TConnection>
class ServiceInterface
{
public:
	virtual ~ServiceInterface() {}

	virtual string Identifier() = 0;

	virtual void NetworkReadCallback(std::map<string, string> meta, string message) = 0;
	virtual void NetworkWriteCallback(const boost::system::error_code& errorCode, size bytesTransferred) = 0;

	void Initialize(boost::shared_ptr<class Logger> Log) { this->Log = Log; }
	void PostInitialize(boost::shared_ptr<TConnection> Remote) { this->Remote = Remote; }

protected:
	ServiceInterface(boost::shared_ptr<class CommandParser> Parser, boost::shared_ptr<class EventMessengerService> Messenger)
	{
		this->Parser = Parser;
		this->Messenger = Messenger;
	}

	boost::shared_ptr<class CommandParser> Parser;
	boost::shared_ptr<class EventMessengerService> Messenger;
	boost::shared_ptr<TConnection> Remote;
	boost::shared_ptr<class Logger> Log;
};
#endif