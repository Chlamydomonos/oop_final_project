#pragma once
#include <string>
#include <map>

class ItemStack;
class ItemStackSprite;
class Item
{
protected:
	std::string Name;
	int value;
public:
	Item(const std::string &n, int _value) :Name{ n }, value{ _value } { ALL_ITEMS[n] = this; }
	static std::map<std::string, Item *> ALL_ITEMS;
	const char* getName() {
		return Name.c_str();
	}
	friend ItemStack;
	friend ItemStackSprite;
	virtual void Picked() {};
	virtual void Crashed() {};
	int getValue() { return value; }
};

