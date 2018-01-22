#include "ScvAgent.h"



ScvAgent::ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
}

void ScvAgent::OnStep() {
	if (shouldBuildSupplyDepot()) buildSupplyDeppot();
};

void ScvAgent::OnUnitIdle() {
	this->harvest();
};

ScvAgent::~ScvAgent()
{
}

bool ScvAgent::shouldBuildSupplyDepot()
{
	return this->observations->GetFoodCap() + this->countBuildOrders(ABILITY_ID::BUILD_SUPPLYDEPOT)*10  < this->observations->GetFoodUsed() + this->getProductionCapacity() + 1
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

bool ScvAgent::harvest()
{
	Units units = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
	for (const auto& commandCenter : units) {

		if (commandCenter->ideal_harvesters - commandCenter->assigned_harvesters > 0) {
			
			Units units = this->observations->GetUnits(Unit::Alliance::Neutral, IsUnit(UNIT_TYPEID::NEUTRAL_MINERALFIELD));
			float distance = std::numeric_limits<float>::max();
			const Unit* mineral_target = nullptr;

			for (const auto& mineralPatch : units) {

				float d = DistanceSquared2D(mineralPatch->pos, commandCenter->pos);
				if (d < distance) {
					distance = d;
					mineral_target = mineralPatch;
				}
			}

			this->actions->Command(ABILITY_ID::SMART, mineral_target);
			return true;
		}
	}

	return false;
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
