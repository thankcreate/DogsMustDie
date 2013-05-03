#include "Stage1_06Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_06Layer::Stage1_06Layer() :
	m_pDog(NULL),
	m_pMiddle1(NULL),
	m_pMiddle2(NULL),
	m_pMiddle3(NULL)
{

}

bool Stage1_06Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_06Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(97,81),  25, 1);
	m_pDog = makePlanet(kForceSideDog, ccp(612,409), 50, 3);
	
	m_pMiddle1 = makePlanet(kForceSideMiddle, ccp(236,371), 7, 1);
	m_pMiddle1->stopIncrease();

	m_pMiddle2 = makePlanet(kForceSideMiddle, ccp(361,245), 7, 1);
	m_pMiddle2->stopIncrease();

	m_pMiddle3 = makePlanet(kForceSideMiddle, ccp(493,128), 7, 1);
	m_pMiddle3->stopIncrease();


	makeStar(ccp(288, 130));
}

void Stage1_06Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pDog, m_pMiddle1, 9);
	sendTroopsToPlanet(m_pDog, m_pMiddle2, 9);
	sendTroopsToPlanet(m_pDog, m_pMiddle3, 15);
}

