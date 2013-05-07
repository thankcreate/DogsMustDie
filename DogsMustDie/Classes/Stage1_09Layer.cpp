#include "Stage1_09Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_09Layer::Stage1_09Layer()
{

}

bool Stage1_09Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_09Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(264, 210), 3, 1);  // 中间
	makePlanet(kForceSideCat, ccp(160, 368), 3, 0);
	makePlanet(kForceSideCat, ccp(118, 67), 3, 0);
	
	
	makePlanet(kForceSideDog, ccp(480, 210), 4, 2); // 中间
	makePlanet(kForceSideDog, ccp(612, 71), 4, 1);
	makePlanet(kForceSideDog, ccp(612, 368), 4, 1);

	makeStar(ccp(51, 286));
	makeStar(ccp(139, 248));
	makeStar(ccp(260, 77));

	makeStar(ccp(455, 358));
	makeStar(ccp(451, 65));
	makeStar(ccp(628, 242));
}