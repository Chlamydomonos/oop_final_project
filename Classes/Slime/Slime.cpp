#include "Slime.h"
#include "../Utils/VectorConversion.h"
#include "SlimeRenderer.h"
#include "../Player/Player.h"
#include "../Physics/Box2DBodyComponent.h"

std::set<Slime *> Slime::SLIMES{};

Slime *Slime::create(float size, float x, float y)
{
    Slime *ret = new (std::nothrow) Slime();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->size = size;
		ret->hp = size * 5;
        ret->setPosition(p2r({ x, y }));
		return ret;
    }

	CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Slime::init()
{
	schedule(
		[=](float dt) {
			bool left = std::rand() % 2;
			if (particleGroup != nullptr)
				particleGroup->ApplyLinearImpulse({ 1.0f * (left ? -1 : 1) * size * size, 4.0f * size * size});
			if ((Player::GetInstance()->getPosition() - getPosition()).length() < size * 64.0f + 32.0f)
				if ((left && Player::GetInstance()->getPositionX() <= getPositionX()) || (!left && Player::GetInstance()->getPositionX() >= getPositionX()))
					Player::GetInstance()->GetBC()->getBody()->SetLinearVelocity(Player::GetInstance()->GetBC()->getBody()->GetLinearVelocity() + b2Vec2{5.0f * (left ? -1 : 1), 5.0f});
		},
		2.0f,
		"jump"
	);
	scheduleUpdate();
	return true;
}

void Slime::addToWorld()
{
	b2ParticleSystem *ps = SlimeRendererNode::getInstance()->getParticleSystem();

	{
		b2CircleShape shape;
		shape.m_p.Set(r2p(getPosition()).x, r2p(getPosition()).y);
		shape.m_radius = size / 2.0f;
		b2ParticleGroupDef pd;
		pd.flags = b2_elasticParticle;
		pd.groupFlags = b2_solidParticleGroup;
		pd.shape = &shape;
		pd.strength = 5;
		pd.color.Set(0x5f, 0xb3, 0x36, 0xff);
		particleGroup = ps->CreateParticleGroup(pd);
	}
}

void Slime::update(float delta)
{
	if(particleGroup)
		setPosition(p2r(particleGroup->GetCenter()));
	if (hp <= 0)
		onDeath();
}

void Slime::onDeath()
{
	if (size < 0.99f)
	{
		auto ps = particleGroup->GetParticleSystem();
		auto positions = ps->GetPositionBuffer();
		auto pn = particleGroup->GetParticleCount();
		auto os = particleGroup->GetBufferIndex();
		b2ParticleDef def;
		def.color = { 0x96, 0xcc, 0x7a, 0x40 };
		for (int i = os; i < os + pn; i++)
		{
			def.lifetime = 7.5f + (std::rand() % 1000) / 200.0f;
			def.velocity.Set((std::rand() % 1000) / 50.0f * size * size, (std::rand() % 1000) / 50.0f * size * size);
			def.position = positions[i];
			ps->CreateParticle(def);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			Slime *temp = Slime::create(size * 0.3f, getPositionX() / 64.0f, getPositionY() / 64.0f);
			getParent()->addChild(temp);
			temp->addToWorld();
		}
		auto ps = particleGroup->GetParticleSystem();
		auto positions = ps->GetPositionBuffer();
		auto pn = particleGroup->GetParticleCount();
		auto os = particleGroup->GetBufferIndex();
		b2ParticleDef def;
		def.color = { 0x96, 0xcc, 0x7a, 0x40 };
		for (int i = os; i < os + pn; i++)
		{
			if (std::rand() % 100 < 64)
			{
				def.lifetime = (std::rand() % 1000) / 200.0f;
				def.velocity.Set((std::rand() % 1000) / 50.0f, (std::rand() % 1000) / 50.0f);
				def.position = positions[i];
				ps->CreateParticle(def);
			}
		}
	}
	particleGroup->DestroyParticles();
	this->removeFromParent();
}
