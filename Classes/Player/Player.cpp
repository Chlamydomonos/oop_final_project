#include <../Classes/Physics/Box2DBodyComponent.h> 
#include <../Classes/Item/ItemStackSprite.h>
#include "Player.h"
#include "PlayerController.h"

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


    return true;
}

bool Player::ObtainItem(ItemStackSprite* i) {
    for (auto it : ItemCollection) {
        if (strcmp(it.Name.c_str(),i->getName()) == 0) {
            it.Count += i->getCount();
            return true;
        }
    }

    if (ItemCollection.size() < pack_grid_max) {
        auto newItem = singleCollection{ i->getName(),i->getCount() };
        ItemCollection.push_back(newItem);
        return true;
    }

    return false;
    
}