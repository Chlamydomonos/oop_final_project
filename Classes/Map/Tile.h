//#pragma once
#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "cocos2d.h"
#include "TileType.h"

class Tile : public cocos2d::Sprite
{
private:
	TileType* tileType;
	float xCenterPlace;
	float yCenterPlace;
public:
	Tile() : tileType{ nullptr }, xCenterPlace{ 0 }, yCenterPlace{ 0 } {}
	Tile(float x, float y): tileType{nullptr}, xCenterPlace{x}, yCenterPlace{y} {}
	float getX() const { return xCenterPlace; }
	float getY() const { return yCenterPlace; }
	void setTileType(TileType tiletype) { tileType = &tiletype; }
	void setX(float x) { xCenterPlace = x; }
	void setY(float y) { yCenterPlace = y; }
	static Tile* create(TileType* type);
	~Tile(){}
};

#endif