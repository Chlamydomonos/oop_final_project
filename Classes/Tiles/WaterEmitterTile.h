#ifndef TILES_WATER_EMITTER_TILE_H
#define TILES_WATER_EMITTER_TILE_H

#include "../Map/TileType.h"
#include "../Water/WaterEmitter.h"

class WaterEmitterTile : public TileType
{
private:
	static std::map<std::pair<int, int>, WaterEmitter *> EMITTERS;
public:
	WaterEmitterTile() : TileType{ "water_emitter" , 0.5f} {}
	virtual void onTileCreated(MapTile *tile);
	virtual void onTileDestroyed(MapTile *tile);
	void initEmitters(cocos2d::Node *parent);
};

#endif // !TILES_WATER_EMITTER_TILE_H
