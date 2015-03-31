#include "Event.h"

const uint8 Event::identity = 0xFF;

Event::Event()
{
	id = identity;
}


Event::~Event()
{
	id = identity;
}


const uint8 Event::GetIdentifier() const
{
	return id;
}