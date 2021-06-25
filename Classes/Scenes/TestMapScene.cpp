#include "TestMapScene.h"

#include "../Map/GameMap.h"
#include "../Map/MapTile.h"
#include "../Map/TileSprite.h"
#include "../Map/TileType.h"
#include "../Player/Player.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Player/PlayerController.h"
#include "../Player/PlayerContact.h"
#include "../Slime/SlimeRenderer.h"
#include "../Slime/Slime.h"
#include "../Tiles/Ore.h"
#include "../Item/Item.h"
#include "../Items/shop_icon.h"
#include "../Utils/DeleteCheck.h"
#include "../Water/WaterRenderer.h"
#include "../Tiles/WaterEmitterTile.h"

using namespace cocos2d;

bool TestMapScene::init()
{
	maxDelta = 0.0f;

	mainNode = Node::create();
	mainNode->setName("mainNode");
	addChild(mainNode);
	mainNode->scheduleUpdate();

	auto gameObjects = Node::create();
	gameObjects->setName("gameObjects");
	mainNode->addChild(gameObjects);
	gameObjects->scheduleUpdate();

	TileSprite::EMPTY = Director::getInstance()->getTextureCache()->addImage("empty.png");
	this->addComponent(Box2DWorldComponent::create({ 0.0f, -10.0f }));

	this->addChild(WaterRenderer::getInstance());
	WaterRenderer::getInstance()->addToWorld();
	
	DeleteCheck::world = dynamic_cast<Box2DWorldComponent *>(getComponent("b2World"))->getWorld();

	Item *iron = new Item("iron");
	TileType *stone = new TileType("stone", 0.5);
	TileType *ironOre = new Ore("iron_ore", 1, iron);
	TileType *bedrock = new TileType("bedrock", -1);
	WaterEmitterTile *waterEmitter = new WaterEmitterTile();

	GameMap *gameMap = GameMap::create(100, 100);
	GameMap::initInstance(gameMap);
	gameObjects->addChild(gameMap);
	gameMap->addToWorld();
	for (int i = 0; i < 100; i++)
	{
		gameMap->createTile(bedrock, i, 0);
		gameMap->createTile(bedrock, i, 99);
	}
	for (int i = 1; i < 99; i++)
	{
		gameMap->createTile(bedrock, 0, i);
		gameMap->createTile(bedrock, 99, i);
	}
	for (int i = 1; i < 30; i++)
	{
		gameMap->createTile(i == 20 ? waterEmitter : stone, i, 1);
	}
	for (int i = 1; i < 29; i++)
		gameMap->createTile(stone, i, 2);
	for (int i = 1; i < 28; i++)
		gameMap->createTile(stone, i, 3);
	for (int i = 31; i < 40; i++)
		gameMap->createTile(ironOre, i, 1);

	waterEmitter->initEmitters(gameObjects);

	gameObjects->addChild(Player::GetInstance());
	Player::GetInstance()->GetBC()->addToWorld();
	Player::GetInstance()->GetBC()->getBody()->SetFixedRotation(true);
	Player::GetInstance()->GetBC()->getBody()->SetUserData(Player::GetInstance());

	gameObjects->addComponent(PlayerController::create());

	this->addChild(SlimeRenderer::getInstance());
	SlimeRenderer::getInstance()->addToWorld();

	auto contact_listener = new PlayerContact();
	dynamic_cast<Box2DWorldComponent*>(getComponent("b2World"))->getWorld()->SetContactListener(contact_listener);

	auto slime = Slime::create(4, 8, 8);
	gameObjects->addChild(slime);
	slime->addToWorld();

	auto shopIco = shop_icon::create(4,4);
	gameObjects->addChild(shopIco);

	scheduleUpdate();
	return true;
}

void TestMapScene::update(float delta)
{
	if (delta > maxDelta)
	{
		maxDelta = delta;
		CCLOG("Max delta: %f", maxDelta);
	}
	mainNode->setPositionX(Player::GetInstance()->getPositionX() * -1 + Director::getInstance()->getWinSize().width / 2);
	mainNode->setPositionY(Player::GetInstance()->getPositionY() * -1 + Director::getInstance()->getWinSize().height / 2);
	DeleteCheck::CheckChild(this);
	Scene::update(delta);
	
}

TestMapScene::~TestMapScene()
{
	delete TileType::ALL_TILE_TYPES["stone"];
	delete TileType::ALL_TILE_TYPES["iron_ore"];
	delete TileType::ALL_TILE_TYPES["bedrock"];
	delete TileType::ALL_TILE_TYPES["water_emitter"];
	delete Item::ALL_ITEMS["iron"];
}
