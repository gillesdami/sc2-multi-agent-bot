#include "MarineAgent.h"

MarineAgent::MarineAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : MilitaryAgent(self, actions, observations, query)
{
}


MarineAgent::~MarineAgent()
{
}

void MarineAgent::OnStep() {
	MilitaryAgent::OnStep();
}

void MarineAgent::OnUnitIdle() {
}
