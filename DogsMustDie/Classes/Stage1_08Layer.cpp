#include "Stage1_08Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_08Layer::Stage1_08Layer() :
	m_pCat(NULL),
	m_pDog1(NULL),
	m_pDog2(NULL),
	m_pDog3(NULL),
	m_pDog4(NULL)

{

}

bool Stage1_08Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_08Layer::initPlanets()
{
	m_pCat = makePlanet(kForceSideCat, ccp(368, 207), 94, 3);

	m_pDog1 = makePlanet(kForceSideDog, ccp(144, 208), 23, 1);
	m_pDog2 = makePlanet(kForceSideDog, ccp(595, 208), 23, 1);
	m_pDog3 = makePlanet(kForceSideDog, ccp(368, 52), 23, 1);
	m_pDog4 = makePlanet(kForceSideDog, ccp(368, 369), 23, 1);

}


void Stage1_08Layer::initLoadedAction()
{

	sendTroopsToPlanet(m_pDog1, m_pCat , 15);	
	sendTroopsToPlanet(m_pDog2, m_pCat , 15);
	sendTroopsToPlanet(m_pDog3, m_pCat , 15);
	sendTroopsToPlanet(m_pDog4, m_pCat , 15);
}