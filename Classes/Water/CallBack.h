//#pragma once
#ifndef CALLBACK_H
#define CALLBACK_H

#include "../Box2D/include/Box2D/Box2D.h"

class CallBack
{
public:
	CallBack() {}
	virtual ~CallBack() {}
	virtual void ParticleCreated(b2ParticleSystem* const partilesystem, const int32 particleindex) = 0;
};

#endif