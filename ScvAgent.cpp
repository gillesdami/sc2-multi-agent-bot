#include "ScvAgent.h"



ScvAgent::ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
	this->isBusy = false;
}

void ScvAgent::OnStep() {
	if (this->isBusy) return;

	if (shouldBuild(ABILITY_ID::BUILD_SUPPLYDEPOT)) build(ABILITY_ID::BUILD_SUPPLYDEPOT);
	else if (shouldBuild(ABILITY_ID::BUILD_REFINERY)) build(ABILITY_ID::BUILD_REFINERY, this->findAvailableGeyser());
	else if (shouldBuild(ABILITY_ID::BUILD_BARRACKS)) build(ABILITY_ID::BUILD_BARRACKS);
};

void ScvAgent::OnUnitIdle() {
	this->isBusy = false;
	this->harvest();
};

ScvAgent::~ScvAgent()
{
}

bool ScvAgent::shouldBuild(ABILITY_ID abilityId)
{
	switch (abilityId)
	{
	case ABILITY_ID::BUILD_SUPPLYDEPOT:
		return this->observations->GetFoodCap() + this->countBuildOrders(ABILITY_ID::BUILD_SUPPLYDEPOT)*10  < this->observations->GetFoodUsed() + this->getProductionCapacity() + 1
				&& this->observations->GetMinerals() > 100;
	case ABILITY_ID::BUILD_REFINERY:
		return this->observations->GetMinerals() > 75
			&& this->countBuildOrders(ABILITY_ID::BUILD_REFINERY) + this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_REFINERY)).size() < this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_SCV)).size() / 11
			&& this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_SCV)).size() > 15
			&& this->findAvailableGeyser() != NULL;
	case ABILITY_ID::BUILD_BARRACKS:
		return this->observations->GetMinerals() > 150 &&
			this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BARRACKS)).size()
			+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BARRACKSFLYING)).size()
			+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BARRACKSREACTOR)).size()
			+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BARRACKSTECHLAB)).size()
			+ this->countBuildOrders(ABILITY_ID::BUILD_BARRACKS)
			< this->observations->GetFoodWorkers() / 15;
	default:
		return false;
	}
}

size_t ScvAgent::getProductionCapacity()
{
	//TODO loop optim
	return this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_BARRACKS)).size()
		+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER)).size()
		+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_FACTORY)).size()*2
		+ this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_STARPORT)).size()*2;
}

void ScvAgent::build(ABILITY_ID abilityId, Tag target)
{
	if (target != NULL) {
		this->actions->Command(abilityId, this->observations->GetUnit(target));
	}
	else {
		this->actions->Command(abilityId, this->findEmptyBuildPlacement(abilityId, this->self->pos));
	}
	this->observations->strategy->publicOrdersThisStep.push_back(abilityId);
	this->isBusy = true;
}

Tag ScvAgent::findAvailableGeyser()
{
	Tag closestGeyser = NULL;
	Units geysers = this->observations->GetUnits(Unit::Alliance::Neutral, IsVespeneGeyser());
	Units commandcenters = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
	
	float max_distance = 15.0f;//must be close from a base

	for (const auto& geyser : geysers) {
		for (const auto& commandcenter : commandcenters) {
			float current_distance = Distance2D(commandcenter->pos, geyser->pos);

			if (current_distance < max_distance && query->Placement(ABILITY_ID::BUILD_REFINERY, geyser->pos)) {
				max_distance = current_distance;
				closestGeyser = geyser->tag;
				std::cout << "geyser found" << std::endl;
			}
		}
	}

	return closestGeyser;
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

Point2D ScvAgent::findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo, float increment)
{
	//abord
	if (increment >= 99) {
		std::cout << "Fail to find" << std::endl;
		return closestTo;
	}

	//free placement
	if (this->query->Placement(abilityId, closestTo)) {
		//not building too close from the nexus
		Units units = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
		bool valid = true;
		for (const auto& unit : units) {
			// 25 = (2nexus_radius)²
			if (DistanceSquared2D(unit->pos, closestTo) < 40) valid = false;
		}
		
		if (valid) {
			return closestTo;
		}
	}
	
	return this->findEmptyBuildPlacement(abilityId, Point2D(closestTo.x+cos(increment)*increment, closestTo.y+sin(increment)*increment), increment + 0.1234f);
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

	for (const auto& ability : this->observations->strategy->publicOrdersThisStep) {
		if (ability == abilityId) count++;
	}

	return count;
}
