#include "MapTile.h"
#include "GameMap.h"

MapTile::MapTile(TileType *_type, int _x, int _y, GameMap *_map):
type { _type },
x{ _x },
y{ _y },
destroyStatus{ 0x10000 },
map{ _map },
body{ nullptr }
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(_x, _y);

	b2PolygonShape box;
	box.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	body = _map->getWorld()->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}

MapTile::~MapTile()
{
	map->getWorld()->DestroyBody(body);
}

void MapTile::setDestroyStatus(int destroyStatus)
{
	this->destroyStatus = destroyStatus;
	onDestroyStatusChanged();
}

void MapTile::destroyByForce(int force)
{
	this->destroyStatus -= force / type->getHardness();
	onDestroyStatusChanged();
}

void MapTile::onDestroyStatusChanged()
{
	map->onTileDestroyStatusChanged(this);
}

cocos2d::Texture2D *MapTile::getTexture()
{
	double destroyRate = ((double)destroyStatus) / ((double)(int)0x10000);
	if (destroyRate < 0.3)
		return type->getTextures()[3];
	if (destroyRate < 0.6)
		return type->getTextures()[2];
	if (destroyRate < 0.9)
		return type->getTextures()[1];
	return type->getTextures()[0];
}
