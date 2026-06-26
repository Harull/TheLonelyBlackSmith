#include "GameRelated/Player.h"
#include "GameRelated/Game.h"
#include "GameRelated/GameSettings/GameSettings.h"

Player::Player()
{
	inventory = std::make_unique<InventoryComponent>();
}

bool Player::CollectItem(const std::string& _item, const int _quantity, const int _numberOfTurns, std::string& _failReasons, const bool _optionalRequirement)
{
	const int _totalCountTurn = Game::GetTotalTurnCount();

	if ((_totalCountTurn + _numberOfTurns) > GameSettings::TURN_TOTAL_COUNT)
	{
		_failReasons = "You don't have enough days left to perform this action";
		return false;
	}
	if (!_optionalRequirement)
	{
		_failReasons = "You don't fill the requirements to perform this action";
		return false;
	}
	if (!inventory)
	{
		_failReasons = "You don't have an inventory";
		return false;
	}
	inventory->AddResource(_item, _quantity);

	Game::IncrementTotalTurnCount(_numberOfTurns);

	return true;
}

bool Player::TryAndCraftItem(const std::string& _itemName, std::string& _failReasons)
{
	if (!Recipes::RecipeExists(_itemName))
	{
		_failReasons = _itemName + " recipe is unknown";
		return false;
	}
	
	const CraftInformations& _craftInformations = Recipes::LIST_OF_RECIPES[_itemName];

	if (Player* _player = Game::GetPlayer())
	{
		if (InventoryComponent* _inventory = _player->GetInventory())
		{
			//From the inventory, check if meet requirements
			if (!_inventory->CheckToolPossession(_craftInformations.craftPossessionRequirement))
			{
				_failReasons = "This item requires you to posses : " + _craftInformations.craftPossessionRequirement;
				return false;
			}

			//From the inventory, check if have resources
			if (!_inventory->TryUseResources(_craftInformations.craftCost))
			{
				_failReasons = "You don't have the resources for that action";
				return false;
			}
			Game::IncrementTotalTurnCount(_craftInformations.numberOfTurns);
			_inventory->AddToolToInventory(std::make_unique<Tool>(Tool(_itemName)));
			return true;
		}
		_failReasons = "Player doesnt have an inventory";
		return false;
	}
	_failReasons = "Player is dead";
	return false;
}

