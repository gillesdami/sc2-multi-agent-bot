#pragma once
#include "MilitaryAgent.h"
class WidowmineAgent : public MilitaryAgent
{
public:
	WidowmineAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);
	
	void OnStep() final;
	void OnUnitIdle() final;
	
	~WidowmineAgent();
};

