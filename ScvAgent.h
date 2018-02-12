#pragma once

#include "cmath"
#include "UnitAgent.h"
#include "util.h"

class ScvAgent :
	public UnitAgent
{
public:
	ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);

	void OnStep();
	void OnUnitIdle();

	~ScvAgent();
private:
	bool isBusy;

	QueryInterface * query;

	bool shouldBuild(ABILITY_ID abilityId);
	void build(ABILITY_ID abilityId, Tag target = NULL);
	
	Tag findAvailableGeyser();

	size_t getProductionCapacity();
	
	bool harvest();
	Point2D findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo);
};

