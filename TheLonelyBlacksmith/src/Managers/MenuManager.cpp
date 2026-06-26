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
				return true; //Let's say ChangeCurrentMenu actions can't fail
			}
		},
		{"Open Inventory", [&](std::string& _failContext)
			{
				ChangeCurrentMenu(displayResourcesMenu);
				return true; //Let's say ChangeCurrentMenu actions can't fail
			}
		},
		{"Close Game", [&](std::string& _failContext)
			{
				Game::Terminate("User requested to terminate the game");
				return true; //Let's say this action can't fail
			}
		},
		}));
}

void MenuManager::internalInitCollectResourcesMenu()
{
	collectResourceMenu = std::make_shared<Menu>(Menu("Collected Items", {
		{"Collect Wood", [&](std::string& _failContext)
			{
				const int _collectableQuantity = 1; //TODO Temp to replace when class tool is implemented, in the end i don't have time anymore for this :c
				return Game::GetPlayer()->CollectItem("Wood", 1, 1, _failContext);
			}
		},
		{"Collect Stone", [&](std::string& _failContext)
			{
				const int _collectableQuantity = 1; //Temp to replace when class tool is implemented
				return Game::GetPlayer()->CollectItem("Stone", 1, 1, _failContext);
			}
		},
		{"Collect Iron - Require Pickaxe", [&](std::string& _failContext)
			{
				const int _collectableQuantity = 1; //Temp to replace when class tool is implemented
				const bool _requirements = Game::GetPlayer()->GetInventory()->CheckToolPossession("Pickaxe");
				return Game::GetPlayer()->CollectItem("Iron", 1, 1, _failContext, _requirements);
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
		std::string _fullItemDisplay = _pair.first + "\t";

		//Add the cost to the full item display
		for (auto& _resource : _pair.second.craftCost)
			_fullItemDisplay += " -" + _resource.GetName() + "(" + std::to_string(_resource.GetCurrentCount()) + ')';


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
