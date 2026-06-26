#include "VisualRelated/Menu.h"
#include "Utility/Util.h"


Menu::Menu(const std::string& _name, const std::vector<std::pair<std::string, std::function<bool(std::string&)>>>& _menuItems)
{
	name = _name;
	menuItems = _menuItems;
}

void Menu::Display()
{
	Util::PrintTitle(name);
	CustomDisplay();
	PrintAllMenuItems();
}

bool Menu::ExecuteAtIndex(const int _index, std::string& _failContext)
{
	//Try and get the std::function at the index, returns 
	if (_index < 0 || _index >= menuItems.size())
	{
		_failContext = std::string("Index invalid, try a value ranging from ") + " 0 " + " to " + std::to_string(menuItems.size() - 1);
		return false;
	}

	return menuItems[_index].second(_failContext);
}

void Menu::AddMenuItem(const MENU_PAIR_TYPE& _pairToAdd)
{
	menuItems.push_back(_pairToAdd);
}

void Menu::PrintAllMenuItems()
{
	int _count = 1;
	for (auto& _pair : menuItems)
	{
		Util::PrintEmbed(std::to_string(_count) + "|\t" + _pair.first);
		_count++;
	}
}
