#include "Stage1_2Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_2Layer::Stage1_2Layer()
{

}

bool Stage1_2Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_2Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(291,110), 20, 0);
	makePlanet(kForceSideDog, ccp(543,353), 16, 0);
	makePlanet(kForceSideMiddle, ccp(197,353), 8, 0)->stopIncrease();

	makeStar(ccp(387, 359));
}

