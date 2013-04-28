#include "Stage2_08Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage2_08Layer::Stage2_08Layer()
{

}

bool Stage2_08Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage2_08Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(352,207), 42, 3);

	makePlanet(kForceSideDog, ccp(84, 205), 12, 1);
	makePlanet(kForceSideDog, ccp(488, 356), 12, 1);
	makePlanet(kForceSideDog, ccp(489, 54), 12, 1);


	makePlanet(kForceSideThird, ccp(218, 54), 12, 1);
	makePlanet(kForceSideThird, ccp(218, 356), 12, 1);
	makePlanet(kForceSideThird, ccp(618, 205), 12, 1);

	makeStar(ccp(354, 351));
	makeStar(ccp(217, 208));
	makeStar(ccp(490, 210));
	makeStar(ccp(62, 60));
	makeStar(ccp(637, 37));


}