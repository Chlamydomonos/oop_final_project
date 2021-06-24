#include "TestPlayerScene.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Utils/VectorConversion.h"
#include "../Item/ItemStackSprite.h"
#include "../Classes/Player/PlayerContact.h"
#include "../Player/PlayerController.h"
#include "../Utils/DeleteCheck.h"
#include "../Items/TestObj.h"
using namespace cocos2d;

bool TestPlayerScene::init() {

    if (!Scene::init())
        return false;
    worldComponent = Box2DWorldComponent::create(b2Vec2(0.0f, -10.0f));

    this->addComponent(worldComponent);

    //create the ground
    Ground = cocos2d::Sprite::create("pure_red.png");
    Ground->setScale(64,4);
    b2BodyDef staticBodyDef;
    staticBodyDef.position.Set(8.0f, 0.5f);
    b2PolygonShape staticBox;
    staticBox.SetAsBox(32.0f, 0.5f);
    b2FixtureDef staticFixtureDef;
    staticFixtureDef.shape = &staticBox;
    auto groundBodyComponent = Box2DBodyComponent::create(&staticBodyDef, &staticFixtureDef);
    Ground->addComponent(groundBodyComponent);
    this->addChild(Ground);
    groundBodyComponent->addToWorld();

 
    auto item = new TestObj1();
    object = ItemStackSprite::create(item, 10);
    this->addChild(object);
    object->GetBodyComponent()->addToWorld();
    object->GetBodyComponent()->getBody()->SetUserData(object);

    auto item2 = new TestObj2();
    object = ItemStackSprite::create(item2, 10, 2.0, 3.0);
    this->addChild(object);
    object->GetBodyComponent()->addToWorld();
    object->GetBodyComponent()->getBody()->SetUserData(object);

    auto item3 = new TestObj3();
    object = ItemStackSprite::create(item3, 10, 11.0, 9.0);
    this->addChild(object);
    object->GetBodyComponent()->addToWorld();
    object->GetBodyComponent()->getBody()->SetUserData(object);

    auto item4 = new TestObj4();
    object = ItemStackSprite::create(item4, 10, 15.0, 10.0);
    this->addChild(object);
    object->GetBodyComponent()->addToWorld();
    object->GetBodyComponent()->getBody()->SetUserData(object);

    auto item5 = new TestObj5();
    object = ItemStackSprite::create(item5, 10, 13.5, 5.0);
    this->addChild(object);
    object->GetBodyComponent()->addToWorld();
    object->GetBodyComponent()->getBody()->SetUserData(object);


    Person = Player::GetInstance();

    this->addChild(Person);
    Person->GetBC()->addToWorld();
    Person->GetBC()->getBody()->SetUserData(Person); // link this object! So that it be obtained easily in the Collision Listener!!
    //Person->GetBC()->getBody()->SetFixedRotation(true);


    auto contact_listener = new PlayerContact();
    worldComponent->getWorld()->SetContactListener(contact_listener);
    
    auto player_controller = PlayerController::create();
    this->addComponent(player_controller);

    scheduleUpdate();
    
    CCLOG("SCENE INIT FINISH!");

    return true;
}

void TestPlayerScene::update(float delta) {
    auto list = this->getChildren();
    DeleteCheck<TestPlayerScene>::CheckChild(this);
    Scene::update(delta);
}

void TestPlayerScene::remove_object(b2Body* body) {
    worldComponent->getWorld()->Step(1 / 60, 5, 5);
    worldComponent->getWorld()->DestroyBody(body);
}