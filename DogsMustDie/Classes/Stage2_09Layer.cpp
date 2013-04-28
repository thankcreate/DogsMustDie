#include "Stage2_09Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_09Layer::Stage2_09Layer()
{

}

bool Stage2_09Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_09Layer::initPlanets()
{
	Planet* cat1 = makePlanet(kForceSideCat, ccp(86,245), 20, 1);
	Planet* cat2 = makePlanet(kForceSideCat, ccp(199,120), 20, 1);

	Planet* dog1 = makePlanet(kForceSideDog, ccp(583,245), 25, 2);
	Planet* dog2 = makePlanet(kForceSideDog, ccp(472,120), 25, 2);

	Planet* third = makePlanet(kForceSideThird, ccp(346,320), 70, 3);
	third->setScale(1.5);

	sendTroopsToPlanet(third, cat1, 10);
	sendTroopsToPlanet(third, cat2, 10);
	sendTroopsToPlanet(third, dog1, 10);
	sendTroopsToPlanet(third, dog2, 10);

	makeStar(ccp(42, 130));
	makeStar(ccp(94, 42));
	makeStar(ccp(343, 198));
	makeStar(ccp(549, 412));
	makeStar(ccp(633, 95));
}