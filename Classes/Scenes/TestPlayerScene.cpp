#include "TestPlayerScene.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Utils/VectorConversion.h"

using namespace cocos2d;

bool TestPlayerScene::init() {
    if (!Scene::init())
        return false;

    this->addComponent(Box2DWorldComponent::create(b2Vec2(0.0f, -10.0f)));

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

    //create the player
    Person = Player::create();
    
    this->addChild(Person);
    Person->GetBC()->addToWorld();

    //create the listener
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        this->KeyPress[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        this->KeyPress[keyCode] = false;
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    scheduleUpdate();

    return true;
}

void TestPlayerScene::update(float delta) {
    Scene::update(delta);

    if (KeyPress[EventKeyboard::KeyCode::KEY_A] && !KeyPress[EventKeyboard::KeyCode::KEY_D]) {
        Person->GetBC()->getBody()->SetLinearVelocity(b2Vec2(-Person->horizontal_velocity, 0) + b2Vec2(0, Person->GetBC()->getBody()->GetLinearVelocity().y));
    }

    if (KeyPress[EventKeyboard::KeyCode::KEY_D] && !KeyPress[EventKeyboard::KeyCode::KEY_A]) {
        Person->GetBC()->getBody()->SetLinearVelocity(b2Vec2(Person->horizontal_velocity, 0)+b2Vec2(0, Person->GetBC()->getBody()->GetLinearVelocity().y));
    }

    if (KeyPress[EventKeyboard::KeyCode::KEY_W]) {
        Person->GetBC()->getBody()->ApplyForce(b2Vec2(0, Person->vertical_force), Person->GetBC()->getBody()->GetWorldCenter(),true);
    }
}