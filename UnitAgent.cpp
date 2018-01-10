#include "UnitAgent.h"

UnitAgent::UnitAgent(Unit * self, SelfActionInterface * actions, ObservationRelativeInterface * observations)
{
	this->self = self;
	this->actions = actions;
	this->observations = observations;
}
