#include "SelfActionInterface.h"


SelfActionInterface::SelfActionInterface(const Unit* self, ActionInterface* actions)
{
	this->self = self;
	this->actions = actions;
}

void SelfActionInterface::Command(AbilityID ability, bool queued_command)
{
	this->actions->UnitCommand(this->self, ability, queued_command);
}

void SelfActionInterface::Command(AbilityID ability, const Point2D & point, bool queued_command)
{
	this->actions->UnitCommand(this->self, ability, point, queued_command);
}

void SelfActionInterface::Command(AbilityID ability, const Unit * target, bool queued_command)
{
	this->actions->UnitCommand(this->self, ability, target, queued_command);
}

void SelfActionInterface::SendActions()
{
	this->actions->SendActions();
}

SelfActionInterface::~SelfActionInterface()
{
}
