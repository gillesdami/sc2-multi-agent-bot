#include "MilitaryAgent.h"

MilitaryAgent::MilitaryAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations,QueryInterface* query) : UnitAgent(self, actions, observations)
{
	this->query = query;
}


MilitaryAgent::~MilitaryAgent()
{
}

void MilitaryAgent::OnStep() {
	if (isIdle) {
		move();
		isIdle = false;
	}
}

void MilitaryAgent::OnUnitIdle() {
	isIdle = true;
}

void MilitaryAgent::move() {
	Units marines = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_MARINE));
	Units units = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
	for (const auto& commandCenter : units) {
		const Point2D point = commandCenter->pos;
		float x = point.x;
		float y = point.y;
		for (const auto& unit : marines)
		{
			if (this->query->PathingDistance(unit, Point2D(x, y))!=0)
			{
				RetreatWithUnit(unit, Point2D(x, y));
			}
			else
			{
				RetreatWithUnit(unit, Point2D(x + 1, y + 1));
			}
			
		}
		//this->actions->Command(ABILITY_ID::MOVE, this->findPlacement(ABILITY_ID::MOVE, Point2D(x + 4, y + 8)));
		//findPlacement(ABILITY_ID::MOVE, Point2D(x + 4, y + 8));
		//this->actions->Command(ABILITY_ID::MOVE, Point2D(x + 4, y + 8));
		
	}
}

Point2D MilitaryAgent::findPlacement(ABILITY_ID abilityId, Point2D point, float increment) {

	if (increment >= 99) {
		std::cout << "Fail to find" << std::endl;
		return point;
	}

	if (this->query->Placement(abilityId,point))
	{
		return point;
	}

	return this->findPlacement(abilityId, Point2D(point.x + cos(increment)*increment, point.y + sin(increment)*increment), increment + 0.1234f);
}

void MilitaryAgent::RetreatWithUnit(const Unit* unit, Point2D retreat_position) {
	float dist = Distance2D(unit->pos, retreat_position);
	std::cout << "Distance : " << dist << std::endl;
	if (dist < 1) {
		if (unit->orders.empty()) {
			return;
		}
		this->actions->Command(ABILITY_ID::STOP, unit);
		return;
	}

	if (unit->orders.empty() && dist > 2) {
		this->actions->Command(ABILITY_ID::MOVE, retreat_position);
	}
	else if (!unit->orders.empty() && dist > 2) {
		if (unit->orders.front().ability_id != ABILITY_ID::MOVE) {
			this->actions->Command(ABILITY_ID::MOVE, retreat_position);
		}
	}
}