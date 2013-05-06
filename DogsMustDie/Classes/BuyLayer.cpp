#include "BuyLayer.h"
#include "StageSelectScene.h"
#include "Defines.h"
#include "StartupScene.h"
#include "MyUseDefaultDef.h"
#include "AudioManager.h"
#include "AdViewManager.h"
#include "LocalizeManager.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "IOSWrapper.h"
#include "IAPWrapper.h"
#endif

using namespace cocos2d;

BuyLayer::BuyLayer(void) :
	m_pFrame(NULL),
	m_pCoinCountLabel(NULL)
{	
}

BuyLayer::~BuyLayer(void)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	// 清除掉iap的delegate不然回调过来必然会崩溃
	IAPWrapper::sharedInstance()->clearDelegate();
#endif
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

		// 背景图
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
		CCLabelTTF* pTitle  = CCLabelTTF::create("Coin  Store", FONT_8BITOPERATOR_JVE, 60);		
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
		setCoinCountLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, 35));		
		m_pCoinCountLabel->setPosition(ccp(124,290));
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

	CCLabelTTF* pPrice10  = CCLabelTTF::create("0.99$", FONT_8BITOPERATOR_JVE, 30);		
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

	CCLabelTTF* pPrice20  = CCLabelTTF::create("1.99$", FONT_8BITOPERATOR_JVE, 30);		
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

	CCLabelTTF* pPrice50  = CCLabelTTF::create("4.99$", FONT_8BITOPERATOR_JVE, 30);		
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    int tag = ((CCNode*)pSender)->getTag();
    bool bIsLite = IOSWrapper::isLiteVersion();
    std::string productID = "";
    if(tag == TAG_10)
    {
        productID = bIsLite ? AppPurchaseCoin10_Lite : AppPurchaseCoin10_Pro;
    }
    else if(tag == TAG_20)
    {
        productID = bIsLite? AppPurchaseCoin20_Lite : AppPurchaseCoin20_Pro;
    }
    else if(tag == TAG_50)
    {
        productID = bIsLite ? AppPurchaseCoin50_Lite : AppPurchaseCoin50_Pro;
    }
    IAPWrapper::sharedInstance()->buyProductIdentifierWithPromptDialog(productID, I18N_STR("IAP_Buy_Coin_Description"), this);    
#endif
}

void BuyLayer::purchased(bool isSuccessful)
{
    if(isSuccessful)
        refreshCoinCountLabel();
}

