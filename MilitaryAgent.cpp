#include "MilitaryAgent.h"

MilitaryAgent::MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
}

MilitaryAgent::~MilitaryAgent()
{
}

void MilitaryAgent::OnStep() {
}

void MilitaryAgent::OnUnitIdle() {
}

float MilitaryAgent::GetPathingDistance(Point2D dest)
{
	return query->PathingDistance(self, dest) > 0.1f;
}
