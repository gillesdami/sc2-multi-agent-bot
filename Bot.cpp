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
	this->getAgent(unit)->get()->OnUnitIdle();
}

std::unique_ptr<UnitAgent>* Bot::getAgent(const Unit* unit)
{
	std::unique_ptr<UnitAgent>* agent;
	std::unordered_map<const Unit*, std::unique_ptr<UnitAgent>*>::const_iterator it = this->agents.find(unit);

	if (it == this->agents.end()) //if not found
	{
		switch (unit->unit_type.ToType()) {
		case UNIT_TYPEID::TERRAN_COMMANDCENTER:
			agent = new std::unique_ptr<UnitAgent>( 
				new CommandCenterAgent(
					unit, 
					new SelfActionInterface(unit, this->Actions()), 
					new SelfObservationInterface(unit, this->Observation(), this->strategy)));

			this->agents.insert(std::make_pair(unit, agent));
			return agent;
		default:
			agent = new std::unique_ptr<UnitAgent>(
				new DefaultAgent(
					unit,
					new SelfActionInterface(unit, this->Actions()),
					new SelfObservationInterface(unit, this->Observation(), this->strategy)));

			this->agents.insert(std::make_pair(unit, agent));
			return agent;
		}
	}

	return it->second;
}

void Bot::deleteAgent(const Unit* unit)
{
	this->agents.erase(this->agents.find(unit));
}
