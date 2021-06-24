#ifndef MAP_TILE_SPRITE_H
#define MAP_TILE_SPRITE_H

#include "MapTile.h"
#include "GameMap.h"

class TileSprite : public cocos2d::Sprite
{
private:
	int relativeX;
	int relativeY;
public:
	void setRelativeX(int relativeX) { this->relativeX = relativeX; }
	void setRelativeY(int relativeY) { this->relativeY = relativeY; }
	static cocos2d::Texture2D *EMPTY;
	static TileSprite *create();
	virtual void update(float delta);
};

#endif // !MAP_TILE_SPRITE_H
