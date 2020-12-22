#pragma once

#include<memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Nutcracker {

	class NUTCRACKER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define NC_CORE_TRACE(...)		::Nutcracker::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define NC_CORE_INFO(...)		::Nutcracker::Log::GetCoreLogger()->info(__VA_ARGS__);
#define NC_CORE_WARN(...)		::Nutcracker::Log::GetCoreLogger()->warn(__VA_ARGS__);
//#define NC_CORE_FATAL(...)	::Nutcracker::Log::GetCoreLogger()->fata(__VA_ARGS__);


//Client log macros
#define NC_TRACE(...)		::Nutcracker::Log::GetClientLogger()->trace(__VA_ARGS__);
#define NC_INFO(...)		::Nutcracker::Log::GetClientLogger()->info(__VA_ARGS__);
#define NC_WARN(...)		::Nutcracker::Log::GetClientLogger()->warn(__VA_ARGS__);
//#define NC_FATAL(...)	::Nutcracker::Log::GetCoreLogger()->fata(__VA_ARGS__);



