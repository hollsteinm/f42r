#ifndef NETWORK_EVENT_H
#define NETWORK_EVENT_H
#include "Event.h"
#include <map>
#include <boost/serialization/map.hpp>
namespace NetworkProtocol
{
	ENUM_3(Type, Message, Checkin, Checkout, Checkout)
}

class NetworkEvent :
	public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
		ar & message;
		ar & meta;
		ar & type;
	}

public:
	NetworkEvent(string message, std::map<string, string> meta, NetworkProtocol::Type type);
	NetworkEvent(string message, std::map<string, string> meta, string type);
	NetworkEvent(); //See if we can avoid this
	virtual ~NetworkEvent();

	string GetMessageData() const;
	std::map<string, string> GetMeta() const;
	NetworkProtocol::Type GetType() const;

	const static uint8 identity;

private:
	string message;
	std::map<string, string> meta;
	NetworkProtocol::Type type;
};
#endif