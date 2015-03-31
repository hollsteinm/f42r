#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include "types.h"
namespace boost
{
	namespace serialization
	{
		class access;
	};
};

struct Serializable
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	}

public:
	Serializable();
	virtual ~Serializable();

};
#endif