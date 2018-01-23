#pragma once

#include <sc2api\sc2_unit.h>

#include "UnitAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

class BarrackAgent : public UnitAgent
{
private:
	bool isIdle;

public:
	BarrackAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep();
	void OnUnitIdle();

	~BarrackAgent();
};

