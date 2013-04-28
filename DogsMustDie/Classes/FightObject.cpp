#include "FightObject.h"
#include "Defines.h"

FightObject::FightObject() :
	m_nFightUnitCount(0)
{

}

bool FightObject::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!GameObject::init());
		setType(kGameObjectFight);
		bRet = true;
	}while(0);  

	return bRet;
}

void FightObject::setFightUnitCount( int input )
{
	m_nFightUnitCount = input;
	// To be implemented by inherited class
}

// 现在的逻辑是，如果增加后来的值大于max，则沿用原来的值，而不是把原来的值改成max
void FightObject::increaseFightUnitCount( int input )
{
	int result = m_nFightUnitCount + input;
	int max = getMaximumUnitCount();
	if(result > max)
	{
		result = m_nFightUnitCount;
	}
	setFightUnitCount(result);
}

void FightObject::decreaseFightUnitCount( int input )
{
	int result = m_nFightUnitCount - input;
	int min = 0;
	if(result < min)
	{
		result = min;
	}
	setFightUnitCount(result);
}
