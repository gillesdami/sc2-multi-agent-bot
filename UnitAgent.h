#pragma once

#include <sc2api\sc2_unit.h>
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

using namespace sc2;

class UnitAgent
{
public:
	UnitAgent(Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);
	virtual ~UnitAgent() = 0;
	
	virtual void OnStep() = 0;
	virtual void OnUnitIdle() = 0;

protected:
	Unit* self;
	SelfActionInterface* actions;
	SelfObservationInterface* observations;
};

