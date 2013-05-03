#include "Stage2_04Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_04Layer::Stage2_04Layer() :
	m_pCat(NULL),
	m_pDog1(NULL),
	m_pDog2(NULL),
	m_pMiddle1(NULL),
	m_pMiddle2(NULL)
{
}

bool Stage2_04Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_04Layer::initPlanets()
{
	m_pCat = makePlanet(kForceSideCat, ccp(319,71),  25, 0);
	m_pDog1 = makePlanet(kForceSideDog, ccp(493, 363), 20, 1);
	m_pDog2 = makePlanet(kForceSideDog, ccp(612, 249), 20, 1);

	m_pMiddle1 = makePlanet(kForceSideMiddle, ccp(138,118), 0, 3);
	m_pMiddle1->stopIncrease();

	m_pMiddle2 = makePlanet(kForceSideMiddle, ccp(123,249), 0, 3);
	m_pMiddle2->stopIncrease();	

	makeStar(ccp(353, 242));
	makeStar(ccp(201, 360));
}


void Stage2_04Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pDog1, m_pCat, 16);
	sendTroopsToPlanet(m_pDog2, m_pCat, 16);
}