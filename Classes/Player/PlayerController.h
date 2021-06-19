#ifndef PLAYER_PLAYER_CONTROLLER_H
#define PLAYER_PLAYER_CONTROLLER_H

#include <cocos2d.h>
#include <map>
#include "Player.h"

class PlayerController : public cocos2d::Component
{
public:
	CREATE_FUNC(PlayerController);

	bool init();

	PlayerController() : cocos2d::Component{}, player{ nullptr }, keyPress{}{}

	virtual void onAdd();

	virtual void update(float delta);

	void TransientActionCheck(cocos2d::EventKeyboard::KeyCode keyCode);

private:
	Player* player{nullptr};
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyPress;
};

#endif // !PLAYER_PLAYER_CONTROLLER_H