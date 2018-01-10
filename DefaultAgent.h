#pragma once
#include "UnitAgent.h"
class DefaultAgent :
	public UnitAgent
{
public:
	DefaultAgent(Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep() {};
	void OnUnitIdle() {};

	~DefaultAgent();
};

