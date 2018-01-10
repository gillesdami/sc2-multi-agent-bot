#pragma once

#include <sc2api\sc2_unit.h>
#include "SelfActionInterface.h"
#include "ObservationRelativeInterface.h"

class UnitAgent
{
public:
	UnitAgent(Unit* self, SelfActionInterface* actions, ObservationRelativeInterface* observations);
	virtual ~UnitAgent();
	
	virtual void OnStep() = 0;
	virtual void OnUnitIdle() = 0;

private:
	Unit* self;
	SelfActionInterface* actions;
	ObservationRelativeInterface* observat
};

