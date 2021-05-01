#include "Tile.h"
#include "../Physics/Box2DBodyComponent.h"

Tile* Tile::create(TileType* type)
{
    auto tile = new (std::nothrow) Tile();
    tile->tileType = type;
    if (tile && tile->initWithFile(type->getImageName()))
    {
        tile->autorelease();
        b2BodyDef fileDef;
        fileDef.position.Set(tile->getX(), tile->getY());

        b2PolygonShape staticBox;
        staticBox.SetAsBox(1.0f, 1.0f);

        b2FixtureDef fileFixtureDef;
        fileFixtureDef.shape = &staticBox;

        auto mapComponent = Box2DBodyComponent::create(&fileDef, &fileFixtureDef);
        tile->addComponent(mapComponent);
        mapComponent->addToWorld();
        return tile;
    }
    else
        CC_SAFE_DELETE(tile);

    return nullptr;
}
