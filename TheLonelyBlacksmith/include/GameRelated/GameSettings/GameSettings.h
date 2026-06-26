#pragma once

#include <Components/InventoryComponent.h>
#include <vector>

class GameSettings
{
public: //TODO maybe change this public with accessors to values
	inline static int TURN_TOTAL_COUNT = 100;
	
	inline static std::vector<Resource> INITIAL_RESOURCES = {
		Resource("Wood", 2),
		Resource("Stone", 1),
		Resource("Iron", 0)	
	};

};