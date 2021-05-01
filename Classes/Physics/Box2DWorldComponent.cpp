#include "Box2DWorldComponent.h"

Box2DWorldComponent *Box2DWorldComponent::create(const b2Vec2 &gravity)
{
    auto ret = new Box2DWorldComponent();

    ret->world = new b2World(gravity);
    ret->setName("b2World");

    if (ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);

    return ret;
}

void Box2DWorldComponent::update(float delta)
{
    world->Step(delta, 8, 3);
}
