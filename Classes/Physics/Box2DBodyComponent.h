#ifndef PHYSICS_BOX_2D_BODY_COMPONENT_H
#define PHYSICS_BOX_2D_BODY_COMPONENT_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

/**
* @brief 用于Sprite的物理刚体组件。
* 
* 基于Box2D中的刚体。为Sprite添加该组件时Sprite
* 应该至少有一个上级对象拥有Box2DWorldComponent，
* 否则会抛出异常。该组件的内存会自动释放。
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
	* 需要手动删除bodyDef和fixtureDef两个变量，并
	* 确保它们存活到该组件被添加到Sprite。
	*/
	static Box2DBodyComponent *create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef);

	virtual ~Box2DBodyComponent(){}

	virtual void onAdd();
	virtual void update(float delta);
};

#endif