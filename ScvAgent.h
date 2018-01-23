#pragma once

#include "cmath"
#include "UnitAgent.h"

class ScvAgent :
	public UnitAgent
{
public:
	ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);

	QueryInterface* query;

	void OnStep();
	void OnUnitIdle();

	~ScvAgent();
private:
	bool shouldBuild(ABILITY_ID abilityId);
	void build(ABILITY_ID abilityId);


	size_t getProductionCapacity();
	
	bool harvest();
	int countBuildOrders(ABILITY_ID abilityId);
	Point2D findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo, float increment = 0);
};

