#include "EventHandler.h"
#include "EventMessengerService.h"

EventHandler::EventHandler(boost::shared_ptr<EventMessengerService> EventSystem)
	: MySlot(EventSystem->Register(boost::bind(&EventHandler::Handle, this, _1)))
{
	this->EventSystem = EventSystem;
}

EventHandler::~EventHandler()
{
}

void EventHandler::Unregister()
{
	EventSystem->Unregister(MySlot);
}