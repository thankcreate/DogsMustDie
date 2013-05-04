//
//  StartupLayer.cpp
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//


#include "StartupLayer.h"
#include "Defines.h"
#include "StageSelectScene.h"
#include "SettingScene.h"
#include "AboutScene.h"
#include "AudioManager.h"
#include "StageStartupCGScene.h"
#include "StageEndlessScene.h"
#include "LocalizeManager.h"
using namespace cocos2d;

StartupLayer::StartupLayer(void) :
m_pDogPlanet(NULL),
m_pCatPlanet(NULL)
{
}

StartupLayer::~StartupLayer(void)
{	
}


bool StartupLayer::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());	

		CCSize size = WIN_SIZE;
        
        const char* test = LocalizeManager::makeResourceFileName("Startup_bkg.png");

		// 背景
		CCSprite* pBackground = CCSprite::create("Startup_bkg.png");
		pBackground->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pBackground, 0);
		
		// 两侧的星球
		setCatPlanet(CCSprite::create("Startup_cat.png"));
		m_pCatPlanet->setPosition(ccp(120,133));
		this->addChild(m_pCatPlanet, 1);

		setDogPlanet(CCSprite::create("Startup_dog.png"));
		m_pDogPlanet->setPosition(ccp(680,133));
		this->addChild(m_pDogPlanet, 1);

		// 菜单
		CCMenu* pMenu = CCMenu::create(NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);

		// start
		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			"Startup_btn_start_normal.png",
			"Startup_btn_start_pressed.png",
			this,
			menu_selector(StartupLayer::startCallback));
		CC_BREAK_IF(! pStartItem);		

		pStartItem->setPosition(ccp(400, 244));
		pMenu->addChild(pStartItem);

		// endless
		CCMenuItemImage *pEndlessItem = CCMenuItemImage::create(
			"Startup_btn_endless_normal.png",
			"Startup_btn_endless_pressed.png",
			this,
			menu_selector(StartupLayer::endlessCallback));
		CC_BREAK_IF(! pEndlessItem);		

		pEndlessItem->setPosition(ccp(400, 177));
		pMenu->addChild(pEndlessItem);

		// option
		CCMenuItemImage *pOptionItem = CCMenuItemImage::create(
			"Startup_btn_option_normal.png",
			"Startup_btn_option_pressed.png",
			this,
			menu_selector(StartupLayer::optionCallback));
		CC_BREAK_IF(! pOptionItem);		

		pOptionItem->setPosition(ccp(400, 110));
		pMenu->addChild(pOptionItem);


		// about
		CCMenuItemImage *pAboutItem = CCMenuItemImage::create(
			"Startup_btn_about_normal.png",
			"Startup_btn_about_pressed.png",
			this,
			menu_selector(StartupLayer::aboutCallback));
		CC_BREAK_IF(! pAboutItem);		



		pAboutItem->setPosition(ccp(400, 43));
		pMenu->addChild(pAboutItem);		

		shakePlanets();

		this->setKeypadEnabled(true);

		PreloadEffect("Audio_button.mp3");
		bRet = true;
	} while (0);

	return bRet;	
}

// 使两个星球上下晃动
void StartupLayer::shakePlanets()
{
	if(m_pDogPlanet== NULL || m_pCatPlanet == NULL)
		return;

	CCPoint originalPostion = m_pDogPlanet->getPosition();
	CCMoveTo* pMoveUp = CCMoveTo::create(0.8, ccpAdd(originalPostion, ccp(0,10)));
	CCMoveTo* pMoveDown = CCMoveTo::create(0.8,originalPostion);
	CCFiniteTimeAction* pSeq = CCSequence::create(pMoveUp, pMoveDown, NULL);
	CCRepeat* repeat = CCRepeat::create(pSeq, 5000);
	m_pDogPlanet->runAction(repeat);

	originalPostion = m_pCatPlanet->getPosition();
	pMoveDown = CCMoveTo::create(0.8, ccpAdd(originalPostion, ccp(0,-10)));
	pMoveUp = CCMoveTo::create(0.8,originalPostion);
	pSeq = CCSequence::create(pMoveDown,pMoveUp, NULL);
	repeat = CCRepeat::create(pSeq, 5000);
	m_pCatPlanet->runAction(repeat);
}

void StartupLayer::startCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");
	CCScene* stage = StageSelectScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);	
}
void StartupLayer::optionCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");
	CCScene* stage = SettingScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);
}

void StartupLayer::aboutCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");	
	CCScene* stage = AboutScene::create();	
	CCDirector::sharedDirector()->replaceScene(stage);
}

// 目前仅对iOS版有效，评分
void StartupLayer::rateusCallback(CCObject* pSender)
{
    
}

// 目前仅对安卓有效，后退时退出
void StartupLayer::keyBackClicked()
{
   CCDirector::sharedDirector()->end(); 
}

void StartupLayer::endlessCallback( CCObject* pSender )
{
	PlayEffect("Audio_button.mp3");
	CCScene* stage = StageEndlessScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);
}
