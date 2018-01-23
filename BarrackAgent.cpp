#include "BarrackAgent.h"

BarrackAgent::BarrackAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}


BarrackAgent::~BarrackAgent()
{
}

void BarrackAgent::OnStep() 
{

}

void BarrackAgent::OnUnitIdle()
{
	this->actions->Command(ABILITY_ID::TRAIN_MARINE);
}
