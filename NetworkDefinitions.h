#ifndef NETWORK_DEFINITIONS_H
#define NETWORK_DEFINITIONS_H

#include "types.h"
#include <boost\bind.hpp>
#include <boost\signals2.hpp>

#define BUFFER_SIZE			1024
#define BEGIN_TRANSMISSION	"%BEG%\r\n"
#define END_TRANSMISSION	"\r\n%END%"
#define META_BEGIN			"{meta="
#define META_END			"}"
#define BODY_BEGIN			"{body="
#define BODY_END			"}"
#define NULL_META			"nil"
#define IP					"ip"
#define SERIALIZED			"serialized"

#endif