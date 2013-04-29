#include "Stage3_06Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage3_06Layer::Stage3_06Layer()
{

}

bool Stage3_06Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void Stage3_06Layer::initPlanets()
{
	makePlanet(kForceSideDog, ccp(394,57), 2, 1);
	makePlanet(kForceSideDog, ccp(568,159), 2, 1);

	makePlanet(kForceSideThird, ccp(175,103), 2, 0);
	makePlanet(kForceSideThird, ccp(339,218), 2, 0);
	makePlanet(kForceSideThird, ccp(509,319), 2, 0);


	makePlanet(kForceSideCat, ccp(98, 267), 2, 1);
	makePlanet(kForceSideCat, ccp(267, 376), 2, 1);

	makeStar(ccp(135, 392));
	makeStar(ccp(44, 35));

	setStarCountForForceSide(kForceSideCat, 2);
}