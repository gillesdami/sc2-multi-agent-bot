#include "DefaultAgent.h"



DefaultAgent::DefaultAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations) : UnitAgent(self, actions, observations)
{
	std::cout << "WARNING: Default agent instanciated (" << (int)self->unit_type.ToType() << ")" << std::endl;
}

DefaultAgent::~DefaultAgent()
{
}
