#pragma once

#include <cocos/cocos2d.h>
#include <../Classes/Physics/Box2DBodyComponent.h> 

class Player: public cocos2d::Sprite
{
public:
	const float horizontal_velocity{ 2.0 };// the horizontal velocity (positive)
	const float vertical_force{ 20.0 };
	virtual bool init();
	CREATE_FUNC(Player);
	~Player() {}
	Box2DBodyComponent* GetBC() { return BC; }
private:
	Box2DBodyComponent* BC;
};

