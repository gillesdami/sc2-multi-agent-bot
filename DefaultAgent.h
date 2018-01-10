#pragma once

#include <iostream>
#include "UnitAgent.h"

class DefaultAgent :
	public UnitAgent
{
public:
	DefaultAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep() {};
	void OnUnitIdle() {};

	~DefaultAgent();
};

