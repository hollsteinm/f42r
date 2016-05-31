#ifndef SECURE_SERVER_TCP
#define SECURE_SERVER_TCP
#include "types.h"
#include <boost\asio.hpp>
#include <boost\asio\ssl.hpp>
#include "NetworkDefinitions.h"
class SecureServerTCP
{
public:
	SecureServerTCP(boost::shared_ptr<boost::asio::io_service> service,
		uint16 port,
		string chainfile,
		string keyfile,
		string dhfile,
		string password,
		boost::function2<void, std::map<string, string>, string> OnReadComplete,
		boost::function2<void, const boost::system::error_code&, size> OnWriteComplete,
		boost::shared_ptr<class EventMessengerService> Messenger,
		boost::shared_ptr<class Logger> Log);
	virtual ~SecureServerTCP();

	virtual void Listen();

private:
	boost::shared_ptr<boost::asio::ip::tcp::acceptor>				Acceptor;
	boost::shared_ptr<boost::asio::io_service>						IOService;
	boost::shared_ptr<boost::asio::ssl::context>					SSLContext;
	boost::function2<void, std::map<string, string>, string>		OnReadComplete;
	boost::function2<void, const boost::system::error_code&, size>	OnWriteComplete;
	boost::shared_ptr<class Logger>									Log;

	string GetPassword() const;
	string Password;

	virtual void OnAccept(class ServerSessionTCP* session, const boost::system::error_code& error);

	boost::shared_ptr<class EventMessengerService> Messenger;
};
#endif