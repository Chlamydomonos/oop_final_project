#ifndef SCENES_TEST_MAP_SCENE_H
#define SCENES_TEST_MAP_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class TestMapScene : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(TestMapScene);

	virtual ~TestMapScene();
private:
	cocos2d::Node *mainNode;
};

#endif
#pragma once
