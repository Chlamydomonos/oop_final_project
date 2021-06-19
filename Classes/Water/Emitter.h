//#pragma once
#ifndef EMITTER_H
#define EMITTER_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

class Emitter :public cocos2d::Node
{
public:
	Emitter() : particleSystem{ NULL }, particleSystemDef{ NULL }, flag{ b2_waterParticle },
	emitRate{0.0f}
	{}
	~Emitter()
	{
		CC_SAFE_DELETE(particleSystemDef);
	}
	Emitter* create(b2ParticleSystemDef* b2ParticleSystem, b2ParticleColor color, float32 x, float32 y, float32 halfsize);
	void addToWorld(); // used for creating the particle system
	// When you use the method Emit, the emitter will keep pushing the particle at the speed of emitrate
	// as long as a period of time
	void Emit(float32 emitrate, float32 time, b2Vec2& velocity, float32 speed);
	// create some API
	void setPosition(float32 x, float32 y) { this->x = x; this->y = y; }
	b2Vec2& getPosition() { b2Vec2 res = b2Vec2(x, y); return res; }
	float32 getXPosition() { return x; }
	float32 getYPosition() { return y; }
	void setEmitRate(float32 emitrate) { this->emitRate = emitrate; }
	float32 getEmitRate() { return emitRate; }
	void setColor(b2ParticleColor color) { this->color = color; }
	b2ParticleColor getColor() { return color; }
	void setFlag(uint32 flag) { flag = flag; }
	uint32 getFlag() { return flag; }
	void setHalfSize(float32 halfsize) { this->halfsize = halfsize; }
	float32 getHalfSize() { return halfsize; }

private:
	b2ParticleSystem* particleSystem;
	b2ParticleSystemDef* particleSystemDef;
	float32 x;
	float32 y;
	float32 emitRate;
	b2ParticleColor color;
	uint32 flag;
	float32 halfsize; // a parameter used to introduce some noise
};

#endif
