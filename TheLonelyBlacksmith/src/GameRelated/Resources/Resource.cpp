#include <GameRelated/Resources/Resource.h>

Resource::Resource(const std::string& _name, const int _currentCount, const int _maxStackCount)
{
	name = _name;
	currentCount = _currentCount > _maxStackCount ? _maxStackCount : _currentCount;
	maxStackCount = _maxStackCount;
}

void Resource::AddResourceAmount(const int _amount)
{
	currentCount = (currentCount + _amount) > maxStackCount ? maxStackCount : (currentCount + _amount);
}

void Resource::SubstractResourceAmount(const int _amount)
{
	currentCount -= _amount;
}