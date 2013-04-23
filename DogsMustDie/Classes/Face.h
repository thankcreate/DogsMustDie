#ifndef Face_h__
#define Face_h__

#include "cocos2d.h"

using namespace cocos2d;
#define CRY_DURATION 1.0f

class Face : public CCSprite
{
public:
	Face();

	CC_SYNTHESIZE(CCSprite*, m_pLeftWing, LeftWing);
	CC_SYNTHESIZE(CCSprite*, m_pRightWing, RightWing);

	int m_nForceSide;
	int getForceSide() { return m_nForceSide; }

	static Face* createWithForceSide(int force);
	void initWithForceSide(int force);

	void setWingsVisiable(bool visible);

	void cry();
	void restore(float dt);

private:
	bool m_bIsInCry;

};

#endif // Face_h__
