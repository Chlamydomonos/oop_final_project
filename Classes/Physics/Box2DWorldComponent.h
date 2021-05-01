#ifndef PHYSICS_BOX_2D_WORLD_COMPONENT_H
#define PHYSICS_BOX_2D_WORLD_COMPONENT_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "../Exception/Exception.h"

/**
* @brief ����Scene������ռ����
* 
* ע�⣬��Ӹ�����ĳ�������ʹ��
* scheduleUpdate()��������֡ģ��
*/
class Box2DWorldComponent : public cocos2d::Component
{
private:
	b2World *world;

public:

	/**
	* @brief ��Ҫʹ�ô˹��캯����
	* 
	* ʹ��create���������Զ��ͷ��ڴ档
	*/
	Box2DWorldComponent() :
		cocos2d::Component{},
		world{ nullptr } {}

	virtual ~Box2DWorldComponent()
	{
		delete world;
	}

	static Box2DWorldComponent *create(const b2Vec2 &gravity);

	b2World *getWorld()
	{
		return world;
	}

	virtual void update(float delta);
};

#endif