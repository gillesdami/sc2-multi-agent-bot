#pragma once

#include <sc2api/sc2_api.h>
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
private:
	std::unique_ptr<UnitAgent>* getAgent(const Unit* unit);
	void deleteAgent(const Unit* unit);

	std::unordered_map<const Unit*, std::unique_ptr<UnitAgent>*> agents;
	BotStrategy* strategy;
};
