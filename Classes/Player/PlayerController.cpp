#include "PlayerController.h"
#include <../Classes/Physics/Box2DBodyComponent.h> 
#include <../Classes/Item/ItemStackSprite.h>
#include "Player.h"
#include "../Scenes/PlayerCollection.h"
#include "../Scenes/Shop.h"

using namespace cocos2d;

bool PlayerController::ReadyToShop{ false };

void PlayerController::onAdd()
{
    Component::onAdd();

    auto listener = EventListenerKeyboard::create();
    auto listener2 = EventListenerMouse::create();

    listener2->onMouseDown = [=](EventMouse *event) {
        cx = event->getCursorX() - Director::getInstance()->getWinSize().width / 2;
        cy = event->getCursorY() - Director::getInstance()->getWinSize().height / 2;
        if (attacking)
            nextAttack = true;
        else
        {
            if (cy < 0 && cy + cx < 0 && cy - cx < 0)
                player->attack(1);
            else if (cx > 0)
                player->attack(2);
            else
                player->attack(3);
            attacking = true;
            nextAttack = false;
            player->schedule(
                [=](float dt) {
                    if (nextAttack)
                    {
                        if (cy < 0 && cy + cx < 0 && cy - cx < 0)
                            player->attack(1);
                        else if (cx > 0)
                            player->attack(2);
                        else
                            player->attack(3);
                        nextAttack = false;
                    }
                    else
                    {
                        attacking = false;
                        player->unschedule("attack");
                    }
                },
                1.0f / player->attackSpeed,
                "attack"
            );
        }
    };

    listener2->onMouseMove = [=](EventMouse *event) {

    };

    listener2->onMouseScroll = [=](EventMouse *event) {

    };

    listener2->onMouseUp = [=](EventMouse *event) {

    };

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_W)
            player->GetBC()->getBody()->SetLinearVelocity(b2Vec2(player->GetBC()->getBody()->GetLinearVelocity().x, player->GetBC()->getBody()->GetLinearVelocity().y + player->horizontal_velocity / 4.0f));
        this->keyPress[keyCode] = true;
    };
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event) {
        this->keyPress[keyCode] = false;
        TransientActionCheck(keyCode);
    };

    this->getOwner()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->getOwner());
    this->getOwner()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this->getOwner());
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

        //If the player is on the ground, then it can gain the initial velocity
        if (player->on_the_ground == true) {
            player->GetBC()->getBody()->SetLinearVelocity(
                b2Vec2(0, player->vertical_initial_velocity) + b2Vec2(player->GetBC()->getBody()->GetLinearVelocity().x, player->GetBC()->getBody()->GetLinearVelocity().y));
        }
        
        player->GetBC()->getBody()->ApplyForce(b2Vec2(0, player->vertical_force), player->GetBC()->getBody()->GetWorldCenter(), true);
    }

    if (ReadyToShop) {
        ReadyToShop = false;
        if (player->just_out_of_shop) {
            player->just_out_of_shop = false;
        }
        else {
            auto shop_scene = Shop::create();
            Director::getInstance()->pushScene(shop_scene);
        }
    }

}

bool PlayerController::init() {
    if (!Component::init())
        return false;
    player = Player::GetInstance();
    attacking = false;
    return true;
}

void PlayerController::TransientActionCheck(EventKeyboard::KeyCode keyCode) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_E:
        if (this->getOwner()->getTag() != BAG_TAG) {
            auto collection_scene = PlayerCollection::create();
            Director::getInstance()->pushScene(collection_scene);
        }
        if (this->getOwner()->getTag() == BAG_TAG) {
            Director::getInstance()->popScene();
        }
        break;

    default:
        break;
    }
}

void PlayerController::ReadyToGoToShop() {
    ReadyToShop = true;
}