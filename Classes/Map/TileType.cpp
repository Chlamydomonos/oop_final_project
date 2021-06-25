#include "TileType.h"
#include <regex>

using namespace std;
using namespace cocos2d;

map<string, TileType *> TileType::ALL_TILE_TYPES{};

TileType::TileType(const std::string &_name, float _hardness) : name{ _name }, hardness{ _hardness }, textures{ new Texture2D * [4] }
{
	ALL_TILE_TYPES[_name] = this;

	for (int i = 0; i < 4; i++)
		textures[i] = Director::getInstance()->getTextureCache()->addImage("assets/tiles/" + _name + "_" + to_string(i) + ".png");
}

void TileType::onTileCreated(MapTile *tile)
{

}

void TileType::onTileDestroyed(MapTile *tile)
{
}
