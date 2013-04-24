#include "WinLayer.h"
#include "MyMenu.h"
#include "Defines.h"

#define SHAKE_ANGLE 12
#define SCALE 1.2

WinLayer::WinLayer() :	
	m_pHappyCat(NULL),
	m_pFlickerAction(NULL)
{
}

WinLayer::~WinLayer()
{
	CC_SAFE_RELEASE(m_pFlickerAction);
}


bool WinLayer::init()
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
		CCCallFunc* pCatFunc1 = CCCallFunc::create(this, callfunc_selector(WinLayer::catFunc1));
		CCCallFunc* pCatFunc2 = CCCallFunc::create(this, callfunc_selector(WinLayer::catFunc2));
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
			menu_selector(WinLayer::backCallback));	

		pBack->setPosition(ccp(240, 70));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pNext = new CCMenuItemImage();		
		pNext->initWithNormalImage(
			"Navigator_btn_next_normal.png",
			"Navigator_btn_next_pressed.png",
			"Navigator_btn_next_pressed.png",
			this,
			menu_selector(WinLayer::nextCallback));	

		pNext->setPosition(ccp(310, 70));	
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
	getStageScene()->opGoBack();
}

void WinLayer::nextCallback(CCObject* pOb)
{
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
	NavigatorLayer::show();
	m_pHappyCat->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyCat->runAction(m_pFlickerAction);
}