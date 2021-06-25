#include "TestMapScene.h"

#include "ui/CocosGUI.h"
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

	Item *iron = new Item("iron", 1);
	TileType *stone = new TileType("stone", 0.5);
	TileType *ironOre = new Ore("iron_ore", 1, iron);
	TileType *bedrock = new TileType("bedrock", -1);
	WaterEmitterTile *waterEmitter = new WaterEmitterTile();

	gameMap = GameMap::create(100, 100);
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

	auto slime = Slime::create(4, 8, 8, false);
	gameObjects->addChild(slime);
	slime->addToWorld();

	auto shopIco = shop_icon::create(4,8);
	gameObjects->addChild(shopIco);



	//Hp and Oxygen
	auto width = Director::getInstance()->getVisibleSize().width;
	auto height = Director::getInstance()->getVisibleSize().height;

	HpBar = ui::LoadingBar::create("HpBar.png");
	HpBar->setDirection(ui::LoadingBar::Direction::RIGHT);
	HpBar->setAnchorPoint(Vec2(1, 0.5));
	HpBar->setPosition(Vec2(0.98 * width, 0.81 * height));
	this->addChild(HpBar);

	OxyBar = ui::LoadingBar::create("OxyBar.png");
	OxyBar->setDirection(ui::LoadingBar::Direction::RIGHT);
	OxyBar->setAnchorPoint(Vec2(1, 0.5));
	OxyBar->setPosition(Vec2(0.98 * width, 0.78 * height));
	this->addChild(OxyBar);
	


	//Map Index 
	MapIndex = DrawNode::create();
	MapIndex->setPosition(width * 0.93, height * 0.91);
	this->addChild(MapIndex);

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

	//Update Hp and Oxygen Bar
	HpBar->setPercent(Player::GetInstance()->hp / Player::GetInstance()->maxHp * 100);
	OxyBar->setPercent(Player::GetInstance()->oxygen / Player::GetInstance()->maxOxygen * 100);
	Scene::update(delta);
	
	//Update Map Index
	MapIndex->clear();
	int rad{ 6 };
		int x = Player::GetInstance()->GetBC()->getBody()->GetPosition().x;
	int y = Player::GetInstance()->GetBC()->getBody()->GetPosition().y;
	//MapIndex->drawDot(Vec2(-0.5, -0.5) * rad, rad / 2, Color4F::RED); //Index the player
	for (int i = 0; i < 16; ++i) {
		if (x + i - 8 < 0)
			continue;
		for (int j = 0; j < 16; ++j) {
			if (y + j - 8 < 0)
				continue;
			if (gameMap->IfTiled(x + i - 8, y + j - 8)) {
				MapIndex->drawPoint(Vec2((i - 8) * rad, (j - 8) * rad), rad, Color4F::WHITE);
			}
		}
	}
	MapIndex->drawRect(Vec2(-9.5, -9.5) * rad, Vec2(8.5, 8.5) * rad, Color4F::WHITE);
}

TestMapScene::~TestMapScene()
{
	delete TileType::ALL_TILE_TYPES["stone"];
	delete TileType::ALL_TILE_TYPES["iron_ore"];
	delete TileType::ALL_TILE_TYPES["bedrock"];
	delete TileType::ALL_TILE_TYPES["water_emitter"];
	delete Item::ALL_ITEMS["iron"];
}
