#include "RestartLayer.h"
#include "MyMenu.h"
#include "Defines.h"

#define SHAKE_ANGLE 12
#define SCALE 1.2
RestartLayer::RestartLayer() :	
	m_pHappyDog(NULL),
	m_pFlickerAction(NULL),
	m_pTimeLabel(NULL),
	m_pLostUnitLabel(NULL)
{

}

RestartLayer::~RestartLayer()
{	
}

bool RestartLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!NavigatorLayer::init());

		// 左侧头像
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


		// 按钮
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
	restore();
	// m_pFlickerAction 与 本类存在互相引用，故要提前做release
	CC_SAFE_RELEASE(m_pFlickerAction);
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
	if(m_bInShow)
		return;
	NavigatorLayer::show();
	m_pHappyDog->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyDog->runAction(m_pFlickerAction);
}


void RestartLayer::setTime(int nTime)
{
	m_nTime = nTime;
	if(!m_pTimeLabel)
	{		
		setTimeLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 30));		
		m_pTimeLabel->setDimensions(CCSizeMake(220, 25));
		m_pTimeLabel->setPosition(ccp(255, 201));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTimeLabel->setColor(ccMyOrange);
		m_pTimeLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pTimeLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pTimeLabel);
	}

	CCString* pFullTimeString = CCString::createWithFormat("Time:  %d s", m_nTime);
	m_pTimeLabel->setString(pFullTimeString->getCString());
}

void RestartLayer::setLostUnit(int nLost)
{
	m_nLostUnit = nLost;
	if(!m_pLostUnitLabel)
	{		
		setLostUnitLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 30));		
		m_pLostUnitLabel->setDimensions(CCSizeMake(220, 25));
		m_pLostUnitLabel->setPosition(ccp(255, 170));
		m_pLostUnitLabel->getTexture()->setAliasTexParameters();
		ccColor3B ccMyOrange={255, 104, 0};
		m_pLostUnitLabel->setColor(ccMyOrange);
		m_pLostUnitLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pLostUnitLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pLostUnitLabel);
	}

	CCString* pFullLostUnitString = CCString::createWithFormat("Unit lost:  %d cat", m_nLostUnit);
	m_pLostUnitLabel->setString(pFullLostUnitString->getCString());
}