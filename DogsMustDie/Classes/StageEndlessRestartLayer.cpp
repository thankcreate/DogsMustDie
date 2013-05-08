#include "StageEndlessRestartLayer.h"
#include "MyMenu.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"
#include "BuyScene.h"
#include "LocalizeManager.h"
#include "StageEndlessScene.h"


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AppOfferManager.h"
#endif

#define SHAKE_ANGLE 12
#define SCALE 1.2
StageEndlessRestartLayer::StageEndlessRestartLayer() :	
	m_pHappyDog(NULL),
	m_pFlickerAction(NULL),
	m_pCoinCountLabel(NULL),
	m_nCoinCount(0),
	m_pContinueItem(NULL),
	m_bContinueAlreadyUsedInOneSession(false)
{
}

StageEndlessRestartLayer::~StageEndlessRestartLayer()
{
	CC_SAFE_RELEASE(m_pFlickerAction);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AppOfferManager::sharedInstance()->setDelegate(NULL);
#endif

}

bool StageEndlessRestartLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!NavigatorLayer::init());

		// 左侧头像
		setHappyDog(CCSprite::create("Navigator_dog_win.png"));
		m_pHappyDog->setPosition(ccp(70,160));
		m_pHappyDog->setRotation(-SHAKE_ANGLE);
		m_pHappyDog->setScaleX(-SCALE);
		m_pHappyDog->setScaleY(SCALE);
		m_pFrame->addChild(m_pHappyDog, 2);
		CCCallFunc* pDogFunc1 = CCCallFunc::create(this, callfunc_selector(StageEndlessRestartLayer::dogFunc1));
		CCCallFunc* pDogFunc2 = CCCallFunc::create(this, callfunc_selector(StageEndlessRestartLayer::dogFunc2));
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
			menu_selector(StageEndlessRestartLayer::backCallback));	

		pBack->setPosition(ccp(245, 67));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pGetCoin = new CCMenuItemImage();		
		pGetCoin->initWithNormalImage(
			"Endless_btn_getcoin_normal.png",
			"Endless_btn_getcoin_pressed.png",
			"Endless_btn_getcoin_normal.png",
			this,
			menu_selector(StageEndlessRestartLayer::getCoinCallback));	

		pGetCoin->setPosition(ccp(73, 67));	
		pMenu->addChild(pGetCoin);

		CCMenuItemImage *pRestart = new CCMenuItemImage();		
		pRestart->initWithNormalImage(
			"Navigator_btn_restart_normal.png",
			"Navigator_btn_restart_pressed.png",
			"Navigator_btn_restart_normal.png",
			this,
			menu_selector(StageEndlessRestartLayer::restartCallback));	

		pRestart->setPosition(ccp(310, 67));
		pMenu->addChild(pRestart);

		// 本类中第一次加载m_nCoinCount
		m_nCoinCount = LoadIntegerFromXML(KEY_COIN_COUNT , 0);

		setContinueItem(new CCMenuItemImage());		
		m_pContinueItem->initWithNormalImage(
			I18N_FILE("Endless_btn_continue_normal.png"),
			I18N_FILE("Endless_btn_continue_pressed.png"),
			I18N_FILE("Endless_btn_continue_disable.png"),
			this,
			menu_selector(StageEndlessRestartLayer::continueCallback));	

		m_pContinueItem->setPosition(ccp(248, 126));	
		pMenu->addChild(m_pContinueItem);

		refreshContinueButtonEnableState();

		// coin part
		CCSprite* pCoin = CCSprite::create("Coin.png");
		pCoin->setPosition(ccp(150, 67));
		m_pFrame->addChild(pCoin);
		
		setCoinCountLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, 28));		
		m_pCoinCountLabel->setPosition(ccp(194, 65));
		m_pCoinCountLabel->setDimensions(CCSizeMake(58, 30));
		m_pCoinCountLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pCoinCountLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		ccColor3B ccMyOrange={255, 104, 0};
		m_pCoinCountLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pCoinCountLabel);

		refreshCoinCountLabel();

		bRet = true;
	}while(0);

	return bRet;
}

void StageEndlessRestartLayer::refreshCoinCountLabel()
{
    if(!m_pCoinCountLabel)
        return;
	m_nCoinCount = LoadIntegerFromXML(KEY_COIN_COUNT , 0);
	CCString* pStrCoinCount = CCString::createWithFormat(": %d", m_nCoinCount);
	m_pCoinCountLabel->setString((pStrCoinCount->getCString()));
	refreshContinueButtonEnableState();
}

