#include "Stage1_08Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_08Layer::Stage1_08Layer()
{

}

bool Stage1_08Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_08Layer::initPlanets()
{
	Planet* cat = makePlanet(kForceSideCat, ccp(368, 207), 90, 3);

	Planet* dog1 = makePlanet(kForceSideDog, ccp(144, 208), 23, 1);
	Planet* dog2 = makePlanet(kForceSideDog, ccp(595, 208), 23, 1);
	Planet* dog3 = makePlanet(kForceSideDog, ccp(368, 52), 23, 1);
	Planet* dog4 = makePlanet(kForceSideDog, ccp(368, 369), 23, 1);

	sendTroopsToPlanet(dog1, cat , 15);	
	sendTroopsToPlanet(dog2, cat , 15);
	sendTroopsToPlanet(dog3, cat , 15);
	sendTroopsToPlanet(dog4, cat , 15);
}
