#include "CommandCenterAgent.h"

CommandCenterAgent::CommandCenterAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}

void CommandCenterAgent::OnStep()
{
	if (this->self->orders.empty()
		&& this->observations->GetMinerals() > 50
		&& this->self->ideal_harvesters - this->self->assigned_harvesters > 0) {

		this->actions->Command(ABILITY_ID::TRAIN_SCV);
	}
}

void CommandCenterAgent::OnUnitIdle()
{
}

CommandCenterAgent::~CommandCenterAgent()
{
}
