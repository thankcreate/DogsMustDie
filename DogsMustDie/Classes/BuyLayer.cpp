#include "BuyLayer.h"
#include "StageSelectScene.h"
#include "Defines.h"
#include "StartupScene.h"
#include "MyUseDefaultDef.h"
#include "AudioManager.h"
#include "AdViewManager.h"

using namespace cocos2d;

BuyLayer::BuyLayer(void) :
	m_pFrame(NULL),
	m_pCoinCountLabel(NULL)
{	
}

BuyLayer::~BuyLayer(void)
{

}


bool BuyLayer::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());	

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// ±³¾°Í¼
		CCSprite* pBKG = CCSprite::create("Buy_bkg.png");
		pBKG->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(pBKG,1);		

		// goback		
		CCMenu* pMenu = CCMenu::create(NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);

		CCMenuItemImage *pGobackItem = CCMenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(BuyLayer::gobackCallback));
		CC_BREAK_IF(! pGobackItem);		
		float iconSize = 40;
		float margin = 0;
		pGobackItem->setPosition(ccp(iconSize + margin, size.height - iconSize - margin));		
		pMenu->addChild(pGobackItem);

		// frame
		setFrame(CCSprite::create("Buy_frame_full.png"));
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(m_pFrame, 1);

		// title
		CCLabelTTF* pTitle  = CCLabelTTF::create("Coin  Store", "8bitoperator JVE.ttf", 60);		
		pTitle->setPosition(ccp(260, 207));
		ccColor3B ccMyOrange={255, 104, 0};
		pTitle->setColor(ccMyOrange);
		m_pFrame->addChild(pTitle);

		CCSprite* pCatFace = CCSprite::create("Cat_normal.png");
		pCatFace->setPosition(ccp(100, 207));
		m_pFrame->addChild(pCatFace, 1);

		CCSprite* pDogFace = CCSprite::create("Dog_cry.png");
		pDogFace->setPosition(ccp(420, 207));
		m_pFrame->addChild(pDogFace, 1);

		// coin part
		CCSprite* pCoin = CCSprite::create("Coin.png");
		pCoin->setPosition(ccp(70, 290));
		m_pFrame->addChild(pCoin);

		// coin label
		setCoinCountLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 35));		
		m_pCoinCountLabel->setPosition(ccp(124,293));	
		m_pCoinCountLabel->setDimensions(CCSizeMake(58, 30));
		m_pCoinCountLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pCoinCountLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);		
		m_pCoinCountLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pCoinCountLabel);

		refreshCoinCountLabel();

		// buy button
		initButtons();

		setKeypadEnabled(true);
		PreloadEffect("Audio_button.mp3");

		bRet = true;
	} while (0);

	return bRet;
}

void BuyLayer::refreshCoinCountLabel()
{
	int count = LoadIntegerFromXML(KEY_COIN_COUNT , 0);
	CCString* pStrCoinCount = CCString::createWithFormat("x %d", count);
	m_pCoinCountLabel->setString((pStrCoinCount->getCString()));
}

void BuyLayer::initButtons()
{
	if(!m_pFrame)
		return;

	CCMenu* pMenu = CCMenu::create(NULL);
	pMenu->setPosition(CCPointZero);	
	m_pFrame->addChild(pMenu, 1);

	// 10
	CCMenuItemImage *pBtn10 = CCMenuItemImage::create(
		"Buy_btn_10_normal.png",
		"Buy_btn_10_pressed.png",
		this,
		menu_selector(BuyLayer::buyCallback));
	pBtn10->setTag(TAG_10);
	pBtn10->setPosition(ccp(138,127));
	pMenu->addChild(pBtn10);

	CCLabelTTF* pPrice10  = CCLabelTTF::create("0.99$", "8bitoperator JVE.ttf", 30);		
	pPrice10->setPosition(ccp(138, 71));
	ccColor3B ccMyOrange={255, 104, 0};
	pPrice10->setColor(ccMyOrange);
	m_pFrame->addChild(pPrice10);

	// 20
	CCMenuItemImage *pBtn20 = CCMenuItemImage::create(
		"Buy_btn_20_normal.png",
		"Buy_btn_20_pressed.png",
		this,
		menu_selector(BuyLayer::buyCallback));
	pBtn20->setTag(TAG_20);
	pBtn20->setPosition(ccp(255,127));
	pMenu->addChild(pBtn20);

	CCLabelTTF* pPrice20  = CCLabelTTF::create("1.99$", "8bitoperator JVE.ttf", 30);		
	pPrice20->setPosition(ccp(255, 71));	
	pPrice20->setColor(ccMyOrange);
	m_pFrame->addChild(pPrice20);

	// 50
	CCMenuItemImage *pBtn50 = CCMenuItemImage::create(
		"Buy_btn_50_normal.png",
		"Buy_btn_50_pressed.png",
		this,
		menu_selector(BuyLayer::buyCallback));
	pBtn50->setTag(TAG_50);
	pBtn50->setPosition(ccp(372,127));
	pMenu->addChild(pBtn50);

	CCLabelTTF* pPrice50  = CCLabelTTF::create("4.99$", "8bitoperator JVE.ttf", 30);		
	pPrice50->setPosition(ccp(372, 71));	
	pPrice50->setColor(ccMyOrange);
	m_pFrame->addChild(pPrice50);
}



void BuyLayer::gobackCallback(CCObject* pSender)
{	
	CCDirector::sharedDirector()->popScene();
	PlayEffect("Audio_button.mp3");
}


void BuyLayer::keyBackClicked()
{
	gobackCallback(NULL);    
}

void BuyLayer::buyCallback( CCObject* pSender )
{

}

