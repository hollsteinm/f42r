#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include "types.h"
#include <map>
class CommandParser
{
public:
	CommandParser();
	~CommandParser();
	CommandParser(const CommandParser& rhs);

	const passfail Parse(string param);
	const string& GetValue(string key) const;
	const logic HasKey(string key) const;
	const size Count() const;

	const string& operator[](string key) const;
	void CreateUsingFormat(string& formattedString) const;

	const std::map<string, string> Content() const;

private:
	std::map<string, string> commands;
};
#endif