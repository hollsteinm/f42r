#include "SecureClientTCP.h"
#include "NetworkDefinitions.h"
#include "CommandParser.h"
#include "ParserKeys.h"
#include <boost\bind.hpp>
#include <iostream>
#include <boost\shared_ptr.hpp>

SecureClientTCP::SecureClientTCP(boost::shared_ptr<boost::asio::io_service> service,
	string verifyFile,
	boost::function2<void, std::map<string, string>, string> OnReadComplete,
	boost::function2<void, const boost::system::error_code&, size> OnWriteComplete
	) : SecureTCP(service, OnReadComplete, OnWriteComplete)
{
	boost::system::error_code error;
	SSLContext = boost::shared_ptr<boost::asio::ssl::context>(new boost::asio::ssl::context(boost::asio::ssl::context::sslv23));
	SSLContext->load_verify_file(verifyFile, error);
	if (error)
		std::cout << error.message() << std::endl;
}

SecureClientTCP::~SecureClientTCP()
{

}

passfail SecureClientTCP::Connect(string host, string port)
{
	boost::system::error_code error;

	Socket = boost::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(*IOService, *SSLContext));
	boost::asio::ip::tcp::resolver resolver(*IOService);
	boost::asio::ip::tcp::resolver::query query(host, port);

	Socket->set_verify_mode(boost::asio::ssl::verify_peer, error);
	Socket->set_verify_callback(boost::asio::ssl::rfc2818_verification(host), error);

	boost::asio::connect(Socket->lowest_layer(), resolver.resolve(query), error);

	Socket->handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::handshake_type::client, error);

	bConnectionEstablished = !error;
	if (error)
		std::cerr << error.message();
	return bConnectionEstablished;
}