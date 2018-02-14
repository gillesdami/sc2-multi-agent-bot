#pragma once
#include "MilitaryAgent.h"
class VikingAgent : public MilitaryAgent
{
public:
	VikingAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);

	void OnStep() final;
	void OnUnitIdle() final;

	~VikingAgent();
};

