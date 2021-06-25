#ifndef WATER_WATER_RENDERER_H
#define WATER_WATER_RENDERER_H

#include <cocos2d.h>
#include "WaterRendererNode.h"

class WaterRenderer : public cocos2d::Node
{
private:
	static WaterRenderer *instance;
	cocos2d::Node *mainNode;
	cocos2d::Node *gameObjects;
	cocos2d::RenderTexture *texture;
public:
	CREATE_FUNC(WaterRenderer);
	bool init();
	void update(float delta);
	static WaterRenderer *getInstance()
	{
		if (!instance)
			instance = create();
		return instance;
	}
	void addToWorld();
};

#endif // !WATER_WATER_RENDERER_H
