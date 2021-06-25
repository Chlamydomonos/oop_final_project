//#pragma once
#ifndef EMITTERWORLD_H
#define EMITTERWORLD_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "Emitter.h"

class EmitterWorld :public cocos2d::Node
{
public:
	EmitterWorld() : world{ nullptr } {}
	virtual ~EmitterWorld() { delete world; }
	b2World* getWorld() { return world; }
	static EmitterWorld* create(const b2Vec2& gravity);
	virtual void update(float delta);
protected:
	b2World* world;
};
#endif
