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

	// ���ڲ�ͬ����������ụ��ת��������Planet����Ҫ��Ƶþ��п�ת����
	// ������ת��������delete��һ��planet���½�һ��planet
	// ����Ĵ�array��remove����add���Ĺ��̷ǳ����׳���
	static Planet* createWithForceSide(int force);
	void initWithForceSide(int force);
		
	CC_SYNTHESIZE(Face*, m_pFace, Face);	// �������ĵ�ռ������ͷ��
	CC_SYNTHESIZE(CCLabelTTF*, m_pFightUnitLabel, FightUnitLabel );

	void setFightUnitCount(int input);	
	int getMaximumUnitCount();

	float getIncreaseInterval();

	void myUpdate(float dt);
	CCPoint getBox2dObjectSize();

	// ����������ԣ���һ���ȼ�����	
	// ��ʼĬ��Ϊ0������UI��û���κ���ʾ
	// ����ÿ��һ����UI�������½Ǽ�һ�����θܸ�
	// ���Ϊ3������Ҳ����3����
private:
	int m_nLevel;
	float m_fLastTimeIncreased;
};

#endif // Planet_h__
