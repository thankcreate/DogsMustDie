#include "Stage3_09Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_09Layer::Stage3_09Layer()
{

}

bool Stage3_09Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_09Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(170,105), 0, 0);
	makePlanet(kForceSideDog, ccp(548,105), 0, 0);
	makePlanet(kForceSideMiddle, ccp(354,360), 12, 1);

	makeStar(ccp(360, 218));


}