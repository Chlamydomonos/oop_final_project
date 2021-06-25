#include "shop_icon.h"
#include "../Player/Player.h"
#include "../Player/PlayerController.h"
#include "../Utils/VectorConversion.h"
USING_NS_CC;

shop_icon* shop_icon::create(float physical_x, float physical_y) {
    shop_icon* spr = new (std::nothrow) shop_icon();
    if (spr && spr->initWithFile("shop.jpg"))
    {
        spr->autorelease();

        spr->setAnchorPoint(Vec2(0.5, 0.5));
        spr->setScaleX(64/ spr->getContentSize().width);
        spr->setScaleY(64 / spr->getContentSize().height);
        spr->setPosition(p2r(b2Vec2(physical_x,physical_y)));

        spr->setTag(SHOP_ICON_TAG);
        spr->scheduleUpdate();

        return spr;
    }
    CC_SAFE_DELETE(spr);
    return nullptr;
    
}

void shop_icon::update(float delta) {
    if (this->getPosition().distance(Player::GetInstance()->getPosition()) < 64.0) {
        if(!Player::GetInstance()->just_out_of_shop)
            PlayerController::ReadyToGoToShop();
    }

    if (this->getPosition().distance(Player::GetInstance()->getPosition()) > 64.0) {
        Player::GetInstance()->just_out_of_shop = false;
    }

}