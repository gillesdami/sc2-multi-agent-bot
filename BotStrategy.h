#pragma once

#include <sc2api\sc2_common.h>
#include <iostream>

using namespace sc2;

struct BotStrategy {
	int enemyMilitarySupply;

	std::vector<ABILITY_ID> publicOrdersThisStep;

	std::map<Tag, Point2D> objectives;

	std::vector<Point3D> expansionLocations;
};