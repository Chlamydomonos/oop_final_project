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
	bool newly_disabled{ true };
	void create_menu();
	cocos2d::Menu* menu{ nullptr };

template <class func, class is_max> 
void ShoppingItemCreate(cocos2d::Vector <cocos2d::MenuItem*>& Menuitems, std::string name, int price, func f,is_max c) {
	std::string text{ name };
	if (c()) {
		text += " [SOLD OUT]";
		price = 0x7fffffff;
	}else if (price > 0) {
		text += "  [$";
		text += std::to_string(price);
		text += "]";
	}

	auto t = cocos2d::MenuItemLabel::create(
		Label::createWithSystemFont(text, Font, 30),
		[=,this](Ref* sender) {
			if (PurchaseCheck(price)) {
				f();
				if (c()) {
					this->newly_disabled = true;
				}
			}
		});
	
	Menuitems.pushBack(t);
}


};

