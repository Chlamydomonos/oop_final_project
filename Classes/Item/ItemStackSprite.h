#pragma once
#include <cocos/cocos2d.h>
#include <string>
#include "ItemStack.h"
#include "../Physics/Box2DBodyComponent.h"
using std::string;

class ItemStackSprite: public cocos2d::Sprite
{
public:
	static ItemStackSprite* create(string Name);
	ItemStackSprite() : Sprite(), Object{ nullptr }, BodyComponent{ nullptr }{};
	~ItemStackSprite() {}
	Box2DBodyComponent* GetBodyComponent();
	void BeObtained();

private:
	ItemStack* Object;
	Box2DBodyComponent* BodyComponent;
};

