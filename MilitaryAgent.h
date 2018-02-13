#pragma once

#include "UnitAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

class MilitaryAgent : public UnitAgent
{
private:
	QueryInterface* query;
public:
	virtual void OnStep();
	virtual void OnUnitIdle();

	float GetPathingDistance(Point2D dest);
	
	MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query);
	~MilitaryAgent();
};

