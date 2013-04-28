#include "Stage3_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_02Layer::Stage3_02Layer()
{

}

bool Stage3_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_02Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(83,79), 25, 1)->speedUp();
	Planet* dog = makePlanet(kForceSideDog, ccp(595,391), 40, 2);
	makePlanet(kForceSideDog, ccp(595,267), 10, 1);


	Planet* middle1 = makePlanet(kForceSideMiddle, ccp(360,170), 12, 2);
	middle1->stopIncrease();
	Planet* middle2 = makePlanet(kForceSideMiddle, ccp(358,284), 12, 2);
	middle2->stopIncrease();
	
	makeStar(ccp(142, 231));

	sendTroopsToPlanet(dog, middle1, 10);
	sendTroopsToPlanet(dog, middle2, 20);

}