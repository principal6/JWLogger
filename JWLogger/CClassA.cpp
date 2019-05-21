#include "CClassA.h"

JW_LOGGER_USE;

void CClassA::foo()
{
	JW_LOG_METHOD_START(0);

	using namespace JWEngine;

	JW_LOG_D(0, "testing foo()");

	JW_LOG_METHOD_END(0);
}