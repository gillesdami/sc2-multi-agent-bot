#include "WidowmineAgent.h"



WidowmineAgent::WidowmineAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : MilitaryAgent(self, actions, observations, query)
{
}

void WidowmineAgent::OnStep()
{
	if (!self->is_burrowed && h->CountAgentType(Unit::Alliance::Enemy, AGENT_TYPE::ALL_MILITARY) + h->CountAgentType(Unit::Alliance::Enemy, AGENT_TYPE::ALL_CIVIL) > 0) {
		actions->Command(ABILITY_ID::BURROWDOWN_WIDOWMINE);
	}
	else if (self->is_burrowed && h->CountAgentType(Unit::Alliance::Enemy, AGENT_TYPE::ALL_MILITARY) + h->CountAgentType(Unit::Alliance::Enemy, AGENT_TYPE::ALL_CIVIL) == 0) {
		actions->Command(ABILITY_ID::BURROWUP_WIDOWMINE);
	}
	else if (!self->is_burrowed) {
		MilitaryAgent::OnStep();
	}
}

void WidowmineAgent::OnUnitIdle()
{
}


WidowmineAgent::~WidowmineAgent()
{
}
