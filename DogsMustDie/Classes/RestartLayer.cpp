#include "RestartLayer.h"
#include "MyMenu.h"
#include "Defines.h"
#include "..\StrangeAdventure\Classes\RestartLayer.h"

#define SHAKE_ANGLE 12
#define SCALE 1.2
RestartLayer::RestartLayer() :	
	m_pHappyDog(NULL),
	m_pFlickerAction(NULL)
{

}

RestartLayer::~RestartLayer()
{
	CC_SAFE_RELEASE(m_pFlickerAction);
}

bool RestartLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!NavigatorLayer::init());

		// ×ó²àÍ·Ïñ
		setHappyDog(CCSprite::create("Navigator_dog_win.png"));
		m_pHappyDog->setPosition(ccp(70,150));
		m_pHappyDog->setRotation(-SHAKE_ANGLE);
		m_pHappyDog->setScaleX(-SCALE);
		m_pHappyDog->setScaleY(SCALE);
		m_pFrame->addChild(m_pHappyDog, 2);
		CCCallFunc* pDogFunc1 = CCCallFunc::create(this, callfunc_selector(RestartLayer::dogFunc1));
		CCCallFunc* pDogFunc2 = CCCallFunc::create(this, callfunc_selector(RestartLayer::dogFunc2));
		CCActionInterval* pDelay = CCActionInterval::create(0.6);
		CCFiniteTimeAction* pSeq = CCSequence::create(pDogFunc1, pDelay, pDogFunc2, pDelay ,NULL);
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
			"Navigator_btn_back_normal.png",
			this,
			menu_selector(RestartLayer::backCallback));	

		pBack->setPosition(ccp(240, 67));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pNext = new CCMenuItemImage();		
		pNext->initWithNormalImage(
			"Navigator_btn_restart_normal.png",
			"Navigator_btn_restart_pressed.png",
			"Navigator_btn_restart_normal.png",
			this,
			menu_selector(RestartLayer::restartCallback));	

		pNext->setPosition(ccp(310, 67));	
		pMenu->addChild(pNext);
		
		bRet = true;
	}while(0);

	return bRet;
}


void RestartLayer::dogFunc1()
{
	m_pHappyDog->setScaleX(-SCALE);
	m_pHappyDog->setScaleY(SCALE);
	m_pHappyDog->setRotation(-SHAKE_ANGLE);
}

void RestartLayer::dogFunc2()
{
	m_pHappyDog->setScaleX(+SCALE);
	m_pHappyDog->setScaleY(SCALE);
	m_pHappyDog->setRotation(+SHAKE_ANGLE);
}


void RestartLayer::backCallback(CCObject* pOb)
{
	getStageScene()->opGoBack();
}

void RestartLayer::restartCallback(CCObject* pOb)
{
	restore();
	getStageScene()->opReStart();
}
CCString* RestartLayer::getTitle()
{
	return CCString::create("LOSE");
}


void RestartLayer::restore()
{
	NavigatorLayer::restore();
	m_pHappyDog->stopAllActions();
}



void RestartLayer::show()
{
	NavigatorLayer::show();
	m_pHappyDog->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyDog->runAction(m_pFlickerAction);
}