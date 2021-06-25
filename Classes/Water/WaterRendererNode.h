#ifndef WATER_WATER_RENDERER_NODE_H
#define WATER_WATER_RENDERER_NODE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class WaterRendererNode : public cocos2d::DrawNode
{
private:
	b2ParticleSystem *particleSystem;
	static WaterRendererNode *instance;
public:
	static WaterRendererNode *getInstance()
	{
		if (!instance)
			instance = create();
		return instance;
	}
	CREATE_FUNC(WaterRendererNode);
	bool init();
	void addToWorld();
	void update(float delta);
	b2ParticleSystem *getParticleSystem() { return particleSystem; }
};

#endif // !Water_Water_RENDERER_H
