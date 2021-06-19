#ifndef PHYSICS_BOX_2D_BODY_COMPONENT_H
#define PHYSICS_BOX_2D_BODY_COMPONENT_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

/**
* @brief ����Sprite��������������
* 
* ����Box2D�еĸ��塣��ӵ�и������
* Sprite����ӵ��Box2DWorldComponent
* �ĳ���ʱ����Ҫ�ֶ�����addToWorld
* ��������������ģ�⡣
* 
* �����������Ϊb2Body����ֱ����
* getComponent("b2Body")��ȡ��
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
	* ���������bodyDef��fixtureDef���ᱻ�ͷš�
	*/
	static Box2DBodyComponent *create(b2BodyDef *bodyDef, b2FixtureDef *fixtureDef);

	virtual ~Box2DBodyComponent();

	virtual void update(float delta);

	/**
	* @brief �������ӽ�����ռ䡣
	* 
	* @attention ���øú���ʱ�����뱣֤���ӵ����
	* �Ѿ�λ�ھ���Box2DWorldComponent�ĳ����У�
	* ������׳��쳣��
	*/
	void addToWorld();

	/**
	* @brief ��ȡʵ�ʵ�b2Body��
	* 
	* @attention ��Ҫdelete���ص�b2Body��
	*/
	b2Body *getBody()
	{
		return body;
	}
};

#endif