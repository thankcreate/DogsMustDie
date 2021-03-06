#include "Stage1_01Layer.h"
#include "Defines.h"
#include "StarObject.h"
#include "StageBaseLayer.h"
#include "Planet.h"
#include "LocalizeManager.h"

Stage1_01Layer::Stage1_01Layer() :
	m_pGuideBorder(NULL),
	m_pGuideLabel(NULL),
	m_pFinger(NULL),
	m_pDogPlanet1(NULL),
	m_pStar(NULL),
	m_bAskedToFocusAPlanet(false),
	m_pSkillPrompt(NULL),
	m_bAskedToClickSkillUpgrade(false),
	m_bAskedToClickSkillSpeedUp(false),
	m_bAskedToClickSkillDown(false),
	m_pDogPlanet2(NULL),
	m_bAskedToFinalStrike(false),
	m_bAreadyDragToOccupy(false)
{

}

Stage1_01Layer::~Stage1_01Layer()
{

}

bool Stage1_01Layer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		CCSize size = WIN_SIZE;			

		initGuideLayer();
		
		CCMenu* pMenu = CCMenu::create(NULL);
		pMenu->setPosition(CCPointZero);	
		this->addChild(pMenu, 1);
				
		CCMenuItemImage *pSkipBtn = CCMenuItemImage::create();
		pSkipBtn->initWithNormalImage(
			I18N_FILE("StageBase_btn_skip_normal.png"),
			I18N_FILE("StageBase_btn_skip_pressed.png"),
			I18N_FILE("StageBase_btn_skip_pressed.png"),
			this,
			menu_selector(Stage1_01Layer::skipCallback));	

		pSkipBtn->setPosition(ccp(378, size.height - 16));	
		pMenu->addChild(pSkipBtn);

		bRet = true;
	} while (0);

	return bRet;
}

void Stage1_01Layer::skipCallback(CCObject* pObject)
{
	gotoWin();	
}

void Stage1_01Layer::initPlanets()
{
	CCSize size = WIN_SIZE;
	Planet* pPlanet = NULL;
	pPlanet = makePlanet(kForceSideCat, ccp(190, 370), 30, 0);
	pPlanet->stopIncrease();

	pPlanet = makePlanet(kForceSideDog, ccp(540, 370), 10, 0);
	setDogPlanet1(pPlanet);
	pPlanet->stopIncrease();

	m_bIsAddStarStopped = true;
}

void Stage1_01Layer::initLoadedAction()
{
	this->schedule(schedule_selector(Stage1_01Layer::guideDragToOccupy), 3);
}

void Stage1_01Layer::initGuideLayer()
{
	setGuideBorder(CCSprite::create("StageBase_guide_border.png"));
	CCSize borderSize = m_pGuideBorder->boundingBox().size;
	CCSize winSize = WIN_SIZE;
	m_pGuideBorder->setPosition(ccp(winSize.width / 2 - 50, borderSize.height / 2));
	this->addChild(m_pGuideBorder, kGuideLayerIndex);	

	//setGuideLabel(CCLabelTTF::create("Good day, commander! \nStupid dogs are comming.\nWe should teach them a lesson, mew~", FONT_00_STARMAP_TRUETYPE, 30));	
	setGuideLabel(CCLabelTTF::create(" ", "Arial", 26));
    m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_1"));
	m_pGuideLabel->setDimensions(CCSizeMake(420, 140));
	m_pGuideLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_pGuideLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	
	ccColor3B ccMyOrange={255, 104, 0};
	m_pGuideLabel->setPosition(ccp(250,60));
	m_pGuideLabel->setColor(ccMyOrange);
	m_pGuideBorder->addChild(m_pGuideLabel);
}

void Stage1_01Layer::guideDragToOccupy(float dt)
{
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_2"));
	}

	if(!m_bAreadyDragToOccupy)
	{
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
	else
	{
		this->unschedule(schedule_selector(Stage1_01Layer::guideDragToOccupy));
	}
}

