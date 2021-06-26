#include "MainScene.h"

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
#include "WinScene.h"

using namespace cocos2d;

bool MainScene::init()
{
    if(!Scene::init())
        return false;

	initBackGround();
	initNodes();
	initPhysics();
	initDeleteCheck();
	initWaterRenderer();
	initSlimeRenderer();
	initItems();
	initTiles();
	initMap();
	initPlayer();
	initSlimes();
	initShop();
	initHUDandBar();

    scheduleUpdate();
    return true;
}

void MainScene::initHUDandBar() {
	//Hp and Oxygen
	auto width = Director::getInstance()->getVisibleSize().width;
	auto height = Director::getInstance()->getVisibleSize().height;

	HpBar = ui::LoadingBar::create("HpBar.png");
	HpBar->setDirection(ui::LoadingBar::Direction::RIGHT);
	HpBar->setAnchorPoint(Vec2(1, 0.5));
	HpBar->setPosition(Vec2(0.98 * width, 0.81 * height));
	HpBar->setGlobalZOrder(2);
	this->addChild(HpBar);

	OxyBar = ui::LoadingBar::create("OxyBar.png");
	OxyBar->setDirection(ui::LoadingBar::Direction::RIGHT);
	OxyBar->setAnchorPoint(Vec2(1, 0.5));
	OxyBar->setPosition(Vec2(0.98 * width, 0.78 * height));
	OxyBar->setGlobalZOrder(2);
	this->addChild(OxyBar);

	//Map Index 
	MapIndex = DrawNode::create();
	MapIndex->setPosition(width * 0.93, height * 0.91);
	MapIndex->setGlobalZOrder(2);
	this->addChild(MapIndex);
}

void MainScene::update(float delta)
{
	mainNode->setPositionX(Player::GetInstance()->getPositionX() * -1 + Director::getInstance()->getWinSize().width / 2);
	mainNode->setPositionY(Player::GetInstance()->getPositionY() * -1 + Director::getInstance()->getWinSize().height / 2);
	DeleteCheck::CheckChild(this);
	if (Player::GetInstance()->getPositionX() < 0 || Player::GetInstance()->getPositionX() > 121 * 64 || Player::GetInstance()->getPositionY() < 0 || Player::GetInstance()->getPositionY() > 64000)
		Player::GetInstance()->GetBC()->getBody()->SetTransform({ 61, 505 }, 0);

	if (Slime::SLIME_BOSSES.size() == 0)
		Director::getInstance()->replaceScene(WinScene::create());

	//Update Hp and Oxygen Bar
	HpBar->setPercent((float)Player::GetInstance()->hp / Player::GetInstance()->maxHp * 100);
	OxyBar->setPercent((float)Player::GetInstance()->oxygen / Player::GetInstance()->maxOxygen * 100);
	//CCLOG("OXYGEN: %d", Player::GetInstance()->oxygen);

	//Update Map Index
	MapIndex->clear();
	int rad{ 6 };
	int x = Player::GetInstance()->GetBC()->getBody()->GetPosition().x;
	int y = Player::GetInstance()->GetBC()->getBody()->GetPosition().y;
	int max_x = GameMap::getInstance()->getWidth();
	int max_y = GameMap::getInstance()->getHeight();
	for (int i = 0; i < 16; ++i) {
		if (x + i - 8 < 0 || x + i - 8 >= max_x)
			continue;
		for (int j = 0; j < 16; ++j) {
			if (y + j - 8 < 0 || y + j - 8 >= max_y)
				continue;
			if (GameMap::getInstance()->IfTiled(x + i - 8, y + j - 8)) {
				MapIndex->drawPoint(Vec2((i - 8) * rad, (j - 8) * rad), rad, Color4F::WHITE);
			}
		}
	}
	MapIndex->drawRect(Vec2(-9.5, -9.5) * rad, Vec2(8.5, 8.5) * rad, Color4F::WHITE);
	Scene::update(delta);
}

MainScene::~MainScene()
{
	for (auto i : TileType::ALL_TILE_TYPES)
		delete i.second;
	TileType::ALL_TILE_TYPES.clear();
	for (auto i : Item::ALL_ITEMS)
		delete i.second;
	Item::ALL_ITEMS.clear();
	Player::releaseInstance();
	GameMap::releaseInstance();
	SlimeRenderer::releaseInstance();
	WaterRenderer::releaseInstance();
	Slime::SLIMES.clear();
	Slime::SLIME_BOSSES.clear();
}

void MainScene::initBackGround()
{
	auto background = Sprite::create("background.png");
	background->setAnchorPoint({ 0, 0 });
	background->setPosition(0, 0);
	background->setGlobalZOrder(-1);
	this->addChild(background);
}

