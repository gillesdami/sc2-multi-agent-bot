#include "Bot.h"

void Bot::OnGameStart() 
{
	std::cout << "Hello, World!" << std::endl;
	this->strategy = new BotStrategy();
	this->strategy->expansionLocations = search::CalculateExpansionLocations(Observation(), Query());
}

void Bot::OnStep() 
{
	this->strategy->publicOrdersThisStep.clear();

	for (auto it = this->agents.begin(); it != this->agents.end(); ++it) {
		it->second.get()->OnStep();
	}
}

void Bot::OnUnitIdle(const Unit* unit)
{
	this->agents.find(unit)->second.get()->OnUnitIdle();
}

void Bot::OnUnitCreated(const Unit* unit)
{
	switch (unit->unit_type.ToType()) {
	case UNIT_TYPEID::TERRAN_COMMANDCENTER:
		this->agents.insert(std::make_pair(unit, std::make_unique<CommandCenterAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy))));
		break;
	case UNIT_TYPEID::TERRAN_SCV:
		this->agents.insert(std::make_pair(unit, std::make_unique<ScvAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy),
			this->Query())));
		break;
	case UNIT_TYPEID::TERRAN_SUPPLYDEPOT:
		this->agents.insert(std::make_pair(unit, std::make_unique<SupplydepotAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy))));
		break;
	case UNIT_TYPEID::TERRAN_BARRACKS:
		this->agents.insert(std::make_pair(unit, std::make_unique<BarrackAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy))));
		break;
	case UNIT_TYPEID::TERRAN_FACTORY:
		this->agents.insert(std::make_pair(unit, std::make_unique<FactoryAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy))));
		break;
	case UNIT_TYPEID::TERRAN_STARPORT:
		this->agents.insert(std::make_pair(unit, std::make_unique<StarportAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy))));
		break;
	case UNIT_TYPEID::TERRAN_MARINE:
		this->agents.insert(std::make_pair(unit, std::make_unique<MarineAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy),
			this->Query())));
		break;
	case UNIT_TYPEID::TERRAN_REAPER:
		this->agents.insert(std::make_pair(unit, std::make_unique<ReaperAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy),
			this->Query())));
		break;
	case UNIT_TYPEID::TERRAN_WIDOWMINE:
		this->agents.insert(std::make_pair(unit, std::make_unique<WidowmineAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy),
			this->Query())));
		break;
	case UNIT_TYPEID::TERRAN_VIKINGFIGHTER:
		this->agents.insert(std::make_pair(unit, std::make_unique<VikingAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy),
			this->Query())));
		break;
	case UNIT_TYPEID::TERRAN_REFINERY:
		this->agents.insert(std::make_pair(unit, std::make_unique<UnitAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy)
			)));
		break;
	default:
		std::cout << "WARNING: Default agent instanciated (" << unit->unit_type.to_string() << ")" << std::endl;

		this->agents.insert(std::make_pair(unit, std::make_unique<UnitAgent>(
			unit,
			new SelfActionInterface(unit, this->Actions()),
			new SelfObservationInterface(unit, this->Observation(), this->strategy))));
	}
}

void Bot::OnUnitDestroyed(const Unit* unit)
{
	std::unordered_map<const Unit*, std::unique_ptr<UnitAgent>>::const_iterator it = this->agents.find(unit);
	if (it != this->agents.end()) {
		this->agents.erase(it);
	}
}
