#include "Bot.h"

void Bot::OnGameStart() 
{
	std::cout << "Hello, World!" << std::endl;
}

void Bot::OnStep() 
{
	for (auto it = this->agents.begin(); it != this->agents.end(); ++it)
		it->second->get()->OnStep();
}

void Bot::OnUnitIdle(Unit* unit)
{
	this->getAgent(unit)->get()->OnUnitIdle();
}

std::unique_ptr<UnitAgent>* Bot::getAgent(Unit* unit)
{
	std::unordered_map<Unit*, std::unique_ptr<UnitAgent>*>::const_iterator it = this->agents.find(unit);

	if (it == this->agents.end()) //if not found
	{
		//TODO
	}

	return it->second;
}

void Bot::deleteAgent(Unit* unit)
{
	this->agents.erase(this->agents.find(unit));
}
