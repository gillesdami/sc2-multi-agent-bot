#include "ReaperAgent.h"

ReaperAgent::ReaperAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations, QueryInterface * query) : MilitaryAgent(self, actions, observations, query)
{
}

void ReaperAgent::OnStep()
{
}

ReaperAgent::~ReaperAgent()
{
}
