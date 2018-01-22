#include "ScvAgent.h"



ScvAgent::ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
}

void ScvAgent::OnStep() {
	if (shouldBuildSupplyDepot()) buildSupplyDeppot();
};

void ScvAgent::OnUnitIdle() {
};

ScvAgent::~ScvAgent()
{
}

bool ScvAgent::shouldBuildSupplyDepot()
{
	return this->observations->GetFoodCap() + this->countBuildOrders(ABILITY_ID::BUILD_SUPPLYDEPOT)*10  < this->observations->GetFoodUsed() + this->getProductionCapacity()
		&& this->observations->GetMinerals() > 100;
}

int ScvAgent::getProductionCapacity()
{
	//TODO loop optim
	return this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BARRACKS)).size()
		+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER)).size()
		+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_FACTORY)).size()*2
		+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_STARPORT)).size()*2;
}

void ScvAgent::buildSupplyDeppot()
{
	this->actions->Command(ABILITY_ID::BUILD_SUPPLYDEPOT, this->findEmptyBuildPlacement(ABILITY_ID::BUILD_SUPPLYDEPOT, this->self->pos));
}

Point2D ScvAgent::findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo, double increment)
{
	if (increment >= 99) return closestTo;

	if (this->query->Placement(abilityId, closestTo))
		return closestTo;
	else
		return this->findEmptyBuildPlacement(abilityId, Point2D(closestTo.x+cos(increment)*increment*increment, closestTo.y+sin(increment)*increment*increment), increment + 0.1);
}

int ScvAgent::countBuildOrders(ABILITY_ID abilityId)
{
	int count = 0;

	Units units = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_SCV));
	for (const auto& unit : units) {
		for (const auto& order : unit->orders) {
			if (order.ability_id == abilityId) {
				count++;
			}
		}
	}

	return count;
}
