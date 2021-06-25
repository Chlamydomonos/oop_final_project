#ifndef MAP_TILE_TYPE_H
#define MAP_TILE_TYPE_H

#include <cocos2d.h>

#include <string>
#include <map>

class MapTile;

class TileType
{
private:
	std::string name;
	cocos2d::Texture2D **textures;
	float hardness;
public:
	const std::string &getName() const { return name; }
	cocos2d::Texture2D **getTextures() const { return textures; }
	float getHardness() const { return hardness; }
	static std::map<std::string, TileType *> ALL_TILE_TYPES;
	TileType(const std::string &_name, float _hardness);
	virtual ~TileType() { delete[] textures; }
	virtual void onTileCreated(MapTile* tile);
	virtual void onTileDestroyed(MapTile *tile);
};

#endif