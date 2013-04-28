#include "Stage1_06Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_06Layer::Stage1_06Layer()
{

}

bool Stage1_06Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_06Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(97,81),  25, 1);
	Planet* dog = makePlanet(kForceSideDog, ccp(612,409), 50, 3);
	
	Planet* middle1 = makePlanet(kForceSideMiddle, ccp(236,371), 7, 1);
	middle1->stopIncrease();

	Planet* middle2 = makePlanet(kForceSideMiddle, ccp(361,245), 7, 1);
	middle2->stopIncrease();

	Planet* middle3 = makePlanet(kForceSideMiddle, ccp(493,128), 7, 1);
	middle3->stopIncrease();

	sendTroopsToPlanet(dog, middle1, 9);
	sendTroopsToPlanet(dog, middle2, 9);
	sendTroopsToPlanet(dog, middle3, 15);

	makeStar(ccp(288, 130));


}


