#include "EventMessengerService.h"
#include "Event.h"

EventMessengerService::EventMessengerService()
	: EventSignal(new EventSignaler())
{
}


EventMessengerService::~EventMessengerService()
{
}

void EventMessengerService::Unregister(Slot& Slot)
{
	EventSignal->disconnect(Slot);
}

EventMessengerService::Slot& EventMessengerService::Register(boost::function1<void, const Event&> EventHandler)
{
	return EventSignal->connect(EventHandler);
}

void EventMessengerService::Signal(const struct Event& Event)
{
	(*EventSignal)(Event);
}