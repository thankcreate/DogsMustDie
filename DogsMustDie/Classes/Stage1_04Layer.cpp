#include "Stage1_04Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_04Layer::Stage1_04Layer() :
	m_pDog(NULL),
	m_pMiddle1(NULL),
	m_pMiddle2(NULL)
{

}

bool Stage1_04Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_04Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(532,323), 16, 0);
	m_pDog = makePlanet(kForceSideDog, ccp(143,112), 20, 1);

	m_pMiddle1 = makePlanet(kForceSideMiddle, ccp(250,323), 5, 0);
	m_pMiddle1->stopIncrease();

	m_pMiddle2 = makePlanet(kForceSideMiddle, ccp(440,112), 5, 0);
	m_pMiddle2->stopIncrease();


	makeStar(ccp(360, 218));
}



void Stage1_04Layer::initLoadedAction()
{
	sendTroopsToPlanet(m_pDog, m_pMiddle1, 9);
	sendTroopsToPlanet(m_pDog, m_pMiddle2, 9);
}