#include "CommandCenterAgent.h"

CommandCenterAgent::CommandCenterAgent(const Unit * self, SelfActionInterface * actions, SelfObservationInterface * observations) : UnitAgent(self, actions, observations)
{
}

void CommandCenterAgent::OnStep()
{
	if (this->self->orders.empty()
		&& this->observations->GetMinerals() > 50
		&& (this->self->ideal_harvesters - this->self->assigned_harvesters > 0
			|| this->refineryRequireWorkers())) {

		this->actions->Command(ABILITY_ID::TRAIN_SCV);
	}
}

void CommandCenterAgent::OnUnitIdle()
{
}

CommandCenterAgent::~CommandCenterAgent()
{
}

bool CommandCenterAgent::refineryRequireWorkers()
{
	Units refineries = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_REFINERY));
	Units commandcenters = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));

	for (const auto& refinery : refineries) {
		if (Distance2D(this->self->pos, refinery->pos) < 15.0f && refinery->ideal_harvesters > refinery->assigned_harvesters) {
			return true;
		}
	}

	return false;
}
