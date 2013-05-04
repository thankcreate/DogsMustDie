#include "WinLayer.h"
#include "MyMenu.h"
#include "Defines.h"
#include "AudioManager.h"
#include "NavigatorLayer.h"
#include "LocalizeManager.h"

#define SHAKE_ANGLE 12
#define SCALE 1.2

WinLayer::WinLayer() :	
	m_pHappyCat(NULL),
	m_pFlickerAction(NULL),
	m_pStarArray(NULL),
	m_nScoreStarCount(1),
	m_nAlreadyFilledStarCount(0),
	m_pTimeLabel(NULL),
	m_pLostUnitLabel(NULL)
{
}

WinLayer::~WinLayer()
{	
	CC_SAFE_RELEASE(m_pStarArray);
}

bool WinLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!NavigatorLayer::init());

		// 左侧头像
		setHappyCat(CCSprite::create("Navigator_cat_win.png"));
		m_pHappyCat->setPosition(ccp(70,150));
		m_pHappyCat->setRotation(-SHAKE_ANGLE);
		m_pHappyCat->setScaleX(-SCALE);
		m_pHappyCat->setScaleY(SCALE);
		m_pFrame->addChild(m_pHappyCat, 2);
		CCCallFunc* pCatFunc1 = CCCallFunc::create(this, callfunc_selector(WinLayer::catFunc1));
		CCCallFunc* pCatFunc2 = CCCallFunc::create(this, callfunc_selector(WinLayer::catFunc2));
		CCActionInterval* pDelay = CCActionInterval::create(0.6);
		CCFiniteTimeAction* pSeq = CCSequence::create(pCatFunc1, pDelay, pCatFunc2, pDelay ,NULL);
		CCRepeat* pReapeat = CCRepeat::create(pSeq, ENDLESS_COUNT);
		setFlickerAction(pReapeat);		

		// 分级星星
		setStarArray(CCArray::createWithCapacity(3));
		float xInterval = 63;
		for(int i = 0; i < 3; i ++)
		{
			CCSprite* pStar = CCSprite::create("Navigator_star_empty.png");
			pStar->setPosition(ccp(188 + xInterval * i, 122));
			m_pFrame->addChild(pStar);
			m_pStarArray->addObject(pStar);
		}		

		// 按钮
		MyMenu* pMenu = MyMenu::create();
		pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(pMenu, 1);	
		

		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			"Navigator_btn_back_normal.png",
			"Navigator_btn_back_pressed.png",
			"Navigator_btn_back_pressed.png",
			this,
			menu_selector(WinLayer::backCallback));	

		pBack->setPosition(ccp(240, 67));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pNext = new CCMenuItemImage();		
		pNext->initWithNormalImage(
			"Navigator_btn_next_normal.png",
			"Navigator_btn_next_pressed.png",
			"Navigator_btn_next_pressed.png",
			this,
			menu_selector(WinLayer::nextCallback));	

		pNext->setPosition(ccp(310, 67));	
		pMenu->addChild(pNext);
		bRet = true;
	}while(0);

	return bRet;
}

void WinLayer::catFunc1()
{
	m_pHappyCat->setScaleX(-SCALE);
	m_pHappyCat->setScaleY(SCALE);
	m_pHappyCat->setRotation(-SHAKE_ANGLE);
}

void WinLayer::catFunc2()
{
	m_pHappyCat->setScaleX(+SCALE);
	m_pHappyCat->setScaleY(SCALE);
	m_pHappyCat->setRotation(+SHAKE_ANGLE);
}

void WinLayer::backCallback(CCObject* pOb)
{
	restore();
	getStageScene()->opGoBack();
	// m_pFlickerAction 与 本类存在互相引用，故要提前做release
	CC_SAFE_RELEASE(m_pFlickerAction);
}

void WinLayer::nextCallback(CCObject* pOb)
{
	restore();
	getStageScene()->gotoNext();
}


CCString* WinLayer::getTitle()
{
	return CCString::create("W I N");
}



void WinLayer::restore()
{
	NavigatorLayer::restore();
	m_pHappyCat->stopAllActions();
}



void WinLayer::show()
{
	if(m_bInShow)
		return;

	NavigatorLayer::show();
	m_pHappyCat->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyCat->runAction(m_pFlickerAction);

	this->schedule(schedule_selector(WinLayer::fillEmptyStar), 0.8);
}

void WinLayer::fillEmptyStar(float dt)
{
	if(m_nAlreadyFilledStarCount == m_nScoreStarCount)
	{
		this->unschedule(schedule_selector(WinLayer::fillEmptyStar));	
		return;
	}

	if(m_pStarArray)
	{
		CCObject* pOb = m_pStarArray->objectAtIndex(m_nAlreadyFilledStarCount);
		CCSprite* pStar = (CCSprite*) pOb;
		pStar->initWithFile("Navigator_star_solid.png");
		PlayEffect("Audio_cat_mew.mp3");

		CCScaleTo* pScaleBig = CCScaleTo::create(0.09, 1.3);
		CCScaleTo* pScaleRestore = CCScaleTo::create(0.09, 1);
		CCSequence* pShake = CCSequence::createWithTwoActions(pScaleBig, pScaleRestore);		
		pStar->runAction(pShake);
	}

	m_nAlreadyFilledStarCount++;
}

void WinLayer::setScoreStarCount( int count )
{
	if(count > 3)
		count = 3;
	if(count < 1)
		count = 1;
	m_nScoreStarCount = count;
}



void WinLayer::setTime(int nTime)
{
	m_nTime = nTime;
	if(!m_pTimeLabel)
	{		
		setTimeLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, 30));		
		m_pTimeLabel->setDimensions(CCSizeMake(220, 25));
		m_pTimeLabel->setPosition(ccp(255, 201));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTimeLabel->setColor(ccMyOrange);
		m_pTimeLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pTimeLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pTimeLabel);
	}

	CCString* pFullTimeString = CCString::createWithFormat("%s:  %d %s",I18N_STR("Time"), m_nTime, I18N_STR("Second_For_Short"));
	m_pTimeLabel->setString(pFullTimeString->getCString());
}

void WinLayer::setLostUnit(int nLost)
{
	m_nLostUnit = nLost;
	if(!m_pLostUnitLabel)
	{		
		setLostUnitLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, 30));		
		m_pLostUnitLabel->setDimensions(CCSizeMake(220, 25));
		m_pLostUnitLabel->setPosition(ccp(255, 170));
		m_pLostUnitLabel->getTexture()->setAliasTexParameters();
		ccColor3B ccMyOrange={255, 104, 0};
		m_pLostUnitLabel->setColor(ccMyOrange);
		m_pLostUnitLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pLostUnitLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pLostUnitLabel);
	}

	CCString* pFullLostUnitString = CCString::createWithFormat("%s:  %d", I18N_STR("Unit_Lost") , m_nLostUnit);
	m_pLostUnitLabel->setString(pFullLostUnitString->getCString());
}