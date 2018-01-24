#pragma once

#include "cmath"
#include "UnitAgent.h"

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
	int countBuildOrders(ABILITY_ID abilityId);
	Point2D findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo, float increment = 0);
};

struct IsVespeneGeyser {
	bool operator()(const Unit& unit) {
		switch (unit.unit_type.ToType()) {
		case UNIT_TYPEID::NEUTRAL_VESPENEGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER: return true;
		default: return false;
		}
	}
};
