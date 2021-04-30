#ifndef PHYSICS_BOX_2D_BODY_COMPONENT_H
#define PHYSICS_BOX_2D_BODY_COMPONENT_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

/**
* @brief ����Sprite��������������
* 
* ����Box2D�еĸ��塣ΪSprite��Ӹ����ʱSprite
* Ӧ��������һ���ϼ�����ӵ��Box2DWorldComponent��
* ������׳��쳣����������ڴ���Զ��ͷš�
*/
class Box2DBodyComponent : public cocos2d::Component
{
private:
	b2Body *body;
	b2BodyDef *bodyDef;
	b2FixtureDef *fixtureDef;

public:

	/**
	* @brief ��Ҫʹ�ô˹��캯����
	* 
	* ʹ��create���������Զ��ͷ��ڴ档
	*/
	Box2DBodyComponent() :
		cocos2d::Component{},
		body{ nullptr },
		bodyDef{ nullptr },
		fixtureDef{ nullptr } {}

	/**
	* @brief ��Box2D�ı�׼��ʽ����һ��������������
	* 
	* ��Ҫ�ֶ�ɾ��bodyDef��fixtureDef������������
	* ȷ�����Ǵ����������ӵ�Sprite��
	*/
	static Box2DBodyComponent *create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef);

	virtual ~Box2DBodyComponent(){}

	virtual void onAdd();
	virtual void update(float delta);
};

#endif