#include "Stage2_04Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_04Layer::Stage2_04Layer()
{

}

bool Stage2_04Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_04Layer::initPlanets()
{
	Planet* cat = makePlanet(kForceSideCat, ccp(319,71),  25, 0);
	Planet* dog1 = makePlanet(kForceSideDog, ccp(493, 363), 20, 1);
	Planet* dog2 = makePlanet(kForceSideDog, ccp(612, 249), 20, 1);

	Planet* middle1 = makePlanet(kForceSideMiddle, ccp(138,118), 0, 3);
	middle1->stopIncrease();

	Planet* middle2 = makePlanet(kForceSideMiddle, ccp(123,249), 0, 3);
	middle2->stopIncrease();	

	sendTroopsToPlanet(dog1, cat, 16);
	sendTroopsToPlanet(dog2, cat, 16);

	makeStar(ccp(353, 242));
	makeStar(ccp(201, 360));


}
