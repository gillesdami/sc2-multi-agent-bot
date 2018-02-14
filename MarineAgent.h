#pragma once

#include "MilitaryAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

class MarineAgent : public MilitaryAgent
{
public:
	void OnStep();
	void OnUnitIdle();
	MarineAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);
	~MarineAgent();
};

