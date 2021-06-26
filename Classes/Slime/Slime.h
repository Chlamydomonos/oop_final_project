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
	bool isBoss;
	bool inWorld;
public:
	static std::set<Slime *> SLIMES;
	static std::set<Slime *> SLIME_BOSSES;
	static Slime *create(float size, float x, float y, bool isBoss);
	Slime():
		size{0},
		hp{ 0 },
		particleGroup{ nullptr },
		isBoss{false},
		inWorld{false}
	{
		SLIMES.insert(this);
	}
	~Slime()
	{ 
		SLIMES.erase(this); 
		if (isBoss)
			SLIME_BOSSES.erase(this);
	}
	bool init();
	void addToWorld();
	void update(float delta);
	void onDeath();
	void hurt(int value) { hp -= value; }
	b2ParticleGroup *getParticleGroup() { return particleGroup; }
	float getSize() { return size; }
};

#endif // !SLIME_SLIME_H
