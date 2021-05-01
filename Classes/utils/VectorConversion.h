#ifndef UTILS_VECTOR_CONVERSION_H
#define UTILS_VECTOR_CONVERTION_H

#include <cocos2d.h>
#include <Box2D/Box2D.h>

inline cocos2d::Vec2 p2r (const b2Vec2& pV) {
	cocos2d::Vec2 rV(pV.x * 64, pV.y * 64);
	return rV;
}

inline b2Vec2 r2p(const cocos2d::Vec2& rV) {
	b2Vec2 pV(rV.x / 64, rV.y / 64);
	return pV;
}

#endif // !UTILS_VECTOR_CONVERSION_H