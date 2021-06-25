#include "Ore.h"
#include "../Item/Item.h"
#include "../Item/ItemStack.h"
#include "../Item/ItemStackSprite.h"
#include "../Map/MapTile.h"
#include "../Map/GameMap.h"

void Ore::onTileDestroyed(MapTile *tile)
{
	auto sprite = ItemStackSprite::create(item, 1, tile->getX(), tile->getY() + 1);
	GameMap::getInstance()->getParent()->addChild(sprite);
	sprite->GetBodyComponent()->addToWorld();
	sprite->GetBodyComponent()->getBody()->SetUserData(sprite);
}
