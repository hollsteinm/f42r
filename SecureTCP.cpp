#include <boost\bind.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include "SecureTCP.h"
#include "NetworkDefinitions.h"
#include "CommandParser.h"
#include "ParserKeys.h"
#include "Event.h"
#include "NetworkEvent.h"
#include <iostream>

SecureTCP::SecureTCP(boost::shared_ptr<boost::asio::io_service> service,
	boost::function2<void, std::map<string, string>, string> OnReadComplete,
	boost::function2<void, const boost::system::error_code&, size> OnWriteComplete
	)
	: bConnectionEstablished(false)
{
	this->OnReadComplete = OnReadComplete;
	this->OnWriteComplete = OnWriteComplete;

	IOService = service;
}

SecureTCP::~SecureTCP()
{
}

logic SecureTCP::ConnectionEstablished()
{
	return bConnectionEstablished;
}

void SecureTCP::WriteAsync(string& writeData)
{
	string write = BEGIN_TRANSMISSION;
	write.append(META_BEGIN)
		.append(NULL_META)
		.append(META_END)
		.append(BODY_BEGIN)
		.append(writeData)
		.append(BODY_END)
		.append(END_TRANSMISSION);
	boost::asio::async_write(*Socket, boost::asio::buffer(write, write.size()), OnWriteComplete);
}

void SecureTCP::WriteAsync(string& writeData, std::map<string, string> metaHeaders)
{
	string write = BEGIN_TRANSMISSION;
	write.append(META_BEGIN);
	for (auto pair : metaHeaders)
	{
		string meta = "{";
		meta.append(pair.first)
			.append("=")
			.append(pair.second)
			.append("} ");
		write.append(meta);
	}
	write.append(META_END)
		.append(BODY_BEGIN)
		.append(writeData)
		.append(BODY_END)
		.append(END_TRANSMISSION);
	boost::asio::async_write(*Socket, boost::asio::buffer(write, write.size()), OnWriteComplete);
}

void SecureTCP::WriteAsync(Event* event)
{
	/**TESTING SERIALIZATION**/
	std::ostringstream archivestream;
	{
		boost::archive::text_oarchive archive(archivestream);

		archive.register_type<Event>();
		archive.register_type<NetworkEvent>();

		archive << event;
	}
	static std::map<string, string> serialMeta({
		std::pair<string, string>(CLASS, SERIALIZED)
	});
	WriteAsync(archivestream.str(), serialMeta);
	/**END TESTING SERIALIZATION**/
}

void SecureTCP::ReadAsync()
{
	boost::asio::async_read_until(*Socket, readStream, END_TRANSMISSION, boost::bind(&SecureTCP::ReadHandler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void SecureTCP::ReadHandler(const boost::system::error_code& errorCode, size bytesTransferred)
{
	std::istream input(&readStream);
	string data;
	string msg;
	while (std::getline(input, msg) && msg != END_TRANSMISSION)
	{
		data.append(msg);
	}
	boost::replace_first(data, BEGIN_TRANSMISSION, "");
	CommandParser parser;
	CommandParser metaOnly;
	std::map<string, string> metaData;

	if (parser.Parse(data))
	{
		if (parser.HasKey(META))
		{

			if (!boost::iequals(parser[META], NULL_META)){
				metaOnly.Parse(parser[META]);
				metaData = metaOnly.Content();
				if (metaOnly.HasKey(CLASS))
				{
					if (boost::iequals(metaOnly[CLASS], SERIALIZED))
					{
						/**TESTING SERIALIZATION**/
						Event e;
						if (parser.HasKey(BODY))
						{
							data = parser[BODY];
							{
								std::istringstream archivestream(data);
								boost::archive::text_iarchive archive(archivestream);

								archive.register_type<Event>();
								archive.register_type<NetworkEvent>();

								archive >> e;
							}
						}
						/**END TESTING SERIALIZATION**/
					}
				}

			}
		}
		if (parser.HasKey(BODY))
		{
			data = parser[BODY];
		}
	}
	OnReadComplete(metaData, data);
}
