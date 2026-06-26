#include "Builders/PlayerBuilder.h"
#include <Utility/Util.h>
#include <GameRelated/GameSettings/GameSettings.h>

PlayerBuilder::PlayerBuilder()
{
	player = std::make_unique<Player>();
}

PlayerBuilder& PlayerBuilder::InitializeResourcesFromSettings()
{
	if (!player)
	{
		Util::Debug("PlayerBuilder::InitializeResourcesFromSettings Player is null");
		return *this;
	}

	InventoryComponent* _playersInventory = player->GetInventory();
	if (!_playersInventory) return *this;
	_playersInventory->AddResources(GameSettings::INITIAL_RESOURCES);
	return *this;
}

std::unique_ptr<Player> PlayerBuilder::Build()
{
    return std::move(player);
}

