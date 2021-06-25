#ifndef SCENES_TEST_MAP_SCENE_H
#define SCENES_TEST_MAP_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "ui/CocosGUI.h"
#include "../Map/GameMap.h"

class TestMapScene : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(TestMapScene);

	virtual ~TestMapScene();
private:
	cocos2d::Node *mainNode;
	cocos2d::ui::LoadingBar* HpBar;
	cocos2d::ui::LoadingBar* OxyBar;
	cocos2d::DrawNode* MapIndex;
	float maxDelta;
	GameMap* gameMap;
};

#endif
#pragma once
