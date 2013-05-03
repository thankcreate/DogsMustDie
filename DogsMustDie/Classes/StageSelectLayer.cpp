#include "StageSelectLayer.h"
#include "Defines.h"
#include "StageSelectScene.h"
#include "SubStageItem.h"
#include "StageMap.h"
#include "StartupScene.h"
#include "StageSelectFrameSprite.h"
#include "MyUseDefaultDef.h"
#include "AudioManager.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IAPWrapper.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AdViewManager.h"
#endif

using namespace cocos2d;

StageSelectLayer::StageSelectLayer() :
m_pScrollLayer(NULL),
	m_pLeftThumb(NULL),
	m_pRightThumb(NULL),
	m_pBuyBtnArray(NULL)
{	
}

StageSelectLayer::~StageSelectLayer()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	CC_SAFE_RELEASE(m_pBuyBtnArray);
	// 清除掉iap的delegate不然回调过来必然会崩溃
	IAPWrapper::sharedInstance()->clearDelegate();
#endif
}

float sCurrentIndex = 0;

bool StageSelectLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		// 背景图
		CCSprite* pBKG = CCSprite::create("StageSelect_bkg.png");
		pBKG->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pBKG,1);

		// 关数
		// 关数层增加在一个独立的scroll层上
		setScrollLayer(CCLayer::create());	
		CCSize frameLayerSize = CCSizeMake(size.width * BIG_STAGE_COUNT, size.height);
		m_pScrollLayer->setContentSize(frameLayerSize);
		m_pScrollLayer->setPosition(0,0);
		this->addChild(m_pScrollLayer, 1);

		this->setContentSize(CCSizeMake(size.width * BIG_STAGE_COUNT, size.height));
		float frameX1 = size.width / 2;
		float frameY1 = size.height / 2 + 5;
		char *titleArray[3] = {"StageSelect_title1.png", "StageSelect_title2.png", "StageSelect_title3.png"};
		
		for(int i = 0; i < BIG_STAGE_COUNT; i++)
		{
			StageSelectFrameSprite* pMainFrame = 
				StageSelectFrameSprite::create(this, this, menu_selector(StageSelectLayer::gotoStageCallback),
				i + 1, titleArray[i]);
			pMainFrame->setPosition(ccp(frameX1 + size.width * i, frameY1));
			m_pScrollLayer->addChild(pMainFrame, 1);			
		}



		// 左右小按钮
		CCMenu* pRootMenu = CCMenu::create(NULL);
		pRootMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pRootMenu);
		this->addChild(pRootMenu, 2);

		setLeftThumb(CCMenuItemImage::create(
			"StageSelect_moveleft.png",
			"StageSelect_moveleft_pressed.png",
			this,
			menu_selector(StageSelectLayer::slideCallback)));
		CCSprite* disableLeft = CCSprite::create("StageSelect_moveleft.png");
		disableLeft->setOpacity(50);
		m_pLeftThumb->setDisabledImage(disableLeft);
		m_pLeftThumb->setTag(SLIDER_LEFT);		
		m_pLeftThumb->setPosition(ccp(77, 240));		
		pRootMenu->addChild(m_pLeftThumb);



		setRightThumb(CCMenuItemImage::create(
			"StageSelect_moveright.png",
			"StageSelect_moveright_pressed.png",
			this,
			menu_selector(StageSelectLayer::slideCallback)));
		CCSprite* disableRight = CCSprite::create("StageSelect_moveright.png");
		disableRight->setOpacity(50);
		m_pRightThumb->setDisabledImage(disableRight);		
		m_pRightThumb->setTag(SLIDER_RIGHT);
		m_pRightThumb->setPosition(ccp(size.width - 77, 240));
		pRootMenu->addChild(m_pRightThumb);


		// 左上角的返回键
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(StageSelectLayer::menuBackCallback));
		CC_BREAK_IF(! pCloseItem);				
		float iconSize = 40;
		float margin = 0;
		pCloseItem->setPosition(ccp(iconSize + margin, size.height - iconSize - margin));
		pRootMenu->addChild(pCloseItem);


		// 移m_pScrollLayer到指定位子
		m_pScrollLayer->setPositionX(- sCurrentIndex * size.width);
		if(sCurrentIndex == 0)
		{
			m_pLeftThumb->setEnabled(false);
		}
		else if(sCurrentIndex == BIG_STAGE_COUNT - 1)
		{
			m_pRightThumb->setEnabled(false);
		}

		setKeypadEnabled(true);
		PreloadEffect("Audio_button.mp3");
		bRet = true;
	} while (0);

	return bRet;
}

void StageSelectLayer::buyCallback(CCObject* pSender)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	IAPWrapper::sharedInstance()->buyProductIdentifierWithPromptDialog(AppPurchaseProUpgradeProductId,"Upgrade to PRO version to unlock stage 2 ~ 3. That's a lot of help for us to improve this game.", this);
#endif
}

void StageSelectLayer::restoreCallback(CCObject* pSender)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	IAPWrapper::sharedInstance()->restorePurchase(this);
#endif    
}

