#include "Stage1_05Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_05Layer::Stage1_05Layer()
{

}

bool Stage1_05Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_05Layer::initPlanets()
{
	
	makePlanet(kForceSideDog, ccp(272,381), 9, 0);
	makePlanet(kForceSideDog, ccp(112,279), 9, 0);

	makePlanet(kForceSideCat, ccp(389,206), 10, 0);

	makePlanet(kForceSideMiddle, ccp(531,61), 3, 3)->stopIncrease();
	makePlanet(kForceSideMiddle, ccp(590,247), 3, 3)->stopIncrease();

	makeStar(ccp(261, 112));
	makeStar(ccp(551, 403));


}

