#include "Stage3_04Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_04Layer::Stage3_04Layer()
{

}

bool Stage3_04Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_04Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(69,199), 15, 1);
	makePlanet(kForceSideCat, ccp(71,57), 15, 1);
	makePlanet(kForceSideThird, ccp(243, 56), 12, 3);



	makePlanet(kForceSideDog, ccp(619, 365), 15, 2);
	makePlanet(kForceSideDog, ccp(619, 229), 15, 2);
	makePlanet(kForceSideThird, ccp(452, 365), 12, 3);


	makePlanet(kForceSideMiddle, ccp(359, 212), 12, 1)->stopIncrease();

	makeStar(ccp(292, 394));
	makeStar(ccp(134, 300));
	makeStar(ccp(415, 50));
	makeStar(ccp(635, 88));
}