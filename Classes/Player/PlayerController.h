#ifndef PLAYER_PLAYER_CONTROLLER_H
#define PLAYER_PLAYER_CONTROLLER_H

#include <cocos2d.h>
#include <map>
#include "Player.h"

class PlayerController : public cocos2d::Component
{
public:
	CREATE_FUNC(PlayerController);

	PlayerController() : cocos2d::Component{}, player{ nullptr }, keyPress{}{}

	virtual void onAdd();

	virtual void update(float delta);
private:
	Player *player;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyPress;
};

#endif // !PLAYER_PLAYER_CONTROLLER_H
