#include "Box2DBodyComponent.h"
#include "Box2DWorldComponent.h"

Box2DBodyComponent *Box2DBodyComponent::create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef)
{
    Box2DBodyComponent *ret = new Box2DBodyComponent();

    ret->bodyDef = bodyDef;
    ret->fixtureDef = fixtureDef;

    if (ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
        throw(1);

    return ret;
}

void Box2DBodyComponent::onAdd()
{
    try
    {
        cocos2d::Component::onAdd();
        auto wp = dynamic_cast<Box2DWorldComponent *>(getOwner()->getComponent("b2World"));
        auto w = wp->getWorld();
        body = w->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
    }
    catch (...)
    {
        throw Exception("Error adding physics body to sprite");
    }
}

void Box2DBodyComponent::update(float delta)
{
}
