#include "CClassA.h"

GLOBAL_LOGGER_GET;

void CClassA::foo()
{
	using namespace JWEngine;

	GLOBAL_LOG_D("foo()");
}