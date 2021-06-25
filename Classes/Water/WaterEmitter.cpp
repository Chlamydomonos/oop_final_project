#include "WaterEmitter.h"
#include "WaterRenderer.h"
#include "../Utils/VectorConversion.h"

bool WaterEmitter::init()
{
    emitting = false;
    scheduleUpdate();
    return true;
}

void WaterEmitter::emit(float time)
{
    emitting = true;
    schedule(
        [=](float) {emitting = false; },
        time,
        "emit"
    );
}

void WaterEmitter::update(float delta)
{
    if (emitting)
    {
        b2ParticleDef def;
        def.position = r2p(getPosition());
        def.color = {0x8a, 0xa8, 0xe5, 0xff};
        def.lifetime = -1;
        def.flags = b2_tensileParticle;
        for (int i = 0; i < 3; i++)
        {
            def.velocity = { (float)(std::rand() % 50), (float)(std::rand() % 50) };
            WaterRendererNode::getInstance()->getParticleSystem()->CreateParticle(def);
        }
    }
}
