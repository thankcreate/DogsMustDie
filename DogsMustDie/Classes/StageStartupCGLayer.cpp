#include "StageStartupCGLayer.h"
#include "AudioManager.h"
#include "Defines.h"
#include "StartupScene.h"
#include "LocalizeManager.h"
StageStartupCGLayer::StageStartupCGLayer( void ) :
	m_pStoryLabel(NULL)
{

}


bool StageStartupCGLayer::init()
{

	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());	

		CCSize size = WIN_SIZE;

		// 背景
		CCSprite* pBackground = CCSprite::create("StageStartupCG_bkg.png");
		pBackground->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pBackground, 0);

		CCSprite* pRainbowHeader = CCSprite::create("StageStartupCG_rainbow.png");
		pRainbowHeader->setPosition(ccp(size.width / 2, size.height - pRainbowHeader->boundingBox().size.height / 2));
		this->addChild(pRainbowHeader, 2);

		CCSprite* pCat = CCSprite::create("StageStartupCG_cat.png");
		pCat->setPosition(ccp(68, 375));
		this->addChild(pCat, 2);

		CCSprite* pDog = CCSprite::create("StageStartupCG_dog.png");
		pDog->setPosition(ccp(732, 375));
		this->addChild(pDog, 2);


		// 菜单
		CCMenu* pMenu = CCMenu::create(NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);

		// start
		CCMenuItemImage *pSkipItem = CCMenuItemImage::create(
			"StageStartupCG_skip_normal.png",
			"StageStartupCG_skip_pressed.png",
			this,
			menu_selector(StageStartupCGLayer::skipCallback));
		CC_BREAK_IF(! pSkipItem);		

		pSkipItem->setPosition(ccp(745, 28));
		pMenu->addChild(pSkipItem);

		// 故事
		initStory();	

		this->setKeypadEnabled(true);
		
		bRet = true;
	} while (0);

	return bRet;	
}



void StageStartupCGLayer::initStory()
{
	CCSize size = WIN_SIZE;
	setStoryLabel(CCLabelTTF::create(I18N_STR("CG_Startup_Text"),
		FONT_8BITOPERATOR_JVE, 30));
	m_pStoryLabel->setDimensions(CCSizeMake(566, 450));
	m_pStoryLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_pStoryLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	m_pStoryLabel->setPosition(ccp(size.width / 2, 0 - m_pStoryLabel->boundingBox().size.height / 2 + 60));
	this->addChild(m_pStoryLabel, 1); // 字要放要rainbow下面

	CCMoveTo* pMoveUp = CCMoveTo::create(30, ccp(size.width / 2, size.height / 2 + 170));
	m_pStoryLabel->runAction(pMoveUp);

	this->scheduleOnce(schedule_selector(StageStartupCGLayer::skipAutoInDelay), 33);
}

void StageStartupCGLayer::skipAutoInDelay(float dt)
{
	skipCallback(NULL);
}

void StageStartupCGLayer::skipCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");		
	CCScene* stage = StartupScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);
}