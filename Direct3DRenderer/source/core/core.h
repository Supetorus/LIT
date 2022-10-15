#pragma once
#include "Log.h"
#include <memory>
#include <filesystem>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

#if defined(DEBUG) | defined(_DEBUG)
	#define ASSERT(x, msg, ... ) {if (!(x)) { LOG_W(std::string{ "Assertion Failed: " }.append(msg) __VA_OPT__(,) __VA_ARGS__); __debugbreak(); }}
#else
	#define ASSERT(x, msg, ...)
#endif