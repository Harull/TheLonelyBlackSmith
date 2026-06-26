#include "Components/InventoryComponent.h"
#include <Utility/Util.h>
#include <GameRelated/Game.h>



InventoryComponent::InventoryComponent()
{

}

void InventoryComponent::AddResource(const std::string& _name, const int _amount)
{
	//If we don't find the resource, we create it
	if (resources.find(_name) == resources.end())
	{
		Util::Debug("Creating new resource named " + _name);

		resources.emplace(_name, std::make_unique<Resource>(_name, _amount));
		return;
	}
	//Add resource to existing resource;
	resources[_name]->AddResourceAmount(_amount);
}

void InventoryComponent::AddResources(const std::vector<std::pair<std::string, int>>& _pairNameAmounts)
{
	for (auto& _pair : _pairNameAmounts)
		AddResource(_pair.first, _pair.second);
}

void InventoryComponent::AddResources(const std::vector<Resource>& _resources)
{
	for (auto& _resource : _resources)
		AddResource(_resource.GetName(), _resource.GetCurrentCount());
}


void InventoryComponent::RemoveResource(const std::string& _name, const int _amount)
{
	//If we found the resource we would like to remove from
	if (resources.find(_name) != resources.end())
	{
		Util::Debug("Removing " + std::to_string(_amount) + " resources for " + _name);
		resources[_name]->SubstractResourceAmount(_amount);

		if(resources[_name]->GetCurrentCount() <= 0)
			resources.erase(_name);
	}
}

bool InventoryComponent::HasResources(const std::string& _name, const int _amount, int& _numberOfRessourcePossessed)
{
	_numberOfRessourcePossessed = 0;

	//If there is no ressources of this name
	if (resources.find(_name) == resources.end())
		return false;

	_numberOfRessourcePossessed = resources[_name]->GetCurrentCount();
	return _numberOfRessourcePossessed >= _amount;
}

bool InventoryComponent::TryUseResources(const std::vector<std::pair<std::string, int>>& _pairNameAmounts)
{
	//See if has all the ressources here
	for (auto& _pair : _pairNameAmounts)
	{
		int _trueAmountPossessed = 0;
		const bool _hasResources = HasResources(_pair.first, _pair.second, _trueAmountPossessed);

		if (!_hasResources)
		{
			Util::Debug("You don't have this ressource, you have " + std::to_string(_trueAmountPossessed) + " " + _pair.first);
			return false;
		}
	}

	//Removes the resources 
	for (auto& _pair : _pairNameAmounts)
		resources[_pair.first]->SubstractResourceAmount(_pair.second);

	return true;
}

bool InventoryComponent::TryUseResources(const std::vector<Resource>& _resources)
{
	//See if has all the ressources here
	for (auto& _resource : _resources)
	{
		int _trueAmountPossessed = 0;
		const bool _hasResources = HasResources(_resource.GetName(), _resource.GetCurrentCount(), _trueAmountPossessed);

		if (!_hasResources)
		{
			Util::Debug("You don't have enough of " + _resource.GetName() + ", you have " + std::to_string(_trueAmountPossessed));
			return false;
		}
	}

	//Removes the resources 
	for (auto& _resource : _resources)
		resources[_resource.GetName()]->SubstractResourceAmount(_resource.GetCurrentCount());

	return true;
}


void InventoryComponent::DisplayInventory()
{
	DisplayResources();
	DisplayItems();
}

void InventoryComponent::DisplayResources()
{
	if (resources.size() <= 0)
		Util::PrintEmbed("You have no items in your inventory");

	for (auto& _pair : resources)
	{
		if (_pair.second)
			Util::PrintEmbed(_pair.second->GetName() + " : " + std::to_string(_pair.second->GetCurrentCount()));
	}
}

void InventoryComponent::DisplayItems()
{
	if (tools.size() <= 0)
		Util::PrintEmbed("You have no tools in your inventory");

	for (auto& _tool : tools)
		Util::PrintEmbed(_tool->GetName());
}

void InventoryComponent::AddToolToInventory(std::unique_ptr<Tool> _toolToAdd)
{
	if (_toolToAdd)
		Game::IncrementTotalScore(_toolToAdd->GetCraftInformations().scoreItGives);

	tools.emplace_back(std::move(_toolToAdd));
}

bool InventoryComponent::CheckToolPossession(const std::string& _toolSubName)
{
	const size_t _size = tools.size();
	for (size_t _i = 0; _i < _size; _i++)
	{
		Tool* _tool = tools[_i].get();
		if (!_tool)continue;
		if (Util::Contains(_tool->GetName(), _toolSubName))
			return true;
	}
	return false;
}

