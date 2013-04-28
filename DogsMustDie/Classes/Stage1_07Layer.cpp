#include "Stage1_07Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_07Layer::Stage1_07Layer()
{

}

bool Stage1_07Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_07Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(149,81), 1, 1);
	makePlanet(kForceSideCat, ccp(591,352), 1, 1);
	makePlanet(kForceSideDog, ccp(149,352), 1, 2);
	makePlanet(kForceSideDog, ccp(591,81), 1, 2);


	makePlanet(kForceSideMiddle, ccp(378,219), 15, 3)->stopIncrease();

	makeStar(ccp(377, 356));
	makeStar(ccp(165, 234));
	makeStar(ccp(580, 214));
	makeStar(ccp(390, 79));
}
