#include "util.h"

sc2::IsAgent sc2::Helper::IsAgent(AGENT_TYPE agentType) {
	return sc2::IsAgent(agentType, observations);
}

int sc2::Helper::CountAgentType(Unit::Alliance alliance, AGENT_TYPE agentType) {
	return this->FilterOutOfRangeUnits(observations->GetUnits(alliance, IsAgent(agentType))).size();
}

int sc2::Helper::CountSelfAgentType(AGENT_TYPE agentType) {
	return CountAgentType(Unit::Alliance::Self, agentType);
}

bool sc2::Helper::HasResourcesToBuild(UNIT_TYPEID typeId)
{
	return observations->GetMinerals() >= observations->GetUnitTypeData().at(((UnitTypeID)typeId)).mineral_cost
		&& observations->GetVespene() >= observations->GetUnitTypeData().at((UnitTypeID)typeId).vespene_cost;
}

bool sc2::Helper::IsIdle() {
	return self->orders.size() == 0;
}

bool sc2::Helper::IsIdle(const Unit* unit) {
	return unit->orders.size() == 0;
}

bool sc2::Helper::IsIdle(Tag tag) {
	return IsIdle(this->observations->GetUnit(tag));
}

int sc2::Helper::CountOrdersType(ABILITY_ID abilityId, Unit::Alliance alliance)
{
	int count = 0;

	Units units = observations->GetUnits(alliance);
	for (const auto& unit : units) {
		for (const auto& order : unit->orders) {
			if (order.ability_id == abilityId) {
				count++;
			}
		}
	}

	if (Unit::Alliance::Self == alliance) {
		for (auto ability : this->strategy->publicOrdersThisStep) {
			if (ability == abilityId) count++;
		}
	}

	return count;
}

int sc2::Helper::CountSelfOrdersType(ABILITY_ID abilityId) {
	return CountOrdersType(abilityId, Unit::Alliance::Self);
}

Units sc2::Helper::GetUnits(Unit::Alliance alliance, AGENT_TYPE agentType) {
	return this->FilterOutOfRangeUnits(this->observations->GetUnits(alliance, IsAgent(agentType)));
}

Units sc2::Helper::GetSelfUnits(AGENT_TYPE agentType) {
	return GetUnits(Unit::Alliance::Self, agentType);
}

const Unit * sc2::Helper::GetClosest(Units units)
{
	const Unit* closest = nullptr;
	float distance = std::numeric_limits<float>::max();

	for (const auto& unit : units) {

		float d = DistanceSquared2D(unit->pos, self->pos);
		if (d < distance) {
			distance = d;
			closest = unit;
		}
	}

	return closest;
}

bool sc2::Helper::isSupplyBlock()
{
	return this->observations->GetFoodCap() <= this->observations->GetFoodUsed();
}

Units sc2::Helper::FilterOutOfRangeUnits(Units units)
{
	for (auto it = units.begin(); it != units.end();)
	{
		auto & unit = *it;

		if (((unit->alliance == Unit::Alliance::Self || unit->alliance == Unit::Alliance::Neutral) && isCivil)
			|| IsInSight(unit->pos)
			|| IsAgent(AGENT_TYPE::TERRAN_ANY_TOWN_HALL)(*unit))
			++it;
		else
			it = units.erase(it);
	}

	return units;
}

bool sc2::Helper::IsInSight(Point2D point)
{
	return selfSightRange > Distance2D(self->pos, point);
}
