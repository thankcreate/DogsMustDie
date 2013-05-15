#include "AboutLayer.h"
#include "StageSelectScene.h"
#include "Defines.h"
#include "StartupScene.h"
#include "MyUseDefaultDef.h"
#include "AudioManager.h"
#include "AdViewManager.h"
#include "LocalizeManager.h"

using namespace cocos2d;

AboutLayer::AboutLayer(void)
{	
}

AboutLayer::~AboutLayer(void)
{

}


bool AboutLayer::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());	

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// 1. ±³¾°Í¼
		CCSprite* pBKG = CCSprite::create("About_bkg.png");
		pBKG->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pBKG,1);	


		CCSprite* pTitle = CCSprite::create(I18N_FILE("About_title.png"));
		pTitle->setPosition(ccp(size.width / 2, 420));
		this->addChild(pTitle, 1);
		
		// goback		
		CCMenu* pMenu = CCMenu::create(NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);

		CCMenuItemImage *pGobackItem = CCMenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(AboutLayer::gobackCallback));
		CC_BREAK_IF(! pGobackItem);		
		float iconSize = 40;
		float margin = 0;
		pGobackItem->setPosition(ccp(iconSize + margin, size.height - iconSize - margin));		
		pMenu->addChild(pGobackItem);

		setKeypadEnabled(true);
		PreloadEffect("Audio_button.mp3");



		bRet = true;
	} while (0);

	return bRet;
}

void AboutLayer::gobackCallback(CCObject* pSender)
{
	CCScene* stage = StartupScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);
	PlayEffect("Audio_button.mp3");
}


void AboutLayer::keyBackClicked()
{
    gobackCallback(NULL);    
}


void AboutLayer::onExit()
{
	CCLayer::onExit();
}