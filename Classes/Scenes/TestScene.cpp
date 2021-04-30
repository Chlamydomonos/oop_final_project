#include "TestScene.h"

using namespace cocos2d;

bool TestScene::init()
{
    if(!Scene::init())
        return false;

    world = new b2World(b2Vec2(0.0f, -10.0f));

    auto sprite = Sprite::create("pure_red.png");
    sprite->setScaleX(64.0f);
    sprite->setPosition(Vec2(512.0f, 8.0f));
    this->addChild(sprite);

    b2BodyDef def;
    def.position.Set(32.0f, 0.5f);

    b2Body* body = world->CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(32.0f, 0.5f);

    body->CreateFixture(&shape, 0.0f);

    dynamicSprite = Sprite::create("pure_red.png");
    dynamicSprite->setPosition(Vec2(512.0f, 640.0f));
    this->addChild(dynamicSprite);

    b2BodyDef dDef;
    dDef.type = b2_dynamicBody;
    dDef.position.Set(32.0f, 40.0f);

    dynamicBody = world->CreateBody(&dDef);

    b2PolygonShape dShape;
    dShape.SetAsBox(0.5f, 0.5f);
    b2FixtureDef dFixtureDef;
    dFixtureDef.shape = &dShape;
    dFixtureDef.density = 1.0f;
    dFixtureDef.friction = 0.3f;
    dFixtureDef.restitution = 0.9f;
    dynamicBody->CreateFixture(&dFixtureDef);

    scheduleUpdate();

    return true;
}

void TestScene::update(float delta)
{
    Scene::update(delta);
    world->Step(delta, 8, 3);

    auto position = dynamicBody->GetPosition();
    dynamicSprite->setPosition(Vec2(position.x * 16, position.y * 16));

    auto rotation = dynamicBody->GetAngle();

    dynamicSprite->setRotation(rotation / 3.1415926 * 180);
}

TestScene::~TestScene()
{
    delete world;
}
