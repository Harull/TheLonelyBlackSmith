#pragma once
#include <memory>
#include <string>
#include "VisualRelated/Menu.h"

class MenuManager
{
	static MenuManager& GetInstance()
	{
		static MenuManager _instance;
		return _instance;
	}

private:
	//Current menu displayed
	std::shared_ptr<Menu> currentMenu;

	//All menus
	std::shared_ptr<Menu> mainMenu;
	std::shared_ptr<Menu> collectResourceMenu;
	std::shared_ptr<Menu> objectCreationMenu;
	std::shared_ptr<Menu> displayResourcesMenu;


private:
	MenuManager() = default;

public:
	MenuManager(const MenuManager& _game) = delete;

	void operator=(const MenuManager& _other) = delete;

public:
	__forceinline static void InitMenus() {
		GetInstance().internalInitMenus();
	}

	__forceinline static Menu* GetCurrentMenu() {
		return GetInstance().currentMenu.get();
	}

	__forceinline static void DisplayCurrentMenu() {
		Menu* _currentMenu = GetCurrentMenu();
		if (!_currentMenu)return;
		_currentMenu->Display();
	}

	__forceinline static bool ExecuteMenuAtIndex(const int _index, std::string& _failContext) {
		Menu* _currentMenu = GetCurrentMenu();
		_failContext = std::string("There is no current menu to select an action from ! ");
		if (!_currentMenu)return false;
		return _currentMenu->ExecuteAtIndex(_index, _failContext);
	}

private: // coudl be called outside this class
	//Maybe could have called this in the constructor of MenuManager, but decided to call it manually
	void internalInitMenus();

	void internalInitMainMenu();
	void internalInitCollectResourcesMenu();
	void internalInitObjectCreationMenu();
	void internalInitDisplayResourceMenu();


private:
	void ChangeCurrentMenu(std::shared_ptr<Menu> _menuToChangeTo);
	bool CollectRessource(std::string& _failContext, const std::string& _resourceName, const bool _requirement = true);
};

