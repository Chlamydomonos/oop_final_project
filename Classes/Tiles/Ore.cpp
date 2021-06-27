#include "Ore.h"
#include "../Item/Item.h"
#include "../Item/ItemStack.h"
#include "../Item/ItemStackSprite.h"
#include "../Map/MapTile.h"
#include "../Map/GameMap.h"

void Ore::onTileDestroyed(MapTile *tile)
{
	auto sprite = ItemStackSprite::create(item, 1, tile->getX(), tile->getY());
	GameMap::getInstance()->getParent()->addChild(sprite);
	GameMap::getInstance()->scheduleOnce([=](float) {
			sprite->GetBodyComponent()->addToWorld();
			sprite->GetBodyComponent()->getBody()->SetUserData(sprite);
		},
		0.05f,
		"dropItem"
	);
}
