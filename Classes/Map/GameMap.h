#ifndef MAP_GAME_MAP_H
#define MAP_GAME_MAP_H

#include "TileType.h"
#include "MapTile.h"

class GameMap : public cocos2d::Node
{
private:
	int width;
	int height;
	MapTile ***tiles;
	cocos2d::Sprite ***sprites;
	b2World *world;
public:
	GameMap(): 
		width{ 0 }, 
		height{ 0 }, 
		tiles{ nullptr }, 
		sprites{nullptr}, 
		world{ nullptr }{}
	~GameMap();
	static GameMap *create(int width, int height);
	MapTile *getTile(int x, int y);
	MapTile *getTile(b2Vec2 position) { return getTile(position.x, position.y); }
	void createTile(TileType *type, int x, int y);
	void onTileDestroyStatusChanged(MapTile *tile);
	b2World *getWorld() { return world; }
	void addToWorld();
};

#endif // !MAP_GAME_MAP_H