void StageEndlessRestartLayer::refreshContinueButtonEnableState()
{
    if(!m_pContinueItem)
        return;
	m_nCoinCount =  LoadIntegerFromXML(KEY_COIN_COUNT , 0);
	if(m_nCoinCount <= 0)
		m_pContinueItem->setEnabled(false);
	else
		m_pContinueItem->setEnabled(true);

    // 目前允许多次使用复活功能
//	if(m_bContinueAlreadyUsedInOneSession)
//		m_pContinueItem->setVisible(false);
//	else
//		m_pContinueItem->setVisible(true);
}

void StageEndlessRestartLayer::dogFunc1()
{
	m_pHappyDog->setScaleX(-SCALE);
	m_pHappyDog->setScaleY(SCALE);
	m_pHappyDog->setRotation(-SHAKE_ANGLE);
}

void StageEndlessRestartLayer::dogFunc2()
{
	m_pHappyDog->setScaleX(+SCALE);
	m_pHappyDog->setScaleY(SCALE);
	m_pHappyDog->setRotation(+SHAKE_ANGLE);
}

void StageEndlessRestartLayer::continueCallback(CCObject* pOb)
{
	if(m_nCoinCount <= 0)
		return;
	--m_nCoinCount;
	SaveIntegerToXML(KEY_COIN_COUNT, m_nCoinCount);
	SaveUserDefault();

	m_bContinueAlreadyUsedInOneSession = true;

	refreshCoinCountLabel();	
	restore();
    StageEndlessScene* scene = (StageEndlessScene*)getStageScene();
	scene->continueRestartWithThisRound();
}

void StageEndlessRestartLayer::backCallback(CCObject* pOb)
{
	getStageScene()->opGoBack();
}

void StageEndlessRestartLayer::restartCallback(CCObject* pOb)
{
	m_bContinueAlreadyUsedInOneSession = false;
	restore();
	getStageScene()->opReStart();
}

CCString* StageEndlessRestartLayer::getTitle()
{
	return CCString::create("LOSE");
}


void StageEndlessRestartLayer::restore()
{
	NavigatorLayer::restore();
	refreshContinueButtonEnableState();
	m_pHappyDog->stopAllActions();
}



void StageEndlessRestartLayer::show()
{
	NavigatorLayer::show();
    refreshCoinCountLabel();
	refreshContinueButtonEnableState();
	m_pHappyDog->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyDog->runAction(m_pFlickerAction);
}


void StageEndlessRestartLayer::setRound( int round )
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

	// 代码走到此处说明已经失败了，所以前一关的round值才是current，不然会引起用户误解
	// 当前逻辑里的best round是指完成某一关，不是指玩到某一关
	int before = m_nRound - 1;
	if(before < 0)
		before = 0;
	CCString* pFullRoundString = CCString::createWithFormat("%s:  %d", I18N_STR("Current_Round") ,before);
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

void StageEndlessRestartLayer::getCoinCallback( CCObject* pOb )
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	BuyScene* pBuyScene = BuyScene::create();
	CCDirector::sharedDirector()->pushScene(pBuyScene);
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AppOfferManager::sharedInstance()->setDelegate(this);
	AppOfferManager::sharedInstance()->show();
#endif
}

void StageEndlessRestartLayer::onEnterTransitionDidFinish()
{
    StageEndlessNavigatorLayer::onEnterTransitionDidFinish();
    refreshCoinCountLabel();
	refreshContinueButtonEnableState();
}

void StageEndlessRestartLayer::pointAdded( int n )
{
	// 1
	// 实际上这里不会用到n，早在AppOfferManager中已经把增加值更新到UserDefault中去了
	// 这是因为很有可能此函数调用前，本类就已经析构了置delegate为NULL
	// 也就可能不会调用到这里
	
	// 2
	// 这里已经是在UI线程了，但是不知为何此处直接操作label会导致其黑掉
	// 所以还是schedule一下
	this->scheduleOnce(schedule_selector(StageEndlessRestartLayer::pointAddedInternal), 0.1);
}

void StageEndlessRestartLayer::pointAddedInternal(float dt)
{
	refreshCoinCountLabel();
	refreshContinueButtonEnableState();
}