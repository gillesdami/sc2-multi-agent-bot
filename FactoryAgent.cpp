#include "FactoryAgent.h"

FactoryAgent::FactoryAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}

void FactoryAgent::OnStep()
{
	if (!self->orders.size()) {
		if (h->HasResourcesToBuild(UNIT_TYPEID::TERRAN_WIDOWMINE)) train(ABILITY_ID::TRAIN_WIDOWMINE);
	}
}

void FactoryAgent::OnUnitIdle()
{
}

void FactoryAgent::train(ABILITY_ID abilityId)
{
	actions->Command(abilityId);
}

FactoryAgent::~FactoryAgent()
{
}
