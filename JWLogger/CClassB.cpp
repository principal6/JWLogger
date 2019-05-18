#include "CClassB.h"

GLOBAL_LOGGER_GET;

void CClassB::bar()
{
	using namespace JWEngine;

	GLOBAL_LOG_D("bar()");
}