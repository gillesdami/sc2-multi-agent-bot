#pragma once

#include <sc2api\sc2_unit.h>

#include "UnitAgent.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

using namespace sc2;

class CommandCenterAgent : public UnitAgent
{
public:
	CommandCenterAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations);

	void OnStep();
	void OnUnitIdle();

	~CommandCenterAgent();

private:
	bool refineryRequireWorkers();
};

