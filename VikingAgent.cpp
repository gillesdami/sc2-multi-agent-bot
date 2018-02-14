#include "VikingAgent.h"



VikingAgent::VikingAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : MilitaryAgent(self, actions, observations, query)
{
}

void VikingAgent::OnStep()
{
	if (!self->is_flying && h->CountAgentType(Unit::Alliance::Enemy, AGENT_TYPE::ALL_FLYING) > 0) {
		actions->Command(ABILITY_ID::MORPH_VIKINGFIGHTERMODE);
	}
	else if (self->is_flying && h->CountAgentType(Unit::Alliance::Enemy, AGENT_TYPE::ALL_FLYING) == 0) {
		actions->Command(ABILITY_ID::MORPH_VIKINGASSAULTMODE);
	}
	else {
		MilitaryAgent::OnStep();
	}
}

void VikingAgent::OnUnitIdle()
{
}


VikingAgent::~VikingAgent()
{
}
