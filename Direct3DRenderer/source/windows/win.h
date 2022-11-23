#pragma once

// target Windows 7 or later
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif // !_WIN32_WINNT

#include <sdkddkver.h>
// The following #defines disable a bunch of unused windows stuff. If you 
// get weird errors when trying to do some windows stuff, try removing some
// (or all) of these defines (it will increase build time though).
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#ifndef STRICT
#define STRICT
#endif // !STRICT

#include "core/util.h"
#include <Windows.h>
std::wstring TranslateError(HRESULT hr);

#if defined(DEBUG) | defined(_DEBUG)
	#define ASSERT_HR(x, msg) {																					\
		HRESULT hr__LINE__ = (x);																				\
		if (FAILED(hr__LINE__))																					\
		{																										\
			std::string err__LINE__ = ::wl::wstrToStr(TranslateError(hr__LINE__));							\
			LOG_E("HR assertion failed: {0}\n\tFile: {1}\n\tLine: {2}\n\t{3}", msg, __FILE__, __LINE__, err__LINE__);	\
			__debugbreak();																						\
		}																										\
	}
#else
	#define ASSERT_HR(x, msg)
#endif