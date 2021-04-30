#ifndef SCENES_TEST_SCENE_H
#define SCENES_TEST_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class TestScene : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(TestScene);

	virtual ~TestScene();
private:
	b2World *world;
	cocos2d::Sprite *dynamicSprite;
	b2Body *dynamicBody;
};

#endif
