#pragma once
#include "UnitAgent.h"
class ScvAgent :
	public UnitAgent
{
public:
	ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep() {};
	void OnUnitIdle() {};

	~ScvAgent();
};

