#include "Player.h"


bool Player::init() {
	if (!Sprite::init() || !initWithFile("player_init.png"))
		return false;

    b2BodyDef dynamicBodyDef;
    dynamicBodyDef.type = b2_dynamicBody;
    dynamicBodyDef.position.Set(8.0f, 8.0f);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);

    b2FixtureDef dynamicFixtureDef;
    dynamicFixtureDef.shape = &dynamicBox;
    dynamicFixtureDef.density = 1.0f;
    dynamicFixtureDef.friction = 2;
    dynamicFixtureDef.restitution = 0.2f;

    auto dynamicBodyComponent = Box2DBodyComponent::create(&dynamicBodyDef, &dynamicFixtureDef);
    this->addComponent(dynamicBodyComponent);
    this->BC = dynamicBodyComponent;
    
}
