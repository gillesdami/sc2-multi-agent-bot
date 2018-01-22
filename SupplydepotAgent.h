#pragma once

#include "UnitAgent.h"

class SupplydepotAgent : public UnitAgent
{
public:
	SupplydepotAgent::SupplydepotAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations);
	~SupplydepotAgent();

	void OnStep();
};

