#ifndef TILES_ORE_H
#define TILES_ORE_H

#include "../Map/TileType.h"
#include "../Item/Item.h"

class Ore : public TileType
{
public:
	Ore(const std::string &name, int hardness, Item *_item) : TileType{ name, hardness }, item{ _item }{}
	virtual void onTileDestroyed(MapTile *tile);
private:
	Item *item;
};

#endif // !TILES_ORE_H
