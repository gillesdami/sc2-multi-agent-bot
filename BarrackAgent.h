#pragma once

#include <sc2api\sc2_unit.h>

#include "UnitAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

class BarrackAgent : public UnitAgent
{
private:
public:
	BarrackAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep();
	void OnUnitIdle();
	void trainAgent();
	void train(ABILITY_ID abilityId);

	~BarrackAgent();
};

