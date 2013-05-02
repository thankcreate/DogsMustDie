#include "Stage1_02Layer.h"
#include "Defines.h"
#include "Planet.h"

Stage1_02Layer::Stage1_02Layer() :
	m_pDog(NULL),
	m_pCatRight(NULL),
	m_pGuideBorder(NULL),
	m_pGuideLabel(NULL)	
{
}

bool Stage1_02Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());		
		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_02Layer::initPlanets()
{
	makePlanet(kForceSideCat, ccp(170,105), 12, 0)->speedUp();
	m_pCatRight = makePlanet(kForceSideCat, ccp(548,105), 1, 0);	
	m_pDog = makePlanet(kForceSideDog, ccp(354,360), 12, 0);
	
	makeStar(ccp(360, 218));	

	m_bIsAIStopped = true;
	this->scheduleOnce(schedule_selector(Stage1_02Layer::attack), 2);
	this->scheduleOnce(schedule_selector(Stage1_02Layer::initGuideLayer), 2.8);
}

void Stage1_02Layer::attack(float dt)
{
	sendTroopsToPlanet(m_pDog, m_pCatRight);
	m_bIsAIStopped = false;
}


void Stage1_02Layer::initGuideLayer(float dt)
{
	setGuideBorder(CCSprite::create("StageBase_notice2.png"));
	CCSize borderSize = m_pGuideBorder->boundingBox().size;
	CCSize winSize = WIN_SIZE;
	m_pGuideBorder->setPosition(ccp(550, 244));
	this->addChild(m_pGuideBorder, kTroopsLayerIndex - 1);	

	//setGuideLabel(CCLabelTTF::create("Good day, commander! \nStupid dogs are comming.\nWe should teach them a lesson, mew~", "00 Starmap Truetype.ttf", 30));	
	setGuideLabel(CCLabelTTF::create(">_<\nWe are under attack. Help! Help!", "Arial", 23));		
	m_pGuideLabel->setDimensions(CCSizeMake(196, 80));
	m_pGuideLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_pGuideLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);

	ccColor3B ccMyOrange={255, 104, 0};
	m_pGuideLabel->setPosition(ccp(142,86));
	m_pGuideLabel->setColor(ccMyOrange);
	m_pGuideBorder->addChild(m_pGuideLabel);

	this->scheduleOnce(schedule_selector(Stage1_02Layer::moveRightGuideLayer), 4);
}


void Stage1_02Layer::moveRightGuideLayer(float dt)
{
	CCSize winSize = WIN_SIZE;
	CCMoveBy* pRight = CCMoveBy::create(0.5, ccp(425, 0));
	m_pGuideBorder->runAction(pRight);
}
