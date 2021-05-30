//#pragma once
#ifndef MAP_TILE_H
#define MAP_TILE_H

#include <cocos2d.h>
#include "TileType.h"
#include "../Physics/Box2DBodyComponent.h"
#include "Map.h"

class Tile : public cocos2d::Sprite
{
private:
	TileType *type;
	unsigned int breakProcess;
	Box2DBodyComponent *body;
	cocos2d::Sprite *breakSprite;
	Map *map;
	int x;
	int y;

public:
	Tile(): 
		type{ nullptr }, 
		breakProcess{ 0xffffffff }, 
		body{ nullptr }, 
		breakSprite{ nullptr }, 
		map{ nullptr }, 
		x{ 0 }, 
		y{0}{}

	static Tile *create(TileType *type, int x, int y);

	int getBreakProcess() { return breakProcess; }

	Box2DBodyComponent *getBodyComponent() { return body; }
	void addToMap();

	void breakBy(int force);

	void onBroken() {}
};

#endif