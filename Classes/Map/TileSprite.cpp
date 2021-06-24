#include "TileSprite.h"
#include "../Utils/VectorConversion.h"
#include "../Player/Player.h"

using namespace cocos2d;

Texture2D *TileSprite::EMPTY{ nullptr };

TileSprite *TileSprite::create()
{
	TileSprite *ret = new TileSprite();
	if (ret && ret->initWithFile("pure_red.png"))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

void TileSprite::update(float delta)
{
	int px = (((int)(Player::GetInstance()->getPositionX())) / 64) * 64;
	int py = (((int)(Player::GetInstance()->getPositionY())) / 64) * 64;
	setPositionX(px + relativeX * 64);
	setPositionY(py + relativeY * 64);

	MapTile *tile = dynamic_cast<GameMap *>(getParent())->getTile(r2p(getPosition()));
	if (tile == nullptr)
		setTexture(EMPTY);
	else
	{
		setTexture(tile->getTexture());
		int tw = tile->getTexture()->getContentSizeInPixels().width;
		int th = tile->getTexture()->getContentSizeInPixels().height;
		setScaleX(64.0f / tw);
		setScaleY(64.0f / th);
	}

	Sprite::update(delta);
}
