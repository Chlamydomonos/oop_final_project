#include "PlayerController.h"
#include <../Classes/Physics/Box2DBodyComponent.h> 
#include <../Classes/Item/ItemStackSprite.h>
#include "Player.h"
#include "../Scenes/PlayerCollection.h"

using namespace cocos2d;

void PlayerController::onAdd()
{
    Component::onAdd();

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        this->keyPress[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        this->keyPress[keyCode] = false;
        TransientActionCheck(keyCode);
    };

    this->getOwner()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->getOwner());
}

void PlayerController::update(float delta)
{
    Component::update(delta);

    if (keyPress[EventKeyboard::KeyCode::KEY_A] && !keyPress[EventKeyboard::KeyCode::KEY_D]) {
        player->GetBC()->getBody()->SetLinearVelocity(b2Vec2(-player->horizontal_velocity, 0) + b2Vec2(0, player->GetBC()->getBody()->GetLinearVelocity().y));
    }

    if (keyPress[EventKeyboard::KeyCode::KEY_D] && !keyPress[EventKeyboard::KeyCode::KEY_A]) {
        player->GetBC()->getBody()->SetLinearVelocity(b2Vec2(player->horizontal_velocity, 0) + b2Vec2(0, player->GetBC()->getBody()->GetLinearVelocity().y));
    }

    if (keyPress[EventKeyboard::KeyCode::KEY_W]) {
        player->GetBC()->getBody()->ApplyForce(b2Vec2(0, player->vertical_force), player->GetBC()->getBody()->GetWorldCenter(), true);
    }

}

bool PlayerController::init() {
    if (!Component::init())
        return false;
    player = Player::GetInstance();
    return true;
}

void PlayerController::TransientActionCheck(EventKeyboard::KeyCode keyCode) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_E:
        if (this->getOwner()->getTag() != BAG_TAG) {
            auto collection_scene = PlayerCollection::create();
            Director::getInstance()->pushScene(collection_scene);
        }
        break;
    case EventKeyboard::KeyCode::KEY_B:
        if (this->getOwner()->getTag() == BAG_TAG) {
            Director::getInstance()->popScene();
        }
        break;
    }
}