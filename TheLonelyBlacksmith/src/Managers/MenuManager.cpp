#include <Managers/MenuManager.h>
#include <Utility/Util.h>
#include "GameRelated/Game.h"
#include "VisualRelated/DisplayResourcesMenu.h"

void MenuManager::internalInitMenus()
{
	internalInitMainMenu();
	internalInitCollectResourcesMenu();
	internalInitObjectCreationMenu();
	internalInitDisplayResourceMenu();

	//Init currentMenu
	currentMenu = mainMenu;
}

void MenuManager::internalInitMainMenu()
{
	mainMenu = std::make_shared<Menu>(Menu("Main Menu", {
		{"Collect Resources", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(collectResourceMenu);
				return true; //Let's say ChangeCurrentMenu actions can't fail
			}
		},
		{"Craft An Item", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(objectCreationMenu);
				return true; 
			}
		},
		{"Open Inventory", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(displayResourcesMenu);
				return true; 
			}
		},
		{"Close Game", [&](std::string& _failContext)
			{
				Game::Terminate("User requested to terminate the game");
				return true;
			}
		},
		}));
}

void MenuManager::internalInitCollectResourcesMenu()
{
	collectResourceMenu = std::make_shared<Menu>(Menu("Collect Resources", {
		{"Collect Wood", [&](std::string& _failContext)
			{
				return CollectRessource(_failContext, "Wood");
			}
		},
		{"Collect Stone", [&](std::string& _failContext)
			{
				return CollectRessource(_failContext, "Stone");
			}
		},
		{"Collect Iron - Require Pickaxe", [&](std::string& _failContext)
			{
				return CollectRessource(_failContext, "Iron", Game::GetPlayer()->GetInventory()->CheckToolPossession("Pickaxe"));
			}
		},
		{"{Back}", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(mainMenu);
				return true; //Let's say this action can't fail
			}
		},
		}));
}

void MenuManager::internalInitObjectCreationMenu()
{
	objectCreationMenu = std::make_shared<Menu>(Menu("Crafting Place", {}));
	const std::map<std::string, CraftInformations>& _recipesToAdd = Recipes::LIST_OF_RECIPES;

	//Loops through the recipes, and add them to the array
	for (auto& _pair : _recipesToAdd)
	{
		//Gets informations displayed (name, cost, requirements)
		std::string _fullItemDisplay = _pair.first + " ] [";

		//Add the cost to the full item display
		for (auto& _resource : _pair.second.craftCost)
			_fullItemDisplay += " -" + _resource.GetName() + "(" + std::to_string(_resource.GetCurrentCount()) + ')';
		_fullItemDisplay += " -" + std::to_string(_pair.second.numberOfTurns) + " days ]";

		//Add the number of score it gives
		_fullItemDisplay += " [ +" + std::to_string(_pair.second.scoreItGives) + " score points ]";
		 
		//Add the requirement to the craft
		if(_pair.second.craftPossessionRequirement.size() > 0)
			_fullItemDisplay += std::string("\n\t[ ") + BRIGHT_RED + "Require: " + _pair.second.craftPossessionRequirement + WHITE;

		objectCreationMenu->AddMenuItem({ _fullItemDisplay, [&](std::string& _failContext) {

			return Game::GetPlayer()->TryAndCraftItem(_pair.first, _failContext);
		}
		});
	}

	// finally, add the {back} option at the end
	objectCreationMenu->AddMenuItem({ "{Back}", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(mainMenu);
				return true; //Let's say this action can't fail
			}
		});
}

void MenuManager::internalInitDisplayResourceMenu()
{
	displayResourcesMenu = std::make_shared<DisplayResourcesMenu>(DisplayResourcesMenu("Inventory", {
		{"{Back}", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(mainMenu);
				return true; //Let's say this action can't fail
			}
		},
		}));
}

void MenuManager::ChangeCurrentMenu(std::shared_ptr<Menu> _menuToChangeTo)
{
	if (!_menuToChangeTo)return;
	Util::Debug("Changed the current menu to: " + _menuToChangeTo->GetName());
	currentMenu = _menuToChangeTo;
}

bool MenuManager::CollectRessource(std::string& _failContext, const std::string& _resourceName, const bool _requirement)
{
	//Retrieve the biggest advantage available for this resource
	const std::pair<uint8_t, uint8_t> _advantageMinMax = Game::GetPlayer()->GetInventory()->GetBiggestToolAdvantage(_resourceName);
	//Extract a random quantity from it
	const int _collectableQuantity = Util::Randint(_advantageMinMax.first, _advantageMinMax.second);
	//Collects the item, and returning success
	return Game::GetPlayer()->CollectItem(_resourceName, _collectableQuantity, 1, _failContext, _requirement);
}
