#include "PlayerCollection.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Utils/VectorConversion.h"
#include "../Item/ItemStackSprite.h"
#include "../Player/PlayerController.h"
using namespace cocos2d;

bool PlayerCollection::init() {

    if (!Scene::init())
        return false;
    auto Person = Player::GetInstance();
    float height = Director::getInstance()->getVisibleSize().height;
    float width = Director::getInstance()->getVisibleSize().width;
    this->setTag(BAG_TAG);

    //Title
    auto title = Label::createWithSystemFont("Collections of the player", "Arial", 40);
    title->setPosition(Vec2(width / 2, height * 0.94));
    this->addChild(title);

    //Normal Collections
    auto Items{ Person->GetCollection() };
    int cnt{ 0 };
    for (auto it : Items) {
        auto center = Vec2(width * (0.1 + 0.2 * (cnt % 5)), height * (1-(0.2 + 0.2 * (cnt / 5))));

        auto entity = Sprite::create("assets/items/" + it.Name+".png");
        entity->setScaleX(64 / entity->getContentSize().width);
        entity->setScaleY(64 / entity->getContentSize().height);
        entity->setAnchorPoint(Vec2(0.5, 0.5));
        entity->setPosition(center+Vec2(0,0.05*height));

        auto caption = Label::createWithSystemFont(it.Name, "Arial", 20);
        caption->setAnchorPoint(Vec2(0.0, 0.5));
        caption->setPosition(center+Vec2(-0.06*width,-0.03*height));

        auto number_string = new char[50];
        itoa(it.Count, number_string,10);

        auto number = Label::createWithSystemFont(number_string, "Arial", 30);
        number->setAnchorPoint(Vec2(1.0, 0.5));
        number->setPosition(center + Vec2(0.06 * width, -0.03 * height));
        
        this->addChild(entity);
        this->addChild(caption);
        this->addChild(number);
        cnt++;
    }



    auto player_controller = PlayerController::create();
    this->addComponent(player_controller);

    scheduleUpdate();

    return true;
}

void PlayerCollection::update(float delta) {
    Scene::update(delta);
}