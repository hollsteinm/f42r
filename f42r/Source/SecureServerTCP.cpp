#include "SecureServerTCP.h"
#include "ServerSessionTCP.h"
#include "Logger.h"
#include "EventMessengerService.h"
#include <boost\bind.hpp>
#include <iostream>

SecureServerTCP::SecureServerTCP(boost::shared_ptr<boost::asio::io_service> service,
	uint16 port,
	string chainfile,
	string keyfile,
	string dhfile,
	string password,
	boost::function2<void, std::map<string, string>, string> OnReadComplete,
	boost::function2<void, const boost::system::error_code&, size> OnWriteComplete,
	boost::shared_ptr<EventMessengerService> Messenger,
	boost::shared_ptr<Logger> Log)
	: Acceptor(new boost::asio::ip::tcp::acceptor(*service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))),
	SSLContext(new boost::asio::ssl::context(boost::asio::ssl::context::sslv23))
{
	boost::system::error_code error;
	this->Log = Log;
	this->IOService = service;
	this->OnReadComplete = OnReadComplete;
	this->OnWriteComplete = OnWriteComplete;
	this->Password = password;
	this->Messenger = Messenger;

	SSLContext->set_options(
		boost::asio::ssl::context::default_workarounds
		| boost::asio::ssl::context::no_sslv2
		| boost::asio::ssl::context::single_dh_use);
	SSLContext->set_password_callback(boost::bind(&SecureServerTCP::GetPassword, this));
	SSLContext->use_certificate_chain_file(chainfile, error);
	SSLContext->use_private_key_file(keyfile, boost::asio::ssl::context::pem, error);
	SSLContext->use_tmp_dh_file(dhfile, error);
	if (!error)
	{
		Listen();
	}
	else{
		Log->Erro(error.message());
	}
}

SecureServerTCP::~SecureServerTCP()
{
}

string SecureServerTCP::GetPassword() const
{
	//TODO SecureString implementation (encrypted in memory)
	return Password;
}

void SecureServerTCP::Listen()
{
	ServerSessionTCP* session = new ServerSessionTCP(SSLContext, IOService, OnReadComplete, OnWriteComplete, Messenger, Log);
	Acceptor->async_accept(session->GetSocket(), boost::bind(&SecureServerTCP::OnAccept, this, session, boost::asio::placeholders::error));
}

void SecureServerTCP::OnAccept(ServerSessionTCP* Session, const boost::system::error_code& error)
{
	if (!error)
	{
		if (Session->Connect(NULL_META, NULL_META))
			Session->ReadAsync();
		else
			delete Session;
	}
	else
	{
		delete Session;
	}
	Listen();
}