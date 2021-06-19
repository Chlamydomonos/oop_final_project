#include "ItemStackSprite.h"
#include "../Player/Player.h"


ItemStackSprite* ItemStackSprite::create(Item* Type, int Count, float x, float y) {
	ItemStackSprite* spr = new (std::nothrow) ItemStackSprite();

    spr->Object = new ItemStack;
    spr->Object->Type = Type;
    spr->Object->Count = Count;

    if (spr && spr->initWithFile(string(Type->getName())+".png"))
    {
        spr->autorelease();

        b2BodyDef BodyDef;
        BodyDef.type = b2_dynamicBody;
        BodyDef.position.Set(x, y);

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
    setTag(DEL_TAG);
}

void ItemStackSprite::update(float delta) {
    Sprite::update(delta);
}