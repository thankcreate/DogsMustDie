#ifndef Planet_h__
#define Planet_h__

#include "cocos2d.h"
#include "FightObject.h"

using namespace cocos2d;

class Planet : public FightObject
{
public:	
	Planet();
	bool init();
		
	CC_SYNTHESIZE(CCSprite*, m_pAvatar, Avatar);	// 星球中心的占领势力头像
	CC_SYNTHESIZE(CCLabelTTF*, m_pFightUnitLabel, FightUnitLabel );

	void setFightUnitCount(int input);
};

#endif // Planet_h__
