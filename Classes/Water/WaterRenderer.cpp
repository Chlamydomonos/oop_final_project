#include "WaterRenderer.h"

#include "../Player/Player.h"

using namespace cocos2d;

WaterRenderer *WaterRenderer::instance = nullptr;

bool WaterRenderer::init()
{
    scheduleUpdate();
    return true;
}

void WaterRenderer::update(float delta)
{
    WaterRendererNode::getInstance()->setVisible(true);
    gameObjects->setVisible(false);
    texture->beginWithClear(0, 0, 0, 0);
    getParent()->visit();
    texture->end();
    WaterRendererNode::getInstance()->setVisible(false);
    gameObjects->setVisible(true);
}

void WaterRenderer::addToWorld()
{
    mainNode = getParent()->getChildByName("mainNode");
    gameObjects = mainNode->getChildByName("gameObjects");
    texture = RenderTexture::create(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    texture->setName("RenderTexture");
    texture->getSprite()->setOpacity(0x80);
    texture->setPosition(Director::getInstance()->getWinSize() / 2);
    getParent()->addChild(texture);
    mainNode->addChild(WaterRendererNode::getInstance());
    WaterRendererNode::getInstance()->addToWorld();
}
