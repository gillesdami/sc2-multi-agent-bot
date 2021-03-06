#include <sc2api/sc2_api.h>
#include <iostream>

#include "Bot.h"

using namespace sc2;

int main(int argc, char* argv[]) {
	Coordinator coordinator;
	if (!coordinator.LoadSettings(argc, argv)) {
		return 1;
	}

	Bot bot;
	coordinator.SetParticipants({
		CreateParticipant(Race::Terran, &bot),
		CreateComputer(Race::Random)
		});

	coordinator.LaunchStarcraft();
	coordinator.StartGame("../maps/Ladder/(2)Bel'ShirVestigeLE (Void).SC2Map");

	while (coordinator.Update()) {
	}

	return 0;
}