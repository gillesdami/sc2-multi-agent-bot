#pragma once

#include <sc2api/sc2_api.h>
#include <sc2lib/sc2_search.h>

#include <iostream>
#include <memory>

#include "UnitAgent.h"
#include "BotStrategy.h"
#include "Agents.h"
#include "SelfActionInterface.h"
#include "SelfObservationInterface.h"

using namespace sc2;

class Bot : public Agent {
public:
	virtual void OnGameStart() final;
	virtual void OnStep() final;
	virtual void OnUnitIdle(const Unit* unit) final;
	virtual void OnUnitCreated(const Unit* unit) final;
	virtual void OnUnitDestroyed(const Unit* unit) final;
private:
	std::unordered_map<const Unit*, std::unique_ptr<UnitAgent>> agents;
	BotStrategy* strategy;
};
	