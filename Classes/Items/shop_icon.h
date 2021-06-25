#pragma once
#include <cocos/cocos2d.h>
#include <string>
#include "shop_icon.h"
#include "../Physics/Box2DBodyComponent.h"
using std::string;

class shop_icon : public cocos2d::Sprite
{
public:
	static shop_icon* create(float, float);
	shop_icon() : Sprite() {}
	~shop_icon() {}
	void update(float delta);
private:
};

