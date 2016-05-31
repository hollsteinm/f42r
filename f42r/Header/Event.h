#ifndef EVENT_H
#define EVENT_H
#include "types.h"
#include <boost/serialization/base_object.hpp>
struct Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & id;
	}

public:
	Event();
	virtual ~Event();

	const uint8 GetIdentifier() const;

	const static uint8 identity;

protected:
	uint8 id;
};
#endif