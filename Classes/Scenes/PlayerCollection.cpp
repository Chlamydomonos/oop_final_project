#include "PlayerCollection.h"

#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Utils/VectorConversion.h"
#include "../Item/ItemStackSprite.h"

using namespace cocos2d;

bool PlayerCollection::init() {

    if (!Scene::init())
        return false;
    auto Person = Player::GetInstance();

    auto title = Label::createWithSystemFont("Collections of the player", "Arial", 30);
    float height = Director::getInstance()->getVisibleSize().height;
    float width = Director::getInstance()->getVisibleSize().width;
    title->setPosition(Vec2(width / 2, height * 0.95));

    this->addChild(title);

    auto Items = Person->GetCollection();

    int pages = Items.size() % 24 ? Items.size() / 24 : Items.size() / 24 + 1;
    
    int page_fix = 0;

    auto testimg = ItemStackSprite::create("testsprite");
    testimg->setScaleX(testimg->getScaleX() * 2);
    testimg->setScaleY(testimg->getScaleY() * 2);
    testimg->setPosition(Vec2(width / 7 * ((0 % 6) + 1), (0.85 - 0.15 * (0 / 6)) * height));

    this->addChild(testimg);


    CCLOG("CLOLLECTION INIT!");
    scheduleUpdate();

    //Director::getInstance()->popScene();
    return true;
}

void PlayerCollection::update(float delta) {
    Scene::update(delta);
    

}