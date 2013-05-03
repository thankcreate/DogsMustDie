#include "StageGameOverLayer.h"
#include "AudioManager.h"
#include "Defines.h"
#include "StartupScene.h"
StageGameOverLayer::StageGameOverLayer( void ) :
m_pStoryLabel(NULL)
{

}


bool StageGameOverLayer::init()
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
			menu_selector(StageGameOverLayer::skipCallback));
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



void StageGameOverLayer::initStory()
{
	CCSize size = WIN_SIZE;
	setStoryLabel(CCLabelTTF::create("Congratulations!\nWe finally defeated the invaders.\nDog sucks! God bless we cats.\nYou are the new hero of the cat planet!\nThe era of cats is coming.\nIf you feel unsatisfied, you can still go to endless mode to continue your noble career.\nDogs must die!", 
		FONT_8BITOPERATOR_JVE, 30));
	m_pStoryLabel->setDimensions(CCSizeMake(566, -1));
	m_pStoryLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_pStoryLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	m_pStoryLabel->setPosition(ccp(size.width / 2, 0 - m_pStoryLabel->boundingBox().size.height / 2 + 60));
	this->addChild(m_pStoryLabel, 1); // 字要放要rainbow下面

	CCMoveTo* pMoveUp = CCMoveTo::create(26, ccp(size.width / 2, size.height / 2));
	m_pStoryLabel->runAction(pMoveUp);

	//this->scheduleOnce(schedule_selector(StageGameOverLayer::skipAutoInDelay), 40);
}

void StageGameOverLayer::skipAutoInDelay(float dt)
{
	skipCallback(NULL);
}

void StageGameOverLayer::skipCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");		
	CCScene* stage = StartupScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);
}