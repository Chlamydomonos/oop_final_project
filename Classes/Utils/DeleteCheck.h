#pragma once
#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "../Item/ItemStackSprite.h"
#include "../Player/Player.h"

class DeleteCheck {
public:
    static b2World *world;
    static void CheckChild(cocos2d::Node* rootNode) {
        int cnt{ rootNode->getChildrenCount() };
        auto list = rootNode->getChildren();
        for (auto it = list.begin(); it != list.end(); it++) {
            if (dynamic_cast<cocos2d::Node*>(*it)->getTag() == DEL_TAG) {
                dynamic_cast<cocos2d::Node*>(*it)->removeFromParent();
                world->DestroyBody(dynamic_cast<ItemStackSprite*>(*it)->GetBodyComponent()->getBody());
            }
            CheckChild(dynamic_cast<cocos2d::Node *>(*it));
        }
        return;
    }
};