#include "CClassB.h"

GLOBAL_LOGGER_USE;

void CClassB::bar()
{
	GLOBAL_LOG_METHOD_START;

	using namespace JWEngine;

	GLOBAL_LOG_D("testing bar()");

	GLOBAL_LOG_METHOD_END;
}