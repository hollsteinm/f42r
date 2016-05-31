#include "NetworkEvent.h"

const uint8 NetworkEvent::identity = 0x00;

NetworkEvent::NetworkEvent(string message, std::map<string, string> meta, NetworkProtocol::Type type)
{
	this->message = message;
	this->meta = meta;
	this->type = type;
	id = identity;
}

NetworkEvent::NetworkEvent(string message, std::map<string, string> meta, string type)
{
	this->message = message;
	this->meta = meta;
	parse(type, &this->type);
	id = identity;
}

NetworkEvent::NetworkEvent()
	:meta()
{
	type = NetworkProtocol::Message;
	message = "";
	id = identity;
}

NetworkEvent::~NetworkEvent()
{
	
}

string NetworkEvent::GetMessageData() const 
{
	return message;
}

std::map<string, string> NetworkEvent::GetMeta() const 
{ 
	return meta; 
}

NetworkProtocol::Type NetworkEvent::GetType() const 
{ 
	return type; 
}