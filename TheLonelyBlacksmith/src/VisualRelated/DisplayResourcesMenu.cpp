#include "VisualRelated/DisplayResourcesMenu.h"
#include <Utility/Util.h>
#include <GameRelated/Game.h>

void DisplayResourcesMenu::CustomDisplay()
{
	if (Player* _player = Game::GetPlayer())
		if (InventoryComponent* _inventory = _player->GetInventory())
			_inventory->DisplayInventory();
}

DisplayResourcesMenu::DisplayResourcesMenu(const std::string& _name, const std::vector<std::pair<std::string, std::function<bool(std::string&)>>>& _menuItems)
	: Menu(_name, _menuItems)
{
}

