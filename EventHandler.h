#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include "types.h"
#include <boost\signals2.hpp>
class EventMessengerService;
struct EventHandler
{
public:
	EventHandler(boost::shared_ptr<EventMessengerService> EventSystem);
	virtual ~EventHandler();

	virtual void Handle(const struct Event& Event) = 0;

	void Unregister();
private:
	boost::signals2::connection MySlot;
	boost::shared_ptr<EventMessengerService> EventSystem;
};
#endif