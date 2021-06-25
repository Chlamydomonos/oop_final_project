#ifndef SCENES_TEST_SLIME_SCENE_H
#define SCENES_TEST_SLIME_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class TestSlimeScene : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(TestSlimeScene);

	virtual ~TestSlimeScene();
private:
	cocos2d::Sprite *dynamicSprite;
	cocos2d::Sprite *staticSprite;
};

#endif
