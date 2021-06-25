#include "PlayerContact.h"
#include "Player.h"
#include "PlayerController.h"
#include "../Item/ItemStackSprite.h"
#include "../Scenes/TestPlayerScene.h"


void PlayerContact::BeginContact(b2Contact* contact) {
    
    auto bodyA = contact->GetFixtureA()->GetBody();
    auto bodyB = contact->GetFixtureB()->GetBody();
    auto spriteA = (cocos2d::Sprite*)bodyA->GetUserData();
    auto spriteB = (cocos2d::Sprite*)bodyB->GetUserData();

    //Eat item 
    EatItemCheck(spriteA, spriteB);

    //Invoke shop
    InvokeShopCheck(spriteA, spriteB);

    //On the ground
    OnTheGroundCheck(spriteA, spriteB, true);

}

void PlayerContact::EndContact(b2Contact* contact) {
    auto bodyA = contact->GetFixtureA()->GetBody();
    auto bodyB = contact->GetFixtureB()->GetBody();
    auto spriteA = (cocos2d::Sprite*)bodyA->GetUserData();
    auto spriteB = (cocos2d::Sprite*)bodyB->GetUserData();

    OnTheGroundCheck(spriteA, spriteB, false);

}

void PlayerContact::EatItemCheck(cocos2d::Sprite* spriteA, cocos2d::Sprite* spriteB) {
    if (!spriteA || !spriteB)
        return;
    Player* Person{ nullptr };
    ItemStackSprite* ItemObj{ nullptr };
    if (spriteA->getTag() == PLAYER_TAG && spriteB->getTag() == ITEM_TAG) {
        Person = dynamic_cast<Player*>(spriteA);
        ItemObj = dynamic_cast<ItemStackSprite*>(spriteB);
    }

    if (spriteB->getTag() == PLAYER_TAG && spriteA->getTag() == ITEM_TAG) {
        Person = dynamic_cast<Player*>(spriteB);
        ItemObj = dynamic_cast<ItemStackSprite*>(spriteA);
    }

    if (Person)
        if (Person->ObtainItem(ItemObj))
            ItemObj->BeObtained();
}

void PlayerContact::InvokeShopCheck(cocos2d::Sprite* spriteA, cocos2d::Sprite* spriteB) {
    if (!spriteA || !spriteB)
        return;
    Player* Person{ nullptr };
    if ((spriteA->getTag() == PLAYER_TAG && spriteB->getTag() == SHOP_ICON_TAG) ||
       (spriteB->getTag() == PLAYER_TAG && spriteA->getTag() == SHOP_ICON_TAG)) {
        PlayerController::ReadyToGoToShop();
    }
}

void PlayerContact::OnTheGroundCheck(cocos2d::Sprite* spriteA, cocos2d::Sprite* spriteB, bool begin) {
    if (!spriteA || !spriteB)
        return;
    Player* Person{ nullptr };
    if (spriteA->getTag() == PLAYER_TAG && spriteB->getTag() == GROUND_TAG) {
        Person = dynamic_cast<Player*>(spriteA);
    }

    if (spriteB->getTag() == PLAYER_TAG && spriteA->getTag() == GROUND_TAG) {
        Person = dynamic_cast<Player*>(spriteB);
    }

    if (Person) {
        if (begin) {
            Person->on_the_ground = true;
        }
        else {
            Person->on_the_ground = false;
        }
    }
               
}