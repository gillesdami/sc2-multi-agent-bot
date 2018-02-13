#pragma once

#include "MilitaryAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

class MarineAgent : public MilitaryAgent
{
private:
	bool isIdle;
public:
	void OnStep();
	void OnUnitIdle();
	void move();
	void RetreatWithUnit(const Unit* unit, Point2D retreat_position);
	MarineAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);
	~MarineAgent();
};

