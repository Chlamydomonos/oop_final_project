#include "PlayerContact.h"
#include "Player.h"
#include "../Item/ItemStackSprite.h"
#include "../Scenes/TestPlayerScene.h"


void PlayerContact::BeginContact(b2Contact* contact) {
    

    auto bodyA = contact->GetFixtureA()->GetBody();
    auto bodyB= contact->GetFixtureB()->GetBody();


    auto spriteA = (cocos2d::Sprite*)bodyA->GetUserData();
    auto spriteB = (cocos2d::Sprite*)bodyB->GetUserData();
    Player* Person{ nullptr };
    ItemStackSprite* ItemObj{ nullptr };

    if (!spriteA || !spriteB)
        return;

    if (spriteA->getTag() == PLAYER_TAG && spriteB->getTag() == ITEM_TAG) {
        Person = dynamic_cast<Player*>(spriteA);
        ItemObj = dynamic_cast<ItemStackSprite*>(spriteB);
    }

    if (spriteB->getTag() == PLAYER_TAG && spriteA->getTag() == ITEM_TAG) {
        Person = dynamic_cast<Player*>(spriteB);
        ItemObj = dynamic_cast<ItemStackSprite*>(spriteA);
    }
    
    Person->ObtainItem(ItemObj);
    ItemObj->BeObtained();

    dynamic_cast<TestPlayerScene*>(
        Director::getInstance()->getRunningScene()
        )
        ->remove_object(
            ItemObj->GetBodyComponent()->getBody()
        );
}