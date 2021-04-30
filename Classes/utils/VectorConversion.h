#pragma once
#include <cocos\cocos2d.h>
#include <external\Box2D\include\Box2D\Box2D.h>

cocos2d::Vec2 p2r (const b2Vec2& pV) {
	cocos2d::Vec2 rV(pV.x * 64, pV.y * 64);
	return rV;
}

b2Vec2 r2p(const cocos2d::Vec2& rV) {
	b2Vec2 pV(rV.x / 64, rV.y / 64);
	return pV;
}