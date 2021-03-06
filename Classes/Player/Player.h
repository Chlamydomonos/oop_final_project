#pragma once

#define PLAYER_TAG 1
#define ITEM_TAG 2
#define DEL_TAG -7
#define BAG_TAG 3
#define SHOP_TAG 4
#define SHOP_ICON_TAG 5
#define GROUND_TAG 6


#include <map>
#include <vector>
#include <cocos/cocos2d.h>
#include <string>


class ItemStackSprite;
class Box2DBodyComponent;
class PlayerController;
//inlcude the header files in cpp file to avoid circulation of inclusion


class Player: public cocos2d::Sprite
{

private:
	Box2DBodyComponent* BC;
	PlayerController* Controller;

	class singleCollection {
	public:
		std::string Name;
		int Count;
		singleCollection(const char* n, int cnt) :Name{ n }, Count{ cnt } { }

	};
	std::vector <singleCollection> ItemCollection;
	int money{ 0 };
	static Player* instance;

public:

	int& GetMoney() {
		return money;
	}

	static Player* GetInstance() {
		if (Player::instance) {
			return Player::instance;
		}
		else
		{
			Player::instance = Player::create();
			return Player::instance;
		}
	}

	static void releaseInstance() { instance = nullptr; }

	std::vector <singleCollection>& GetCollection() {
		return ItemCollection;
	}


	float horizontal_velocity{ 5.0 };// the horizontal velocity (positive)
	float vertical_force{ 20.0 };
	float vertical_initial_velocity{ 0.0 };
	const int pack_grid_max{ 15 };

	float attackSpeed;
	int attackForce;

	int hp;
	int maxHp;
	int oxygen;
	int maxOxygen;

	int maxHorizontalVel{ 10 };
	int maxVeritcalVel{ 5 };
	int maxmaxOxygen{ 1000 };
	int maxmaxHp{ 100 };
	float maxAttackSpeed{ 10.0f };
	int maxAttackForce{ (0x1000) * 10 };

	std::map <cocos2d::EventKeyboard::KeyCode, bool> KeyPress;
	bool just_out_of_shop{ false };
	bool in_shop{ false };
	bool on_the_ground{ false };

	virtual bool init();
	bool ObtainItem(ItemStackSprite* item);

	CREATE_FUNC(Player);
	~Player() {}

	Box2DBodyComponent* GetBC() { return BC; }

	void attack(int target);
};
