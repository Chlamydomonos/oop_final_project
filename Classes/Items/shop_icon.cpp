#include "shop_icon.h"
#include "../Player/Player.h"



Box2DBodyComponent* shop_icon::GetBodyComponent() {
    return BodyComponent;
}

shop_icon* shop_icon::create() {
    shop_icon* spr = new (std::nothrow) shop_icon();
    if (spr && spr->initWithFile("shop.jpg"))
    {
        spr->autorelease();

        b2BodyDef BodyDef;
        BodyDef.position.Set(12.0, 11.0);
        b2PolygonShape Box;
        Box.SetAsBox(0.5f, 0.5f);
        b2FixtureDef FixtureDef;
        FixtureDef.shape = &Box;
        spr->BodyComponent = Box2DBodyComponent::create(&BodyDef, &FixtureDef);


        spr->addComponent(spr->BodyComponent);

        auto w = spr->getContentSize().width;
        auto h = spr->getContentSize().height;
        spr->setScaleX(64 / w);
        spr->setScaleY(64 / h);

        spr->setTag(SHOP_ICON_TAG);

        return spr;
    }
    CC_SAFE_DELETE(spr);
    return nullptr;
    
}