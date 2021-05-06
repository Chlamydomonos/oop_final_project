#include "ItemStackSprite.h"

ItemStackSprite* ItemStackSprite::create(string Name) {
	ItemStackSprite* spr = new (std::nothrow) ItemStackSprite();

    if (spr && spr->initWithFile(Name+".png"))
    {
        spr->autorelease();

        b2BodyDef BodyDef;
        BodyDef.type = b2_dynamicBody;
        BodyDef.position.Set(8.0f, 8.0f);
        BodyDef.angularVelocity = 0.1f;

        b2PolygonShape Box;
        Box.SetAsBox(0.5f, 0.5f);

        b2FixtureDef FixtureDef;
        FixtureDef.shape = &Box;
        FixtureDef.density = 1.0f;
        FixtureDef.friction = 0.3f;
        FixtureDef.restitution = 0.8f;

        spr->BodyComponent = Box2DBodyComponent::create(&BodyDef, &FixtureDef);
        spr->addComponent(spr->BodyComponent);

        return spr;
    }
    CC_SAFE_DELETE(spr);
    return nullptr;
}

Box2DBodyComponent* ItemStackSprite::GetBodyComponent() {
    return BodyComponent;
}