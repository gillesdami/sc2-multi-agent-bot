#include "MarineAgent.h"

MarineAgent::MarineAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query) : MilitaryAgent(self, actions, observations, query)
{
}


MarineAgent::~MarineAgent()
{
}

void MarineAgent::OnStep() {
	if (isIdle) {
		move();
		isIdle = false;
	}
}

void MarineAgent::OnUnitIdle() {
	isIdle = true;
}

void MarineAgent::move() {
	Units marines = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_MARINE));
	Units units = this->observations->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::TERRAN_COMMANDCENTER));
	for (const auto& commandCenter : units) {
		const Point2D point = commandCenter->pos;
		float x = point.x;
		float y = point.y;
		for (const auto& unit : marines)
		{
			if (this->GetPathingDistance(Point2D(x, y)) != 0)
			{
				RetreatWithUnit(unit, Point2D(x, y));
			}
			else
			{
				RetreatWithUnit(unit, Point2D(x + 1, y + 1));
			}

		}
	}
}


void MarineAgent::RetreatWithUnit(const Unit* unit, Point2D retreat_position) {
	float dist = Distance2D(unit->pos, retreat_position);
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