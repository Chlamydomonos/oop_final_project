//#pragma once
#ifndef MAP_MAP_H
#define MAP_MAP_H

#include "TileType.h"
#include <cocos2d.h>

class Tile;

class Map : public cocos2d::Node
{
private:
	int width; // 共width列
	int height; // 共height行
	Tile*** tiles;
public:
	Map() : width{ 0 }, height{ 0 }, tiles{ nullptr } {}

	CREATE_FUNC(Map);

	void initialLoad(const std::string &name);

	void onTileBroken(int x, int y);
};

#endif