void Stage1_01Layer::guideDragToStar(float dt)
{
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_3"));
	}
		

	if(!m_pStar)
	{
		StarObject* pStar = makeStar(ccp(352, 250));
		setStar(pStar);		
	}

	if(!m_pFinger)
	{
		setFinger(CCSprite::create("Finger.png"));
		this->addChild(m_pFinger, kPannelLayerIndex);
	}

	m_pFinger->setVisible(true);
	m_pFinger->setPosition(ccp(215, 295));	
	float xDistance = 376 - 215;
	float yDistance = 200 - 295;
	CCMoveBy* pMove = CCMoveBy::create(1.5, ccp(xDistance, yDistance));
	m_pFinger->runAction(pMove);

	this->schedule(schedule_selector(Stage1_01Layer::guideDragToStar), 3);
}

void Stage1_01Layer::guideFocusOnPlanet(float dt)
{
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_4"));
	}

	if(!m_pFinger)
	{
		setFinger(CCSprite::create("Finger.png"));
		this->addChild(m_pFinger, kPannelLayerIndex);
	}
	
	m_pFinger->setVisible(true);
	m_pFinger->setPosition(ccp(230, 280));		
	CCMoveTo* pTo1 = CCMoveTo::create(0.4, ccp(230, 280));
	CCMoveTo* pTo2 = CCMoveTo::create(0.4, ccp(215, 295));
	CCSequence* pSep = CCSequence::createWithTwoActions(pTo2, pTo1);
	m_pFinger->runAction(pSep);
	this->schedule(schedule_selector(Stage1_01Layer::guideFocusOnPlanet), 2);

	m_bAskedToFocusAPlanet = true;
}


void Stage1_01Layer::guideClickOnUpgrade()
{
	if(getStarCountForForceSide(kForceSideCat)  < SKILL_UPGRADE_COUNT)
	{
		setStarCountForForceSide(kForceSideCat, SKILL_UPGRADE_COUNT);		
	}
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_5"));
	}

	if(!m_pSkillPrompt)
	{
		setSkillPrompt(CCSprite::create("SkillPrompt.png"));
		m_pSkillPrompt->setPosition(ccp(666,434));
		this->addChild(m_pSkillPrompt, kPannelLayerIndex);
	}

	CCMoveTo* pTo1 = CCMoveTo::create(0.4, ccp(651, 434));
	CCMoveTo* pTo2 = CCMoveTo::create(0.4, ccp(666, 434));
	CCSequence* pSeq = CCSequence::createWithTwoActions(pTo2, pTo1);
	m_pSkillPrompt->stopAllActions();
	m_pSkillPrompt->runAction(CCRepeatForever::create(pSeq));	

	m_bAskedToClickSkillUpgrade = true;
}

void Stage1_01Layer::guideClickOnSpeedUp()
{
	if(getStarCountForForceSide(kForceSideCat) < SKILL_SPEED_COUNT)
	{
		setStarCountForForceSide(kForceSideCat, SKILL_SPEED_COUNT);		
	}
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_6"));
	}

	if(!m_pSkillPrompt)
	{
		setSkillPrompt(CCSprite::create("SkillPrompt.png"));
		m_pSkillPrompt->setPosition(ccp(666,349));
		this->addChild(m_pSkillPrompt, kPannelLayerIndex);
	}

	CCMoveTo* pTo1 = CCMoveTo::create(0.4, ccp(651, 349));
	CCMoveTo* pTo2 = CCMoveTo::create(0.4, ccp(666, 349));
	CCSequence* pSeq = CCSequence::createWithTwoActions(pTo2, pTo1);
	m_pSkillPrompt->stopAllActions();
	m_pSkillPrompt->runAction(CCRepeatForever::create(pSeq));	

	m_bAskedToClickSkillSpeedUp = true;
}

