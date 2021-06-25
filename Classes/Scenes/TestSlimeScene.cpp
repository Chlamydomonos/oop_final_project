#include "TestSlimeScene.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Player/Player.h"
#include "../Player/PlayerController.h"
#include "../Slime/Slime.h"
#include "../Slime/SlimeRenderer.h"

using namespace cocos2d;

bool TestSlimeScene::init()
{
    //--向场景添加物理空间组件----------------------
    if (!Scene::init())
        return false;

    this->addComponent(Box2DWorldComponent::create(b2Vec2(0.0f, -10.0f)));

    //--建立动态Sprite-----------------------------

    dynamicSprite = Sprite::create("pure_red.png");
    dynamicSprite->setScale(4, 4);
    this->addChild(dynamicSprite);

    //--建立静态Sprite-----------------------------

    staticSprite = Sprite::create("pure_red.png");
    staticSprite->setScale(64, 4);
    this->addChild(staticSprite);

    //--建立静态物理组件----------------------------

    b2BodyDef staticBodyDef;
    staticBodyDef.position.Set(8.0f, 0.5f);

    b2PolygonShape staticBox;
    staticBox.SetAsBox(32.0f, 0.5f);

    b2FixtureDef staticFixtureDef;
    staticFixtureDef.shape = &staticBox;

    auto staticBodyComponent = Box2DBodyComponent::create(&staticBodyDef, &staticFixtureDef);
    staticSprite->addComponent(staticBodyComponent);
    staticBodyComponent->addToWorld();

    //--建立动态物理组件----------------------------

    b2BodyDef dynamicBodyDef;
    dynamicBodyDef.type = b2_dynamicBody;
    dynamicBodyDef.position.Set(8.0f, 8.0f);

    dynamicBodyDef.angularVelocity = 0.1f;

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);

    b2FixtureDef dynamicFixtureDef;
    dynamicFixtureDef.shape = &dynamicBox;
    dynamicFixtureDef.density = 1.0f;
    dynamicFixtureDef.friction = 0.3f;
    dynamicFixtureDef.restitution = 0.8f;

    auto dynamicBodyComponent = Box2DBodyComponent::create(&dynamicBodyDef, &dynamicFixtureDef);
    dynamicSprite->addComponent(dynamicBodyComponent);
    dynamicBodyComponent->addToWorld();


    addChild(Player::GetInstance());
    Player::GetInstance()->GetBC()->addToWorld();
    Player::GetInstance()->GetBC()->getBody()->SetFixedRotation(true);
    addComponent(PlayerController::create());

    addChild(SlimeRenderer::getInstance());
    SlimeRenderer::getInstance()->addToWorld();

    auto slime = Slime::create(1, 8, 2);
    this->addChild(slime);
    slime->addToWorld();

    //--开启update函数------------------------------

    scheduleUpdate();

    return true;
    return true;
}

void TestSlimeScene::update(float delta)
{
    Scene::update(delta);
}

TestSlimeScene::~TestSlimeScene()
{
}
