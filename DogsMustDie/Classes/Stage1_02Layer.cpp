#include "Stage1_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_02Layer::Stage1_02Layer() :
	m_pDog(NULL),
	m_pCatRight(NULL)
	
{

}

bool Stage1_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_02Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(170,105), 12, 0);
	m_pCatRight = makePlanet(kForceSideCat, ccp(548,105), 1, 0);
	m_pDog = makePlanet(kForceSideDog, ccp(354,360), 12, 1);
	
	makeStar(ccp(360, 218));	

	m_bIsAIStopped = true;
	this->scheduleOnce(schedule_selector(Stage1_02Layer::attack), 2);
}

void Stage1_02Layer::attack(float dt)
{
	sendTroopsToPlanet(m_pDog, m_pCatRight);
	m_bIsAIStopped = false;
}

