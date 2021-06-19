#pragma once
#include <cocos/cocos2d.h>
#include <string>
#include "ItemStack.h"
#include "../Physics/Box2DBodyComponent.h"
using std::string;

class ItemStackSprite: public cocos2d::Sprite
{
public:
	static ItemStackSprite* create(Item*, int, float x = 8.0f, float y = 8.0f);
	ItemStackSprite() : Sprite(), Object{ nullptr }, BodyComponent{ nullptr }{};
	~ItemStackSprite() {}
	Box2DBodyComponent* GetBodyComponent();
	void BeObtained();
	virtual void update(float delta);

	const char* getName() {
		return Object->Type->Name.c_str();
	}

	int getCount() {
		return Object->getCount();
	}

	ItemStack getItemStack() {
		return *Object;
	}
private:
	ItemStack* Object;
	Box2DBodyComponent* BodyComponent;
};

