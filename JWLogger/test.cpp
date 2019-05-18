#include <thread>
#include "JWLogger.h"
#include "CClassA.h"
#include "CClassB.h"

using namespace std;
using namespace JWEngine;

GLOBAL_LOGGER_GET;

void foo(int thread_id, int count, JWLogger* out_logger)
{
	THREAD_LOGGER_DECL;

	for (int i = 0; i < count; ++i)
	{
		THREAD_LOG_D(thread_id, ("iterating... " + to_string(i)).c_str());
	}

	THREAD_LOGGER_SEND_OUT(out_logger);
}

int main()
{
	JWLogger logger_a{}, logger_b{};

	thread a{ thread(foo, 0, 100, &logger_a) };
	thread b{ thread(foo, 1, 100, &logger_b) };
	a.join();
	b.join();

	JOIN_THREAD_LOG(logger_a);
	JOIN_THREAD_LOG(logger_b);

	CClassA class_a{};
	class_a.foo();

	CClassB class_b{};
	class_b.bar();

	GLOBAL_LOGGER.DisplayEntireLog();
	GLOBAL_LOGGER.SaveToFile("test_log.txt");

	return 0;
}