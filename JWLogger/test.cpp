#include <thread>
#include "JWLogger.h"
#include "CClassA.h"
#include "CClassB.h"

using namespace std;
using namespace JWEngine;

JW_LOGGER_DECL;

void foo(int thread_id, int count)
{
	JW_LOG_FREE_FUNC_START(thread_id);

	for (int i = 0; i < count; ++i)
	{
		JW_LOG_D(thread_id, ("iterating... " + to_string(i)).c_str());
	}

	JW_LOG_FREE_FUNC_END(thread_id);
}

int main()
{
	JW_LOGGER_INITIALIZE;

	thread a{ thread(foo, 0, 100) };
	thread b{ thread(foo, 1, 100) };
	a.join();
	b.join();

	CClassA class_a{};
	class_a.foo();

	CClassB class_b{};
	class_b.bar();

	JW_LOGGER_SAVE("test_log.txt");

	return 0;
}