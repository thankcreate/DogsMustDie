#include "Stage2_05Layer.h"
#include "Defines.h"
#include "Planet.h"
#include "MiscTool.h"
#include "StageBaseLayer.h"

Stage2_05Layer::Stage2_05Layer() :
	m_pMiddleToDog1(NULL),
	m_pMiddleToDog2(NULL),
	m_pMiddleToCat1(NULL),
	m_pMiddleToCat2(NULL),
	m_pThird(NULL),
	m_pDog(NULL)
{

}

bool Stage2_05Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_05Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(264,378), 20, 0);
	m_pDog = makePlanet(kForceSideDog, ccp(437,47), 20, 2);
	
	m_pThird = makePlanet(kForceSideThird, ccp(350,205), 65, 3);

	m_pMiddleToDog1 = makePlanet(kForceSideMiddle, ccp(581, 145), 15, 1);
	m_pMiddleToDog1->stopIncrease();
	m_pMiddleToDog2 = makePlanet(kForceSideMiddle, ccp(607, 297), 15, 1);
	m_pMiddleToDog2->stopIncrease();

	m_pMiddleToCat1 = makePlanet(kForceSideMiddle, ccp(110, 303), 15, 1);
	m_pMiddleToCat1->stopIncrease();
	m_pMiddleToCat2 = makePlanet(kForceSideMiddle, ccp(63, 146), 15, 1);
	m_pMiddleToCat2->stopIncrease();

	makeStar(ccp(428, 408));
	makeStar(ccp(315, 58));
	makeStar(ccp(582, 415));
}

void Stage2_05Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pThird,m_pMiddleToDog1, 10);
	sendTroopsToPlanet(m_pThird,m_pMiddleToDog2, 10);
	sendTroopsToPlanet(m_pThird,m_pMiddleToCat1, 10);
	sendTroopsToPlanet(m_pThird,m_pMiddleToCat2, 10);
}


void Stage2_05Layer::extraUpdateAIForPlanet( Planet* pPlanet )
{
	if(pPlanet == m_pDog)
	{
		if(m_pMiddleToDog2->getForceSide() == kForceSideMiddle)
		{
			if(HIT(0.3))
			{
				sendTroopsToPlanet(pPlanet, m_pMiddleToDog2);
			}
		}

		if(m_pMiddleToDog1->getForceSide() == kForceSideMiddle)
		{
			if(HIT(0.3))
			{
				sendTroopsToPlanet(pPlanet, m_pMiddleToDog1);
			}
		}
	}
	
}