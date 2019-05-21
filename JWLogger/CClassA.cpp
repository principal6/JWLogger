#include "CClassA.h"

GLOBAL_LOGGER_USE;

void CClassA::foo()
{
	GLOBAL_LOG_METHOD_START;

	using namespace JWEngine;

	GLOBAL_LOG_D("testing foo()");

	GLOBAL_LOG_METHOD_END;
}