#include "WaterEmitterTile.h"
#include "../Map/MapTile.h"
#include "../Utils/VectorConversion.h"

std::map<std::pair<int, int>, WaterEmitter *> WaterEmitterTile::EMITTERS{};

void WaterEmitterTile::onTileCreated(MapTile *tile)
{
	WaterEmitter *emitter = WaterEmitter::create();
	emitter->setPosition(p2r(tile->getPosition()));
	EMITTERS[{tile->getX(), tile->getY()}] = emitter;
}

void WaterEmitterTile::onTileDestroyed(MapTile *tile)
{
	EMITTERS[{tile->getX(), tile->getY()}]->emit(10);
}

void WaterEmitterTile::initEmitters(cocos2d::Node *parent)
{
	for (auto i : EMITTERS)
	{
		parent->addChild(i.second);
	}
}
