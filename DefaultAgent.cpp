#include "DefaultAgent.h"



DefaultAgent::DefaultAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations) : UnitAgent(self, actions, observations)
{
	std::cout << "A default agent is born, his type is: " << (int)self->unit_type.ToType() << std::endl;
}

DefaultAgent::~DefaultAgent()
{
}
