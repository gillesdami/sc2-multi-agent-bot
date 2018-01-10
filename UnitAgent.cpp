#include "UnitAgent.h"
#include <iostream>
UnitAgent::UnitAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations)
{
	this->self = self;
	this->actions = actions;
	this->observations = observations;
}

UnitAgent::~UnitAgent()
{
	delete this->actions;
	delete this->observations;
}
