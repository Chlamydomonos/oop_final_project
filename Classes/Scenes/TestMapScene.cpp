#include "TestMapScene.h"

#include "../Map/GameMap.h"
#include "../Map/MapTile.h"
#include "../Map/TileSprite.h"
#include "../Map/TileType.h"
#include "../Player/Player.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Player/PlayerController.h"

using namespace cocos2d;

bool TestMapScene::init()
{
	TileSprite::EMPTY = Director::getInstance()->getTextureCache()->addImage("empty.png");
	this->addComponent(Box2DWorldComponent::create({ 0.0f, -10.0f }));
	TileType *stone = new TileType("stone", 1);
	GameMap *gameMap = GameMap::create(100, 100);
	this->addChild(gameMap);
	gameMap->addToWorld();
	for (int i = 0; i < 100; i++)
		gameMap->createTile(stone, i, 0);
	this->addChild(Player::GetInstance());
	Player::GetInstance()->GetBC()->addToWorld();
	Player::GetInstance()->GetBC()->getBody()->SetFixedRotation(true);

	this->addComponent(PlayerController::create());

	scheduleUpdate();
	return true;
}

void TestMapScene::update(float delta)
{
	this->setPositionX(Player::GetInstance()->getPositionX() * -1 + Director::getInstance()->getWinSize().width / 2);
	this->setPositionY(Player::GetInstance()->getPositionY() * -1 + Director::getInstance()->getWinSize().height / 2);
	Scene::update(delta);
}

TestMapScene::~TestMapScene()
{
	delete TileType::ALL_TILE_TYPES["stone"];
}
