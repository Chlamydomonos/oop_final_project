#pragma once
#include <string>

using std::string;

class ItemStack;
class ItemStackSprite;
class Item
{
protected:
	string Name;
	Item(const char* n) :Name{n} {}
public:
	const char* getName() {
		return Name.c_str();
	}
	friend ItemStack;
	friend ItemStackSprite;
	virtual void Picked() {};
	virtual void Crashed() {};
};

