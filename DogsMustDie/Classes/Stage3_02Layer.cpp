#include "Stage3_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_02Layer::Stage3_02Layer() :
	m_pDog(NULL),
	m_pMiddle1(NULL),
	m_pMiddle2(NULL)
{

}

bool Stage3_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_02Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(83,79), 25, 1)->speedUp();
	m_pDog = makePlanet(kForceSideDog, ccp(595,391), 40, 2);
	makePlanet(kForceSideDog, ccp(595,267), 10, 1);


	m_pMiddle1 = makePlanet(kForceSideMiddle, ccp(360,170), 12, 2);
	m_pMiddle1->stopIncrease();
	m_pMiddle2 = makePlanet(kForceSideMiddle, ccp(358,284), 12, 2);
	m_pMiddle2->stopIncrease();
	
	makeStar(ccp(142, 231));



}

void Stage3_02Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pDog, m_pMiddle1, 10);
	sendTroopsToPlanet(m_pDog, m_pMiddle2, 20);
}