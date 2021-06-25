#pragma once
#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "../Item/ItemStackSprite.h"

template<class T>
class DeleteCheck {
public:
    static void CheckChild(T* rootNode) {
        int cnt{ rootNode->getChildrenCount() };
        auto list = rootNode->getChildren();
        for (auto it = list.begin(); it != list.end(); it++) {
            if (dynamic_cast<Node*>(*it)->getTag() == DEL_TAG) {
                dynamic_cast<Node*>(*it)->removeFromParent();
                rootNode->GetWorld()->DestroyBody(dynamic_cast<ItemStackSprite*>(*it)->GetBodyComponent()->getBody());
            }
        }
        return;
    }
};