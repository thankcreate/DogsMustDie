#include "Stage1_02Layer.h"
#include "Defines.h"
#include "Planet.h"
#include "StageBaseScene.h"
#include "MyUseDefaultDef.h"

Stage1_02Layer::Stage1_02Layer() :
	m_pDog(NULL),
	m_pCatRight(NULL),
	m_pGuideBorder(NULL),
	m_pScorePrompt(NULL),
	m_pScorePromptLabel(NULL)
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
	
}

void Stage1_02Layer::initLoadedAction(float dt)
{
	initLoadedAction();
	m_bIsAIStopped = true;
}

void Stage1_02Layer::initLoadedAction()
{
	m_bIsAIStopped = true;
	this->scheduleOnce(schedule_selector(Stage1_02Layer::attack),  2);
	this->scheduleOnce(schedule_selector(Stage1_02Layer::initGuideLayer), 2.8);

	bool first = LoadBooleanFromXML(KEY_Stage_1_02_FIRST_JUDGE_SHOW_SCORE_PROMPT, true);
	if(first)
	{
		SaveBooleanToXML(KEY_Stage_1_02_FIRST_JUDGE_SHOW_SCORE_PROMPT, false);
		SaveUserDefault();
		this->scheduleOnce(schedule_selector(Stage1_02Layer::showScorePrompt), 8);
	}	
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
		
	CCLabelTTF* pGuideLabel = CCLabelTTF::create(">_<\nWe are under attack. Help! Help!", "Arial", 23);
	pGuideLabel->setDimensions(CCSizeMake(196, 200));
	pGuideLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	pGuideLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);

	ccColor3B ccMyOrange={255, 104, 0};
	pGuideLabel->setPosition(ccp(142,86));
	pGuideLabel->setColor(ccMyOrange);
	m_pGuideBorder->addChild(pGuideLabel);

	this->scheduleOnce(schedule_selector(Stage1_02Layer::moveRightGuideLayer),  4);
}


void Stage1_02Layer::showScorePrompt(float dt)
{
	setScorePrompt(CCSprite::create("StageBase_notice2.png"));
	CCSize borderSize = m_pScorePrompt->boundingBox().size;
	CCSize winSize = WIN_SIZE;
	m_pScorePrompt->setPosition(ccp(173, 244));
	this->addChild(m_pScorePrompt, kTroopsLayerIndex - 1);	
		
	setScorePromptLabel(CCLabelTTF::create("The less time costs, the better score mark you'll have", "Arial", 20));
	m_pScorePromptLabel->setDimensions(CCSizeMake(196, 200));
	m_pScorePromptLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_pScorePromptLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);

	ccColor3B ccMyOrange={255, 104, 0};
	m_pScorePromptLabel->setPosition(ccp(142,86));
	m_pScorePromptLabel->setColor(ccMyOrange);
	m_pScorePrompt->addChild(m_pScorePromptLabel);

	this->scheduleOnce(schedule_selector(Stage1_02Layer::showNextScorePrompt),  4);	
}

void Stage1_02Layer::showNextScorePrompt(float dt)
{
	m_pScorePromptLabel->setString("Try your best to win with 3 score marks! Meow~");
	this->scheduleOnce(schedule_selector(Stage1_02Layer::moveLeftScorePromptLayer),  3);	
}

void Stage1_02Layer::moveLeftScorePromptLayer(float dt)
{
	CCSize winSize = WIN_SIZE;
	CCMoveBy* pLeft = CCMoveBy::create(0.5, ccp(-410, 0));
	m_pScorePrompt->runAction(pLeft);
}


void Stage1_02Layer::moveRightGuideLayer(float dt)
{
	CCSize winSize = WIN_SIZE;
	CCMoveBy* pRight = CCMoveBy::create(0.5, ccp(425, 0));
	m_pGuideBorder->runAction(pRight);
}
