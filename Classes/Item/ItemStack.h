#pragma once

#include "Item.h"

class ItemStackSprite;

class ItemStack
{
	Item* Type;
	int Count;

public:

	int getCount() {
		return Count;
	}
	int increaseCount(int increment) {
		Count += increment;
	}

	friend ItemStackSprite;
};

