#include "Debug_Log.h"
#include <windows.h>
#include <iostream>
#include <algorithm>

inline uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length);

Debug::Debug_Log* Debug::Debug_Log::Instance = nullptr;

void Debug::Debug_Log::Internal_Print()
{
	if (myIsDirty == false) return;

	system("cls");

	std::string data;
	for (auto& log : myLogs)
	{
		switch (log.logLevel)
		{
		case LogLevel::Message: { data += "Message: ";	break; }
		case LogLevel::Warning: { data += "Warning!: "; break; }
		case LogLevel::Error:   { data += "ERROR!: ";	break; }
		default:				{ data += "Message: ";	break; }
		}

		if (1 < log.Count) data += " [" + std::to_string(log.Count) + "]";

		data += "\n";
		data += log.Message;

		Internal_SetDisplaySettings(log.logLevel);

		std::cout << data << std::endl;
		data.clear();
	}

	Internal_ResetDisplaySettings();
	myIsDirty = false;
}

void Debug::Debug_Log::Internal_Clear()
{
	myLogs.clear();
}

void Debug::Debug_Log::Internal_Log(LogLevel aLogLevel, const char* aFile, int aLine, const char* aFunc, const std::string& aMessage)
{
	myIsDirty = true;

	LogContainer data;

	std::string filePath = aFile;
	//Shorten path
	{
		size_t pos = filePath.find_last_of("\\");
		filePath = (pos != std::string::npos) ? filePath.substr(pos + 1) : filePath;
	}

	 data.Message += "File: ";
	 data.Message += filePath;
	 data.Message += "\nFunction: ";
	 data.Message += aFunc;
	 data.Message += " : ";
	 data.Message += std::to_string(aLine);

	 data.Message += "\n----------------\n";
	 data.Message += aMessage;

	 data.Hash = jenkins_one_at_a_time_hash((uint8_t*)data.Message.c_str(), data.Message.size());
	 
	 auto find = std::find_if(myLogs.begin(), myLogs.end(), 
		 [hash = data.Hash](const LogContainer& aLogC) { return hash == aLogC.Hash; });

	 if (find != myLogs.end()) 
	 { 
		 find->Count++; 
		 return;
	 };


	//Create some space
	 data.Message += "\n\n";
	 data.logLevel = aLogLevel;
	 data.Count = 1;
	 
	 myLogs.push_back(data);
}

enum class ConcoleColor
{
	Red = 12,
	Yellow = 14,
	White = 15
};

void Debug::Debug_Log::Internal_SetDisplaySettings(LogLevel aLogLevel)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hConsole)
	{
		return;
	}

	ConcoleColor color = ConcoleColor::White;

	switch (aLogLevel)
	{
	case LogLevel::Message: { color = ConcoleColor::White;		break; }
	case LogLevel::Warning: { color = ConcoleColor::Yellow;		break; }
	case LogLevel::Error:   { color = ConcoleColor::Red;		break; }
	default:				{ color = ConcoleColor::White;		break; }
	}

	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}


void Debug::Debug_Log::Internal_ResetDisplaySettings()
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hConsole)
	{
		return;
	}

	SetConsoleTextAttribute(hConsole, static_cast<WORD>(ConcoleColor::White));
}


inline uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
	size_t i = 0;
	uint32_t hash = 0;
	while (i != length) {
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return hash;
}