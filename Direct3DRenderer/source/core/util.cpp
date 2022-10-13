#include "util.h"

#include <string>
#include <wchar.h>
#include <cstring>
#include <stdlib.h>

namespace wl
{
	std::string wstrToStr(std::wstring wstr)
	{
		return { wstr.begin(), wstr.end() };
	}
}
