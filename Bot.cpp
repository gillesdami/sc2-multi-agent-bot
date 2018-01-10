#include "Bot.h"

void Bot::OnGameStart() {
	std::cout << "Hello, World!" << std::endl;
}

void Bot::OnStep() {
}

std::unique_ptr<UnitAgent>* Bot::getAgent(Unit * unit)
{
	return this->agents.find(unit)->second;
}

void Bot::deleteAgent(Unit * unit)
{
	this->agents.erase(this->agents.find(unit));
}
