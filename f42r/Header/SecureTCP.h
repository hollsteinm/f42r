#ifndef SECURE_TCP
#define SECURE_TCP
#include "types.h"
#include <boost\asio.hpp>
#include <boost\asio\ssl.hpp>

class SecureTCP
{
public:
	virtual ~SecureTCP();

	virtual void WriteAsync(string& writeData);
	virtual void WriteAsync(string& writeData, std::map<string, string> metaHeaders);
	virtual void WriteAsync(struct Event* event);
	virtual void ReadAsync();
	virtual logic ConnectionEstablished();
	virtual passfail Connect(string host, string port) = 0;

protected:
	SecureTCP(boost::shared_ptr<boost::asio::io_service> service,
		boost::function2<void, std::map<string, string>, string> OnReadComplete,
		boost::function2<void, const boost::system::error_code&, size> OnWriteComplete
		);

	virtual void ReadHandler(const boost::system::error_code& errorCode, size bytesTransferred);

	boost::shared_ptr<boost::asio::io_service>										IOService;
	boost::shared_ptr<boost::asio::ssl::context>									SSLContext;
	boost::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>		Socket;
	boost::function2<void, std::map<string, string>, string>						OnReadComplete;
	boost::function2<void, const boost::system::error_code&, size>					OnWriteComplete;
	boost::asio::streambuf readStream;

	logic bConnectionEstablished;
private:
};
#endif