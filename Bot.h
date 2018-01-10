#pragma once

#include <sc2api/sc2_api.h>
#include <iostream>
#include <memory>

#include "UnitAgent.h"
#include "BotStrategy.h"

using namespace sc2;

class Bot : public Agent {
public:
	virtual void OnGameStart() final;
	virtual void OnStep() final;
private:
	std::unique_ptr<UnitAgent>* getAgent(Unit* unit);
	void deleteAgent(Unit* unit);

	std::unordered_map<Unit*, std::unique_ptr<UnitAgent>*> agents;
	BotStrategy* strategy;
};
