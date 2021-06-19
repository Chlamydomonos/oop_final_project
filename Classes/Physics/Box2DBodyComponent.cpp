#include "Box2DBodyComponent.h"
#include "Box2DWorldComponent.h"
#include "../Utils/VectorConversion.h"
#include "Box2DWorldComponent.h"

Box2DBodyComponent *Box2DBodyComponent::create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef)
{
    Box2DBodyComponent *ret = new Box2DBodyComponent();

    ret->bodyDef = new b2BodyDef(*bodyDef);
    ret->fixtureDef = new b2FixtureDef(*fixtureDef);
    auto shapeType = fixtureDef->shape->GetType();

    switch (shapeType)
    {
    case b2Shape::e_circle:
        ret->fixtureDef->shape = new b2CircleShape(*dynamic_cast<const b2CircleShape*>(fixtureDef->shape));
        break;
    case b2Shape::e_edge:
        ret->fixtureDef->shape = new b2EdgeShape(*dynamic_cast<const b2EdgeShape *>(fixtureDef->shape));
        break;
    case b2Shape::e_polygon:
        ret->fixtureDef->shape = new b2PolygonShape(*dynamic_cast<const b2PolygonShape *>(fixtureDef->shape));
        break;
    case b2Shape::e_chain:
        ret->fixtureDef->shape = new b2ChainShape(*dynamic_cast<const b2ChainShape *>(fixtureDef->shape));
        break;
    case b2Shape::e_typeCount:
        break;
    default:
        break;
    }

    if (ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);

    return ret;
}

Box2DBodyComponent::~Box2DBodyComponent()
{
    CC_SAFE_DELETE(bodyDef);
    CC_SAFE_DELETE(fixtureDef);
    bool temp = true;

    auto node = getOwner();
    cocos2d::Component *p = nullptr;

    while (p == nullptr && node != nullptr)
    {
        p = node->getComponent("b2World");
        node = node->getParent();
    }

    if (p)
    {
        auto world = dynamic_cast<Box2DWorldComponent *>(p);
        world->getWorld()->DestroyBody(body);
    }
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

        CC_SAFE_DELETE(fixtureDef->shape);
        CC_SAFE_DELETE(bodyDef);
        CC_SAFE_DELETE(fixtureDef);
    }
    catch (...)
    {
        throw Exception("Error adding physics body to sprite");
    }
}
