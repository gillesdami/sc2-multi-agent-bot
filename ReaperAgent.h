#pragma once
#include "MilitaryAgent.h"

class ReaperAgent : public MilitaryAgent
{
public:
	ReaperAgent(const Unit* self, SelfActionInterface* actions, SelfObservationInterface* observations, QueryInterface* query);
	
	void OnStep();
	
	~ReaperAgent();
};