void MainScene::initNodes()
{
	mainNode = Node::create();
	mainNode->setName("mainNode");
	addChild(mainNode);
	mainNode->scheduleUpdate();

	gameObjects = Node::create();
	gameObjects->setName("gameObjects");
	mainNode->addChild(gameObjects);
	gameObjects->scheduleUpdate();
}

void MainScene::initPhysics()
{
	this->addComponent(Box2DWorldComponent::create({ 0.0f, -10.0f }));
}

void MainScene::initDeleteCheck()
{
	DeleteCheck::world = dynamic_cast<Box2DWorldComponent *>(getComponent("b2World"))->getWorld();
}

void MainScene::initWaterRenderer()
{
	this->addChild(WaterRenderer::getInstance());
	WaterRenderer::getInstance()->addToWorld();
}

void MainScene::initSlimeRenderer()
{
	this->addChild(SlimeRenderer::getInstance());
	SlimeRenderer::getInstance()->addToWorld();
}

void MainScene::initItems()
{
	Item *iron = new Item("iron", 1);
	Item *gold = new Item("gold", 10);
}

void MainScene::initTiles()
{
	TileSprite::EMPTY = Director::getInstance()->getTextureCache()->addImage("empty.png");

	TileType *stone = new TileType("stone", 0.5);
	TileType *bedrock = new TileType("bedrock", -1);
	TileType *ironOre = new Ore("iron_ore", 1, Item::ALL_ITEMS["iron"]);
	TileType *goldOre = new Ore("gold_ore", 1.5, Item::ALL_ITEMS["gold"]);
	TileType *waterEmitter = new WaterEmitterTile();
}

void MainScene::initMap()
{
	TileType *stone = TileType::ALL_TILE_TYPES["stone"];
	TileType *bedrock = TileType::ALL_TILE_TYPES["bedrock"];
	TileType *ironOre = TileType::ALL_TILE_TYPES["iron_ore"];
	TileType *goldOre = TileType::ALL_TILE_TYPES["gold_ore"];
	WaterEmitterTile *waterEmitter = dynamic_cast<WaterEmitterTile*>(TileType::ALL_TILE_TYPES["water_emitter"]);

	GameMap::initInstance(GameMap::create(121, 500));
	gameObjects->addChild(GameMap::getInstance());
	GameMap::getInstance()->addToWorld();

	FILE *file = fopen(FileUtils::getInstance()->fullPathForFilename("mapDef.txt").c_str(), "r");
	char temp;
	for (int j = 499; j >= 0; j--)
	{
		for (int i = 0; i < 121; i++)
		{
			temp = fgetc(file);
			if (temp == '1')
				GameMap::getInstance()->createTile(stone, i, j);
			else if (temp == '2')
				GameMap::getInstance()->createTile(bedrock, i, j);
			else if (temp == '3')
				GameMap::getInstance()->createTile(ironOre, i, j);
			else if (temp == '4')
				GameMap::getInstance()->createTile(goldOre, i, j);
			else if (temp == '5')
				GameMap::getInstance()->createTile(waterEmitter, i, j);
		}
	}
	fclose(file);

	waterEmitter->initEmitters(gameObjects);
}

void MainScene::initPlayer()
{
	gameObjects->addChild(Player::GetInstance());
	Player::GetInstance()->GetBC()->addToWorld();
	Player::GetInstance()->GetBC()->getBody()->SetFixedRotation(true);
	Player::GetInstance()->GetBC()->getBody()->SetUserData(Player::GetInstance());
	Player::GetInstance()->GetBC()->getBody()->SetTransform({ 61, 505 }, 0);

	gameObjects->addComponent(PlayerController::create());

	auto contact_listener = new PlayerContact();
	dynamic_cast<Box2DWorldComponent *>(getComponent("b2World"))->getWorld()->SetContactListener(contact_listener);
}

void MainScene::initSlimes()
{
	auto slime = Slime::create(4, 61, 18, true);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 66, 33, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 28, 42, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 88, 46, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 44, 69, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 70, 89, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 99, 97, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 40, 106, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 89, 121, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 57, 136, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 89, 147, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 39, 170, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 84, 171, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 65, 184, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 32, 194, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 103, 194, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 83, 204, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 40, 209, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(1, 69, 217, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 93, 238, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 49, 246, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 25, 263, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 70, 274, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 93, 296, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 30, 310, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 85, 334, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 36, 355, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 59, 380, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 101, 397, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 32, 406, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 83, 420, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 58, 424, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 41, 447, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 91, 458, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 95, 476, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
	slime = Slime::create(0.5, 39, 486, false);
	gameObjects->addChild(slime);
	slime->addToWorld();
}

void MainScene::initShop()
{
	auto shopIco = shop_icon::create(61, 500);
	gameObjects->addChild(shopIco);
}
