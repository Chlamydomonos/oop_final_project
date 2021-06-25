#include "Shop.h"
#include <vector>
#include "../Player/PlayerController.h"
#include "../Item/Item.h"
#include "ui/CocosGUI.h"
#include <string>
using namespace cocos2d;

bool Shop::init() {

    if (!Scene::init())
        return false;
    Person = Player::GetInstance();
    float height = Director::getInstance()->getVisibleSize().height;
    float width = Director::getInstance()->getVisibleSize().width;
    this->setTag(BAG_TAG);

    //Title
    auto title = Label::createWithSystemFont("Shop", Font, 40);
    title->setPosition(Vec2(width / 2, height * 0.94));
    this->addChild(title);

    //MoneyLabel
    moneyLabel = Label::createWithSystemFont(std::string("Money ")+std::to_string(Person->GetMoney()), Font, 35);
    moneyLabel->setPosition(Vec2(width * 0.3, height * 0.8));
    this->addChild(moneyLabel);

    //Sell everything
    auto button = ui::Button::create("sell_everything_button.png", "sell_everything_button_sel.png", "sell_everything_button.png");
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            SellEverything();
            break;
        default:
            break;
        }
        });
    button->setPosition(Vec2(width * 0.7, height * 0.8));
    this->addChild(button);


    //Buy things
    Vector <MenuItem*> Menuitems;
    auto t = MenuItemLabel::create(
        Label::createWithSystemFont("Horizontal volocity +0.5", Font, 30), 
        [this](Ref* sender) {
            HorizontalSpeedIncrease(0.5);
        });
    Menuitems.pushBack(t);

    t = MenuItemLabel::create(
        Label::createWithSystemFont("Vertical inital volocity +0.5", Font, 30),
        [this](Ref* sender) {
            VerticalSpeedIncrease(0.5);
        });
    Menuitems.pushBack(t);


    t = MenuItemLabel::create(
        Label::createWithSystemFont("ESC Shop", Font, 30),
        [this](Ref* sender) {
            Person->just_out_of_shop = true;
            Person->in_shop= false;
            Director::getInstance()->popScene();
        });
    Menuitems.pushBack(t);

    auto menu = Menu::createWithArray(Menuitems);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(Vec2(0.5, 1));
    menu->setPosition(Vec2(width * 0.5, height * 0.5));
    this->addChild(menu,1);
   
    auto player_controller = PlayerController::create();
    this->addComponent(player_controller);

    scheduleUpdate();

    return true;
}

void Shop::update(float delta) {
    Scene::update(delta);

    //update the money label
    if (moneyModified) {
        moneyModified = false;
        this->removeChild(moneyLabel);
        //delete moneyLabel;
        moneyLabel = Label::createWithSystemFont(std::string("Money ") + std::to_string(Person->GetMoney()), Font, 35);
        float height = Director::getInstance()->getVisibleSize().height;
        float width = Director::getInstance()->getVisibleSize().width;
        moneyLabel->setPosition(Vec2(width * 0.3, height * 0.8));
        this->addChild(moneyLabel);
    }
}

bool Shop::PurchaseCheck(int money) {
    if (Person->GetMoney() < money)
        return false;

    Person->GetMoney() = Person->GetMoney() - money;
    moneyModified = true;
    return true;
}

void Shop::HorizontalSpeedIncrease(float increment) {
    const float ratio = 10.0; //money per velocity;
    
    if(PurchaseCheck(increment * ratio))
        Person->horizontal_velocity += increment;
}

void Shop::VerticalSpeedIncrease(float increment) {
    const float ratio = 10.0; //money per volocity;

    if (PurchaseCheck(increment * ratio)) {
        Person->vertical_initial_velocity += increment;
    }
}

void Shop::SellEverything() {
    for (auto it : Person->GetCollection()) {
        Person->GetMoney() += it.Count * Item::ALL_ITEMS[it.Name]->getValue();
    }
    moneyModified = true;
    Person->GetCollection().clear();
}