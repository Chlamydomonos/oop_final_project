#include "Map.h"
#include "Tile.h"
#include <json/rapidjson.h>
#include <json/document.h>
#include <json/filereadstream.h>
#include <cstdio>

void Map::initialLoad(const std::string &name)
{
    std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(name);
    FILE *jsonFile = fopen(path.c_str(), "r");
    char *readBuffer = new char[65536];
    rapidjson::FileReadStream jsonStream(jsonFile, readBuffer, 65536);
    rapidjson::Document json;
    json.ParseStream(jsonStream);

    width = json["width"].GetInt();
    height = json["height"].GetInt();

    auto temp = new Tile * [width * height];
    tiles = new Tile * *[width];

    for (int i = 0; i < width; i++)
        tiles[i] = temp + i * height;

    auto tileArray = json["tiles"].GetArray();

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            std::string tileName = tileArray[i].GetArray()[j].GetString();
            if (tileName != "null")
            {
                tiles[i][j] = Tile::create(TileType::ALL_TILES[tileName], i, j);
                addChild(tiles[i][j]);
                tiles[i][j]->addToMap();
            }
            else
                tiles[i][j] = nullptr;
        }
}

void Map::onTileBroken(int x, int y)
{
    tiles[x][y]->onBroken();
    tiles[x][y]->removeFromParent();
    CC_SAFE_DELETE(tiles[x][y]);
}
