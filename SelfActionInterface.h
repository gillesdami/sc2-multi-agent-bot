#pragma once

#include <sc2api\sc2_interfaces.h>

using namespace sc2;

class SelfActionInterface
{
public:
	SelfActionInterface(const Unit* self, ActionInterface* actions);

	void Command(AbilityID ability, bool queued_command = false);
	void Command(AbilityID ability, const Point2D &point, bool queued_command = false);
	void Command(AbilityID ability, const Unit *target, bool queued_command = false);
	void SendActions();

	~SelfActionInterface();

private:
	const Unit* self;
	ActionInterface* actions;
};

