#ifndef MAP_MAP_TILE_H
#define MAP_MAP_TILE_H

#include <Box2D/Box2D.h>
#include "TileType.h"

class GameMap;

class MapTile
{
private:
	TileType *type;
	int x;
	int y;
	int destroyStatus;
	GameMap *map;
	b2Body *body;
public:
	MapTile(TileType *_type, int _x, int _y, GameMap *_map);
	~MapTile();
	TileType *getType() const { return type; }
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	b2Vec2 getPosition() const { return b2Vec2(x, y); }
	void setPosition(b2Vec2 position)
	{
		x = position.x;
		y = position.y;
	}
	int getDestroyStatus() const { return destroyStatus; }
	void setDestroyStatus(int destroyStatus);
	void destroyByForce(int force);
	void onDestroyStatusChanged();
	cocos2d::Texture2D *getTexture();
};

#endif // !MAP_TILE_H
