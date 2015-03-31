#include "CommandParser.h"
#include <vector>
#include <boost\algorithm\string.hpp>

CommandParser::CommandParser()
{
}

CommandParser::CommandParser(const CommandParser& rhs){
	for (auto pair : rhs.commands){
		commands.emplace(pair);
	}
}


CommandParser::~CommandParser()
{
}

const char assign = '=';
const char delim_s = '{';
const char delim_e = '}';
const char f_slash = '/';
const char b_slash = '\\';

const std::map<string, string> CommandParser::Content() const
{
	return commands;
}

const passfail CommandParser::Parse(std::string param){

	std::vector<std::string> params;
	std::string copy;
	bool startCopy = false;

	int32 skip = 0;
	for (auto c : param){
		if (c == delim_s && !startCopy)
			startCopy = true;
		else if (startCopy && (c != delim_s && c != delim_e))
			copy += c;
		else if (startCopy && (c == delim_s))
		{
			copy += c;
			skip++;
		}
		else if (startCopy && (c == delim_e) && skip > 0)
		{
			copy += c;
			skip--;
		}
		else if (c == delim_e && startCopy)
		{
			startCopy = false;
			params.push_back(std::string(copy));
			copy.clear();
		}
	}

	if (params.size() <= 0)
		return false;

	for (auto c : params)
	{
		size eIndex = c.find_first_of(assign);
		if (eIndex == std::string::npos)
			return false;

		std::string value = boost::algorithm::to_lower_copy(c.substr(eIndex + 1, c.size()));
		if (value.find_first_of(f_slash) == std::string::npos && value.find_first_of(b_slash) == std::string::npos)
			boost::algorithm::trim(value);
		commands[boost::algorithm::trim_copy(boost::algorithm::to_lower_copy(c.substr(0, eIndex)))] = value;
	}

	return true;
}

const string& CommandParser::GetValue(string key) const{
	boost::algorithm::to_lower(key);
	return commands.at(key);
}

const logic CommandParser::HasKey(string key) const{
	boost::algorithm::to_lower(key);
	return commands.find(key) != commands.cend();
}

const size CommandParser::Count() const{
	return commands.size();
}

const string& CommandParser::operator[](string key) const{
	return GetValue(key);
}

void CommandParser::CreateUsingFormat(string& formattedString) const{
	string copy;
	logic startCopy = false;

	while (formattedString.find_first_of(delim_s) != string::npos && formattedString.find_first_of(delim_e) != string::npos){
		for (unsigned int i = 0; i < formattedString.size(); ++i){
			char c = formattedString[i];
			if (c == delim_s && !startCopy)
			{
				startCopy = true;
			}
			else if (startCopy && (c != delim_s && c != delim_e))
				copy += c;
			else if (c == delim_e && startCopy)
			{
				startCopy = false;
				if (HasKey(copy))
				{
					string value = GetValue(copy);
					boost::replace_all(formattedString, delim_s + copy + delim_e, value);
					CreateUsingFormat(formattedString);
					break;
				}

				copy.clear();
			}
		}
	}
}