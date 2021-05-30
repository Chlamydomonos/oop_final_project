#ifndef MAP_BREAK_SPRITE_H
#define MAP_BREAK_SPRITE_H

#include <cocos2d.h>
#include "Tile.h"

class BreakSprite : public cocos2d::Sprite
{
private:
	Tile *tile;
public:
	static cocos2d::SpriteFrame **frames;
	static void initAllFrames();
};

#endif // !MAP_BREAK_SPRITE_H
