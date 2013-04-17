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

		pStartItem->setPosition(ccp(400, 210));
		pMenu->addChild(pStartItem);

		// option
		CCMenuItemImage *pOptionItem = CCMenuItemImage::create(
			"Startup_btn_option_normal.png",
			"Startup_btn_option_pressed.png",
			this,
			menu_selector(StartupLayer::optionCallback));
		CC_BREAK_IF(! pOptionItem);		

		pOptionItem->setPosition(ccp(400, 140));
		pMenu->addChild(pOptionItem);


		// about
		CCMenuItemImage *pAboutItem = CCMenuItemImage::create(
			"Startup_btn_about_normal.png",
			"Startup_btn_about_pressed.png",
			this,
			menu_selector(StartupLayer::aboutCallback));
		CC_BREAK_IF(! pAboutItem);		

		pAboutItem->setPosition(ccp(400, 70));
		pMenu->addChild(pAboutItem);

		
		shakePlanets();
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
	CCScene* stage = StageSelectScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);	
}
void StartupLayer::optionCallback(CCObject* pSender)
{
	CCScene* stage = SettingScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);
}

void StartupLayer::aboutCallback(CCObject* pSender)
{
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
    
}