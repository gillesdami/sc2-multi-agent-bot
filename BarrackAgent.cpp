#include "BarrackAgent.h"

BarrackAgent::BarrackAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
	actions->Command(ABILITY_ID::SMART, h->GetClosest(h->GetSelfUnits(AGENT_TYPE::TERRAN_COMMANDCENTER))->pos);
}


BarrackAgent::~BarrackAgent()
{
}

void BarrackAgent::OnStep() 
{
	if (self->orders.size() == 0) {
		trainAgent();
	}
}

void BarrackAgent::OnUnitIdle()
{
}

void BarrackAgent::trainAgent() {
	if (this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_MARINE)).size()/2 >
		this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_REAPER)).size()) {
		if (this->observations->GetMinerals() > 100 && this->observations->GetVespene() > 100)
		{
			train(ABILITY_ID::TRAIN_REAPER);
		}
	}
	else
	{
		if (this->observations->GetMinerals() > 100)
		{
			train(ABILITY_ID::TRAIN_MARINE);
		}
	}
}

void BarrackAgent::train(ABILITY_ID abilityId) {
	this->actions->Command(abilityId);
}