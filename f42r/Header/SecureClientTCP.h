#ifndef SECURE_CLIENT_H
#define SECURE_CLIENT_H
#include "SecureTCP.h"
class SecureClientTCP : public SecureTCP
{
public:
	SecureClientTCP(boost::shared_ptr<boost::asio::io_service> service,
		string verifyFile,
		boost::function2<void, std::map<string, string>, string> OnReadComplete,
		boost::function2<void, const boost::system::error_code&, size> OnWriteComplete
		);
	virtual ~SecureClientTCP();

	virtual passfail Connect(string host, string port) override;

protected:
private:
};
#endif