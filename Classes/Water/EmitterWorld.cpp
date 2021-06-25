#include "EmitterWorld.h"

void EmitterWorld::update(float delta)
{
    world->Step(delta, 8, 3);
}

EmitterWorld* EmitterWorld::create(const b2Vec2& gravity)
{
    auto p = new EmitterWorld();
    p->world = new b2World(gravity);

    if (p && p->init())
        p->autorelease();
    else
        CC_SAFE_DELETE(p);

    return p;
}