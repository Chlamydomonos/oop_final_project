//#pragma once
#ifndef MAP_MAP_H
#define MAP_MAP_H

#include "Tile.h"
#include "TileType.h"

class Map
{
private:
	int width; // 共width列
	int height; // 共height行
	Tile*** tiles;
public:
	Map(int w, int h, TileType** tiletype, float x_start, float y_start) :width{ w }, height{ h }
	{
		Tile*** tiles = new Tile * *[h];
		for (int i = 0; i < h; i++)
			tiles[i] = new Tile * [w];
		for(int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				tiles[i][j]->setTileType(tiletype[i][j]);
				tiles[i][j]->setX(x_start + j * 1.0);
				tiles[i][j]->setY(y_start + i * 1.0);
			}
	}
	~Map()
	{
		for (int i = 0; i < height; i++)
			delete[] tiles[i];
		delete[] tiles;
	}
};

#endif