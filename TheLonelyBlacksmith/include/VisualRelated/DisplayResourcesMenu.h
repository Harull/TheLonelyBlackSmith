#pragma once
#include "VisualRelated/Menu.h"

class DisplayResourcesMenu : public Menu
{
	virtual void CustomDisplay() override;

public:
	DisplayResourcesMenu(const std::string& _name, const std::vector<std::pair<std::string, std::function<bool(std::string&)>>>& _menuItems);
};

