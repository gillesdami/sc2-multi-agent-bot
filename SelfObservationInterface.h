#pragma once

#include <sc2api\sc2_interfaces.h>
#include "BotStrategy.h"

using namespace sc2;

class SelfObservationInterface
{
public:
	SelfObservationInterface(const Unit* self,const ObservationInterface* observations, BotStrategy* strategy);
	~SelfObservationInterface();

	uint32_t GetPlayerID() const;
	uint32_t SelfObservationInterface::GetGameLoop() const;
	Units SelfObservationInterface::GetUnits() const;
	Units SelfObservationInterface::GetUnits(Unit::Alliance alliance, Filter filter = {}) const;
	Units SelfObservationInterface::GetUnits(Filter filter) const;
	const Unit * SelfObservationInterface::GetUnit(Tag tag) const;
	const RawActions & SelfObservationInterface::GetRawActions() const;
	const SpatialActions & SelfObservationInterface::GetFeatureLayerActions() const;
	const SpatialActions & SelfObservationInterface::GetRenderedActions() const;
	const std::vector< ChatMessage > & SelfObservationInterface::GetChatMessages() const;
	const std::vector< PowerSource > & SelfObservationInterface::GetPowerSources() const;
	const std::vector< Effect > & SelfObservationInterface::GetEffects() const;
	const std::vector< UpgradeID > & SelfObservationInterface::GetUpgrades() const;
	const Score & SelfObservationInterface::GetScore() const;
	const Abilities & SelfObservationInterface::GetAbilityData(bool force_refresh = false) const;
	const UnitTypes & SelfObservationInterface::GetUnitTypeData(bool force_refresh = false) const;
	const Upgrades & SelfObservationInterface::GetUpgradeData(bool force_refresh = false) const;
	const Buffs & SelfObservationInterface::GetBuffData(bool force_refresh = false) const;
	const Effects & SelfObservationInterface::GetEffectData(bool force_refresh = false) const;
	const GameInfo & SelfObservationInterface::GetGameInfo() const;
	int32_t SelfObservationInterface::GetMinerals() const;
	int32_t SelfObservationInterface::GetVespene() const;
	int32_t SelfObservationInterface::GetFoodCap() const;
	int32_t SelfObservationInterface::GetFoodUsed() const;
	int32_t SelfObservationInterface::GetFoodArmy() const;
	int32_t SelfObservationInterface::GetFoodWorkers() const;
	int32_t SelfObservationInterface::GetIdleWorkerCount() const;
	int32_t SelfObservationInterface::GetArmyCount() const;
	int32_t SelfObservationInterface::GetWarpGateCount() const;
	Point2D SelfObservationInterface::GetCameraPos() const;
	Point3D SelfObservationInterface::GetStartLocation() const;
	const std::vector< PlayerResult > & SelfObservationInterface::GetResults() const;
	bool SelfObservationInterface::HasCreep(const Point2D &point) const;
	Visibility SelfObservationInterface::GetVisibility(const Point2D &point) const;
	bool SelfObservationInterface::IsPathable(const Point2D &point) const;
	bool SelfObservationInterface::IsPlacable(const Point2D &point) const;
	float SelfObservationInterface::TerrainHeight(const Point2D &point) const;

	BotStrategy* strategy;
private:
	const Unit* self;
	const ObservationInterface* observations;
};

