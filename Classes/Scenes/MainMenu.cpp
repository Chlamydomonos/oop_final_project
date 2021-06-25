#include "MainMenu.h"
#include "../Scenes/MainScene.h"

using namespace cocos2d;

bool MainMenu::init()
{
    if (!Scene::init())
        return false;

    float height = Director::getInstance()->getVisibleSize().height;
    float width = Director::getInstance()->getVisibleSize().width;

    Vector <MenuItem *> menuItems;
    auto t = MenuItemLabel::create(
        Label::createWithSystemFont("Start Game", "Arial", 30),
        [this](Ref *sender) {
            Director::getInstance()->replaceScene(MainScene::create());
        });
    menuItems.pushBack(t);

    t = MenuItemLabel::create(
        Label::createWithSystemFont("Quit Game", "Arial", 30),
        [this](Ref *sender) {
            Director::getInstance()->end();
        });
    menuItems.pushBack(t);

    auto menu = Menu::createWithArray(menuItems);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(Vec2(0.5, 1));
    menu->setPosition(Vec2(width * 0.5, height * 0.5));
    this->addChild(menu, 1);

    return true;
}
