#include "Recipes.h"


bool Recipes::RecipeExists(const std::string& _name)
{
	const std::map<std::string, CraftInformations>& _map = Recipes::LIST_OF_RECIPES;

	return (_map.find(_name) != _map.end());
}
