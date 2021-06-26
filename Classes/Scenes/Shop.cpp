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

    auto player_controller = PlayerController::create();
    this->addComponent(player_controller);

    scheduleUpdate();

    return true;
}

void Shop::create_menu() {
    Vector <MenuItem*> Menuitems;

    ShoppingItemCreate(Menuitems, "Horizontal Speed +0.5", (int)(0.5 * 10), 
        [this]() {
        Person->horizontal_velocity += 0.5;
        }, 
        [this]() {
            return Person->horizontal_velocity >= Person->maxHorizontalVel;
        });
    ShoppingItemCreate(Menuitems, "Vertical Speed +0.5", (int)(0.5 * 10), 
        [this]() {
        Person->vertical_initial_velocity += 0.5;
        },
        [this]() {
            return Person->vertical_initial_velocity >= Person->maxVeritcalVel;
        });

    ShoppingItemCreate(Menuitems, "Oxygen Capacity *1.5", 1, [this]() {
        Person->maxOxygen *= 1.5;
        },
        [this]() {
            return Person->maxOxygen >= Person->maxmaxOxygen;
        });

    ShoppingItemCreate(Menuitems, "Hint Point Max *1.25", 1, [this]() {
        Person->maxHp *= 1.25;
        },
        [this]() {
            return Person->maxHp >= Person->maxmaxHp;
        });

    ShoppingItemCreate(Menuitems, "Hint Point *1.25", 1, [this]() {
        Person->hp *= 1.25;
        },
        [this]() {
            return Person->hp >= Person->maxHp;
        });

    ShoppingItemCreate(Menuitems, "Attacking Speed +1", 1, [this]() {
        Person->attackSpeed += 1;
        },
        [this]() {
            return Person->attackSpeed >= Person->maxAttackSpeed;
        });

    ShoppingItemCreate(Menuitems, "Attacking Force +0x1000 ", 1, [this]() {
        Person->attackSpeed += 0x1000;
        },
        [this]() {
            return Person->attackForce >= Person->maxAttackForce;
        });

    ShoppingItemCreate(Menuitems, "ESC Shop", 0, [this]() {
        Person->just_out_of_shop = true;
        Person->in_shop = false;
        Director::getInstance()->popScene();
        },
        [this]() {
            return false;
        });

    float height = Director::getInstance()->getVisibleSize().height;
    float width = Director::getInstance()->getVisibleSize().width;
    menu = Menu::createWithArray(Menuitems);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(Vec2(0.5, 1));
    menu->setPosition(Vec2(width * 0.5, height * 0.4));
    this->addChild(menu, 1);
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

    if (newly_disabled) {
        newly_disabled = false;
        if (menu) {
            this->removeChild(menu);
        }
        create_menu();
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
    for (auto it : Person->GetCollection()) {
        Person->GetMoney() += it.Count * Item::ALL_ITEMS[it.Name]->getValue();
    }
    moneyModified = true;
    Person->GetCollection().clear();
}