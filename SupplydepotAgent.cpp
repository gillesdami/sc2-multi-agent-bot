#include "SupplydepotAgent.h"

SupplydepotAgent::SupplydepotAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}

void SupplydepotAgent::OnStep()
{
	Units ennemies = this->observations->GetUnits(Unit::Alliance::Enemy);
	if (ennemies.size() > 0 && this->self->unit_type == UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED) {
		this->actions->Command(ABILITY_ID::MORPH_SUPPLYDEPOT_RAISE);
	}
	else if (ennemies.size() == 0 && this->self->unit_type == UNIT_TYPEID::TERRAN_SUPPLYDEPOT) {
		this->actions->Command(ABILITY_ID::MORPH_SUPPLYDEPOT_LOWER);
	}
}

SupplydepotAgent::~SupplydepotAgent()
{
}
