#include "Stage3_08Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_08Layer::Stage3_08Layer()
{

}

bool Stage3_08Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_08Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(65,69), 12, 0);
	makePlanet(kForceSideDog, ccp(353,395), 12, 1);
	makePlanet(kForceSideThird, ccp(618,69), 12, 1);

	makePlanet(kForceSideMiddle, ccp(209,232), 8, 1)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(485.5,232), 8, 1)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(353,69), 8, 1)->stopIncrease();

	makeStar(ccp(45, 252));
	makeStar(ccp(136, 392));
	makeStar(ccp(593, 400));
	makeStar(ccp(359, 218));
	makeStar(ccp(204, 127));
	makeStar(ccp(472, 124));
}