// 提示去点击down时，开始新建个dog 星
void Stage1_01Layer::guideClickOnDown(float dt)
{
	if(getStarCountForForceSide(kForceSideCat)  < SKILL_DOWN_COUNT)
	{
		setStarCountForForceSide(kForceSideCat, SKILL_DOWN_COUNT);
	}

	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_7"));
	}

	if(!m_pSkillPrompt)
	{
		setSkillPrompt(CCSprite::create("SkillPrompt.png"));
		m_pSkillPrompt->setPosition(ccp(666,264));
		this->addChild(m_pSkillPrompt, kPannelLayerIndex);
	}

	// 提示箭头
	CCMoveTo* pTo1 = CCMoveTo::create(0.4, ccp(651, 264));
	CCMoveTo* pTo2 = CCMoveTo::create(0.4, ccp(666, 264));
	CCSequence* pSeq = CCSequence::createWithTwoActions(pTo2, pTo1);
	m_pSkillPrompt->stopAllActions();
	m_pSkillPrompt->runAction(CCRepeatForever::create(pSeq));	

	m_bAskedToClickSkillDown = true;

	// 画一个新Dog星球
	Planet* pDog = makePlanet(kForceSideDog, ccp(362, 222), 15, 0);
	setDogPlanet2(pDog);
	
	// 恢复所有星球增长
	CCObject* pOb = NULL;
	bool bCanSlowDown = false;
	CCARRAY_FOREACH(getPlanetArray(), pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		if(!pPlanet->isDirty())
		{			
			pPlanet->startIncrease();
		}
	}
}

void Stage1_01Layer::guideFinalStrike(float dt)
{
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_8"));
	}

	if(!m_pFinger)
	{
		setFinger(CCSprite::create("Finger.png"));
		this->addChild(m_pFinger, kPannelLayerIndex);
	}

	m_pFinger->setVisible(true);
	m_pFinger->setPosition(ccp(215, 295));	
	CCMoveTo* pTo1 = CCMoveTo::create(0.9, ccp(400, 170));	
	CCCallFunc* pFunc1 = CCCallFunc::create(this, callfunc_selector(Stage1_01Layer::callFunc1));
	CCMoveTo* pTo2 = CCMoveTo::create(0.9, ccp(400, 170));	

	CCFiniteTimeAction* pSeq = CCSequence::create(pTo1, pFunc1, pTo2, NULL);
	m_pFinger->stopAllActions();
	m_pFinger->runAction(pSeq);
	this->schedule(schedule_selector(Stage1_01Layer::guideFinalStrike), 2.3f);
	m_bAskedToFinalStrike = true;
}

void Stage1_01Layer::guideWin()
{
	if(m_pGuideLabel)
	{
		m_pGuideLabel->setString(I18N_STR("Stage1_1_Guide_9"));
	}
	this->scheduleOnce(schedule_selector(Stage1_01Layer::showWinInDelay), 3.5);
}

void Stage1_01Layer::showWinInDelay(float dt)
{
	gotoWin();
}

void Stage1_01Layer::callFunc1()
{
	if(m_pFinger)
		m_pFinger->setPosition(ccp(565, 295));
}

void Stage1_01Layer::sendTroopsToPlanet(Planet* fromPlanet, Planet* toPlanet,  int count  )
{
	StageBaseLayer::sendTroopsToPlanet(fromPlanet, toPlanet);
	if(toPlanet == m_pDogPlanet1
		&& toPlanet != NULL)
	{
		// 说明已经完成了drag动作
		this->unschedule(schedule_selector(Stage1_01Layer::guideDragToOccupy));
		m_bAreadyDragToOccupy = true;
		if(m_pFinger)
		{
			m_pFinger->setVisible(false);			
		}
	}

	if(toPlanet == m_pDogPlanet2
		&& toPlanet != NULL
		&& m_bAskedToFinalStrike)
	{
		m_bAskedToFinalStrike = false;
		this->unschedule(schedule_selector(Stage1_01Layer::guideFinalStrike));
		if(m_pFinger)
		{
			m_pFinger->setVisible(false);			
		}
	}
}

void Stage1_01Layer::sendTroopsToStar(Planet* fromPlanet, StarObject* toStar)
{
	StageBaseLayer::sendTroopsToStar(fromPlanet, toStar);

	if(toStar == m_pStar)
	{
		// 说明已经完成了drag动作
		this->unschedule(schedule_selector(Stage1_01Layer::guideDragToStar));
		if(m_pFinger)
		{
			m_pFinger->setVisible(false);			
		}
	}
}


