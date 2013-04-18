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
