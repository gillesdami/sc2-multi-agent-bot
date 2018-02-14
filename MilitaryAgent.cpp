#include "MilitaryAgent.h"

MilitaryAgent::MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
}

MilitaryAgent::~MilitaryAgent()
{
}

void MilitaryAgent::OnStep() {
	Units threats = h->GetUnits(Unit::Alliance::Enemy, AGENT_TYPE::ALL_MILITARY);
	Units civil = h->GetUnits(Unit::Alliance::Enemy, AGENT_TYPE::ALL_CIVIL);
	Units building = h->GetUnits(Unit::Alliance::Enemy, AGENT_TYPE::ALL_BUILDING);

	//atk ennemies in sight
	if (threats.size()) {
		actions->Command(ABILITY_ID::ATTACK, h->GetClosest(threats));
	}
	else if (civil.size()) {
		actions->Command(ABILITY_ID::ATTACK, h->GetClosest(civil));
	}
	else if (building.size()) {
		actions->Command(ABILITY_ID::ATTACK, h->GetClosest(building));
	}
	//go to the closest objective
	else if (observations->strategy->objectives.size()) {
		Point2D closest;
		float distance = std::numeric_limits<float>::max();

		for (auto pair : observations->strategy->objectives) {

			float d = DistanceSquared2D(pair.second, self->pos);
			if (d < distance) {
				distance = d;
				closest = pair.second;
			}
		}

		actions->Command(ABILITY_ID::SMART, closest);
	}
	//go to the closest commandCenter
	else {
		Units commandCenters = h->GetSelfUnits(AGENT_TYPE::TERRAN_ANY_TOWN_HALL);

		if (commandCenters.size()) {
			const Unit* closest = h->GetClosest(commandCenters);

			if (Distance2D(closest->pos, self->pos) > 10.0f) {
				actions->Command(ABILITY_ID::SMART, closest);
			}
		}
	}
}

void MilitaryAgent::OnUnitIdle() {
}

float MilitaryAgent::GetPathingDistance(Point2D dest)
{
	return query->PathingDistance(self, dest) > 0.1f;
}
