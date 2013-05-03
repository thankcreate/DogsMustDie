#include "Stage2_06Layer.h"
#include "Defines.h"
#include "Planet.h"
#include "StageBaseLayer.h"

Stage2_06Layer::Stage2_06Layer() :
	m_pCatMiddle(NULL),
	m_pDogMiddle(NULL),
	m_pThird(NULL)
{
}

bool Stage2_06Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_06Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(112,60), 25, 1);
	m_pCatMiddle = makePlanet(kForceSideCat, ccp(112,197), 25, 2);
	makePlanet(kForceSideCat, ccp(112,334), 25, 1);

	makePlanet(kForceSideDog, ccp(581,60), 25, 2);
	m_pDogMiddle = makePlanet(kForceSideDog, ccp(581,197), 25, 2);
	makePlanet(kForceSideDog, ccp(581,334), 25, 2);

	m_pThird = makePlanet(kForceSideThird, ccp(354, 197), 50, 3);

	makeStar(ccp(237, 60));
	makeStar(ccp(237, 334));
	makeStar(ccp(453, 60));
	makeStar(ccp(453, 334));
	makeStar(ccp(354, 334));
}


void Stage2_06Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pThird, m_pCatMiddle, 12);
	sendTroopsToPlanet(m_pThird, m_pDogMiddle, 12);
}