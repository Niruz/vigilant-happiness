#include "SimpleTimer.h"

SimpleTimer* SimpleTimer::Instance()
{
	static SimpleTimer instance;
	return &instance;
}