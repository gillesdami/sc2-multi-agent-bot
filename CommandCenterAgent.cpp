#include "CommandCenterAgent.h"

CommandCenterAgent::CommandCenterAgent(Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}

void CommandCenterAgent::OnStep()
{
}

void CommandCenterAgent::OnUnitIdle()
{
	this->actions->Command(ABILITY_ID::TRAIN_SCV);
}

CommandCenterAgent::~CommandCenterAgent()
{
}
