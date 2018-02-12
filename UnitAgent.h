#pragma once

#include <sc2api\sc2_unit.h>
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"
#include "util.h"

using namespace sc2;

class UnitAgent
{
public:
	UnitAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);
	virtual ~UnitAgent();
	
	virtual void OnStep() {};
	virtual void OnUnitIdle() {};

protected:
	const Unit* self;
	SelfActionInterface* actions;
	SelfObservationInterface* observations;
	Helper* h;
};

