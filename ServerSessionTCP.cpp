#include "ServerSessionTCP.h"
#include "Logger.h"
#include "NetworkEvent.h"
#include "EventMessengerService.h"
#include "EventHandler.h"
#include <iostream>

ServerSessionTCP::ServerSessionTCP(boost::shared_ptr<boost::asio::ssl::context> context, 
	boost::shared_ptr<boost::asio::io_service> service,
	boost::function2<void, std::map<string, string>, string> OnReadComplete,
	boost::function2<void, const boost::system::error_code&, size> OnWriteComplete,
	boost::shared_ptr<EventMessengerService> Messenger,
	boost::shared_ptr<Logger> Log)
	: SecureTCP(service, OnReadComplete, OnWriteComplete),
	EventHandler(Messenger)
{
	this->Log = Log;
	this->Messenger = Messenger;
	SSLContext = context;
	Socket = boost::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(*IOService, *SSLContext));
}

ServerSessionTCP::~ServerSessionTCP()
{

}

void ServerSessionTCP::Handle(const Event& Event)
{
	uint8 id = Event.GetIdentifier();
	//if list
	if (id == NetworkEvent::identity)
	{
		const NetworkEvent& nevent = dynamic_cast<const NetworkEvent&>(Event);
		WriteAsync(nevent.GetMessageData(), nevent.GetMeta());
	}
}

passfail ServerSessionTCP::Connect(string host, string port)
{
	boost::system::error_code error;
	Socket->handshake(boost::asio::ssl::stream_base::server, error);

	auto endpoint = Socket->lowest_layer().remote_endpoint();
	std::stringstream ss;
	ss << "Connection: " << endpoint.address() << " : " << endpoint.port();
	Log->Info(ss.str());
	if (!error){
		bConnectionEstablished = true;
	}
	else{
		Log->Erro(error.message());
	}
	return bConnectionEstablished;
}

boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& ServerSessionTCP::GetSocket() const
{
	return Socket->lowest_layer();
}

void ServerSessionTCP::ReadHandler(const boost::system::error_code& errorCode, size bytesTransferred)
{
	//TODO: fix this hack!
	Log->Info(Socket->lowest_layer().remote_endpoint().address().to_string() + ":" + "bytes(" + std::to_string(bytesTransferred) + ")");
	if (errorCode != boost::asio::error::eof && errorCode.message().compare("The operation completed successfully") != 0)
	{
		Log->Erro(errorCode.message() + ":" + Socket->lowest_layer().remote_endpoint().address().to_string());
	}
	else
	{
		SecureTCP::ReadHandler(errorCode, bytesTransferred);
		ReadAsync();
	}
}

void ServerSessionTCP::WriteAsync(string& writeData)
{
	SecureTCP::WriteAsync(writeData);
}

void ServerSessionTCP::WriteAsync(string& writeData, std::map<string, string> metaHeaders)
{
	SecureTCP::WriteAsync(writeData, metaHeaders);
}