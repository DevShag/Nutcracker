#pragma once
#include <memory>

#ifdef NC_PLATFORM_WINDOWS
#if NC_DYNAMIC_LINK
	#ifdef NC_BUILD_DLL
		#define NUTCRACKER_API _declspec(dllexport)
	#else
		#define NUTCRACKER_API _declspec(dllimport)
	#endif
#else
	#define NUTCRACKER_API
#endif

#else
	#error Nutcracker only support Windows!
#endif

#ifdef NC_ENABLE_ASSERTS
	#define NC_ASSERT(X, ...) { if(!(x)) { NC_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}}
	#define NC_CORE_ASSERT(X, ...) { if(!(x)) { NC_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define NC_ASSERT(x, ...)
	#define NC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Nutcracker{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


}