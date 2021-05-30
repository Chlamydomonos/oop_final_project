#pragma once
#include <cocos2d.h>
#include <Box2D/Box2D.h>




class PlayerContact :
    public b2ContactListener
{
    void BeginContact(b2Contact* contact);
};

