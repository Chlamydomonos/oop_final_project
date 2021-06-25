#pragma once
#include <string>
#include <map>

class ItemStack;
class ItemStackSprite;
class Item
{
protected:
	std::string Name;
public:
	Item(const std::string &n) :Name{ n } { ALL_ITEMS[n] = this; }
	static std::map<std::string, Item *> ALL_ITEMS;
	const char* getName() {
		return Name.c_str();
	}
	friend ItemStack;
	friend ItemStackSprite;
	virtual void Picked() {};
	virtual void Crashed() {};
};

