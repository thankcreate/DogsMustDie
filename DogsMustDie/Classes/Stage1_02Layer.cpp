#include "Stage1_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_02Layer::Stage1_02Layer()
{

}

bool Stage1_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_02Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(170,105), 12, 0);
	Planet* catRight = makePlanet(kForceSideCat, ccp(548,105), 1, 0);
	Planet* dog = makePlanet(kForceSideDog, ccp(354,360), 12, 1);
	sendTroopsToPlanet(dog, catRight);
	makeStar(ccp(360, 218));	
}

