#include "InfoHarvester.h"
#include <iostream>

#ifdef _WIN32
namespace windows{
#include <Windows.h>
	static inline string ProcArchToString(WORD arch)
	{
		switch (arch)
		{
		case PROCESSOR_ARCHITECTURE_AMD64:
			return "amd64";
		case PROCESSOR_ARCHITECTURE_ALPHA:
			return "alpha";
		case PROCESSOR_ARCHITECTURE_ALPHA64:
			return "alpha64";
		case PROCESSOR_ARCHITECTURE_ARM:
			return "arm";
		case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
			return "ia32_win64";
		case PROCESSOR_ARCHITECTURE_IA64:
			return "ia64";
		case PROCESSOR_ARCHITECTURE_INTEL:
			return "intel";
		case PROCESSOR_ARCHITECTURE_MIPS:
			return "mips";
		case PROCESSOR_ARCHITECTURE_MSIL:
			return "msil";
		case PROCESSOR_ARCHITECTURE_NEUTRAL:
			return "neutral";
		case PROCESSOR_ARCHITECTURE_PPC:
			return "ppc";
		case PROCESSOR_ARCHITECTURE_SHX:
			return "shx";
		case PROCESSOR_ARCHITECTURE_UNKNOWN:
			return "unknown";
		default:
			return std::to_string(arch);
		}
	}

	static inline string ProcTypeToString(DWORD type)
	{
		switch (type)
		{
		case PROCESSOR_INTEL_386:
			return "intel_386";
		case PROCESSOR_ALPHA_21064:
			return "alpha_21064";
		case PROCESSOR_AMD_X8664:
			return "amd_x86_64";
		case PROCESSOR_ARM720:
			return "arm_720";
		case PROCESSOR_ARM820:
			return "arm_820";
		case PROCESSOR_ARM920:
			return "arm_920";
		case PROCESSOR_ARM_7TDMI:
			return "arm_7_tdmi";
		case PROCESSOR_HITACHI_SH3:
			return "hitachi_sh3";
		case PROCESSOR_HITACHI_SH3E:
			return "hitachi_sh3e";
		case PROCESSOR_HITACHI_SH4:
			return "hitachi_sh4";
		case PROCESSOR_INTEL_486:
			return "hitachi_486";
		case PROCESSOR_INTEL_IA64:
			return "intel_ia64";
		case PROCESSOR_INTEL_PENTIUM:
			return "intel_pentium";
		case PROCESSOR_MIPS_R4000:
			return "mips_r4000";
		case PROCESSOR_MOTOROLA_821:
			return "motorola_821";
		default:
			return std::to_string(type);
		}
	}

	static inline string AddressString(LPVOID address)
	{
		char buffer[16];
		sprintf_s(buffer, "%lx", address);
		string result(buffer);
		return result;
	}
}

InfoHarvester::InfoHarvester()
{
	windows::SYSTEM_INFO sysInfo;
	windows::DWORD size = 256;
	windows::CHAR buffer[256];

	windows::GetComputerNameA(buffer, &size);
	InfoPairs[COMPUTER_NAME] = std::string(buffer, size);

	windows::GetNativeSystemInfo(&sysInfo);
	InfoPairs[PROCESSOR_ARCH] = windows::ProcArchToString(sysInfo.wProcessorArchitecture);
	InfoPairs[PAGE_SIZE] = std::to_string(sysInfo.dwPageSize);
	InfoPairs[MIN_APP_ADDR] = windows::AddressString(sysInfo.lpMinimumApplicationAddress);
	InfoPairs[MAX_APP_ADDR] = windows::AddressString(sysInfo.lpMaximumApplicationAddress);
	InfoPairs[NUM_PROC] = std::to_string(sysInfo.dwNumberOfProcessors);
	InfoPairs[PROC_TYPE] = windows::ProcTypeToString(sysInfo.dwProcessorType);
	InfoPairs[ALLOC_GRAN] = std::to_string(sysInfo.dwAllocationGranularity);
	InfoPairs[PROC_LEVEL] = std::to_string(sysInfo.wProcessorLevel);
	InfoPairs[PROC_REV] = std::to_string(sysInfo.wProcessorRevision);

	InfoPairs[OS] = OS_;
}
#endif
#ifdef __LINUX__

namespace linux
{
#include <sys/sysinfo.h>
#include <sys/utsname.h>
}

InfoHarvester::InfoHarvester()
{
	linux::sysinfo info;
	linux::sysinfo(&info);

	linux::utsname name;
	linux::uname(&name);

	InfoPairs[COMPUTER_NAME] = string(name.nodename);

	InfoPairs[PROCESSOR_ARCH] = "?";
	InfoPairs[PAGE_SIZE] = "?";
	InfoPairs[MIN_APP_ADDR] = "?";
	InfoPairs[MAX_APP_ADDR] = "?";
	InfoPairs[NUM_PROC] = std::to_string(info.procs);
	InfoPairs[PROC_TYPE] = "?";
	InfoPairs[ALLOC_GRAN] = "?";
	InfoPairs[PROC_LEVEL] = "?";
	InfoPairs[PROC_REV] = "?";

	InfoPairs[OS] = string(name.sysname);
	InfoPairs[OS_VERSION] = string(name.version)
}
#endif
#ifdef __APPLE__

namespace apple
{

}

InfoHarvester::InfoHarvester()
{
	InfoPairs[COMPUTER_NAME] = "?";

	InfoPairs[PROCESSOR_ARCH] = "?";
	InfoPairs[PAGE_SIZE] = "?";
	InfoPairs[MIN_APP_ADDR] = "?";
	InfoPairs[MAX_APP_ADDR] = "?";
	InfoPairs[NUM_PROC] = "?";
	InfoPairs[PROC_TYPE] = "?";
	InfoPairs[ALLOC_GRAN] = "?";
	InfoPairs[PROC_LEVEL] = "?";
	InfoPairs[PROC_REV] = "?";

	InfoPairs[OS] = OS_;
}
#endif


InfoHarvester::~InfoHarvester()
{
}

std::map<string, string> InfoHarvester::GetAllInfoPairs() const
{
	return InfoPairs;
}

string InfoHarvester::Get(string key) const
{
	if (InfoPairs.find(key) != InfoPairs.cend())
		return InfoPairs.at(key);
	else
		return "";
}

string InfoHarvester::GetAll() const
{
	string result;
	for (auto pair : InfoPairs)
	{
		result.append("{")
			.append(pair.first)
			.append("=")
			.append(pair.second)
			.append("}\r\n");
	}
	return result;
}