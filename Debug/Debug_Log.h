#pragma once
#include <string>
#include <vector>

enum class LogLevel
{
	Message,
	Warning,
	Error
};

namespace Sunder
{
	class Engine;
}

#ifdef _DEBUG

#define LOG_BASE __FILE__, __LINE__, __func__

#define LOG(logLevel, message)	Debug::Debug_Log::Log(logLevel, LOG_BASE, message)
#define LOG_MESSAGE(message)	LOG(LogLevel::Message, message)
#define LOG_WARNING(message)	LOG(LogLevel::Warning, message)
#define LOG_ERROR(message)		LOG(LogLevel::Error,   message)

#else
#define LOG_BASE

#define LOG(logLevel, message)
#define LOG_MESSAGE(message)
#define LOG_WARNING(message)
#define LOG_ERROR(message)

#endif // _DEBUG


namespace Debug
{
	class Debug_Log
	{
	public:
		friend class Sunder::Engine;

		static void Log(LogLevel aLogLevel, const char* aFile, int aLine, const char* aFunc, const std::string& aMessage)
		{ Instance->Internal_Log(aLogLevel, aFile, aLine, aFunc, aMessage); }

	private:
		struct LogContainer
		{
			uint32_t Count		= 0;
			uint32_t Hash		= 0;
			LogLevel logLevel	= LogLevel::Message;
			std::string Message = "";
		};

		std::vector<LogContainer> myLogs;
		bool myIsDirty = false;

		static Debug_Log* Instance;

		Debug_Log() = default;
		~Debug_Log() = default;

		void  Internal_Print();
		void  Internal_Clear();

		void Internal_Log(LogLevel aLogLevel, const char* file, int line, const char* func, const std::string& aMessage);
		void Internal_SetDisplaySettings(LogLevel aLogLevel);
		void Internal_ResetDisplaySettings();

		static void Print() { Instance->Internal_Print(); }
		static void Clear() { Instance->Internal_Clear(); }
	};

}
