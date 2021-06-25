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
	cocos2d::Label* moneyLabel{ nullptr };
	bool moneyModified{ true };
	void SellEverything();
	
template <class func>
void ShoppingItemCreate(cocos2d::Vector <cocos2d::MenuItem*>& Menuitems, std::string name, int price, func f) {
	auto t = MenuItemLabel::create(
		Label::createWithSystemFont(name + (price > 0 ? "  [PRICE " + std::to_string(price)+"]" : ""), Font, 30),
		[=,this](Ref* sender) {
			if (PurchaseCheck(price)) f();
		});
	Menuitems.pushBack(t);
}

};

