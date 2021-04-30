#ifndef PHYSICS_BOX_2D_WORLD_COMPONENT_H
#define PHYSICS_BOX_2D_WORLD_COMPONENT_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "../Exception/Exception.h"

class Box2DWorldComponent : public cocos2d::Component
{
private:
	b2World *world;

public:

	/**
	* @brief 不要使用此构造函数。
	* 
	* 使用create函数可以自动释放内存。
	*/
	Box2DWorldComponent() :
		cocos2d::Component{},
		world{ nullptr } {}

	virtual ~Box2DWorldComponent()
	{
		delete world;
	}

	static Box2DWorldComponent *create(b2Vec2 gravity);

	b2World *getWorld()
	{
		return world;
	}
};

#endif