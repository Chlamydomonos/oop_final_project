#ifndef SLIME_SLIME_H
#define SLIME_SLIME_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include <set>

class Slime : public cocos2d::Node
{
private:
	float size;
	int hp;
	b2ParticleGroup *particleGroup;
public:
	static std::set<Slime *> SLIMES;
	static Slime *create(float size, float x, float y);
	Slime():
		size{0},
		hp{ 0 },
		particleGroup{ nullptr }
	{
		SLIMES.insert(this);
	}
	~Slime() { SLIMES.erase(this); }
	bool init();
	void addToWorld();
	void update(float delta);
	void onDeath();
	void hurt(int value) { hp -= value; }
	b2ParticleGroup *getParticleGroup() { return particleGroup; }
	float getSize() { return size; }
};

#endif // !SLIME_SLIME_H
