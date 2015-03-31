#ifndef EVENT_H
#define EVENT_H
#include "Serializable.h"
#include <boost/serialization/base_object.hpp>
struct Event
	: Serializable
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Serializable>(*this);
		ar & id;
	}

public:
	Event();
	virtual ~Event();

	const uint8 GetIdentifier() const;

protected:
	uint8 id;
};
#endif