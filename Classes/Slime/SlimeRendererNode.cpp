#include "SlimeRenderer.h"
#include "../Physics/Box2DWorldComponent.h"
#include "../Player/Player.h"
#include "../Utils/VectorConversion.h"

using namespace cocos2d;

SlimeRendererNode *SlimeRendererNode::instance = nullptr;

bool SlimeRendererNode::init()
{
    if (!DrawNode::init())
        return false;
    this->setName("SlimeRendererNode");
    scheduleUpdate();
    return true;
}

void SlimeRendererNode::addToWorld()
{
    Node *node = this->getParent();
    auto cp = node->getComponent("b2World");

    while (cp == nullptr && node != nullptr)
    {
        cp = node->getComponent("b2World");
        node = node->getParent();
    }

    if (cp == nullptr)
        throw 1;

    auto wcp = dynamic_cast<Box2DWorldComponent *>(cp);
    b2ParticleSystemDef def;
    particleSystem = wcp->getWorld()->CreateParticleSystem(&def);
    particleSystem->SetRadius(0.035f);
}

void SlimeRendererNode::update(float delta)
{
    clear();
    b2Vec2 *positions = particleSystem->GetPositionBuffer();
    b2ParticleColor *colors = particleSystem->GetColorBuffer();
    int particleCount = particleSystem->GetParticleCount();

    Vec2 playerPosition = Player::GetInstance()->getPosition();
    b2Vec2 b2PlayerPosition = r2p(playerPosition);
    int halfScreenWidth = Director::getInstance()->getWinSize().width / 2 + 320;
    int halfScreenHeight = Director::getInstance()->getWinSize().height / 2 + 320;
    int b2HalfScreenWidth = halfScreenWidth / 64;
    int b2HalfScreenHeight = halfScreenHeight / 64;


    for (int i = 0; i < particleCount; i++)
    {
        if (abs((positions[i] - b2PlayerPosition).x) < b2HalfScreenWidth && abs((positions[i] - b2PlayerPosition).y) < b2HalfScreenHeight)
        {
            drawDot(p2r(positions[i]), 4.0f, Color4F(Color4B(colors[i].r, colors[i].g, colors[i].b, colors[i].a / 2)));
            drawDot(p2r(positions[i]), 2.0f, Color4F(Color4B(colors[i].r, colors[i].g, colors[i].b, colors[i].a / 1.5f)));
            drawDot(p2r(positions[i]), 1.0f, Color4F(Color4B(colors[i].r, colors[i].g, colors[i].b, colors[i].a)));
        }
    }
}
