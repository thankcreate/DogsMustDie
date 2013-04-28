#include "Stage2_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_02Layer::Stage2_02Layer()
{

}

bool Stage2_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_02Layer::initPlanets()
{
	Planet* cat = makePlanet(kForceSideCat, ccp(70,218), 40, 1);

	Planet* dog = makePlanet(kForceSideDog, ccp(610,218), 40, 2);


	Planet* middleNearToCat = makePlanet(kForceSideMiddle, ccp(528,381), 20, 1);
	middleNearToCat->stopIncrease();
	Planet* middleNearToDog = makePlanet(kForceSideMiddle, ccp(183,66), 20, 1);
	middleNearToDog->stopIncrease();
	
	Planet* third = makePlanet(kForceSideThird, ccp(338, 218), 95, 3);
	
	sendTroopsToPlanet(third, cat, 15);
	sendTroopsToPlanet(third, dog, 15);
	sendTroopsToPlanet(third, middleNearToCat, 15);
	sendTroopsToPlanet(third, middleNearToDog, 15);
	

	makeStar(ccp(156, 373));
	makeStar(ccp(394, 80));
	makeStar(ccp(353, 402));
	makeStar(ccp(605, 84));


}