#ifndef SCENES_TEST_PARTICLE_SCENE_H
#define SCENES_TEST_PARTICLE_SCENE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "../Physics/Box2DWorldComponent.h"

class TestParticleScene : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(TestParticleScene);

	virtual ~TestParticleScene();
private:
	Box2DWorldComponent *wp;
	b2ParticleSystem *ps;
	cocos2d::Sprite *dynamicSprite;
	cocos2d::Sprite *staticSprite;
	cocos2d::DrawNode *drawNode;
};

#endif
#pragma once
#pragma once
