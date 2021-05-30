#pragma once

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Classes/Player/Player.h"
#include "../Classes/Player/PlayerContact.h"


class PlayerCollection :
    public cocos2d::Scene
{
public:
	bool init();
	~PlayerCollection() { };
	CREATE_FUNC(PlayerCollection);
	virtual void update(float delta);
private:
	Player* Person;
	cocos2d::Sprite* Ground;

};

