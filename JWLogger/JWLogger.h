#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <algorithm>
#include <fstream>

namespace JWEngine
{
	#define FILE_LINE __FILE__, __LINE__

	static constexpr char KLogHead[]{ "        date        |    time    |  thread  | file\t:line\t| lev | comment  \n" };

	enum class ELogLevel
	{
		Default,
		See,
		Warning,
		Fatal,
	};

	struct SLogDatum
	{
		SLogDatum() {};
		SLogDatum(long long _time, ELogLevel _level, const std::string& _log) : time{ _time }, level{ _level }, log{ _log } {};

		long long time{};
		ELogLevel level{};
		std::string log{};
	};

	bool SortLogLess(const SLogDatum& a, const SLogDatum& b)
	{
		return (a.time < b.time);
	}

	class JWLogger
	{
	public:
		void Log(const char* file, int line, int thread_id, const char* comment, ELogLevel level = ELogLevel::Default)
		{
			char date[200]{};
			std::time_t time_now{ m_clock.to_time_t(m_clock.now()) };
			std::tm tm{};
			localtime_s(&tm, &time_now);
			strftime(date, 200, "%Y-%M-%d %T", &tm);

			if (date[strlen(date) - 1] == '\n')
			{
				date[strlen(date) - 1] = NULL;
			}
			auto time_value = m_clock.now().time_since_epoch().count();

			std::string sfile{ file };
			auto upper = sfile.find_last_of('\\');
			sfile = sfile.substr(upper + 1);

			char s_level[4]{};
			switch (level)
			{
			case JWEngine::ELogLevel::Default:
				strcpy_s(s_level, "---");
				break;
			case JWEngine::ELogLevel::See:
				strcpy_s(s_level, "SEE");
				break;
			case JWEngine::ELogLevel::Warning:
				strcpy_s(s_level, "WRN");
				break;
			case JWEngine::ELogLevel::Fatal:
				strcpy_s(s_level, "FTL");
				break;
			default:
				break;
			}
			
			char temp_str[300]{};
			sprintf_s(temp_str, "%s | %lld | thread:%d | %s\t:%d\t| %s | %s\n",
				date, time_value % 10000000000, thread_id, sfile.c_str(), line, s_level, comment);

			m_data.emplace_back(time_value, level, temp_str);
		};

		void JoinLog(const JWLogger& thread_log) 
		{
			for (const auto& iter : thread_log.m_data)
			{
				m_data.emplace_back(iter);
			}

			std::sort(m_data.begin(), m_data.end(), SortLogLess);
		};

		void DisplayEntireLog()
		{
			printf(KLogHead);
			for (const auto& iter : m_data)
			{
				switch (iter.level)
				{
				case JWEngine::ELogLevel::Default:
					SetConsoleTextAttribute(m_hConsole, FOREGROUND_INTENSITY);
					break;
				case JWEngine::ELogLevel::See:
					SetConsoleTextAttribute(m_hConsole, FOREGROUND_GREEN);
					break;
				case JWEngine::ELogLevel::Warning:
					SetConsoleTextAttribute(m_hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
					break;
				case JWEngine::ELogLevel::Fatal:
					SetConsoleTextAttribute(m_hConsole, FOREGROUND_RED);
					break;
				default:
					break;
				}

				printf("%s", iter.log.c_str());
			}
		};

		void SaveToFile(const std::string& FileName)
		{
			std::ofstream ofs{ FileName.c_str() };

			if (ofs.is_open())
			{
				ofs << KLogHead;

				for (const auto& iter : m_data)
				{
					ofs << iter.log;
				}

				ofs.close();
			}
		};

	private:
		std::vector<SLogDatum> m_data{};
		std::chrono::system_clock m_clock{};
		HANDLE m_hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
	};
};