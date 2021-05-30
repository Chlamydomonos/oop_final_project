#include "ItemStackSprite.h"
#include "../Player/Player.h"

ItemStackSprite* ItemStackSprite::create(string Name) {
	ItemStackSprite* spr = new (std::nothrow) ItemStackSprite();

    if (spr && spr->initWithFile(Name+".png"))
    {
        spr->autorelease();

        b2BodyDef BodyDef;
        BodyDef.type = b2_dynamicBody;
        BodyDef.position.Set(8.0f, 8.0f);

        b2PolygonShape Box;
        Box.SetAsBox(0.25f, 0.25f);

        b2FixtureDef FixtureDef;
        FixtureDef.shape = &Box;
        FixtureDef.density = 1.0f;
        FixtureDef.friction = 0.3f;

        spr->BodyComponent = Box2DBodyComponent::create(&BodyDef, &FixtureDef);


        spr->addComponent(spr->BodyComponent);

        auto w = spr->getContentSize().width;
        auto h = spr->getContentSize().height;
        spr->setScaleX(32 / w);
        spr->setScaleY(32 / h);

        spr->setTag(ITEM_TAG); 

        return spr;
    }
    CC_SAFE_DELETE(spr);
    return nullptr;
}

Box2DBodyComponent* ItemStackSprite::GetBodyComponent() {
    return BodyComponent;
}

void ItemStackSprite::BeObtained() {
    CCLOG("OBJECT BE OBTAINED!");
}