#include "MilitaryAgent.h"

MilitaryAgent::MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
}


MilitaryAgent::~MilitaryAgent()
{
}

void MilitaryAgent::OnStep() {
	if (isIdle) {
		move();
		isIdle = false;
	}
}

void MilitaryAgent::OnUnitIdle() {
	isIdle = true;
}

void MilitaryAgent::move() {
	Units marines = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_MARINE));
	const Unit* unit = GetRandomEntry(marines);
	//this->actions->Command(ABILITY_ID::MOVE);
	Units units = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
	for (const auto& commandCenter : units) {
		this->actions->Command(ABILITY_ID::MOVE,commandCenter->pos);
	}
}