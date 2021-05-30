#include "TileType.h"
#include "Tile.h"

using namespace std;

map<string, TileType *> TileType::ALL_TILES{};

TileType::TileType(const std::string &name, int hardness) : _name{name}, _hardness{hardness}
{
	ALL_TILES.insert({ name, this });
	auto frame = cocos2d::SpriteFrame::create("assets/tiles" + name + ".png", cocos2d::Rect{ 0, 0, 32, 32 });
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, name);
}

void TileType::onBroken(Tile *tile)
{
}
