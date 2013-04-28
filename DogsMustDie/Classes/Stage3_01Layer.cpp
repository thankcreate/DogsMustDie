#include "Stage3_01Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_01Layer::Stage3_01Layer()
{

}

bool Stage3_01Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_01Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(69,67), 25, 0);
	
	makePlanet(kForceSideMiddle, ccp(235,149), 12, 1)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(408,239), 12, 1)->stopIncrease();

	makePlanet(kForceSideDog, ccp(502,381), 10, 2);
	makePlanet(kForceSideThird, ccp(621,238), 30, 3);

	makeStar(ccp(129, 356));
	makeStar(ccp(464, 112));
	makeStar(ccp(359, 351));

}