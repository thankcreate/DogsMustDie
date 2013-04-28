#include "Stage2_01Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_01Layer::Stage2_01Layer()
{

}

bool Stage2_01Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_01Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(360,81), 4, 0);
	makePlanet(kForceSideDog, ccp(505,292), 4, 1);
	makePlanet(kForceSideThird, ccp(194,292), 4, 1);

	makeStar(ccp(82, 306));
	makeStar(ccp(590, 406));
	makeStar(ccp(163, 101));
	makeStar(ccp(581, 87));
	makeStar(ccp(349, 221));
}