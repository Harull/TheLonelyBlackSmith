#pragma once
#include <memory>
#include "GameRelated/Player.h"

class Player;

class PlayerBuilder
{
	std::unique_ptr<Player> player;

public:
	PlayerBuilder();

public:
	PlayerBuilder& InitializeResourcesFromSettings();

	std::unique_ptr<Player> Build();

};

