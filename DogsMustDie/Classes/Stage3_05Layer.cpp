#include "Stage3_05Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_05Layer::Stage3_05Layer()  :
	m_pThird(NULL),
	m_pDog1(NULL),
	m_pDog2(NULL),
	m_pDog3(NULL)
{

}

bool Stage3_05Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_05Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(54,230), 15, 1);
	makePlanet(kForceSideCat, ccp(200,68), 15, 1);
	makePlanet(kForceSideCat, ccp(200,378), 15, 1);
	m_pDog1 = makePlanet(kForceSideDog, ccp(359,230), 20, 2);
	m_pDog2 = makePlanet(kForceSideDog, ccp(494,230), 20, 2);
	m_pDog3 = makePlanet(kForceSideDog, ccp(634,230), 20, 2);

	m_pThird = makePlanet(kForceSideThird, ccp(207,229), 50, 1);	

	makeStar(ccp(71, 83));
	makeStar(ccp(375, 398));
	makeStar(ccp(474, 63));
	makeStar(ccp(600, 400));

	this->scheduleOnce(schedule_selector(Stage3_05Layer::attach1) , 1);
	this->scheduleOnce(schedule_selector(Stage3_05Layer::attach2) , 1.6);
	this->scheduleOnce(schedule_selector(Stage3_05Layer::attach3) , 2.2);

	setStarCountForForceSide(kForceSideCat, 2);
}

void Stage3_05Layer::attach1(float dt)
{
	sendTroopsToPlanet(m_pThird, m_pDog1, 10);
}

void Stage3_05Layer::attach2(float dt)
{
	sendTroopsToPlanet(m_pThird, m_pDog2, 10);
}

void Stage3_05Layer::attach3(float dt)
{
	sendTroopsToPlanet(m_pThird, m_pDog3, 10);
}