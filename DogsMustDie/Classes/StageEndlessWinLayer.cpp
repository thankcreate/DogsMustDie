#include "StageEndlessWinLayer.h"
#include "MyMenu.h"
#include "Defines.h"
#include "AudioManager.h"
#include "MyUseDefaultDef.h"
#include "LocalizeManager.h"

#define SHAKE_ANGLE 12
#define SCALE 1.2

StageEndlessWinLayer::StageEndlessWinLayer() :	
	m_pHappyCat(NULL),
	m_pFlickerAction(NULL)
{
}

StageEndlessWinLayer::~StageEndlessWinLayer()
{
	CC_SAFE_RELEASE(m_pFlickerAction);	
}

bool StageEndlessWinLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!NavigatorLayer::init());

		// ×ó²àÍ·Ïñ
		setHappyCat(CCSprite::create("Navigator_cat_win.png"));
		m_pHappyCat->setPosition(ccp(70,150));
		m_pHappyCat->setRotation(-SHAKE_ANGLE);
		m_pHappyCat->setScaleX(-SCALE);
		m_pHappyCat->setScaleY(SCALE);
		m_pFrame->addChild(m_pHappyCat, 2);
		CCCallFunc* pCatFunc1 = CCCallFunc::create(this, callfunc_selector(StageEndlessWinLayer::catFunc1));
		CCCallFunc* pCatFunc2 = CCCallFunc::create(this, callfunc_selector(StageEndlessWinLayer::catFunc2));
		CCActionInterval* pDelay = CCActionInterval::create(0.6);
		CCFiniteTimeAction* pSeq = CCSequence::create(pCatFunc1, pDelay, pCatFunc2, pDelay ,NULL);
		CCRepeat* pReapeat = CCRepeat::create(pSeq, ENDLESS_COUNT);
		setFlickerAction(pReapeat);

		
		// °´Å¥
		MyMenu* pMenu = MyMenu::create();
		pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(pMenu, 1);	


		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			"Navigator_btn_back_normal.png",
			"Navigator_btn_back_pressed.png",
			"Navigator_btn_back_pressed.png",
			this,
			menu_selector(StageEndlessWinLayer::backCallback));	

		pBack->setPosition(ccp(240, 67));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pNext = new CCMenuItemImage();		
		pNext->initWithNormalImage(
			"Navigator_btn_next_normal.png",
			"Navigator_btn_next_pressed.png",
			"Navigator_btn_next_pressed.png",
			this,
			menu_selector(StageEndlessWinLayer::nextCallback));	

		pNext->setPosition(ccp(310, 67));	
		pMenu->addChild(pNext);

		bRet = true;
	}while(0);

	return bRet;
}

void StageEndlessWinLayer::catFunc1()
{
	m_pHappyCat->setScaleX(-SCALE);
	m_pHappyCat->setScaleY(SCALE);
	m_pHappyCat->setRotation(-SHAKE_ANGLE);
}

void StageEndlessWinLayer::catFunc2()
{
	m_pHappyCat->setScaleX(+SCALE);
	m_pHappyCat->setScaleY(SCALE);
	m_pHappyCat->setRotation(+SHAKE_ANGLE);
}

void StageEndlessWinLayer::backCallback(CCObject* pOb)
{
	getStageScene()->opGoBack();
}

void StageEndlessWinLayer::nextCallback(CCObject* pOb)
{
	restore();
	getStageScene()->gotoNext();
}


CCString* StageEndlessWinLayer::getTitle()
{
	return CCString::create("W I N");
}



void StageEndlessWinLayer::restore()
{
	NavigatorLayer::restore();
	m_pHappyCat->stopAllActions();
}



void StageEndlessWinLayer::show()
{
	NavigatorLayer::show();
	m_pHappyCat->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyCat->runAction(m_pFlickerAction);

	
}



void StageEndlessWinLayer::setRound( int round )
{
	m_nRound = round;	

	if(!m_pRoundLabel)
	{	
		int font = 30;
		if(CUR_LANG == kLanguageChinese)
			font = 25;
		setRoundLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, font));		
		m_pRoundLabel->setDimensions(CCSizeMake(220, 25));
		m_pRoundLabel->setPosition(ccp(255, 201));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pRoundLabel->setColor(ccMyOrange);
		m_pRoundLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pRoundLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pRoundLabel);
	}

	CCString* pFullRoundString = CCString::createWithFormat("%s:  %d", I18N_STR("Current_Round") , m_nRound);
	m_pRoundLabel->setString(pFullRoundString->getCString());

	int best = LoadIntegerFromXML(KEY_ENDLESS_BEST_ROUND, 0);
	if(!m_pBestRoundLabel)
	{	
		int font = 30;
		if(CUR_LANG == kLanguageChinese)
			font = 25;
		setBestRoundLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, font));		
		m_pBestRoundLabel->setDimensions(CCSizeMake(220, 25));
		m_pBestRoundLabel->setPosition(ccp(255, 170));
		m_pBestRoundLabel->getTexture()->setAliasTexParameters();
		ccColor3B ccMyOrange={255, 104, 0};
		m_pBestRoundLabel->setColor(ccMyOrange);
		m_pBestRoundLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pBestRoundLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pBestRoundLabel);
	}

	CCString* pFullBestRoundString = CCString::createWithFormat("%s:  %d", I18N_STR("Best_Round"), best);
	m_pBestRoundLabel->setString(pFullBestRoundString->getCString());
}