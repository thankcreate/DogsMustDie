#include "Stage2_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_02Layer::Stage2_02Layer() :
	m_pCat(NULL),
	m_pDog(NULL),
	m_pMiddleNearToDog(NULL),
	m_pMiddleNearToCat(NULL),
	m_pThird(NULL)
{

}

bool Stage2_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_02Layer::initPlanets()
{
	m_pCat = makePlanet(kForceSideCat, ccp(70,218), 40, 1);

	m_pDog = makePlanet(kForceSideDog, ccp(610,218), 40, 2);


	m_pMiddleNearToCat = makePlanet(kForceSideMiddle, ccp(528,381), 20, 1);
	m_pMiddleNearToCat->stopIncrease();
	m_pMiddleNearToDog = makePlanet(kForceSideMiddle, ccp(183,66), 20, 1);
	m_pMiddleNearToDog->stopIncrease();
	
	m_pThird = makePlanet(kForceSideThird, ccp(338, 218), 95, 3);
	

	makeStar(ccp(156, 373));
	makeStar(ccp(394, 80));
	makeStar(ccp(353, 402));
	makeStar(ccp(605, 84));
}

void Stage2_02Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pThird, m_pCat, 15);
	sendTroopsToPlanet(m_pThird, m_pDog, 15);
	sendTroopsToPlanet(m_pThird, m_pMiddleNearToCat, 15);
	sendTroopsToPlanet(m_pThird, m_pMiddleNearToDog, 15);	
}