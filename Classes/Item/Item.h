#pragma once
#include <string>

using std::string;

class Item
{
	string Name;
	virtual void Picked() = 0;
	virtual void Crashed() = 0;
};

