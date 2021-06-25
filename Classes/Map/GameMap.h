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
	static GameMap *instance;
	bool destroyed;
public:
	GameMap(): 
		width{ 0 }, 
		height{ 0 }, 
		tiles{ nullptr }, 
		sprites{nullptr}, 
		world{ nullptr },
		destroyed{ false }{}
	~GameMap();
	static GameMap *create(int width, int height);

	static GameMap *getInstance() { return instance; }
	static void initInstance(GameMap *map)
	{
		if(!instance)
			instance = map; 
	}
	static void releaseInstance() { instance = nullptr; }

	MapTile *getTile(int x, int y);
	MapTile *getTile(b2Vec2 position) { return getTile(position.x, position.y); }
	void createTile(TileType *type, int x, int y);
	void onTileDestroyStatusChanged(MapTile *tile);
	b2World *getWorld() { return world; }
	void addToWorld();
	bool getDestroyed() { return destroyed; }
	void destroyTileByForce(int x, int y, int force)
	{
		if (getTile(x, y))
			getTile(x, y)->destroyByForce(force);
	}
};

#endif // !MAP_GAME_MAP_H
