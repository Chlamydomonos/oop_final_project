#include "Box2DBodyComponent.h"
#include "Box2DWorldComponent.h"
#include "../utils/VectorConversion.h"

Box2DBodyComponent *Box2DBodyComponent::create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef)
{
    Box2DBodyComponent *ret = new Box2DBodyComponent();

    ret->bodyDef = bodyDef;
    ret->fixtureDef = fixtureDef;

    if (ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);

    return ret;
}

void Box2DBodyComponent::onAdd()
{
    try
    {
        cocos2d::Component::onAdd();
        auto node = getOwner();
        auto p = node->getComponent("b2World");

        while (p == nullptr && node != nullptr)
        {
            p = node->getComponent("b2World");
            node = node->getParent();
        }

        if (p == nullptr)
            throw 1;

        auto wp = dynamic_cast<Box2DWorldComponent *>(p);
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
    getOwner()->setPosition(p2r(body->GetPosition()));
    getOwner()->setRotation(body->GetAngle() / 3.1415926 * 180);
}
