#ifndef EVENT_MESSENGER_SERVICE_H
#define EVENT_MESSENGER_SERVICE_H
#include "types.h"
#include <boost\signals2.hpp>
class EventMessengerService
{
	typedef boost::signals2::signal<void(const struct Event&)> EventSignaler;
	typedef boost::signals2::connection Slot;

public:
	EventMessengerService();
	~EventMessengerService();

	Slot& Register(boost::function1<void, const struct Event&> EventHandler);
	void Unregister(Slot& Slot);
	void Signal(const struct Event& Event);

private:
	boost::shared_ptr<EventSignaler> EventSignal;
};
#endif