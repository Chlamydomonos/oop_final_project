#ifndef SCENES_TestPlayer_SCENE_H
#define SCENES_TestPlayer_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Classes/Player/Player.h"


#include <map>

using namespace cocos2d;

class TestPlayerScene : public cocos2d::Scene{
public:
	bool init();
	~TestPlayerScene() { };
	CREATE_FUNC(TestPlayerScene);
	virtual void update(float delta);

	void remove_object(b2Body*);
private:
	Player* Person;
	cocos2d::Sprite* Ground;
	ItemStackSprite* object;
	Box2DWorldComponent* worldComponent;
};

#endif
