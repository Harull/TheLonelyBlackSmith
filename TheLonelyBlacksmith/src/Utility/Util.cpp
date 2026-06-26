#include "Utility/Util.h"
#include <iostream>
#include <algorithm>

#define WITH_DEBUG true


void Util::Clear()
{
	system("cls");
}

void Util::Continue(const bool _withClear)
{
	std::cout << CYAN;
	system("pause");
	if (_withClear) Clear();
	std::cout << WHITE;
}

void Util::PrintTitle(const std::string& _toPrint, const std::string& _color, const bool _withLineBreak)
{
	std::cout << _color;
	std::cout << "\t=| " << _toPrint << " |=";
	if (_withLineBreak) std::cout << std::endl;
	std::cout << WHITE;
}

void Util::PrintEmbed(const std::string& _toPrint, const std::string& _color, const bool _withLineBreak)
{
	std::cout << _color;
	std::cout << "- " << _toPrint << " -" ;
	if (_withLineBreak) std::cout << std::endl;
	std::cout << WHITE;
}

void Util::Separation()
{
	std::cout << "===========================================" << std::endl;
}

//Yes could have made method that regroup both methods below
void Util::Debug(const std::string& _toPrint, const bool _withLineBreak)
{
	#if WITH_DEBUG
		std::cout << YELLOW << _toPrint << WHITE;
		if (_withLineBreak) std::cout << std::endl;
	#endif
}

void Util::Error(const std::string& _toPrint, const bool _withLineBreak)
{
	#if WITH_DEBUG
		std::cout << RED << _toPrint << WHITE;
		if (_withLineBreak) std::cout << std::endl;
	#endif

}

bool Util::Contains(const std::string& _string, const std::string& _contains, const bool _respectCase)
{
	if (_respectCase) return (_string.find(_contains) != std::string::npos);

	std::string _loweredString = ToLower(_string);
	std::string _loweredContains = ToLower(_contains);
	return (_loweredString.find(_loweredContains) != std::string::npos);
}

std::string Util::ToLower(const std::string& _string) //https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
{
	std::string _toReturn = _string;
	std::transform(_toReturn.begin(), _toReturn.end(), _toReturn.begin(),
		[](unsigned char _c) { return std::tolower(_c); });
	return _toReturn;
}
