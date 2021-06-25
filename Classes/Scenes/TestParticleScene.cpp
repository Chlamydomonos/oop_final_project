#include "TestParticleScene.h"

#include "../Map/GameMap.h"
#include "../Map/MapTile.h"
#include "../Map/TileSprite.h"
#include "../Map/TileType.h"
#include "../Player/Player.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Physics/Box2DBodyComponent.h"
#include "../Player/PlayerController.h"
#include "../Utils/VectorConversion.h"
#include "../Slime/Slime.h"
#include "../Slime/SlimeRenderer.h"

using namespace cocos2d;
using namespace std;

bool TestParticleScene::init()
{
    if (!Scene::init())
        return false;

    wp = Box2DWorldComponent::create({ 0.0f, -10.0f });
    addComponent(wp);

    b2ParticleSystemDef d;

    ps = wp->getWorld()->CreateParticleSystem(&d);
	
	{
		b2BodyDef bd;
		b2Body *ground = wp->getWorld()->CreateBody(&bd);

		{
			b2PolygonShape shape;
			const b2Vec2 vertices[4] = {
				b2Vec2(-4, -1),
				b2Vec2(4, -1),
				b2Vec2(4, 0),
				b2Vec2(-4, 0) };
			shape.Set(vertices, 4);
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			b2PolygonShape shape;
			const b2Vec2 vertices[4] = {
				b2Vec2(-4, -0.1f),
				b2Vec2(-2, -0.1f),
				b2Vec2(-2, 2),
				b2Vec2(-4, 2) };
			shape.Set(vertices, 4);
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			b2PolygonShape shape;
			const b2Vec2 vertices[4] = {
				b2Vec2(2, -0.1f),
				b2Vec2(4, -0.1f),
				b2Vec2(4, 2),
				b2Vec2(2, 2) };
			shape.Set(vertices, 4);
			ground->CreateFixture(&shape, 0.0f);
		}
	}

	ps->SetRadius(0.035f);

	{
		b2CircleShape shape;
		shape.m_p.Set(-1, 3);
		shape.m_radius = 0.5f;
		b2ParticleGroupDef pd;
		pd.flags = b2_elasticParticle;
		pd.groupFlags = b2_solidParticleGroup;
		pd.shape = &shape;
		pd.strength = 5;
		pd.color.Set(0, 255, 0, 255);
		ps->CreateParticleGroup(pd);
	}

	{
		b2PolygonShape shape;
		shape.SetAsBox(1, 0.5f);
		b2ParticleGroupDef pd;
		pd.flags = b2_elasticParticle;
		pd.groupFlags = b2_solidParticleGroup;
		pd.position.Set(1, 4);
		pd.angle = -0.5f;
		pd.angularVelocity = 2.0f;
		pd.shape = &shape;
		pd.strength = 5;
		pd.color.Set(0, 0, 255, 255);
		ps->CreateParticleGroup(pd);
	}

	dynamicSprite = Sprite::create("pure_red.png");
	dynamicSprite->setScale(4, 4);
	this->addChild(dynamicSprite);

	//--建立静态Sprite-----------------------------

	staticSprite = Sprite::create("pure_red.png");
	staticSprite->setScale(64, 4);
	this->addChild(staticSprite);

	//--建立静态物理组件----------------------------

	b2BodyDef staticBodyDef;
	staticBodyDef.position.Set(8.0f, 0.5f);

	b2PolygonShape staticBox;
	staticBox.SetAsBox(32.0f, 0.5f);

	b2FixtureDef staticFixtureDef;
	staticFixtureDef.shape = &staticBox;

	auto staticBodyComponent = Box2DBodyComponent::create(&staticBodyDef, &staticFixtureDef);
	staticSprite->addComponent(staticBodyComponent);
	staticBodyComponent->addToWorld();

	//--建立动态物理组件----------------------------

	b2BodyDef dynamicBodyDef;
	dynamicBodyDef.type = b2_dynamicBody;
	dynamicBodyDef.position.Set(8.0f, 8.0f);

	dynamicBodyDef.angularVelocity = 0.1f;

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef dynamicFixtureDef;
	dynamicFixtureDef.shape = &dynamicBox;
	dynamicFixtureDef.density = 1.0f;
	dynamicFixtureDef.friction = 0.3f;
	dynamicFixtureDef.restitution = 0.8f;

	auto dynamicBodyComponent = Box2DBodyComponent::create(&dynamicBodyDef, &dynamicFixtureDef);
	dynamicSprite->addComponent(dynamicBodyComponent);
	dynamicBodyComponent->addToWorld();

	this->addChild(Player::GetInstance());
	Player::GetInstance()->GetBC()->addToWorld();
	Player::GetInstance()->GetBC()->getBody()->SetFixedRotation(true);

	this->addComponent(PlayerController::create());
	this->setPosition(p2r({ 5, 0 }));

	drawNode = DrawNode::create();
	this->addChild(drawNode);

	scheduleUpdate();

    return true;
}

void TestParticleScene::update(float delta)
{
	Scene::update(delta);
	drawNode->clear();
	b2Vec2* positions = ps->GetPositionBuffer();
	b2ParticleColor *colors = ps->GetColorBuffer();
	int count = ps->GetParticleCount();
	for (int i = 0; i < count; i++)
	{
		drawNode->drawDot(p2r(positions[i]), 4.0f, { colors[i].r / 255.0f, colors[i].g / 255.0f, colors[i].b / 255.0f, colors[i].a / 255.0f / 2 });
		drawNode->drawDot(p2r(positions[i]), 2.0f, { colors[i].r / 255.0f, colors[i].g / 255.0f, colors[i].b / 255.0f, colors[i].a / 255.0f / 1.5f });
		drawNode->drawDot(p2r(positions[i]), 1.0f, { colors[i].r / 255.0f, colors[i].g / 255.0f, colors[i].b / 255.0f, colors[i].a / 255.0f });
	}
}

TestParticleScene::~TestParticleScene()
{
}
