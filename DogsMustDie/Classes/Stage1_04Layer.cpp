#include "Stage1_04Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_04Layer::Stage1_04Layer()
{

}

bool Stage1_04Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_04Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(532,323), 15, 0);
	Planet* dog = makePlanet(kForceSideDog, ccp(143,112), 22, 1);

	Planet* middle1 = makePlanet(kForceSideMiddle, ccp(250,323), 5, 0);
	middle1->stopIncrease();

	Planet* middle2 = makePlanet(kForceSideMiddle, ccp(440,112), 5, 0);
	middle2->stopIncrease();

	sendTroopsToPlanet(dog, middle1, 9);
	sendTroopsToPlanet(dog, middle2, 9);
	
	makeStar(ccp(360, 218));
}

