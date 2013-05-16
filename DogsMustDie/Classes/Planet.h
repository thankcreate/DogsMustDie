#ifndef Planet_h__
#define Planet_h__

#include "cocos2d.h"
#include "FightObject.h"

using namespace cocos2d;

class Face;
class Rank;

#define MAX_PLANET_LEVEL 3

class Planet : public FightObject
{
public:	
	Planet();
	bool init();

	// ���ڲ�ͬ����������ụ��ת��������Planet����Ҫ��Ƶþ��п�ת����
	// ������ת��������delete��һ��planet���½�һ��planet
	// ����Ĵ�array��remove����add���Ĺ��̷ǳ����׳���
	static Planet* createWithForceSide(int force);
	void initWithForceSide(int force);
		
	CC_SYNTHESIZE(Face*, m_pFace, Face);	// �������ĵ�ռ������ͷ��
	CC_SYNTHESIZE(CCLabelTTF*, m_pFightUnitLabel, FightUnitLabel );
	CC_SYNTHESIZE(Rank*, m_pRank, Rank);
	CC_SYNTHESIZE(CCSprite*, m_pSlowDownMark, SlowDownMark);
	

	void setFightUnitCount(int input);	
	int getMaximumUnitCount();

	float getIncreaseInterval();

	void myUpdate(float dt);
	CCPoint getBox2dObjectSize();

	// ����������ԣ���һ���ȼ�����	
	// ��ʼĬ��Ϊ0������UI��û���κ���ʾ
	// ����ÿ��һ����UI�������½Ǽ�һ�����θܸ�
	// ���Ϊ3������Ҳ����3����

	void setLevel(int level);
	int getLevel() { return m_nLevel; }

	void levelUp();
	bool canLevelUp() { return m_nLevel != MAX_PLANET_LEVEL;}

	void speedUp();
	bool canSpeedUp() { return !m_bSpeedUped; }
	bool isSpeedUped() { return m_bSpeedUped; }

	void slowDown();
	bool canSlowDown() { return !m_bSlowDowned; }
	bool isSlowDowned() { return m_bSlowDowned; }
	void slowDownRestore(float dt);

	void cry();

	void stopIncrease();
	void startIncrease();
	void clearSpeedUp();
private:
	int m_nLevel;
	bool m_bSpeedUped;
	bool m_bSlowDowned;
	float m_fLastTimeIncreased;
	bool m_bIncreaseStopped;
};

#endif // Planet_h__