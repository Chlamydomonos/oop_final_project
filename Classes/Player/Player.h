#pragma once

#define PLAYER_TAG 1
#define ITEM_TAG 5

#include <map>
#include <vector>
#include <cocos/cocos2d.h>

class ItemStackSprite;
class Box2DBodyComponent;
//inlcude the header files in cpp file to avoid circulation of inclusion


class Player: public cocos2d::Sprite
{
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

	const float horizontal_velocity{ 2.0 };// the horizontal velocity (positive)
	const float vertical_force{ 20.0 };
	virtual bool init();
	cocos2d::EventListenerKeyboard* init_listener();
	virtual void movement_control_listen();
	CREATE_FUNC(Player);
	~Player() {}
	Box2DBodyComponent* GetBC() { return BC; }
	void ObtainItem(ItemStackSprite* item);
	std::vector <ItemStackSprite*> GetCollection() {
		return ItemCollection;
	}
	std::map <cocos2d::EventKeyboard::KeyCode, bool> KeyPress;
private:
	Box2DBodyComponent* BC;
	
	std::vector <ItemStackSprite*> ItemCollection;
	static Player* instance;
};
