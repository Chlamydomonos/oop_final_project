#include "TestScene.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../utils/VectorConversion.h"

using namespace cocos2d;

bool TestScene::init()
{
    if(!Scene::init())
        return false;

    this->addComponent(Box2DWorldComponent::create(b2Vec2(0.0f, -10.0f)));

    //--------------------------------------------
    
    dynamicSprite = Sprite::create("pure_red.png");
    dynamicSprite->setScale(4, 4);
    dynamicSprite->setPosition(p2r(b2Vec2(8.0f, 8.0f)));
    this->addChild(dynamicSprite);

    staticSprite = Sprite::create("pure_red.png");
    staticSprite->setScale(64, 4);
    staticSprite->setPosition(p2r(b2Vec2(8.0f, 0.5f)));
    this->addChild(staticSprite);

    //--------------------------------------------

    b2BodyDef staticBodyDef;
    staticBodyDef.position.Set(8.0f, 0.5f);

    b2PolygonShape staticBox;
    staticBox.SetAsBox(32.0f, 0.5f);

    b2FixtureDef staticFixtureDef;
    staticFixtureDef.shape = &staticBox;

    staticSprite->addComponent(Box2DBodyComponent::create(&staticBodyDef, &staticFixtureDef));

    //--------------------------------------------

    b2BodyDef dynamicBodyDef;
    dynamicBodyDef.type = b2_dynamicBody;
    //dynamicBodyDef.position.Set(32.0f, 15.0f);
    dynamicBodyDef.position.Set(8.0f, 8.0f);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);

    b2FixtureDef dynamicFixtureDef;
    dynamicFixtureDef.shape = &dynamicBox;
    dynamicFixtureDef.density = 1.0f;
    dynamicFixtureDef.friction = 0.3f;
    dynamicFixtureDef.restitution = 0.8f;

    dynamicSprite->addComponent(Box2DBodyComponent::create(&dynamicBodyDef, &dynamicFixtureDef));

    //--------------------------------------------

    scheduleUpdate();
    //dynamicSprite->scheduleUpdate();
    //staticSprite->scheduleUpdate();

    return true;
}

void TestScene::update(float delta)
{
    Scene::update(delta);
}

TestScene::~TestScene()
{
    
}
