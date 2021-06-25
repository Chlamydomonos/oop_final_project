#ifndef WATER_WATER_EMITTER_H
#define WATER_WATER_EMITTER_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class WaterEmitter : public cocos2d::Node
{
private:
	bool emitting;
public:
	WaterEmitter() : emitting{ false }{}
	bool init();
	void emit(float time);
	CREATE_FUNC(WaterEmitter);
	void update(float delta);
};

#endif // !WATER_WATER_EMITTER_H
