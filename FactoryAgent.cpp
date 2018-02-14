#include "FactoryAgent.h"

FactoryAgent::FactoryAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
	actions->Command(ABILITY_ID::SMART, h->GetClosest(h->GetSelfUnits(AGENT_TYPE::TERRAN_COMMANDCENTER))->pos);
}

void FactoryAgent::OnStep()
{
	if (!self->orders.size() && !h->isSupplyBlock()) {
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
