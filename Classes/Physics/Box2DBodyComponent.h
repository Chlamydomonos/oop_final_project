#ifndef PHYSICS_BOX_2D_BODY_COMPONENT_H
#define PHYSICS_BOX_2D_BODY_COMPONENT_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

/**
* @brief 用于Sprite的物理刚体组件。
* 
* 基于Box2D中的刚体。当拥有该组件的
* Sprite进入拥有Box2DWorldComponent
* 的场景时，需要手动调用addToWorld
* 函数来开启物理模拟。
* 
* 该组件的名称为b2Body，可直接用
* getComponent("b2Body")获取。
*/
class Box2DBodyComponent : public cocos2d::Component
{
private:
	b2Body *body;
	b2BodyDef *bodyDef;
	b2FixtureDef *fixtureDef;

public:

	/**
	* @brief 不要使用此构造函数。
	* 
	* 使用create函数可以自动释放内存。
	*/
	Box2DBodyComponent() :
		cocos2d::Component{},
		body{ nullptr },
		bodyDef{ nullptr },
		fixtureDef{ nullptr } {}

	/**
	* @brief 以Box2D的标准方式创建一个物理刚体组件。
	* 
	* 组件创建后，bodyDef与fixtureDef不会被释放。
	*/
	static Box2DBodyComponent *create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef);

	virtual ~Box2DBodyComponent();

	virtual void update(float delta);

	/**
	* @brief 把组件添加进物理空间。
	* 
	* @attention 调用该函数时，必须保证组件拥有者
	* 已经位于具有Box2DWorldComponent的场景中，
	* 否则会抛出异常。
	*/
	void addToWorld();

	/**
	* @brief 获取实际的b2Body。
	* 
	* @attention 不要delete返回的b2Body！
	*/
	b2Body *getBody()
	{
		return body;
	}
};

#endif