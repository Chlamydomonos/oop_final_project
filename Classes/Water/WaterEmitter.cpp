#include "WaterEmitter.h"

int32 RadialEmitter::Step(const float32 dt, int32* const particleIndices, const int32 particleIndicesCount)
{
	b2Assert(m_particleSystem);
	int32 numberOfParticlesCreated = 0;
	m_emitRemainder += m_emitRate * dt;

	b2ParticleDef pd;
	pd.color = m_color;
	pd.flags = m_flags;
	pd.group = m_group;

	while (m_emitRemainder > 1.0f)
	{
		m_emitRemainder -= 1.0f;

		const float32 angle = Random() * 2.0f * b2_pi;
		const float32 distance = Random();
		b2Vec2 positionOnUnitCircle(sin(angle), cos(angle));

		pd.position.Set(
			m_origin.x + positionOnUnitCircle.x * distance * m_halfsize.x,
			m_origin.y + positionOnUnitCircle.y * distance * m_halfsize.y);
		pd.velocity = m_startingVelocity;
		if (m_speed != 0.0f)
		{
			pd.velocity += positionOnUnitCircle * m_speed;
		}
		const int32 particleIndex = m_particleSystem->CreateParticle(pd);
		if (m_callBack)
		{
			m_callBack->ParticleCreated(m_particleSystem, particleIndex);
		}
		if (particleIndices &&
			numberOfParticlesCreated < particleIndicesCount)
		{
			particleIndices[numberOfParticlesCreated] = particleIndex;
		}
		numberOfParticlesCreated++;
	}
	return numberOfParticlesCreated;
}