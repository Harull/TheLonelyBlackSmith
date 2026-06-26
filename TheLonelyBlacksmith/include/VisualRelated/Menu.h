#pragma once
#include <functional>
#include <vector>
#include <string>
 
#define MENU_PAIR_TYPE std::pair<std::string, std::function<bool(std::string&)>>
#define MENU_VECTOR_TYPE std::vector<MENU_PAIR_TYPE>

class Menu 
{
protected:
	//String is the name of the menu, function is the function to execute when menu index is selected
	// std::function<bool(std::string& ) string is the fail context, bool is the success return value
	MENU_VECTOR_TYPE menuItems;

	std::string name;

public:
	Menu(const std::string& _name, const std::vector<std::pair<std::string, std::function<bool(std::string&)>>>& _menuItems);

public:
	__forceinline std::string GetName()const { return name; }

public:
	/// <summary>
	/// Displays the menu
	/// </summary>
	void Display();

	/// <summary>
	/// Execute my std::function at the index of this map
	/// </summary>
	/// <param name="_index">index to execute menu's function from</param>
	/// <param name="_failContext">Context will fill if returning false</param>
	/// <returns>bSuccess</returns>
	bool ExecuteAtIndex(const int _index, std::string& _failContext);

	/// <summary>
	/// Adds an item to the menu of items
	/// </summary>
	void AddMenuItem(const MENU_PAIR_TYPE& _pairToAdd);

private:
	void PrintAllMenuItems();

protected:
	virtual void CustomDisplay() {};
};

