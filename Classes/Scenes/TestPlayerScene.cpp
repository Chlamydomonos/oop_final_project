#include "TestPlayerScene.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Utils/VectorConversion.h"
#include "../Item/ItemStackSprite.h"
#include "../Classes/Player/PlayerContact.h"

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

 

    object = ItemStackSprite::create("testobj");
    this->addChild(object);
    object->GetBodyComponent()->addToWorld();
    object->GetBodyComponent()->getBody()->SetUserData(object); // link this object! So that it be obtained easily in the Collision Listener!!

       //create the player
    Person = Player::GetInstance();

    //Person->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 3, Director::getInstance()->getVisibleSize().height / 3));
    this->addChild(Person);
    Person->GetBC()->addToWorld();
    //Person->GetBC()->getBody()->
    Person->GetBC()->getBody()->SetUserData(Person); // link this object! So that it be obtained easily in the Collision Listener!!


    auto contact_listener = new PlayerContact();
    worldComponent->getWorld()->SetContactListener(contact_listener);
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(Person->init_listener(),this);
    
    scheduleUpdate();
    
    

    CCLOG("SCENE INIT FINISH!");

    return true;
}

void TestPlayerScene::update(float delta) {
    Scene::update(delta);
    Person->movement_control_listen();
        if (Person->KeyPress[EventKeyboard::KeyCode::KEY_R]) {
            worldComponent->getWorld()->Step(1 / 30, 3, 3);
            worldComponent->getWorld()->DestroyBody(object->GetBodyComponent()->getBody());
        }
        //this is where 打断点之后没问题，不打断点就报错
}

void TestPlayerScene::remove_object(b2Body* body) {
    worldComponent->getWorld()->Step(1 / 30, 3, 3);
    worldComponent->getWorld()->DestroyBody(body);
    //world运行时不能使用remove方法，需要step，再destroy
}