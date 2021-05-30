#include "Tile.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Utils/VectorConversion.h"

#define BREAK_FACTOR 1

Tile* Tile::create(TileType *type, int x, int y)
{
    auto tile = new (std::nothrow) Tile();
    if (tile && tile->initWithSpriteFrameName(type->getName()))
    {
        tile->autorelease();

        tile->type = type;
        tile->x = x;
        tile->y = y;

        b2BodyDef fileDef;
        fileDef.position.Set(x, y);

        b2PolygonShape staticBox;
        staticBox.SetAsBox(0.5f, 0.5f);

        b2FixtureDef fileFixtureDef;
        fileFixtureDef.shape = &staticBox;

        tile->body = Box2DBodyComponent::create(&fileDef, &fileFixtureDef);
        tile->addComponent(tile->body);

        return tile;
    }
    else
        CC_SAFE_DELETE(tile);

    return nullptr;
}

void Tile::addToMap()
{
    body->addToWorld();
    map = dynamic_cast<Map*>(getParent());
}

void Tile::breakBy(int force)
{
    if (breakProcess == 0xffffff && force > 0)
    {
        //TODO
    }

    if (breakProcess < force * BREAK_FACTOR)
    {
        breakProcess = 0;
        map->onTileBroken(x, y);
    }

    breakProcess -= force * BREAK_FACTOR;

}
