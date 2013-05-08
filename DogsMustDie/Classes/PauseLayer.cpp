#include "PauseLayer.h"
#include "MyMenu.h"
#include "StageBaseScene.h"
#include "PauseLayerDelegate.h"
#include "Defines.h"
#include "LocalizeManager.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IOSWrapper.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AdViewManager.h"
#endif

PauseLayer::PauseLayer() :
	m_pStageScene(NULL),
	m_pFrame(NULL),
	m_pColorLayer(NULL),
	m_pTitleLabel(NULL),
	m_pDelegate(NULL),
	m_bInShow(false)
{
}

bool PauseLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// 黑色半透明背景
		ccColor4B color = ccc4(0, 0, 0, 190);
		setColorLayer(CCLayerColor::create(color));
		m_pColorLayer->setPosition(0, 0);
		m_pColorLayer->setContentSize(size);
		this->addChild(m_pColorLayer);

		// 框架
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("Pause_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2 + size.height));
		this->addChild(m_pFrame);

		// 标题		
		setTitleLabel(CCLabelTTF::create("Paused", FONT_8BITOPERATOR_JVE, 45));		
		m_pTitleLabel->setPosition(ccp(192, 285));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTitleLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pTitleLabel);

		// 按钮
		MyMenu* pMenu = MyMenu::create();
		pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(pMenu, 1);

		CCMenuItemImage *pResume = new CCMenuItemImage();		
		pResume->initWithNormalImage(
			I18N_FILE("Pause_btn_resume_normal.png"),
			I18N_FILE("Pause_btn_resume_pressed.png"),
			I18N_FILE("Pause_btn_resume_pressed.png"),
			this,
			menu_selector(PauseLayer::resumeCallback));	

		pResume->setPosition(ccp(193, 169));	
		pMenu->addChild(pResume);

		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			I18N_FILE("Pause_btn_menu_normal.png"),
			I18N_FILE("Pause_btn_menu_pressed.png"),
			I18N_FILE("Pause_btn_menu_pressed.png"),
			this,
			menu_selector(PauseLayer::backCallback));	

		pBack->setPosition(ccp(94, 72));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pRestart = new CCMenuItemImage();		
		pRestart->initWithNormalImage(
			I18N_FILE("Pause_btn_restart_normal.png"),
			I18N_FILE("Pause_btn_restart_pressed.png"),
			I18N_FILE("Pause_btn_restart_pressed.png"),
			this,
			menu_selector(PauseLayer::restartCallback));	

		pRestart->setPosition(ccp(293, 72));	
		pMenu->addChild(pRestart);

		// 禁止后层的按键,不写的话得手动remove from dispatcher,否则本类不会被析构
		this->setTouchEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

void PauseLayer::resumeCallback( CCObject* object )
{
	restore();
	if(m_pDelegate)
		m_pDelegate->pauseLayerResumed();
}

void PauseLayer::restartCallback( CCObject* object )
{
	restore();
	if(m_pStageScene)
		m_pStageScene->opReStart();
}

void PauseLayer::backCallback( CCObject* object )
{
	restore();
	if(m_pStageScene)
		m_pStageScene->opGoBack();
}

void PauseLayer::show()
{
	if(m_bInShow)
		return;

	m_bInShow = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMoveTo* pMoveDown = CCMoveTo::create(0.3, ccp(size.width / 2, size.height / 2 + 30));
	CCMoveTo* pMoveShakeBack = CCMoveTo::create(0.1, ccp(size.width / 2, size.height / 2 + 30 + SHAKE_DISTANCE));
	CCFiniteTimeAction* pSeq = CCSequence::create(pMoveDown, pMoveShakeBack,NULL);
	m_pColorLayer->setVisible(true);
	m_pFrame->runAction(pSeq);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::sharedInstance()->showAd();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID	
	AdViewManager::sharedInstance()->show();	
#endif
}

void PauseLayer::restore()
{
	m_bInShow = false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint nowTVPostion = m_pFrame->getPosition();
	CCMoveTo* pMoveUp = CCMoveTo::create(0.4, ccp(size.width / 2, m_pFrame->boundingBox().size.height / 2 + size.height));
	m_pColorLayer->setVisible(false);
	m_pFrame->runAction(pMoveUp);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::sharedInstance()->hideAd();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID	
	AdViewManager::sharedInstance()->hide();	
#endif
}

bool PauseLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bInShow)
		return true;
	else
		return false;
}

void PauseLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);
	if(m_bInShow)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS   
        IOSWrapper::sharedInstance()->showAd();   
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID	
		AdViewManager::sharedInstance()->show();	
#endif
	 }
}

void PauseLayer::onExit()
{
    CCLayer::onExit();
	if(m_bInShow)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS    
        IOSWrapper::sharedInstance()->hideAd();   
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID	
		AdViewManager::sharedInstance()->hide();	
#endif
	}
}

PauseLayer::~PauseLayer()
{
	int a  = 1;
	a++;
}
