#pragma once

#include "UnitAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

class MilitaryAgent : public UnitAgent
{
private:
	bool isIdle;
	QueryInterface* query;

public:
	void OnStep();
	void OnUnitIdle();
	void move();
	MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query);
	~MilitaryAgent();
};