void StageSelectLayer::gotoStageCallback(CCObject* pSender)
{
	if(pSender == NULL)
		return;

	PlayEffect("Audio_button.mp3");
	SubStageItem* item = (SubStageItem*)pSender;
	StageMap::sharedInstance()->gotoStage(item->m_bigIndex, item->m_smallIndex);
}

void StageSelectLayer::slideCallback(CCObject* pSender)
{
	CCSize size = WIN_SIZE;
	CCMenuItemImage* item = (CCMenuItemImage*)pSender;
	int nTag = item->getTag();	

	PlayEffect("Audio_button.mp3");
	if(nTag == SLIDER_LEFT)
	{
		if(sCurrentIndex > 0)
		{
			float moveToX = - (sCurrentIndex - 1) * size.width;
			CCMoveTo* moveRight = CCMoveTo::create(0.4, 
				ccp(moveToX+ 50, m_pScrollLayer->getPositionY()));

			CCMoveTo* moveBack = CCMoveTo::create(0.1, 
				ccp(moveToX, m_pScrollLayer->getPositionY()));

			CCFiniteTimeAction* pSeq = CCSequence::create(moveRight, moveBack,NULL);	
			m_pScrollLayer->runAction(pSeq);			
			if(sCurrentIndex == BIG_STAGE_COUNT - 1)
			{
				m_pRightThumb->setEnabled(true);
			}

			if(--sCurrentIndex == 0)
			{
				m_pLeftThumb->setEnabled(false);
			}
		}
	}
	else if(nTag == SLIDER_RIGHT)
	{
		if(sCurrentIndex < BIG_STAGE_COUNT - 1)
		{
			float moveToX = - (sCurrentIndex + 1)* size.width;
			CCMoveTo* moveLeft = CCMoveTo::create(0.4, 
				ccp(moveToX - 50, m_pScrollLayer->getPositionY()));
			CCMoveTo* moveBack = CCMoveTo::create(0.1, 
				ccp(moveToX, m_pScrollLayer->getPositionY()));			
			CCFiniteTimeAction* pSeq = CCSequence::create(moveLeft, moveBack,NULL);
			m_pScrollLayer->runAction(pSeq);			

			if(sCurrentIndex == 0)
			{
				m_pLeftThumb->setEnabled(true);
			}

			if(++sCurrentIndex == BIG_STAGE_COUNT -1)
			{
				m_pRightThumb->setEnabled(false);
			}			
		}		
	}

}

void StageSelectLayer::menuBackCallback(CCObject* pSender)
{
	PlayEffect("Audio_button.mp3");
	CCScene* stage = StartupScene::create();						
	CCDirector::sharedDirector()->replaceScene(stage);
}

void StageSelectLayer::keyBackClicked()
{
	menuBackCallback(NULL);
}

// IAPCallback
void StageSelectLayer::productsDownloaded(const std::vector<std::string>& products)
{

}

void StageSelectLayer::purchased(bool isSuccessful)
{
	/*if(isSuccessful)
	{
		SaveBooleanToXML(KEY_PRO_UPGRADE_PURCHASED, true);
		SaveUserDefault();

		if(m_pBuyBtnArray && m_pBuyBtnArray->count() != 0)
		{
			CCObject* pOb = NULL;
			CCARRAY_FOREACH(m_pBuyBtnArray, pOb)
			{
				CCMenuItemImage* pItem = (CCMenuItemImage*) pOb;
				pItem->setVisible(false);
			}
		}

		reloadScrollLayer();
	}*/
}

void StageSelectLayer::reloadScrollLayer()
{
	this->removeChild(m_pScrollLayer, true);

	CCSize size = WIN_SIZE;
	setScrollLayer(CCLayer::create());
	CCSize frameLayerSize = CCSizeMake(size.width * BIG_STAGE_COUNT, size.height);
	m_pScrollLayer->setContentSize(frameLayerSize);
	m_pScrollLayer->setPosition(0,0);
	this->addChild(m_pScrollLayer, 1);


	this->setContentSize(CCSizeMake(size.width * BIG_STAGE_COUNT, size.height));
	float frameX1 = size.width / 2;
	float frameY1 = size.height / 2;
	char *titleArray[2] = {"StageSelect_title1.png", "StageSelect_title2.png"};	
	for(int i = 0; i < BIG_STAGE_COUNT; i++)
	{
		StageSelectFrameSprite* pMainFrame =
			StageSelectFrameSprite::create(this, this, menu_selector(StageSelectLayer::gotoStageCallback),
			i + 1, titleArray[i]);
		pMainFrame->setPosition(ccp(frameX1 + size.width * i, frameY1));
		m_pScrollLayer->addChild(pMainFrame, 1);			
	}

	// 移m_pScrollLayer到指定位子
	m_pScrollLayer->setPositionX(- sCurrentIndex * size.width);
	if(sCurrentIndex == 0)
	{
		m_pLeftThumb->setEnabled(false);
	}
	else if(sCurrentIndex == BIG_STAGE_COUNT - 1)
	{
		m_pRightThumb->setEnabled(false);
	}
}



void StageSelectLayer::onExit()
{
	CCLayer::onExit();
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AdViewManager::sharedInstance()->hide();
#endif
}

void StageSelectLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AdViewManager::sharedInstance()->show();	
#endif
}
