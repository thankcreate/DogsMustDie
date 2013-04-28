#include "Stage2_07Layer.h"
#include "Defines.h"
#include "Planet.h"
#include "MiscTool.h"

Stage2_07Layer::Stage2_07Layer() :
	m_pDog(NULL),
	m_pThird(NULL),
	m_pMiddleToDog1(NULL),
	m_pMiddleToThird1(NULL)
{

}

bool Stage2_07Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_07Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(90,224), 2, 1);
	m_pDog = makePlanet(kForceSideDog, ccp(608,410), 3, 3);
	m_pThird = makePlanet(kForceSideThird, ccp(608,51), 3, 3);

	makePlanet(kForceSideMiddle, ccp(261,226), 8, 1)->stopIncrease();
	m_pMiddleToThird1 = makePlanet(kForceSideMiddle, ccp(442,159), 8, 1);
	m_pMiddleToThird1->stopIncrease();
	m_pMiddleToDog1 = makePlanet(kForceSideMiddle, ccp(442,330), 8, 1);
	m_pMiddleToDog1->stopIncrease();

	makeStar(ccp(165, 371));
	makeStar(ccp(296,391));
	makeStar(ccp(177, 99));
	makeStar(ccp(645, 271));
	makeStar(ccp(614, 170));
	makeStar(ccp(33, 48));
}

void Stage2_07Layer::updateAIExtraForPlanet(Planet* pPlanet)
{
	if(pPlanet == m_pDog
		&& HIT(0.4)
		&& pPlanet->getForceSide() != m_pMiddleToDog1->getForceSide())
	{
		sendTroopsToPlanet(m_pDog, m_pMiddleToDog1)	;
	}
	else if(
		pPlanet == m_pThird 
		&& HIT(0.4)
		&& pPlanet->getForceSide() != m_pMiddleToThird1->getForceSide())
	{
		sendTroopsToPlanet(m_pThird, m_pMiddleToThird1);
	}
}