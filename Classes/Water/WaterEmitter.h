//#pragma once
#ifndef WATEREMITTER_H
#define WATEREMITTER_H

#include "CallBack.h"
#include <math.h>
#include <set>

class RadialEmitter
{
private:
	static float32 Random()
	{
		return (float32)(rand() / 100.0);
	}
	b2Vec2 m_origin;
	b2Vec2 m_halfsize;
	b2Vec2 m_startingVelocity;
	float32 m_speed;
	uint32 m_flags;
	b2ParticleColor m_color;
	float32 m_emitRate;
	b2ParticleSystem* m_particleSystem;
	CallBack* m_callBack;
	b2ParticleGroup* m_group;
	float32 m_emitRemainder;
public:
	RadialEmitter(): m_particleSystem{NULL}, m_callBack{NULL}, m_speed{0.0f},
		m_emitRate{1.0f}, m_emitRemainder{0.0f}, m_flags{b2_waterParticle}, m_group{NULL}
	{}
	~RadialEmitter() {setGroup(NULL);}
	void setPosition(const b2Vec2& origin) {m_origin = origin; }// 设置喷射圆的中心位置
	const b2Vec2& getPosition() const { return m_origin; }
	void setSize(const b2Vec2& size) { m_halfsize = size; } // 设置喷射圆的大小
	const b2Vec2& getSize() const { return m_halfsize; }
	void setVelocity(const b2Vec2& velocity) { m_startingVelocity = velocity; } // 设置喷射的初速度矢量
	const b2Vec2& getVelocity() const { return m_startingVelocity; }
	void setSpeed(const float32 speed) { m_speed = speed; } // 设置喷射粒子的速率
	const float32 getSpeed() const { return m_speed; }
	void setParticleFlags(const uint32 flags) {m_flags = flags;} // 设置粒子的flags
	const uint32 getParticleFlags() const { return m_flags; }
	void setColor(const b2ParticleColor& color) { m_color = color; } // 设置粒子的颜色
	const b2ParticleColor& getParticleColor() const { return m_color; }
	void setEmitRate(const float32 emitrate) {m_emitRate = emitrate;} // 设置每秒喷出的粒子数
	const float32 getEmitRate() const { return m_emitRate; }
	void setParticleSystem(b2ParticleSystem* const particlesystem) { m_particleSystem = particlesystem;}
	const b2ParticleSystem* getParticleSystem() const { return m_particleSystem; }
	void setCallBack(CallBack* const callback) { m_callBack = callback; }
	const CallBack* getCallBack() { return m_callBack; }
	void setGroup(b2ParticleGroup* const group)
	{
		if (m_group)
			m_group->SetGroupFlags(m_group->GetGroupFlags() & ~b2_particleGroupCanBeEmpty);
		m_group = group;
		if (m_group)
			m_group->SetGroupFlags(m_group->GetGroupFlags() | b2_particleGroupCanBeEmpty);
	}
	const b2ParticleGroup* getGroup() const { return m_group; }
	int32 Step(const float32, int32* const, const int32 );
};



#endif