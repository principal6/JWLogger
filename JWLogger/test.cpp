#include <thread>
#include "JWLogger.h"

using namespace std;
using namespace JWEngine;

static JWLogger MyLogger{};

void foo(int thread_id, int count, JWLogger* out_logger)
{
	JWLogger internal_logger{};

	for (int i = 0; i < count; ++i)
	{
		internal_logger.Log(FILE_LINE, thread_id, ("iterating... " + to_string(i)).c_str());
	}

	if (out_logger)
	{
		*out_logger = internal_logger;
	}
}

int main()
{
	JWLogger logger_a{}, logger_b{};

	thread a{ thread(foo, 0, 100, &logger_a) };
	thread b{ thread(foo, 1, 100, &logger_b) };
	a.join();
	b.join();

	MyLogger.JoinLog(logger_a);
	MyLogger.JoinLog(logger_b);

	MyLogger.DisplayEntireLog();

	MyLogger.SaveToFile("test_log.txt");

	return 0;
}