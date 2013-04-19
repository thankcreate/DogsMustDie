#ifndef FightObject_h__
#define FightObject_h__

#include "GameObject.h"

// FightObject��ָ�ܹ���ս�Ķ���
// Ŀǰ��Ϊ����:
// 1. ����
// 2. ���ɲ���
class FightObject : public  GameObject
{
public:
	FightObject();
	bool init();

	int m_nFightType;
	
	int m_nForceSide;
	
	int getFightType() { return m_nFightType; }
	int getFightUnitCount() { return m_nFightUnitCount; }
	int getForceSide() { return m_nForceSide; }
	virtual void setFightUnitCount(int input) = 0;
	virtual void increaseFightUnitCount(int input);
	virtual void decreaseFightUnitCount(int input);

	virtual int getMaximumUnitCount() = 0;

	

protected:
	int m_nFightUnitCount;
};




#endif // FightObject_h__

