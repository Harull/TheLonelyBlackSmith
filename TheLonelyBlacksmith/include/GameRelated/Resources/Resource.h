#pragma once
#include <string>

struct Resource //so here i typically could use a builder I'm guessing
{
private:
	std::string name;
	int currentCount;
	int maxStackCount;

public:
	Resource() = default;
	Resource(const std::string& _name, const int _currentCount, const int _maxStackCount = 64);
public:
	__forceinline std::string GetName() const { return name; }
	__forceinline int GetCurrentCount() const { return currentCount; }
	__forceinline int GetMaxStackCount() const { return maxStackCount; }

public:
	//Adds the resource, but clamped
	void AddResourceAmount(const int _amount);
	void SubstractResourceAmount(const int _amount);
};