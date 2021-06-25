#include "GameOver.h"
#include "MainMenu.h"

using namespace cocos2d;

bool GameOver::init()
{
    if (!Scene::init())
        return false;
    float height = Director::getInstance()->getVisibleSize().height;
    float width = Director::getInstance()->getVisibleSize().width;

    auto title = Label::createWithSystemFont("Game Over", "Arial", 40);
    title->setPosition(Vec2(width / 2, height * 0.94));
    this->addChild(title);

    Vector <MenuItem *> menuItems;
    auto t = MenuItemLabel::create(
        Label::createWithSystemFont("Quit To Main Menu", "Arial", 30),
        [this](Ref *sender) {
            Director::getInstance()->replaceScene(MainMenu::create());
        });
    menuItems.pushBack(t);

    auto menu = Menu::createWithArray(menuItems);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(Vec2(0.5, 1));
    menu->setPosition(Vec2(width * 0.5, height * 0.5));
    this->addChild(menu, 1);

    return true;
}