void Stage1_01Layer::planetOccupied(Planet* pPlanet)
{
	// 由于父类的planetOccupied作了输赢检查，所以下一行要注释掉
	// StageBaseLayer::planetOccupied(pPlanet);

	if(pPlanet == m_pDogPlanet1
		&& pPlanet != NULL)
	{
		// 这里必须用schedule
		// 因为此函数是在碰撞回调过程中调入的，而guideDragToStar中涉及到b2Body的创建
		this->schedule(schedule_selector(Stage1_01Layer::guideDragToStar), 0.2);
	}

	if(pPlanet == m_pDogPlanet2
		&& pPlanet != NULL)
	{
		guideWin();
	}
}

void Stage1_01Layer::starFinallyLandedOnMyPlanet( Planet* pPlanet )
{
	StageBaseLayer::starFinallyLandedOnMyPlanet(pPlanet);

	if(pPlanet!= NULL && pPlanet->getForceSide() == kForceSideCat)
	{
		// 星星被送回来后，提示选中该星球
		guideFocusOnPlanet(0);
	}
}


void Stage1_01Layer::planetFocused( Planet* pPlanet )
{
	StageBaseLayer::starFinallyLandedOnMyPlanet(pPlanet);
	if(m_bAskedToFocusAPlanet)
	{
		m_bAskedToFocusAPlanet = false;
		this->unschedule(schedule_selector(Stage1_01Layer::guideFocusOnPlanet));
		if(m_pFinger)
		{
			m_pFinger->setVisible(false);			
		}
		guideClickOnUpgrade();
	}
}

void Stage1_01Layer::skillUpCallback( CCObject* pSender )
{
	StageBaseLayer::skillUpCallback(pSender);
	if(m_bAskedToClickSkillUpgrade)
	{
		m_bAskedToClickSkillUpgrade = false;
		guideClickOnSpeedUp();
	}
}

void Stage1_01Layer::skillSpeedCallback( CCObject* pSender )
{
	StageBaseLayer::skillSpeedCallback(pSender);
	if(m_bAskedToClickSkillSpeedUp)
	{
		m_bAskedToClickSkillSpeedUp = false;
		this->scheduleOnce(schedule_selector(Stage1_01Layer::guideClickOnDown), 0.1);
	}
}

void Stage1_01Layer::skillDownCallback( CCObject* pSender )
{
	StageBaseLayer::skillDownCallback(pSender);
	if(m_bAskedToClickSkillDown)
	{
		m_bAskedToClickSkillDown = false;
		if(m_pSkillPrompt)
		{
			m_pSkillPrompt->stopAllActions();
			m_pSkillPrompt->setVisible(false);
		}
		guideFinalStrike(0);
	}
}



// 在本关里，技能按钮只有在教程中需要按的时候才能按
void Stage1_01Layer::updateSkillButtonState()
{
	int starCount = getStarCountForForceSide(kForceSideCat);
	
	// 升级按钮
	if(m_pFocusedPlanet == NULL
		|| starCount < SKILL_UPGRADE_COUNT
		|| !m_pFocusedPlanet->canLevelUp()
		|| !m_bAskedToClickSkillUpgrade)
	{
		getSkillUpgradeBtn()->setEnabled(false);
	}
	else 
	{		
		getSkillUpgradeBtn()->setEnabled(true);
	}

	// 加速按钮
	if(m_pFocusedPlanet == NULL
		|| starCount< SKILL_SPEED_COUNT
		|| !m_pFocusedPlanet->canSpeedUp()
		|| !m_bAskedToClickSkillSpeedUp)
	{
		getSkillSpeedBtn()->setEnabled(false);
	}
	else
	{
		getSkillSpeedBtn()->setEnabled(true);
	}

	// 减速按钮
	// 减速技能是使所有非己方星球升产速率降低
	CCObject* pOb = NULL;
	bool bCanSlowDown = false;
	CCARRAY_FOREACH(getPlanetArray(), pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		if(!pPlanet->isDirty() 
			&& !pPlanet->getForceSide() == kForceSideCat
			&& pPlanet->canSlowDown())
		{			
			bCanSlowDown = true;
			break;			
		}
	}

	if(  starCount < SKILL_DOWN_COUNT
		|| !bCanSlowDown
		|| !m_bAskedToClickSkillDown)
	{
		getSkillDownBtn()->setEnabled(false);
	}
	else
	{
		getSkillDownBtn()->setEnabled(true);
	}
}

void Stage1_01Layer::updateAI()
{
	// 这一关的电脑什么也不做
}


