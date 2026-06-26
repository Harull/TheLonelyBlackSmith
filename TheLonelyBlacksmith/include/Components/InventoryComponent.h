#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <GameRelated/Resources/Resource.h>
#include <GameRelated/Tools/Tool.h>


class InventoryComponent
{
	std::map<std::string,std::unique_ptr<Resource>> resources;
	std::vector<std::unique_ptr<Tool>> tools;

public:
	InventoryComponent();

public: //Resource related
	/// <summary>
	/// Adds a resource to the inventory, creating it if doesnt exist, else adding amount.
	/// </summary>
	void AddResource(const std::string& _name, const int _amount);
	
	/// <summary>
	/// Adds a resources to the inventory, creating resource if doesnt exist, else adding amount.
	/// </summary>
	void AddResources(const std::vector<std::pair<std::string, int>>& _pairNameAmounts);

	/// <summary>
	/// Adds a resources to the inventory, creating resource if doesnt exist, else adding amount.
	/// </summary>
	void AddResources(const std::vector<Resource>& _resources);

	/// <summary>
	/// Removes the resource amount in the resource, doesnt check if has enough resource.
	/// If has 0 or less resource, remove itself from the map of resources
	/// If no resources were found in the resources map, does nothing
	/// </summary>
	void RemoveResource(const std::string& _name, const int _amount);

	/// <summary>
	/// Has the resource in enough quantity ? 
	/// </summary>
	/// <param name="_name">resource name</param>
	/// <param name="_amount">quantity</param>
	/// <param name="_numberOfResourcePossessed">the resource possessed</param>
	/// <returns></returns>
	bool HasResources(const std::string& _name, const int _amount, int& _numberOfResourcePossessed);

	/// <summary>
	///	Try to use the resources, if every resources in parameter are available,
	///	remove all the resources and return true,
	/// else returns false
	/// </summary>
	/// <param name="_pairNameAmount">key of pair is the name of the resource, the value is the amount of the resource </param>
	/// <returns></returns>
	bool TryUseResources(const std::vector<std::pair<std::string, int>>& _pairNameAmounts);

	bool TryUseResources(const std::vector<Resource>& _resources);

	void DisplayInventory();

	void DisplayResources();
	
	void DisplayItems();


public:
	void AddToolToInventory(std::unique_ptr<Tool> _toolToAdd);

	/// <summary>
	/// Check if possess a tool containing this subname, or full name
	/// </summary>
	bool CheckToolPossession(const std::string& _toolSubName);
};

