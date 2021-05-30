#include "PlayerController.h"
#include <../Classes/Physics/Box2DBodyComponent.h> 
#include <../Classes/Item/ItemStackSprite.h>
#include "Player.h"
using namespace cocos2d;

void PlayerController::onAdd()
{
    Component::onAdd();
    player = dynamic_cast<Player *>(getOwner());

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        this->keyPress[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        this->keyPress[keyCode] = false;
    };

    player->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, player);
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
