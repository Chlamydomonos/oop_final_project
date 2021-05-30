#include <../Classes/Physics/Box2DBodyComponent.h> 
#include <../Classes/Item/ItemStackSprite.h>
#include "Player.h"
#include "../Scenes/PlayerCollection.h"
using namespace cocos2d;

Player* Player::instance = nullptr ;

bool Player::init() {
	if (!Sprite::init() || !initWithFile("player_init.png"))
		return false;

    b2BodyDef dynamicBodyDef;
    dynamicBodyDef.type = b2_dynamicBody;
    dynamicBodyDef.position.Set(6.0f, 8.0f);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);

    b2FixtureDef dynamicFixtureDef;
    dynamicFixtureDef.shape = &dynamicBox;
    dynamicFixtureDef.density = 1.0f;
    dynamicFixtureDef.friction = 2;
    dynamicFixtureDef.restitution = 0.2f;

    auto dynamicBodyComponent = Box2DBodyComponent::create(&dynamicBodyDef, &dynamicFixtureDef);

    this->addComponent(dynamicBodyComponent);
    this->BC = dynamicBodyComponent;
    
    this->setTag(PLAYER_TAG); // 1 for a player

    //Player::instance = this;

    return true;
}

void Player::movement_control_listen() {
    if (KeyPress[EventKeyboard::KeyCode::KEY_A] && !KeyPress[EventKeyboard::KeyCode::KEY_D]) {
        BC->getBody()->SetLinearVelocity(b2Vec2(-this->horizontal_velocity, 0) + b2Vec2(0, BC->getBody()->GetLinearVelocity().y));
    }

    if (KeyPress[EventKeyboard::KeyCode::KEY_D] && !KeyPress[EventKeyboard::KeyCode::KEY_A]) {
        BC->getBody()->SetLinearVelocity(b2Vec2(this->horizontal_velocity, 0) + b2Vec2(0, BC->getBody()->GetLinearVelocity().y));
    }

    if (KeyPress[EventKeyboard::KeyCode::KEY_W]) {
        BC->getBody()->ApplyForce(b2Vec2(0, this->vertical_force), BC->getBody()->GetWorldCenter(), true);
    }

    if (KeyPress[EventKeyboard::KeyCode::KEY_P]) {
        auto collection_scene = PlayerCollection::create();
        Director::getInstance()->pushScene(collection_scene);
        //切换到玩家背包场景
    }
}

cocos2d::EventListenerKeyboard* Player::init_listener() {
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        this->KeyPress[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        this->KeyPress[keyCode] = false;
    };
    return listener;
}

void Player::ObtainItem(ItemStackSprite* i) {
    this->ItemCollection.push_back(i);
}