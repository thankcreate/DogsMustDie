#include "Stage1_03Layer.h"
#include "Defines.h"
#include "Planet.h"
#include "MyUseDefaultDef.h"

Stage1_03Layer::Stage1_03Layer() :
	m_pGuideBorder(NULL),
	m_pGuideLabel(NULL)
{

}

bool Stage1_03Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());

		bool first = LoadBooleanFromXML(KEY_Stage_1_03_FIRST_JUDGE_SHOW_MIDDLE_PROMPT, true);
		if(first)
		{
			SaveBooleanToXML(KEY_Stage_1_03_FIRST_JUDGE_SHOW_MIDDLE_PROMPT, false);
			SaveUserDefault();
			initGuideLayer();
		}
		
		bRet = true;
	} while (0);

	return bRet;
}


void Stage1_03Layer::initGuideLayer()
{
	setGuideBorder(CCSprite::create("StageBase_notice1.png"));
	CCSize borderSize = m_pGuideBorder->boundingBox().size;
	CCSize winSize = WIN_SIZE;
	m_pGuideBorder->setPosition(ccp(156, 181));
	this->addChild(m_pGuideBorder, kGuideLayerIndex);	

	//setGuideLabel(CCLabelTTF::create("Good day, commander! \nStupid dogs are comming.\nWe should teach them a lesson, mew~", FONT_00_STARMAP_TRUETYPE, 30));	
	setGuideLabel(CCLabelTTF::create("This is a neutral planet, it will not launch an attack on own initiative", "Arial", 23));		
	m_pGuideLabel->setDimensions(CCSizeMake(209, 200));
	m_pGuideLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_pGuideLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);

	ccColor3B ccMyOrange={255, 104, 0};
	m_pGuideLabel->setPosition(ccp(140,80));
	m_pGuideLabel->setColor(ccMyOrange);
	m_pGuideBorder->addChild(m_pGuideLabel);
		
	this->scheduleOnce(schedule_selector(Stage1_03Layer::moveLeftGuideLayer), 6);
}


void Stage1_03Layer::moveLeftGuideLayer(float dt)
{
	CCSize winSize = WIN_SIZE;
	CCMoveBy* pLeft = CCMoveBy::create(0.5, ccp(-340, 0));
	m_pGuideBorder->runAction(pLeft);
}


void Stage1_03Layer::initPlanets()
{
	makePlanet(kForceSideMiddle, ccp(216,334), 5, 0)->stopIncrease();
	makePlanet(kForceSideCat, ccp(356,145), 12, 0);
	makePlanet(kForceSideDog, ccp(524,334), 12, 2);

	makeStar(ccp(193, 183));
	makeStar(ccp(639, 214));		
}

