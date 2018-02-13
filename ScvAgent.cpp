#include "ScvAgent.h"



ScvAgent::ScvAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
	this->isBusy = false;
}

void ScvAgent::OnStep() {
	if (isBusy) return;

	if (shouldBuild(ABILITY_ID::BUILD_SUPPLYDEPOT)) build(ABILITY_ID::BUILD_SUPPLYDEPOT);
	else if (shouldBuild(ABILITY_ID::BUILD_REFINERY)) build(ABILITY_ID::BUILD_REFINERY, findAvailableGeyser());
	else if (shouldBuild(ABILITY_ID::BUILD_BARRACKS)) build(ABILITY_ID::BUILD_BARRACKS);
	else if (shouldBuild(ABILITY_ID::BUILD_FACTORY)) build(ABILITY_ID::BUILD_FACTORY);
	else if (shouldBuild(ABILITY_ID::BUILD_STARPORT)) build(ABILITY_ID::BUILD_STARPORT);
	else if (shouldBuild(ABILITY_ID::BUILD_COMMANDCENTER)) build(ABILITY_ID::BUILD_COMMANDCENTER);
};

void ScvAgent::OnUnitIdle() {
	isBusy = false;
	harvest();
};

ScvAgent::~ScvAgent()
{
}

bool ScvAgent::shouldBuild(ABILITY_ID abilityId)
{
	switch (abilityId)
	{
	case ABILITY_ID::BUILD_SUPPLYDEPOT:
		return observations->GetFoodCap() + h->CountSelfOrdersType(ABILITY_ID::BUILD_SUPPLYDEPOT)*10 < observations->GetFoodUsed() + getProductionCapacity() + 1
			&& observations->helper->HasResourcesToBuild(UNIT_TYPEID::TERRAN_SUPPLYDEPOT);
	case ABILITY_ID::BUILD_REFINERY:
		return h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_REFINERY)
			&& h->CountSelfOrdersType(ABILITY_ID::BUILD_REFINERY) + h->CountSelfAgentType(AGENT_TYPE::TERRAN_REFINERY) < h->CountSelfAgentType(AGENT_TYPE::TERRAN_SCV) / 11
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_SCV) > 15
			&& findAvailableGeyser() != NULL;
	case ABILITY_ID::BUILD_BARRACKS:
		return h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_BARRACKS)
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_BARRACKS) + h->CountSelfOrdersType(ABILITY_ID::BUILD_BARRACKS) < observations->GetFoodWorkers() / 9
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_SCV) > 16
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_SUPPLYDEPOT) > 0;
	case ABILITY_ID::BUILD_FACTORY:
		return h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_FACTORY)
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_FACTORY) + h->CountSelfOrdersType(ABILITY_ID::BUILD_FACTORY) < h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_BARRACKS) / 3;
	case ABILITY_ID::BUILD_STARPORT:
		return h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_STARPORT)
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_STARPORT) + h->CountSelfOrdersType(ABILITY_ID::BUILD_STARPORT) < h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_FACTORY);
	case ABILITY_ID::BUILD_COMMANDCENTER:
		return h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_COMMANDCENTER)
			&& h->CountSelfAgentType(AGENT_TYPE::TERRAN_SCV) / (h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_TOWN_HALL) + h->CountSelfOrdersType(ABILITY_ID::BUILD_COMMANDCENTER)) >= 16;
	default:
		return false;
	}
}

size_t ScvAgent::getProductionCapacity()
{
	//TODO loop optim
	return h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_BARRACKS)
		+ h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_TOWN_HALL)
		+ h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_FACTORY)
		+ h->CountSelfAgentType(AGENT_TYPE::TERRAN_ANY_STARPORT);
}

void ScvAgent::build(ABILITY_ID abilityId, Tag target)
{
	if (target != NULL) {
		actions->Command(abilityId, observations->GetUnit(target));
	}
	else if (abilityId == ABILITY_ID::BUILD_COMMANDCENTER) {
		float minimum_distance = std::numeric_limits<float>::max();
		Point3D closest_expansion;
		for (const auto& expansion : observations->strategy->expansionLocations) {
			float current_distance = Distance2D(self->pos, expansion);

			if (current_distance < minimum_distance && query->Placement(abilityId, expansion)) {
				closest_expansion = expansion;
				minimum_distance = current_distance;
			}
		}

		actions->Command(abilityId, closest_expansion);
	}
	else {
		actions->Command(abilityId, findEmptyBuildPlacement(abilityId, self->pos));
	}
	observations->strategy->publicOrdersThisStep.push_back(abilityId);
	isBusy = true;
}

Tag ScvAgent::findAvailableGeyser()
{
	Tag closestGeyser = NULL;
	Units geysers = h->GetUnits(Unit::Alliance::Neutral, AGENT_TYPE::NEUTRAL_ANY_VESPENE);
	Units commandcenters = h->GetUnits(Unit::Alliance::Self, AGENT_TYPE::TERRAN_ANY_TOWN_HALL);
	
	float max_distance = 15.0f;//must be close from a base

	for (const auto& geyser : geysers) {
		for (const auto& commandcenter : commandcenters) {
			float current_distance = Distance2D(commandcenter->pos, geyser->pos);

			if (current_distance < max_distance && query->Placement(ABILITY_ID::BUILD_REFINERY, geyser->pos)) {
				max_distance = current_distance;
				closestGeyser = geyser->tag;
			}
		}
	}

	return closestGeyser;
}

bool ScvAgent::harvest()
{
	//try harvest vespene
	Units refineries = h->GetUnits(Unit::Alliance::Self, AGENT_TYPE::TERRAN_REFINERY);
	float distanceMax = std::numeric_limits<float>::max();
	const Unit* refinery_target = nullptr;
	for (const auto& refinery : refineries) {
		if (refinery->ideal_harvesters - refinery->assigned_harvesters > 0) {
			float d = DistanceSquared2D(refinery->pos, self->pos);

			if (d < distanceMax) {
				distanceMax = d;
				refinery_target = refinery;
			}
		}
	}

	if (refinery_target != nullptr) {
		actions->Command(ABILITY_ID::SMART, refinery_target);
		return true;
	}

	//try harvest mineral
	Units commandCenters = h->GetSelfUnits(AGENT_TYPE::TERRAN_ANY_TOWN_HALL);
	for (const auto& commandCenter : commandCenters) {
		if (commandCenter->ideal_harvesters - commandCenter->assigned_harvesters > 0) {
			
			Units mineralPatchs = h->GetUnits(Unit::Alliance::Neutral, AGENT_TYPE::NEUTRAL_MINERALFIELD);
			float distance = std::numeric_limits<float>::max();
			const Unit* mineral_target = nullptr;

			for (const auto& mineralPatch : mineralPatchs) {

				float d = DistanceSquared2D(mineralPatch->pos, commandCenter->pos);
				if (d < distance) {
					distance = d;
					mineral_target = mineralPatch;
				}
			}

			actions->Command(ABILITY_ID::SMART, mineral_target);
			return true;
		}
	}

	return false;
}

Point2D ScvAgent::findEmptyBuildPlacement(ABILITY_ID abilityId, Point2D closestTo)
{
	float theta = 1, r = 5;
	Point2D pos;

	for (int p = 0; p < 99; p++) {
		pos = Point2D(r * cos(theta) + closestTo.x, r * sin(theta) + closestTo.y);

		if (query->Placement(abilityId, pos)) {
			return pos;
		}

		r++;
		theta++;
	}

	return pos;
}
