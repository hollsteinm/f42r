#ifndef INFO_HARVESTER_H
#define INFO_HARVESTER_H
#include "types.h"
#include <map>
#define PROCESSOR_ARCH	"processor_arch"
#define PAGE_SIZE		"page_size"
#define	MIN_APP_ADDR	"minimum_application_address"
#define MAX_APP_ADDR	"maximum_application_address"
#define NUM_PROC		"number_of_processors"
#define PROC_TYPE		"processor_type"
#define ALLOC_GRAN		"allocation_granularity"
#define PROC_LEVEL		"processor_level"
#define PROC_REV		"processor_revision"
#define COMPUTER_NAME	"computer_name"
#define OS_VERSION		"os_version"
#define OS				"os"
#define USER_NAME		"user_name"

#ifndef OS_
#ifdef _WIN32
#define OS_ "windows"
#endif
#ifdef __LINUX__
#define OS_ "linux"
#endif
#ifdef __APPLE__
#define OS_ "osx"
#endif
#endif
class InfoHarvester
{
public:
	InfoHarvester();
	~InfoHarvester();

	std::map<string, string> GetAllInfoPairs() const;
	string Get(string key) const;
	string GetAll() const;

private:
	std::map<string, string> InfoPairs;
};
#endif