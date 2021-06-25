#pragma once

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Classes/Player/Player.h"
#include "../Classes/Player/PlayerContact.h"


class Shop :
    public cocos2d::Scene
{
public:
	bool init();
	~Shop() { };
	CREATE_FUNC(Shop);
	virtual void update(float delta);
	const char* Font = "Arial";
private:
	Player* Person;
	bool PurchaseCheck(int);
	void HorizontalSpeedIncrease(float);
	void VerticalSpeedIncrease(float);
	cocos2d::Label* moneyLabel;
	bool moneyModified{ false };
	void SellEverything();

};

