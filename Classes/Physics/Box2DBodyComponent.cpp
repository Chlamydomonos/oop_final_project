#include "Box2DBodyComponent.h"
#include "Box2DWorldComponent.h"
#include "../utils/VectorConversion.h"

Box2DBodyComponent *Box2DBodyComponent::create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef)
{
    Box2DBodyComponent *ret = new Box2DBodyComponent();

    ret->bodyDef = new b2BodyDef(*bodyDef);
    ret->fixtureDef = new b2FixtureDef(*fixtureDef);

    if (ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);

    return ret;
}

void Box2DBodyComponent::update(float delta)
{
    if (body != nullptr)
    {
        getOwner()->setPosition(p2r(body->GetPosition()));
        getOwner()->setRotation(body->GetAngle() / 3.1415926 * 180);
    }
}

void Box2DBodyComponent::addToWorld()
{
    try
    {
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

        CC_SAFE_DELETE(bodyDef);
        CC_SAFE_DELETE(fixtureDef);
    }
    catch (...)
    {
        throw Exception("Error adding physics body to sprite");
    }
}
