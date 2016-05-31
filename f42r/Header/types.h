#ifndef TYPES_H
#define TYPES_H
#include <boost\algorithm\string.hpp>
#include <stdint.h>

typedef int8_t				int8;
typedef int16_t				int16;
typedef int32_t				int32;
typedef int64_t				int64;

typedef float_t				float32;
typedef double_t			float64;

typedef bool				logic;
typedef logic				passfail;

typedef uint8_t				uint8;
typedef uint16_t			uint16;
typedef uint32_t			uint32;
typedef uint64_t			uint64;

typedef int8				byte;
typedef int16				word;
typedef int32				dword;
typedef int64				qword;

typedef nullptr_t			null;
typedef	size_t				size;

typedef std::string			string;
typedef string				SecureString;

///
/// QUICK ENUMS
///
#ifndef ENUM_2
///Creates an enumeration with two members as well as auto generated parse and to_string free methods
#define ENUM_2(enumeration, a, b, def) enum enumeration{a, b}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
		else if(boost::iequals(value, #b)) \
		*out_enum = b; \
		else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		default: return #def; }}
#endif

#ifndef ENUM_3
///Creates an enumeration with three members as well as auto generated parse and to_string free methods
#define ENUM_3(enumeration, a, b, c, def) enum enumeration{a, b, c}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
		else if(boost::iequals(value, #b)) \
		*out_enum = b; \
		else if(boost::iequals(value, #c)) \
		*out_enum = c; \
		else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		default: return #def; }}
#endif

#ifndef ENUM_4
///Creates an enumeration with four members as well as auto generated parse and to_string free methods
#define ENUM_4(enumeration, a, b, c, d, def) enum enumeration{a, b, c, d}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
		else if(boost::iequals(value, #b)) \
		*out_enum = b; \
		else if(boost::iequals(value, #c)) \
		*out_enum = c; \
		else if(boost::iequals(value, #d)) \
		*out_enum = d; \
		else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		default: return #def; }}
#endif

#ifndef ENUM_5
///Creates an enumeration with five members as well as auto generated parse and to_string free methods
#define ENUM_5(enumeration, a, b, c, d, e, def) enum enumeration{a, b, c, d, e}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
				else if(boost::iequals(value, #b)) \
		*out_enum = b; \
				else if(boost::iequals(value, #c)) \
		*out_enum = c; \
				else if(boost::iequals(value, #d)) \
		*out_enum = d; \
				else if(boost::iequals(value, #e)) \
		*out_enum = e; \
				else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		case e: return #e; \
		default: return #def; }}
#endif

#ifndef ENUM_6
///Creates an enumeration with six members as well as auto generated parse and to_string free methods
#define ENUM_6(enumeration, a, b, c, d, e, f, def) enum enumeration{a, b, c, d, e, f}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
				else if(boost::iequals(value, #b)) \
		*out_enum = b; \
				else if(boost::iequals(value, #c)) \
		*out_enum = c; \
				else if(boost::iequals(value, #d)) \
		*out_enum = d; \
				else if(boost::iequals(value, #e)) \
		*out_enum = e; \
				else if(boost::iequals(value, #f)) \
		*out_enum = f; \
				else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		case e: return #e; \
		case f: return #f; \
		default: return #def; }}
#endif

#ifndef ENUM_7
///Creates an enumeration with seven members as well as auto generated parse and to_string free methods
#define ENUM_7(enumeration, a, b, c, d, e, f, g, def) enum enumeration{a, b, c, d, e, f, g}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
				else if(boost::iequals(value, #b)) \
		*out_enum = b; \
				else if(boost::iequals(value, #c)) \
		*out_enum = c; \
				else if(boost::iequals(value, #d)) \
		*out_enum = d; \
				else if(boost::iequals(value, #e)) \
		*out_enum = e; \
				else if(boost::iequals(value, #f)) \
		*out_enum = f; \
				else if (boost::iequals(value, #g)) \
		*out_enum = g; \
				else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		case e: return #e; \
		case f: return #f; \
		case g: return #g; \
		default: return #def; }}
#endif

#ifndef ENUM_8
///Creates an enumeration with eight members as well as auto generated parse and to_string free methods
#define ENUM_8(enumeration, a, b, c, d, e, f, g, h, def) enum enumeration{a, b, c, d, e, f, g, h}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
				else if(boost::iequals(value, #b)) \
		*out_enum = b; \
				else if(boost::iequals(value, #c)) \
		*out_enum = c; \
				else if(boost::iequals(value, #d)) \
		*out_enum = d; \
				else if(boost::iequals(value, #e)) \
		*out_enum = e; \
				else if(boost::iequals(value, #f)) \
		*out_enum = f; \
				else if(boost::iequals(value, #g)) \
		*out_enum = g; \
				else if(boost::iequals(value, #h)) \
		*out_enum = h; \
				else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		case e: return #e; \
		case f: return #f; \
		case g: return #g; \
		case h: return #h; \
		default: return #def; }}
#endif

#ifndef ENUM_9
///Creates an enumeration with nine members as well as auto generated parse and to_string free methods
#define ENUM_9(enumeration, a, b, c, d, e, f, g, h, i, def) enum enumeration{a, b, c, d, e, f, g, h, i}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
				else if(boost::iequals(value, #b)) \
		*out_enum = b; \
				else if(boost::iequals(value, #c)) \
		*out_enum = c; \
				else if(boost::iequals(value, #d)) \
		*out_enum = d; \
				else if(boost::iequals(value, #e)) \
		*out_enum = e; \
				else if(boost::iequals(value, #f)) \
		*out_enum = f; \
				else if(boost::iequals(value, #g)) \
		*out_enum = g; \
				else if(boost::iequals(value, #h)) \
		*out_enum = h; \
				else if(boost::iequals(value, #i)) \
		*out_enum = i; \
				else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		case e: return #e; \
		case f: return #f; \
		case g: return #g; \
		case h: return #h; \
		case i: return #i; \
		default: return #def; }}
#endif

#ifndef ENUM_10
///Creates an enumeration with ten members as well as auto generated parse and to_string free methods
#define ENUM_10(enumeration, a, b, c, d, e, f, g, h, i, j, def) enum enumeration{a, b, c, d, e, f, g, h, i, j}; static inline void parse(std::string value, enumeration* out_enum) {\
	if(boost::iequals(value, #a)) \
		*out_enum = a; \
				else if(boost::iequals(value, #b)) \
		*out_enum = b; \
				else if(boost::iequals(value, #c)) \
		*out_enum = c; \
				else if(boost::iequals(value, #d)) \
		*out_enum = d; \
				else if(boost::iequals(value, #e)) \
		*out_enum = e; \
				else if(boost::iequals(value, #f)) \
		*out_enum = f; \
				else if(boost::iequals(value, #g)) \
		*out_enum = g; \
				else if(boost::iequals(value, #h)) \
		*out_enum = h; \
				else if(boost::iequals(value, #i)) \
		*out_enum = i; \
				else if(boost::iequals(value, #j)) \
		*out_enum = j; \
				else \
		*out_enum = def;} \
	static inline std::string to_string(enumeration enumValue){ \
		switch( enumValue ){ \
		case a: return #a; \
		case b: return #b; \
		case c: return #c; \
		case d: return #d; \
		case e: return #e; \
		case f: return #f; \
		case g: return #g; \
		case h: return #h; \
		case i: return #i; \
		case j: return #j; \
		default: return #def; }}
#endif

///
/// END QUICK ENUMS
///
#endif

#ifndef SERVICE_ENUM
#define SERVICE_ENUM
namespace ServiceName{
	namespace Client{
		ENUM_10(Type, CryptoChat, Reserved_1, Reserved_2, Reserved_3, Reserved_4, Reserved_5, Reserved_6, Reserved_7, Reserved_8, Dynamic, Dynamic)
	};
	namespace Server{
		ENUM_10(Type, CryptoChat, Reserved_1, Reserved_2, Reserved_3, Reserved_4, Reserved_5, Reserved_6, Reserved_7, Reserved_8, Dynamic, Dynamic)
	};
};
#endif