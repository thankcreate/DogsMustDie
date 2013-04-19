#include "Stage1_1Layer.h"
#include "Defines.h"
#include "CatPlanet.h"
#include "DogPlanet.h"
#include "StarObject.h"

Stage1_1Layer::Stage1_1Layer()
{

}

Stage1_1Layer::~Stage1_1Layer()
{

}

bool Stage1_1Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		CCSize size = WIN_SIZE;
			
		/*	CCSprite* pTest = CatPlanet::create();
		pTest->setPosition(ccp);
		this->addChild(pTest, kPlanetLayerIndex);
		getPlanetArray()->addObject(pTest);
		getUpdateArray()->addObject(pTest);


		pTest = DogPlanet::create();
		pTest->setPosition(ccp(size.width / 2 + 200, size.height / 2 + 100));
		this->addChild(pTest, kPlanetLayerIndex);
		getPlanetArray()->addObject(pTest);
		getUpdateArray()->addObject(pTest);
		*/
		CCSprite* pTest = StarObject::create();
		pTest->setPosition(ccp(200, 400));
		this->addChild(pTest, kPlanetLayerIndex);
		getStarArray()->addObject(pTest);

		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_1Layer::initPlanets()
{
	CCSize size = WIN_SIZE;
	makePlanet(kForceSideCat, ccp(size.width / 2 - 200, size.height / 2 - 100), 50, 0);
	makePlanet(kForceSideDog, ccp(size.width / 2 + 200, size.height / 2 + 100), 50, 0);
}

