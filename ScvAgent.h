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
	bool shouldBuildSupplyDepot();
	int getProductionCapacity();
	void buildSupplyDeppot();
	int countBuildOrders(ABILITY_ID abilityId);
	Point2D findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo, double increment = 0);
};

