#ifndef MAP_TILETYPE_H
#define MAP_TILETYPE_H

#include <string>
#include <cocos2d.h>
#include <map>

class Tile;

class TileType
{
private:
	std::string _name;
	int _hardness;

public:
	TileType(const std::string &name, int hardness);
	static std::map<std::string, TileType *> ALL_TILES;

	std::string getName() const { return _name; }
	int getHardness() { return _hardness; }

	virtual void onBroken(Tile *tile);
};

#endif