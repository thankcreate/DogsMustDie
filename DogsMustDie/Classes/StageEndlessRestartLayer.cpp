#include "StageEndlessRestartLayer.h"
#include "MyMenu.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"

#define SHAKE_ANGLE 12
#define SCALE 1.2
StageEndlessRestartLayer::StageEndlessRestartLayer() :	
m_pHappyDog(NULL),
	m_pFlickerAction(NULL)
{

}

StageEndlessRestartLayer::~StageEndlessRestartLayer()
{
	CC_SAFE_RELEASE(m_pFlickerAction);
}

bool StageEndlessRestartLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!NavigatorLayer::init());

		// 左侧头像
		setHappyDog(CCSprite::create("Navigator_dog_win.png"));
		m_pHappyDog->setPosition(ccp(70,150));
		m_pHappyDog->setRotation(-SHAKE_ANGLE);
		m_pHappyDog->setScaleX(-SCALE);
		m_pHappyDog->setScaleY(SCALE);
		m_pFrame->addChild(m_pHappyDog, 2);
		CCCallFunc* pDogFunc1 = CCCallFunc::create(this, callfunc_selector(StageEndlessRestartLayer::dogFunc1));
		CCCallFunc* pDogFunc2 = CCCallFunc::create(this, callfunc_selector(StageEndlessRestartLayer::dogFunc2));
		CCActionInterval* pDelay = CCActionInterval::create(0.6);
		CCFiniteTimeAction* pSeq = CCSequence::create(pDogFunc1, pDelay, pDogFunc2, pDelay ,NULL);
		CCRepeat* pReapeat = CCRepeat::create(pSeq, ENDLESS_COUNT);
		setFlickerAction(pReapeat);


		// 按钮
		MyMenu* pMenu = MyMenu::create();
		pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(pMenu, 1);


		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			"Navigator_btn_back_normal.png",
			"Navigator_btn_back_pressed.png",
			"Navigator_btn_back_normal.png",
			this,
			menu_selector(StageEndlessRestartLayer::backCallback));	

		pBack->setPosition(ccp(240, 67));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pNext = new CCMenuItemImage();		
		pNext->initWithNormalImage(
			"Navigator_btn_restart_normal.png",
			"Navigator_btn_restart_pressed.png",
			"Navigator_btn_restart_normal.png",
			this,
			menu_selector(StageEndlessRestartLayer::restartCallback));	

		pNext->setPosition(ccp(310, 67));	
		pMenu->addChild(pNext);

		bRet = true;
	}while(0);

	return bRet;
}


void StageEndlessRestartLayer::dogFunc1()
{
	m_pHappyDog->setScaleX(-SCALE);
	m_pHappyDog->setScaleY(SCALE);
	m_pHappyDog->setRotation(-SHAKE_ANGLE);
}

void StageEndlessRestartLayer::dogFunc2()
{
	m_pHappyDog->setScaleX(+SCALE);
	m_pHappyDog->setScaleY(SCALE);
	m_pHappyDog->setRotation(+SHAKE_ANGLE);
}


void StageEndlessRestartLayer::backCallback(CCObject* pOb)
{
	getStageScene()->opGoBack();
}

void StageEndlessRestartLayer::restartCallback(CCObject* pOb)
{
	restore();
	getStageScene()->opReStart();
}
CCString* StageEndlessRestartLayer::getTitle()
{
	return CCString::create("LOSE");
}


void StageEndlessRestartLayer::restore()
{
	NavigatorLayer::restore();
	m_pHappyDog->stopAllActions();
}



void StageEndlessRestartLayer::show()
{
	NavigatorLayer::show();
	m_pHappyDog->stopAllActions();
	if(m_pFlickerAction)
		m_pHappyDog->runAction(m_pFlickerAction);
}


void StageEndlessRestartLayer::setRound( int round )
{
	m_nRound = round;	

	if(!m_pRoundLabel)
	{		
		setRoundLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 30));		
		m_pRoundLabel->setDimensions(CCSizeMake(220, 25));
		m_pRoundLabel->setPosition(ccp(255, 201));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pRoundLabel->setColor(ccMyOrange);
		m_pRoundLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pRoundLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pRoundLabel);
	}

	// 代码走到此处说明已经失败了，所以前一关的round值才是current，不然会引起用户误解
	// 当前逻辑里的best round是指完成某一关，不是指玩到某一关
	int before = m_nRound - 1;
	if(before < 0)
		before = 0;
	CCString* pFullRoundString = CCString::createWithFormat("Current round:  %d", before);
	m_pRoundLabel->setString(pFullRoundString->getCString());

	int best = LoadIntegerFromXML(KEY_ENDLESS_BEST_ROUND, 0);
	if(!m_pBestRoundLabel)
	{		
		setBestRoundLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 30));		
		m_pBestRoundLabel->setDimensions(CCSizeMake(220, 25));
		m_pBestRoundLabel->setPosition(ccp(255, 170));
		m_pBestRoundLabel->getTexture()->setAliasTexParameters();
		ccColor3B ccMyOrange={255, 104, 0};
		m_pBestRoundLabel->setColor(ccMyOrange);
		m_pBestRoundLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pBestRoundLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pBestRoundLabel);
	}

	CCString* pFullBestRoundString = CCString::createWithFormat("Best round:  %d", best);
	m_pBestRoundLabel->setString(pFullBestRoundString->getCString());
}