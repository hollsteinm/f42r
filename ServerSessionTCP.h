#ifndef SERVER_SESSION_TCP
#define SERVER_SESSION_TCP
#include "SecureTCP.h"
#include "NetworkDefinitions.h"
#include "EventHandler.h"
class ServerSessionTCP : public SecureTCP, EventHandler
{
public:
	ServerSessionTCP(boost::shared_ptr<boost::asio::ssl::context> context, 
		boost::shared_ptr<boost::asio::io_service> service,
		boost::function2<void, std::map<string, string>, string> OnReadComplete,
		boost::function2<void, const boost::system::error_code&, size> OnWriteComplete,
		boost::shared_ptr<class EventMessengerService> Messenger,
		boost::shared_ptr<class Logger> Log);
	virtual ~ServerSessionTCP();

	void Handle(const struct Event& Event) override;

	boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& GetSocket() const;
	virtual passfail Connect(string host, string port) override;

	virtual void WriteAsync(string& writeData) override;
	virtual void WriteAsync(string& writeData, std::map<string, string> metaHeaders) override;
protected:
	virtual void ReadHandler(const boost::system::error_code& errorCode, size bytesTransferred) override;
private:
	boost::shared_ptr<class EventMessengerService> Messenger;
	boost::shared_ptr<class Logger> Log;
};
#endif