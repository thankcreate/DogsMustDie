#include "Stage1_1Layer.h"
#include "Defines.h"
#include "CatPlanet.h"
#include "DogPlanet.h"
#include "StarObject.h"
#include "StageBaseLayer.h"

Stage1_1Layer::Stage1_1Layer() :
	m_pGuideBorder(NULL),
	m_pGuideLabel(NULL),
	m_pFinger(NULL),
	m_pDogPlanet1(NULL)
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

		//StarObject* pTest = StarObject::create();
		//pTest->setPosition(ccp(200, 400));
		//this->addChild(pTest, kPlanetLayerIndex);
		//getStarArray()->addObject(pTest);
		//pTest->createBox2dObject(m_pWorld);
		//getUpdateArray()->addObject(pTest);


		//pTest = StarObject::create();
		//pTest->setPosition(ccp(300, 400));
		//this->addChild(pTest, kPlanetLayerIndex);
		//getStarArray()->addObject(pTest);
		//pTest->createBox2dObject(m_pWorld);
		//getUpdateArray()->addObject(pTest);

		initGuideLayer();

		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_1Layer::initPlanets()
{
	CCSize size = WIN_SIZE;
	Planet* pPlanet = NULL;
	pPlanet = makePlanet(kForceSideCat, ccp(190, 370), 30, 0);
	pPlanet->stopIncrease();

	pPlanet = makePlanet(kForceSideDog, ccp(540, 370), 10, 0);
	setDogPlanet1(pPlanet);
	pPlanet->stopIncrease();
}

void Stage1_1Layer::initGuideLayer()
{
	setGuideBorder(CCSprite::create("StageBase_guide_border.png"));
	CCSize borderSize = m_pGuideBorder->boundingBox().size;
	CCSize winSize = WIN_SIZE;
	m_pGuideBorder->setPosition(ccp(winSize.width / 2 - 50, borderSize.height / 2));
	this->addChild(m_pGuideBorder, kPannelLayerIndex);
	

	setGuideLabel(CCLabelTTF::create("Good day, commander! \nStupid dogs are comming.\nWe should teach them a lesson, mew~", "00 Starmap Truetype.ttf", 30));	
	m_pGuideLabel->setDimensions(CCSizeMake(420, 110));
	//m_pGuideLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	
	ccColor3B ccMyOrange={255, 104, 0};
	m_pGuideLabel->setPosition(ccp(250,60));
	m_pGuideLabel->setColor(ccMyOrange);
	m_pGuideBorder->addChild(m_pGuideLabel);
		
	this->schedule(schedule_selector(Stage1_1Layer::guideDragToOccupy), 3);
}

void Stage1_1Layer::guideDragToOccupy(float dt)
{
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString("Drag as above to occupy the dog planet.\n Each drag will send half the troops");
	}

	if(!m_pFinger)
	{
		setFinger(CCSprite::create("Finger.png"));
		this->addChild(m_pFinger, kPannelLayerIndex);
	}
	m_pFinger->setVisible(true);
	m_pFinger->setPosition(ccp(215, 295));	
	float xDistance = 540 - 190;
	CCMoveBy* pMove = CCMoveBy::create(1.5, ccp(xDistance, 0));
	m_pFinger->runAction(pMove);
}

void Stage1_1Layer::guideDragToStar()
{
	if(!m_pGuideLabel)
		return;

	if(!m_pFinger)
	{
		setFinger(CCSprite::create("Finger.png"));
		this->addChild(m_pFinger, kPannelLayerIndex);
	}

}

void Stage1_1Layer::sendTroopsToPlanet( int force, Planet* fromPlanet, Planet* toPlanet )
{
	StageBaseLayer::sendTroopsToPlanet(force, fromPlanet, toPlanet);
	if(toPlanet == m_pDogPlanet1
		&& toPlanet!= NULL)
	{
		// 说明已经完成了drag动作
		this->unschedule(schedule_selector(Stage1_1Layer::guideDragToOccupy));
		if(m_pFinger)
		{
			m_pFinger->setVisible(false);			
		}
	}
}

void Stage1_1Layer::sendTroopsToStar( int force, Planet* fromPlanet, StarObject* toStar )
{
	StageBaseLayer::sendTroopsToStar(force, fromPlanet, toStar);
}


void Stage1_1Layer::planetOccupied(Planet* pPlanet)
{
	if(pPlanet == m_pDogPlanet1
		&& pPlanet != NULL)
	{

	}
}