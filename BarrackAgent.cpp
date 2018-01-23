#include "BarrackAgent.h"

BarrackAgent::BarrackAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}


BarrackAgent::~BarrackAgent()
{
}

void BarrackAgent::OnStep() 
{
	if (isIdle && this->observations->GetMinerals()>100) {
		isIdle = false;
		this->actions->Command(ABILITY_ID::TRAIN_MARINE);
	}
}

void BarrackAgent::OnUnitIdle()
{
	isIdle = true;
}
