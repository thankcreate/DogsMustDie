#include "SettingLayer.h"
#include "StageSelectScene.h"
#include "Defines.h"
#include "StartupScene.h"
#include "MyUseDefaultDef.h"
#include "AudioManager.h"
#include "AdViewManager.h"
#include "LocalizeManager.h"

using namespace cocos2d;

SettingLayer::SettingLayer(void) :
p(NULL)
{	
}

SettingLayer::~SettingLayer(void)
{
}

bool SettingLayer::init()
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
		CCSprite* pBKG = CCSprite::create("Option_bkg.png");
		pBKG->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pBKG,1);	

		CCSprite* pTitle = CCSprite::create(I18N_FILE("Option_title.png"));
		pTitle->setPosition(ccp(size.width / 2, 420));
		this->addChild(pTitle, 1);

		CCSprite* pLblSound = CCSprite::create(I18N_FILE("Option_lbl_sound.png"));
		pLblSound->setPosition(ccp(289, 173));
		this->addChild(pLblSound, 1);

		CCSprite* pLblMusic = CCSprite::create(I18N_FILE("Option_lbl_music.png"));
		pLblMusic->setPosition(ccp(289, 97));
		this->addChild(pLblMusic, 1);

		// Menu
		CCMenu* pMenu = CCMenu::create(NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);

		CCMenuItemImage *btnOn =CCMenuItemImage::create("Option_btn_on.png" ,"Option_btn_on.png");
		CCMenuItemImage *btnOff =CCMenuItemImage::create("Option_btn_off.png","Option_btn_off.png"); 
		CCMenuItemToggle* soundToggle = CCMenuItemToggle::createWithTarget(
			this, menu_selector(SettingLayer::onSoundCallback),
			btnOn, btnOff, NULL);
		soundToggle->setPosition(ccp(483,174));
		pMenu->addChild(soundToggle);
		


		CCMenuItemImage *btnOn2 =CCMenuItemImage::create("Option_btn_on.png" ,"Option_btn_on.png");
		CCMenuItemImage *btnOff2 =CCMenuItemImage::create("Option_btn_off.png","Option_btn_off.png"); 
		CCMenuItemToggle* musicToggle = CCMenuItemToggle::createWithTarget(
			this, menu_selector(SettingLayer::onMusicCallback),
			btnOn2, btnOff2, NULL);
		musicToggle->setPosition(ccp(483,96));
		pMenu->addChild(musicToggle);


		// goback
		CCMenuItemImage *pGobackItem = CCMenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(SettingLayer::gobackCallback));
		CC_BREAK_IF(! pGobackItem);		
		float iconSize = 40;
		float margin = 0;
		pGobackItem->setPosition(ccp(iconSize + margin, size.height - iconSize - margin));		
		pMenu->addChild(pGobackItem);

		// refresh switch state
		int soundIndex = fromBoolToIndex(LoadBooleanFromXML(KEY_SWITCH_SOUNDS, true));
		int musicIndex = fromBoolToIndex(LoadBooleanFromXML(KEY_SWITCH_MUSIC, true));
		soundToggle->setSelectedIndex(soundIndex);
		musicToggle->setSelectedIndex(musicIndex);

		setKeypadEnabled(true);
		PreloadEffect("Audio_button.mp3");

		bRet = true;
	} while (0);

	return bRet;
}

int SettingLayer::fromBoolToIndex(bool enable)
{
	if(enable)
		return 0;
	return 1;
}

bool SettingLayer::fromIndexToBool(int index)
{
	if(index == 0)
		return true;
	return false;
}

void SettingLayer::onSoundCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");
	CCMenuItemToggle *toggleItem = (CCMenuItemToggle *)pSender;
	int index = toggleItem->getSelectedIndex();
	bool enable = fromIndexToBool(index);
	if(enable)
	{
		SaveBooleanToXML(KEY_SWITCH_SOUNDS,true);
		SaveUserDefault();
	}
	else if(index == 1)
	{
		SaveBooleanToXML(KEY_SWITCH_SOUNDS,false);
		SaveUserDefault();
	}
}
void SettingLayer::onMusicCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");
	CCMenuItemToggle *toggleItem = (CCMenuItemToggle *)pSender;
	int index = toggleItem->getSelectedIndex();
	bool enable = fromIndexToBool(index);
	if(enable)
	{
		SaveBooleanToXML(KEY_SWITCH_MUSIC,true);
		PlayBGM("Audio_bgm_home.mp3");		
		SaveUserDefault();
	}
	else if(index == 1)
	{
		SaveBooleanToXML(KEY_SWITCH_MUSIC,false);
		AudioManager::getSharedInstance()->stopBackgroundMusic();		
		SaveUserDefault();
	}
}

void SettingLayer::gobackCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");
	CCScene* stage = StartupScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);	
}

void SettingLayer::keyBackClicked()
{
	gobackCallback(NULL);
}

void SettingLayer::onExit()
{
	CCLayer::onExit();
}