#include "SelfObservationInterface.h"



SelfObservationInterface::SelfObservationInterface(const Unit* self, const ObservationInterface* observations, BotStrategy* strategy)
{
	this->self = self;
	this->observations = observations;
	this->strategy = strategy;

	this->isCivil = (IsAgent(AGENT_TYPE::TERRAN_ANY_CIVIL, observations)(*self) || IsAgent(AGENT_TYPE::TERRAN_ANY_BUILDING, observations)(*self));
	this->selfSightRange = observations->GetUnitTypeData().at(((UnitTypeID)self->unit_type)).sight_range;
	
	this->helper = new Helper(observations, self, strategy);
}

SelfObservationInterface::~SelfObservationInterface()
{
	delete this->helper;
}

uint32_t SelfObservationInterface::GetPlayerID() const {
	return this->observations->GetPlayerID();
}

uint32_t SelfObservationInterface::GetGameLoop() const {
	return this->observations->GetGameLoop();
}

Units SelfObservationInterface::GetUnits() {
	return this->FilterOutOfRangeUnits(this->observations->GetUnits());
}

Units SelfObservationInterface::GetUnits(Unit::Alliance alliance, Filter filter) {
	return this->FilterOutOfRangeUnits(this->observations->GetUnits(alliance, filter));
}

Units SelfObservationInterface::GetUnits(Filter filter) {
	return this->FilterOutOfRangeUnits(this->observations->GetUnits(filter));
}

const Unit * SelfObservationInterface::GetUnit(Tag tag) const {
	return this->observations->GetUnit(tag);
}

const RawActions & SelfObservationInterface::GetRawActions() const {
	return this->observations->GetRawActions();
}

const SpatialActions & SelfObservationInterface::GetFeatureLayerActions() const {
	return this->observations->GetFeatureLayerActions();
}

const SpatialActions & SelfObservationInterface::GetRenderedActions() const {
	return this->observations->GetRenderedActions();
}

const std::vector< ChatMessage > & SelfObservationInterface::GetChatMessages() const {
	return this->observations->GetChatMessages();
}

const std::vector< PowerSource > & SelfObservationInterface::GetPowerSources() const {
	return this->observations->GetPowerSources();
}

const std::vector< Effect > & SelfObservationInterface::GetEffects() const {
	return this->observations->GetEffects();
}

const std::vector< UpgradeID > & SelfObservationInterface::GetUpgrades() const {
	return this->observations->GetUpgrades();
}

const Score & SelfObservationInterface::GetScore() const {
	return this->observations->GetScore();
}

const Abilities & SelfObservationInterface::GetAbilityData(bool force_refresh) const {
	return this->observations->GetAbilityData(force_refresh);
}

const UnitTypes & SelfObservationInterface::GetUnitTypeData(bool force_refresh) const {
	return this->observations->GetUnitTypeData(force_refresh);
}

const Upgrades & SelfObservationInterface::GetUpgradeData(bool force_refresh) const {
	return this->observations->GetUpgradeData(force_refresh);
}

const Buffs & SelfObservationInterface::GetBuffData(bool force_refresh) const {
	return this->observations->GetBuffData(force_refresh);
}

const Effects & SelfObservationInterface::GetEffectData(bool force_refresh) const {
	return this->observations->GetEffectData(force_refresh);
}

const GameInfo & SelfObservationInterface::GetGameInfo() const {
	return this->observations->GetGameInfo();
}

int32_t SelfObservationInterface::GetMinerals() const {
	return this->observations->GetMinerals();
}

int32_t SelfObservationInterface::GetVespene() const {
	return this->observations->GetVespene();
}

int32_t SelfObservationInterface::GetFoodCap() const {
	return this->observations->GetFoodCap();
}

int32_t SelfObservationInterface::GetFoodUsed() const {
	return this->observations->GetFoodUsed();
}

int32_t SelfObservationInterface::GetFoodArmy() const {
	return this->observations->GetFoodArmy();
}

int32_t SelfObservationInterface::GetFoodWorkers() const {
	return this->observations->GetFoodWorkers();
}

int32_t SelfObservationInterface::GetIdleWorkerCount() const {
	return this->observations->GetIdleWorkerCount();
}

int32_t SelfObservationInterface::GetArmyCount() const {
	return this->observations->GetArmyCount();
}

int32_t SelfObservationInterface::GetWarpGateCount() const {
	return this->observations->GetWarpGateCount();
}

Point2D SelfObservationInterface::GetCameraPos() const {
	return this->observations->GetCameraPos();
}

Point3D SelfObservationInterface::GetStartLocation() const {
	return this->observations->GetStartLocation();
}

const std::vector< PlayerResult > & SelfObservationInterface::GetResults() const {
	return this->observations->GetResults();
}

bool SelfObservationInterface::HasCreep(const Point2D &point) const {
	return this->observations->HasCreep(point);
}

Visibility SelfObservationInterface::GetVisibility(const Point2D &point) const {
	return this->observations->GetVisibility(point);
}

bool SelfObservationInterface::IsPathable(const Point2D &point) const {
	return this->observations->IsPathable(point);
}

bool SelfObservationInterface::IsPlacable(const Point2D &point) const {
	return this->observations->IsPlacable(point);
}

float SelfObservationInterface::TerrainHeight(const Point2D &point) const {
	return this->observations->TerrainHeight(point);
}

Units SelfObservationInterface::FilterOutOfRangeUnits(Units units)
{
	for (auto it = units.begin(); it != units.end();)
	{
		auto & unit = *it;

		if (((unit->alliance == Unit::Alliance::Self || unit->alliance == Unit::Alliance::Neutral) && isCivil) || IsInSight(unit->pos))
			++it;
		else
			it = units.erase(it);
	}

	return units;
}

bool SelfObservationInterface::IsInSight(Point2D point)
{
	return selfSightRange < Distance2D(self->pos, point);
}

