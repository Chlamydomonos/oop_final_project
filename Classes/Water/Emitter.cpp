#include <cstdlib>
#include "Emitter.h"
#include "EmitterWorld.h"
#include "../Exception/Exception.h"

Emitter* Emitter::create(b2ParticleSystemDef* particleSystemDef, b2ParticleColor color, float32 x, float32 y, float32 halfsize)
{
	Emitter* emitter = new Emitter();
	emitter->particleSystemDef = particleSystemDef;
	emitter->setName("WaterEmitter");
	emitter->setColor(color);
	emitter->setPosition(x, y);
	emitter->setHalfSize(halfsize);

	if (emitter && emitter->init())
		emitter->autorelease();
	else
		CC_SAFE_DELETE(emitter);

	return emitter;
}

void Emitter::addToWorld()
{
	try
	{
		auto parent = this->getParent();
		std::string name = this->getName();
		auto node = parent->getChildByName(name);

		while (node == nullptr && parent != nullptr)
		{
			node = parent;
			parent = parent->getParent();
		}

		if (parent == nullptr)
			throw 1;

		auto p = dynamic_cast<EmitterWorld*> (parent);
		auto m_world = p->getWorld();
		this->particleSystem = m_world->CreateParticleSystem(particleSystemDef);

		CC_SAFE_DELETE(particleSystemDef);
	}
	catch (...)
	{
		throw Exception("Error when adding the emitter to world!");
	}
}

// when you use the Emit method, the emitter will keep pushing particles at the 
// speed of emitrate for a period as long as time
void Emitter::Emit(float32 emitrate, float32 time, b2Vec2& velocity, float32 speed)
{
	// Configure the particleDef
	b2ParticleDef pd;
	pd.color = this->getColor();
	pd.flags = this->getFlag();
	pd.position.Set(this->getXPosition(), this->getYPosition());

	float32 emitRemainder = emitrate * time;
	while (emitRemainder >= 1.0f)
	{
		emitRemainder -= 1.0f;
		// Introduce the noise of the initial position and the initial velocity
		const float32 angle = (float32)(rand() / RAND_MAX) * 2.0f * b2_pi;
		const float32 distance = (float32)(rand() / RAND_MAX) * this->getHalfSize();
		b2Vec2 positionOnUnitCircle = b2Vec2(sin(angle), cos(angle));

		pd.position.Set(
			this->getXPosition() + distance * positionOnUnitCircle.x,
			this->getYPosition() + distance * positionOnUnitCircle.y
		);

		float32 velocityx = velocity.x + speed * positionOnUnitCircle.x;
		float32 velocityy = velocity.y + speed * positionOnUnitCircle.y;
		b2Vec2 Velocity = b2Vec2(velocityx, velocityy);
		pd.velocity = Velocity;
	}
}