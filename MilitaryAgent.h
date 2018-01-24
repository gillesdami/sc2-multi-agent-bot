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
	Point2D findPlacement(ABILITY_ID abilityId, Point2D point, float increment = 0);
	void RetreatWithUnit(const Unit* unit, Point2D retreat_position);
	MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query);
	~MilitaryAgent();
};

