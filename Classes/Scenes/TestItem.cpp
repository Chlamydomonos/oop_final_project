#include "TestItem.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"


bool TestItem::init() {
	if (!Scene::init())
		return false;

	this->addComponent(Box2DWorldComponent::create(b2Vec2(0.0f, -10.0f)));

	item = ItemStackSprite::create("testsprite");

	item->GetBodyComponent()->addToWorld();

	scheduleUpdate();

	return true;
}


void TestItem::update(float delta)
{
	Scene::update(delta);
}