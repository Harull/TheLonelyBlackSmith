#pragma once
#include <memory>
#include <GameRelated/Resources/Resource.h>
#include <vector>
#include <GameRelated/GameSettings/Recipes/Recipes.h>

enum ToolType
{
	None,
	ToolType_Pickaxe,
	ToolType_Hammer,
	ToolType_Axe,
	Misc
};

class Tool //typically for this class a builder could be good I'm guessing
{
	std::string name;
	CraftInformations craftInformations;
	ToolType type;

public:
	Tool() = default;
	Tool(const std::string& _name);

public:
	__forceinline std::string& GetName() { return name; }
	__forceinline CraftInformations& GetCraftInformations() { return craftInformations; }

private:
	void InitToolType();
};

