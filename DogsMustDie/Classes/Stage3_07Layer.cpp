#include "Stage3_07Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_07Layer::Stage3_07Layer()
{

}

bool Stage3_07Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_07Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(170,105), 0, 0);
	makePlanet(kForceSideDog, ccp(548,105), 0, 0);
	makePlanet(kForceSideMiddle, ccp(354,360), 12, 1);

	makeStar(ccp(360, 218));


}