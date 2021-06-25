#pragma once
#include <cocos2d.h>
#include <Box2D/Box2D.h>


class PlayerContact :
    public b2ContactListener
{
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void EatItemCheck(cocos2d::Sprite*, cocos2d::Sprite*);
    void InvokeShopCheck(cocos2d::Sprite*, cocos2d::Sprite*);
    void OnTheGroundCheck(cocos2d::Sprite*, cocos2d::Sprite*, bool begin);
};

