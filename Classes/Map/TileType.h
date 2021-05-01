#ifndef MAP_TILETYPE_H
#define MAP_TILETYPE_H

#include <string>

class TileType
{
private:
	std::string imageName;
	std::string tileName;
public:
	TileType(std::string image_name, std::string tile_name) : imageName{ image_name }, tileName{ tile_name }
	{}
	~TileType(){}
	std::string getImageName() const{ return imageName; }
	std::string getTileName() const { return tileName; }
};

#endif