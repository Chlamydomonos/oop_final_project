#include "TestItem.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"


bool TestItem::init() {
	if (!Scene::init())
		return false;

	this->addComponent(Box2DWorldComponent::create(b2Vec2(0.0f, -10.0f)));

	//item = ItemStackSprite::create();

	//this->addChild(item);

	//item->GetBodyComponent()->addToWorld();

	item->GetBodyComponent()->getBody()->SetTransform(b2Vec2(5, 5), 0.0f);

	scheduleUpdate();

	return true;
}


void TestItem::update(float delta)
{
	Scene::update(delta);
}