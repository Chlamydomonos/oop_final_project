#ifndef PLAYER_ATTACK_EFFECT_SPRITE_H
#define PLAYER_ATTACK_EFFECT_SPRITE_H

#include <cocos2d.h>

class AttackEffectSprite : public cocos2d::Sprite
{
public:
	static AttackEffectSprite *create(float angle);
	void execute();
};

#endif