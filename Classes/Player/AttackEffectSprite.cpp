#include "AttackEffectSprite.h"

using namespace cocos2d;

AttackEffectSprite *AttackEffectSprite::create(float angle)
{
    AttackEffectSprite *ret = new (std::nothrow) AttackEffectSprite();

    if (ret && ret->initWithFile("assets/player/attack_effect.png"))
    {
        ret->autorelease();
        ret->setScale(3);
        ret->setRotation(-angle / 3.1415 * 180);
        ret->setPosition(24, 16);
        ret->setGlobalZOrder(1);
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

void AttackEffectSprite::execute()
{
    scheduleOnce([=](float) {removeFromParent(); }, 0.1f, "delete");
}
