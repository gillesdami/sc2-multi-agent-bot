#pragma once

#include <sc2api\sc2_common.h>
#include <iostream>

using namespace sc2;

struct BotStrategy {
	double aggressivity;
	double developpement;

	int enemyMilitarySupply;

	int mineralsAllocated;
	int vespeneAllocated;

	Point2D** militarySupportRequested;
	Point2D** militaryObjectives;
};