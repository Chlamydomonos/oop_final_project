#ifndef SCENES_TESTITEM_H
#define SCENES_TESTITEM_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

#include "../Classes/Item/ItemStackSprite.h"

class TestItem : public cocos2d::Scene
{
public:
	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(TestItem);

	virtual ~TestItem() {};
private:
	ItemStackSprite* item;
};

#endif
