#include "Stage2_03Layer.h"
#include "Defines.h"
#include "Planet.h"
#include "MiscTool.h"

Stage2_03Layer::Stage2_03Layer()  :
	m_pMiddleToDog1(NULL),
	m_pMiddleToDog2(NULL)
{

}

bool Stage2_03Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_03Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(77, 61), 2, 1);



	makePlanet(kForceSideDog, ccp(610,399), 2, 3);

	m_pMiddleToDog1 = makePlanet(kForceSideMiddle, ccp(433, 399), 8, 2);
	m_pMiddleToDog1->stopIncrease();
	m_pMiddleToDog2 = makePlanet(kForceSideMiddle, ccp(610, 240), 8, 2);
	m_pMiddleToDog2->stopIncrease();

	makePlanet(kForceSideMiddle, ccp(77, 215), 8, 2)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(253, 61), 8, 2)->stopIncrease();

	makeStar(ccp(205, 341));
	makeStar(ccp(305, 199));
	makeStar(ccp(444, 115));
	makeStar(ccp(559, 76));


}

void Stage2_03Layer::extraUpdateAIForPlanet( Planet* pPlanet )
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

