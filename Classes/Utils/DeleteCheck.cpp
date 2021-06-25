#include "DeleteCheck.h"
#include "Player/Player.h"
#include <vector>
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Item/ItemStackSprite.h"

USING_NS_CC;

b2World *DeleteCheck::world = nullptr;