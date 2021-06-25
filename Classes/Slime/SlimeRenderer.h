#ifndef SLIME_SLIME_RENDERER_H
#define SLIME_SLIME_RENDERER_H

#include <cocos2d.h>
#include "SlimeRendererNode.h"

class SlimeRenderer : public cocos2d::Node
{
private:
	static SlimeRenderer *instance;
	cocos2d::Node *mainNode;
	cocos2d::Node *gameObjects;
	cocos2d::RenderTexture *texture;
public:
	CREATE_FUNC(SlimeRenderer);
	bool init();
	void update(float delta);
	static SlimeRenderer *getInstance()
	{
		if (!instance)
			instance = create();
		return instance;
	}
	static void releaseInstance()
	{
		instance = nullptr;
		SlimeRendererNode::releaseInstance();
	}
	void addToWorld();
};

#endif // !SLIME_SLIME_RENDERER_H
