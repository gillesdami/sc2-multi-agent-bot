#include "StarportAgent.h"

StarportAgent::StarportAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}

void StarportAgent::OnStep()
{
	if (self->orders.empty()) {
		if (h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_VIKINGFIGHTER)) train(ABILITY_ID::TRAIN_VIKINGFIGHTER);
	}
}

void StarportAgent::OnUnitIdle()
{
}

void StarportAgent::train(ABILITY_ID abilityId)
{
	actions->Command(abilityId);
}

StarportAgent::~StarportAgent()
{
}
