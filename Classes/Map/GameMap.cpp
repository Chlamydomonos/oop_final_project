#include "GameMap.h"
#include "TileSprite.h"
#include "../Physics/Box2DWorldComponent.h"

using namespace std;
using namespace cocos2d;

GameMap::~GameMap()
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            delete tiles[i][j];
    delete[] (*tiles);
    delete[] tiles;
}

GameMap *GameMap::create(int width, int height)
{
    GameMap *ret = new (std::nothrow) GameMap();
    if (ret)
    {
        ret->autorelease();
        ret->width = width;
        ret->height = height;
        MapTile **tiles = new MapTile * [width * height];
        MapTile ***temp = new MapTile * *[width];
        ret->tiles = temp;
        for (int i = 0; i < width; i++)
            temp[i] = tiles + i * height;
        for (int i = 0; i < width * height; i++)
            tiles[i] = nullptr;

        int screenWidth = Director::getInstance()->getWinSize().width;
        int screenHeight = Director::getInstance()->getWinSize().height;
        int spritesWidth = screenWidth / 64 + 5;
        int spritesHeight = screenHeight / 64 + 5;
        Sprite **sprites = new Sprite * [spritesWidth * spritesHeight];
        Sprite ***temp2 = new Sprite * *[spritesWidth];
        for (int i = 0; i < spritesWidth; i++)
            temp2[i] = sprites + i * spritesHeight;
        ret->sprites = temp2;

        for (int i = 0; i < spritesWidth; i++)
        {
            for (int j = 0; j < spritesHeight; j++)
            {
                auto sp = TileSprite::create();
                sp->setRelativeX(i - spritesWidth / 2);
                sp->setRelativeY(j - spritesHeight / 2);
                temp2[i][j] = sp;
                ret->addChild(sp);
                sp->scheduleUpdate();
            }
        }
    }

    return ret;
}

MapTile *GameMap::getTile(int x, int y)
{
    if(x >= 0 && x < width && y >= 0 && y < height)
        return tiles[x][y];
    return nullptr;
}

void GameMap::createTile(TileType *type, int x, int y)
{
    MapTile *tile = new MapTile(type, x, y, this);
    tiles[x][y] = tile;
    tile->getType()->onTileCreated(tile);
}

void GameMap::onTileDestroyStatusChanged(MapTile *tile)
{
    if (tile->getDestroyStatus() <= 0)
    {
        tile->getType()->onTileDestroyed(tile);
        tiles[tile->getX()][tile->getY()] = nullptr;
        delete tile;
    }
}

void GameMap::addToWorld()
{
    Node *node = this->getParent();
    auto cp = node->getComponent("b2World");

    while (cp == nullptr && node != nullptr)
    {
        cp = node->getComponent("b2World");
        node = node->getParent();
    }

    if (cp == nullptr)
        throw 1;

    auto wcp = dynamic_cast<Box2DWorldComponent *>(cp);
    this->world = wcp->getWorld();
}
