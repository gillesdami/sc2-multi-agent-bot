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

void Bot::OnUnitIdle(const Unit* unit)
{
	this->agents.find(unit)->second->get()->OnUnitIdle();
}

void Bot::OnUnitCreated(const Unit* unit)
{
	std::unique_ptr<UnitAgent>* agent;

	switch (unit->unit_type.ToType()) {
	case UNIT_TYPEID::TERRAN_COMMANDCENTER:
		agent = new std::unique_ptr<UnitAgent>(
			new CommandCenterAgent(
				unit,
				new SelfActionInterface(unit, this->Actions()),
				new SelfObservationInterface(unit, this->Observation(), this->strategy)));

		this->agents.insert(std::make_pair(unit, agent));
	default:
		agent = new std::unique_ptr<UnitAgent>(
			new DefaultAgent(
				unit,
				new SelfActionInterface(unit, this->Actions()),
				new SelfObservationInterface(unit, this->Observation(), this->strategy)));

		this->agents.insert(std::make_pair(unit, agent));
	}
}

void Bot::OnUnitDestroyed(const Unit* unit)
{
	std::unordered_map<const Unit*, std::unique_ptr<UnitAgent>*>::const_iterator it = this->agents.find(unit);
	if(it != this->agents.end()) this->agents.erase(it);
}
