#include "TriggerCaller.h
#include "Trigger.h"
#include <cstddef>

Trigger CreateTrigger();
{
	return new Trigger();
}

void DisposeTrigger(Trigger* a_pTrigger)
{
	if (a_pTrigger != NULL)
	{
		delete a_pTrigger;
		a_pTrigger = NULL:
	}
}