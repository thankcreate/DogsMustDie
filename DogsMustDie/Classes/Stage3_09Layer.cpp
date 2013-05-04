#include "Stage3_09Layer.h"
#include "Defines.h"
#include "Planet.h"

#define ROUND_COUNT 4

Stage3_09Layer::Stage3_09Layer() :
	m_pCat(NULL),
	m_pDog(NULL),
	m_pThird(NULL),
	m_pMiddle1(NULL),
	m_pMiddle2(NULL),
	m_pMiddle3(NULL),
	m_nCount1(ROUND_COUNT),
	m_nCount2(ROUND_COUNT),
	m_nCount3(ROUND_COUNT)
{
}

bool Stage3_09Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_09Layer::initPlanets()
{	
	m_pCat = makePlanet(kForceSideCat, ccp(204, 70), 25, 0);
	m_pThird = makePlanet(kForceSideThird, ccp(78, 230), 28, 2);	
	m_pDog = makePlanet(kForceSideDog, ccp(202,390), 28, 2);

	m_pMiddle1 = makePlanet(kForceSideMiddle, ccp(603,70), 22, 1);
	m_pMiddle1->stopIncrease();

	m_pMiddle2 = makePlanet(kForceSideMiddle, ccp(603,230), 22, 1);
	m_pMiddle2->stopIncrease();

	m_pMiddle3 = makePlanet(kForceSideMiddle, ccp(603,390), 22, 1);
	m_pMiddle3->stopIncrease();

	
	m_bIsAIStopped = true;
	setStarCountForForceSide(kForceSideCat, 2);
}

void Stage3_09Layer::initLoadedAction(float dt)
{
	initLoadedAction();
	m_bIsAIStopped = true;
}

void Stage3_09Layer::initLoadedAction()
{
	this->schedule(schedule_selector(Stage3_09Layer::run1), 1);
	this->schedule(schedule_selector(Stage3_09Layer::run2), 1);
	this->schedule(schedule_selector(Stage3_09Layer::run3), 1);	

	this->scheduleOnce(schedule_selector(Stage3_09Layer::restoreAI), 15);
}

void Stage3_09Layer::restoreAI(float dt)
{
	m_bIsAIStopped = false;
}


void Stage3_09Layer::run1(float dt)
{	
	if(--m_nCount1 >= 0)
	{
		sendTroopsToPlanet(m_pMiddle1, m_pCat, 5);
	}
	else 
	{
		
		this->unschedule(schedule_selector(Stage3_09Layer::run1));
	}
}

void Stage3_09Layer::run2(float dt)
{	
	if(--m_nCount2 >= 0)
	{
		sendTroopsToPlanet(m_pMiddle2, m_pThird, 5);
	}
	else 
	{
		this->unschedule(schedule_selector(Stage3_09Layer::run2));
	}
}



void Stage3_09Layer::run3(float dt)
{	
	if(--m_nCount3 >= 0)
	{
		sendTroopsToPlanet(m_pMiddle3, m_pDog, 5);
	}
	else 
	{
		this->unschedule(schedule_selector(Stage3_09Layer::run3));
	}
}