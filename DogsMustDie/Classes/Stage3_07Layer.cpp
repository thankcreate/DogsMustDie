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
	makePlanet(kForceSideCat, ccp(134,83), 2, 0);
	makePlanet(kForceSideCat, ccp(351,83), 2, 0);
	makePlanet(kForceSideCat, ccp(585,83), 2, 0);

	makePlanet(kForceSideDog, ccp(134,359), 3, 1);
	makePlanet(kForceSideDog, ccp(351,359), 3, 1);
	makePlanet(kForceSideDog, ccp(585,359), 3, 1);
	

	makeStar(ccp(43, 246));
	makeStar(ccp(113, 202));
	makeStar(ccp(183, 246));
	makeStar(ccp(253, 202));
	makeStar(ccp(323, 246));
	makeStar(ccp(393, 202));
	makeStar(ccp(463, 246));
	makeStar(ccp(533, 202));
	makeStar(ccp(603, 246));
	makeStar(ccp(673, 202));

}