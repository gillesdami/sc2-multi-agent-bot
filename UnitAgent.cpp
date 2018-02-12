#include "UnitAgent.h"

UnitAgent::UnitAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations)
{
	this->self = self;
	this->actions = actions;
	this->observations = observations;
	this->h = observations->helper;
}

UnitAgent::~UnitAgent()
{
	delete this->actions;
	delete this->observations;
}
