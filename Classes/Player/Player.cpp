#include <../Classes/Physics/Box2DBodyComponent.h> 
#include <../Classes/Item/ItemStackSprite.h>
#include "Player.h"
#include "PlayerController.h"
#include "../Slime/Slime.h"
#include "../Map/GameMap.h"
#include "AttackEffectSprite.h"

using namespace cocos2d;

Player* Player::instance = nullptr ;

bool Player::init() {
	if (!Sprite::init() || !initWithFile("player_init.png"))
		return false;

    b2BodyDef dynamicBodyDef;
    dynamicBodyDef.type = b2_dynamicBody;
    dynamicBodyDef.position.Set(6.0f, 8.0f);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.37f, 0.45f);

    b2FixtureDef dynamicFixtureDef;
    dynamicFixtureDef.shape = &dynamicBox;
    dynamicFixtureDef.density = 1.0f;
    dynamicFixtureDef.friction = 20;
    dynamicFixtureDef.restitution = 0.2f;

    auto dynamicBodyComponent = Box2DBodyComponent::create(&dynamicBodyDef, &dynamicFixtureDef);

    this->addComponent(dynamicBodyComponent);
    this->BC = dynamicBodyComponent;
    
    this->setTag(PLAYER_TAG); // 1 for a player
    this->setName("Player");

    attackSpeed = 2.0f;

    hp = 20;
    maxHp = 20;
    oxygen = 100;
    maxOxygen = 100;

    schedule(
        [=](float) {
            if (getPositionY() / 64 >= 499)
                oxygen = maxOxygen;
            else if (getPositionY() / 64 >= 399)
                oxygen -= 1;
            else if (getPositionY() / 64 >= 299)
                oxygen -= 2;
            else if (getPositionY() / 64 >= 199)
                oxygen -= 3;
            else
                oxygen -= 4;

            if (oxygen < 0)
            {
                oxygen = 0;
                hp -= 1;
            }
        },
        1.0f,
        "decreaseOxygen"
    );

    return true;
}

bool Player::ObtainItem(ItemStackSprite* i) {
    for (auto &it : ItemCollection) {
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

void Player::attack(int target)
{
    Slime *nearest = nullptr;
    for (auto i : Slime::SLIMES)
    {
        if ((i->getPosition() - getPosition()).length() < i->getSize() * 64.0f + 32.0f)
            if (!nearest || (i->getPosition() - getPosition()).length() < (nearest->getPosition() - getPosition()).length())
                nearest = i;
    }
    if (nearest)
    {
        Vec2 direction = Vec2::forAngle((nearest->getPosition() - getPosition()).getAngle());
        nearest->getParticleGroup()->ApplyLinearImpulse({direction.x * 25.0f * nearest->getSize(), direction.y * 25.0f * nearest->getSize()});
        nearest->hurt(1);
        auto effect = AttackEffectSprite::create(direction.getAngle());
        addChild(effect);
        effect->execute();
    }
    else if((int)getPositionY() % 64 <= 10 || (int)getPositionY() % 64 >= 54)
    {
        int x = (int)getPositionX() / 64;
        if ((int)getPositionX() % 64 >= 32)
            x++;
        int y = ((int)getPositionY() + 10) / 64;
        if (GameMap::getInstance()->getTile(x, y - 1))
        {
            Vec2 d;
            if (target == 1)
            {
                GameMap::getInstance()->destroyTileByForce(x, y - 1, 0x2000);
                d = { 0, -1 };
            }
            else if (target == 2)
            {
                GameMap::getInstance()->destroyTileByForce(x + 1, y, 0x2000);
                d = { 1, 0 };
            }
            else
            {
                GameMap::getInstance()->destroyTileByForce(x - 1, y, 0x2000);
                d = { -1, 0 };
            }
            auto effect = AttackEffectSprite::create(d.getAngle());
            addChild(effect);
            effect->execute();
        }
    }
}
