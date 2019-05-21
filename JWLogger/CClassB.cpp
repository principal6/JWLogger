#include "CClassB.h"

JW_LOGGER_USE;

void CClassB::bar()
{
	JW_LOG_METHOD_START(0);

	using namespace JWEngine;

	JW_LOG_D(0, "testing bar()");

	JW_LOG_METHOD_END(0);
}