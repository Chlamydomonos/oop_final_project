#pragma once

#define PLAYER_TAG 1
#define ITEM_TAG 2
#define DEL_TAG -7
#define BAG_TAG 3

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
	static Player* instance;

public:

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
	std::vector <singleCollection>& GetCollection() {
		return ItemCollection;
	}


	const float horizontal_velocity{ 2.0 };// the horizontal velocity (positive)
	const float vertical_force{ 20.0 };
	const int pack_grid_max{ 15 };
	std::map <cocos2d::EventKeyboard::KeyCode, bool> KeyPress;

	virtual bool init();
	bool ObtainItem(ItemStackSprite* item);

	CREATE_FUNC(Player);
	~Player() {}

	Box2DBodyComponent* GetBC() { return BC; }


};
