#include "Planet.h"
#include "Defines.h"
Planet::Planet() :	
	m_pAvatar(NULL),
	m_pFightUnitLabel(NULL)
{
}



bool Planet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!FightObject::init());
		m_nFightType = kFightPlanet;
		bRet = true;
	}while(0);

	return bRet;
}

void Planet::setFightUnitCount( int input )
{
	FightObject::setFightUnitCount(input);

}

