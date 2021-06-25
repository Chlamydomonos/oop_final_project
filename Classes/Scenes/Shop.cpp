#include "Shop.h"
#include <vector>
#include "../Player/PlayerController.h"
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

    ShoppingItemCreate(Menuitems, "Horizontal Speed +0.5", (int)(0.5 * 10), [this]() {
        Person->horizontal_velocity += 0.5;
    });

    ShoppingItemCreate(Menuitems, "Vertical Speed +0.5", (int)(0.5 * 10), [this]() {
        Person->vertical_initial_velocity += 0.5;
    });

    ShoppingItemCreate(Menuitems, "ESC Shop", 0, [this]() {
        Person->just_out_of_shop = true;
        Person->in_shop = false;
        Director::getInstance()->popScene();
    });

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
        if(moneyLabel) this->removeChild(moneyLabel);
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


void Shop::SellEverything() {
    const float ratio = 1.0; //money per item unit

    int item_unit_cnt{ 0 };

    for (auto it : Person->GetCollection()) {
        item_unit_cnt += it.Count;
    }

    Person->GetMoney() += item_unit_cnt * ratio;
    moneyModified = true;
    Person->GetCollection().clear();
}