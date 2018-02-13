#pragma once
#include "UnitAgent.h"
class StarportAgent : public UnitAgent
{
public:
	StarportAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep();
	void OnUnitIdle();
	void train(ABILITY_ID abilityId);

	~StarportAgent();
};

