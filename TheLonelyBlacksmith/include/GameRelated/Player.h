#pragma once
#include <memory>
#include <Components/InventoryComponent.h>
#include <Builders/PlayerBuilder.h>

class Player
{
	//friend class PlayerBuilder;
	std::unique_ptr<InventoryComponent> inventory;

public:
// private: I'm guessing that we need to force to enter the builder to create players, but couldnt make it so playerbuilder could build it if private
	Player();

public:
	InventoryComponent* GetInventory()const { return inventory.get(); }

	/// <summary>
	/// Allows the player to collect items, adding the collected items to player's inventory
	/// Cost a number of turn to execute this action
	/// </summary>
	/// <param name="_item">Item name to collect</param>
	/// <param name="_quantity">Quantity that the player will receive if this action suceed</param>
	/// <param name="_numberOfTurns">The number of turn it will cost the player</param>
	/// <param name="_failReasons">The reason the action could fail</param>
	/// <param name="_optionalRequirement">If needs a requirement to execute</param>
	bool CollectItem(const std::string& _item, const int _quantity, const int _numberOfTurns, std::string& _failReasons, const bool _optionalRequirement = true);

	/// <summary>
	/// Try to craft the item
	/// If success, use resources for creations
	/// If failed, doesnt use resources
	/// </summary>
	/// <param name="_itemName">item to craft</param>
	/// <param name="_failReasons">reason of why it failed</param>
	/// <returns></returns>
	bool TryAndCraftItem(const std::string& _itemName, std::string& _failReasons);
};

