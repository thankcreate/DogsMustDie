#include "Stage1_03Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_03Layer::Stage1_03Layer()
{

}

bool Stage1_03Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_03Layer::initPlanets()
{
	makePlanet(kForceSideMiddle, ccp(216,334), 5, 0)->stopIncrease();
	makePlanet(kForceSideCat, ccp(356,145), 12, 0);
	makePlanet(kForceSideDog, ccp(524,334), 12, 3);

	makeStar(ccp(193, 183));
	makeStar(ccp(639, 214));		
}
