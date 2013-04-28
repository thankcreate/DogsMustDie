#include "Stage3_03Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_03Layer::Stage3_03Layer() :
	m_pDog1(NULL),
	m_pDog2(NULL),
	m_pCat1(NULL)
{

}

bool Stage3_03Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_03Layer::initPlanets()
{
	m_pCat1 = makePlanet(kForceSideCat, ccp(593, 56), 8, 0);

	m_pDog1 = makePlanet(kForceSideDog, ccp(403,56), 16, 1);
	m_pDog2 = makePlanet(kForceSideDog, ccp(593,229), 16, 1);

	makePlanet(kForceSideMiddle, ccp(192,377), 2, 2)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(94,221), 2, 2)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(384,377), 2, 2)->stopIncrease();

	makeStar(ccp(334, 244));
	makeStar(ccp(153, 93));
	makeStar(ccp(570, 412));

	// 这一关里一开始将AI停掉，过一段时间手动发起进攻
	m_bIsAIStopped = true;

	this->scheduleOnce(schedule_selector(Stage3_03Layer::attack1), 10);
}

void Stage3_03Layer::attack1(float dt)
{
	sendTroopsToPlanet(m_pDog1, m_pCat1);
	sendTroopsToPlanet(m_pDog2, m_pCat1);
	this->scheduleOnce(schedule_selector(Stage3_03Layer::restoreAIUpdate), 24);
	
}

void Stage3_03Layer::restoreAIUpdate(float dt)
{
	m_bIsAIStopped = false;
}