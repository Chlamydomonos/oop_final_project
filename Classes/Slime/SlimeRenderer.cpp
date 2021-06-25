#include "SlimeRenderer.h"

#include "../Player/Player.h"

using namespace cocos2d;

SlimeRenderer *SlimeRenderer::instance = nullptr;

bool SlimeRenderer::init()
{
    scheduleUpdate();
    return true;
}

void SlimeRenderer::update(float delta)
{
    SlimeRendererNode::getInstance()->setVisible(true);
    gameObjects->setVisible(false);
    texture->beginWithClear(0, 0, 0, 0);
    getParent()->visit();
    texture->end();
    SlimeRendererNode::getInstance()->setVisible(false);
    gameObjects->setVisible(true);
}

void SlimeRenderer::addToWorld()
{
    mainNode = getParent()->getChildByName("mainNode");
    gameObjects = mainNode->getChildByName("gameObjects");
    texture = RenderTexture::create(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    texture->setName("RenderTexture");
    texture->getSprite()->setOpacity(0x99);
    texture->setPosition(Director::getInstance()->getWinSize() / 2);
    getParent()->addChild(texture);
    mainNode->addChild(SlimeRendererNode::getInstance());
    SlimeRendererNode::getInstance()->addToWorld();
}
