#pragma once
#include <string>
#include <vector>
#include <GameRelated/Resources/Resource.h>
#include <map>



struct CraftInformations
{
	std::vector<Resource> craftCost;
	int numberOfTurns;
	int scoreItGives;
	std::string craftPossessionRequirement;

	CraftInformations() = default;

	CraftInformations(const std::vector<Resource>& _craftCost, const int _numberOfTurns, const int _scoreItGives, const std::string& _craftPossessionRequirements = "")
		: craftCost(_craftCost), numberOfTurns(_numberOfTurns), scoreItGives(_scoreItGives), craftPossessionRequirement(_craftPossessionRequirements)
	{
	}
};

class Recipes
{
	//LIST_OF_RECIPES is Generated using ChatGPT to gain time on a manual task, I don't have time to make a json system or txt read file
public:
	inline static std::map<std::string, CraftInformations> LIST_OF_RECIPES  
	{
		{ "Wooden pickaxe", CraftInformations({ Resource("Wood", 2) }, 1, 10) },

		{ "Wooden axe", CraftInformations({ Resource("Wood", 3) }, 1, 10) },

		{ "Primitive hammer", CraftInformations({ Resource("Wood", 2), Resource("Stone", 1) }, 2, 15) },

		{ "Stone pickaxe", CraftInformations({ Resource("Stone", 3) }, 2, 20) },

		{ "Stone axe", CraftInformations({ Resource("Stone", 4) }, 2, 20) },

		{ "Stone hammer", CraftInformations({ Resource("Stone", 2), Resource("Iron", 1) }, 3, 25, "Primitive hammer") },

		{ "Iron pickaxe", CraftInformations({ Resource("Iron", 3) }, 3, 30) },

		{ "Iron axe", CraftInformations({ Resource("Iron", 4) }, 3, 30) },

		{ "Iron hammer", CraftInformations({ Resource("Iron", 2), Resource("Wood", 1) }, 4, 35, "Stone hammer") },

		{ "Forge", CraftInformations({ Resource("Stone", 5), Resource("Iron", 3) }, 5, 50, "Iron hammer") },
	};

	static bool RecipeExists(const std::string& _name);
};