#pragma once
#include "UnitAgent.h"
class FactoryAgent : public UnitAgent
{
public:
	FactoryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep();
	void OnUnitIdle();
	void train(ABILITY_ID abilityId);

	~FactoryAgent();
};

