#ifndef SLIME_SLIME_RENDERER_NODE_H
#define SLIME_SLIME_RENDERER_NODE_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class SlimeRendererNode : public cocos2d::DrawNode
{
private:
	b2ParticleSystem *particleSystem;
	static SlimeRendererNode *instance;
public:
	static SlimeRendererNode *getInstance()
	{
		if (!instance)
			instance = create();
		return instance;
	}
	CREATE_FUNC(SlimeRendererNode);
	bool init();
	void addToWorld();
	void update(float delta);
	b2ParticleSystem *getParticleSystem() { return particleSystem; }
};

#endif // !SLIME_SLIME_RENDERER_H
