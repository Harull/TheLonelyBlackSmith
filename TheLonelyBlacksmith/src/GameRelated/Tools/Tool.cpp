#include "GameRelated/Tools/Tool.h"
#include "GameRelated/GameSettings/Recipes/Recipes.h"
#include <Utility/Util.h>

Tool::Tool(const std::string& _name)
{
	name = _name;
	craftInformations = Recipes::LIST_OF_RECIPES[name];
	InitToolType();
}

void Tool::InitToolType()
{
	//TODO change logic if have time to string ToolType and remove the prefix maybe ? 
	if (Util::Contains(name, "Pickaxe"))
		type = ToolType_Pickaxe;
	else if (Util::Contains(name, "Hammer"))
		type = ToolType_Pickaxe;
	else if (Util::Contains(name, "Axe"))
		type = ToolType_Pickaxe;
	type = Misc;
}
