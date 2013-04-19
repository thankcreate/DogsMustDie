#ifndef Planet_h__
#define Planet_h__

#include "cocos2d.h"
#include "FightObject.h"

using namespace cocos2d;

class Face;
class Planet : public FightObject
{
public:	
	Planet();
	bool init();

	// 由于不同势力的星球会互相转化，所以Planet类需要设计得具有可转化性
	// 否则在转化过程中delete掉一个planet再新建一个planet
	// 伴随的从array中remove掉和add进的过程非常容易出错
	static Planet* createWithForceSide(int force);
	void initWithForceSide(int force);
		
	CC_SYNTHESIZE(Face*, m_pFace, Face);	// 星球中心的占领势力头像
	CC_SYNTHESIZE(CCLabelTTF*, m_pFightUnitLabel, FightUnitLabel );

	void setFightUnitCount(int input);	
	int getMaximumUnitCount();

	float getIncreaseInterval();

	void myUpdate(float dt);
	CCPoint getBox2dObjectSize();

	// 对于星球而言，有一个等级属性	
	// 初始默认为0级星球，UI上没有任何显示
	// 后来每升一级，UI上在右下角加一个军衔杠杠
	// 最高为3级星球，也就是3道杠
private:
	int m_nLevel;
	float m_fLastTimeIncreased;
};

#endif // Planet_h__
