#include "NavigatorLayer.h"
#include "StageBaseScene.h"
#include "AudioManager.h"
#include "Defines.h"

NavigatorLayer::NavigatorLayer() :
	m_pStageScene(NULL),
	m_bInShow(false),
	m_pTimeLabel(NULL),
	m_pLostUnitLabel(NULL),
	m_pFrame(NULL),
	m_nTime(0),
	m_nLostUnit(0),
	m_pTitleLabel(NULL)
{

}

NavigatorLayer::~NavigatorLayer()
{

}

bool NavigatorLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// ºÚÉ«°ëÍ¸Ã÷±³¾°
		ccColor4B color = ccc4(0, 0, 0, 190);
		setColorLayer(CCLayerColor::create(color));
		m_pColorLayer->setPosition(0, 0);
		m_pColorLayer->setContentSize(size);
		this->addChild(m_pColorLayer);

		// ¿ò¼Ü
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("Navigator_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2 + size.height));
		this->addChild(m_pFrame);

		// ±êÌâ
		CCString* pStrTitle = getTitle();
		setTitleLabel(CCLabelTTF::create(pStrTitle->getCString(), "8bitoperator JVE.ttf", 45));		
		m_pTitleLabel->setPosition(ccp(192, 285));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTitleLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pTitleLabel);

	

		// ½ûÖ¹ºó²ãµÄ°´¼ü
		this->setTouchEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

bool NavigatorLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_bInShow)
		return true;
	else
		return false;
}

void NavigatorLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);	
}




void NavigatorLayer::show()
{
	m_bInShow = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMoveTo* pMoveDown = CCMoveTo::create(0.3, ccp(size.width / 2, size.height / 2));
	CCMoveTo* pMoveShakeBack = CCMoveTo::create(0.1, ccp(size.width / 2, size.height / 2 + SHAKE_DISTANCE));
	CCFiniteTimeAction* pSeq = CCSequence::create(pMoveDown, pMoveShakeBack,NULL);
	m_pColorLayer->setVisible(true);
	m_pFrame->runAction(pSeq);
}

void NavigatorLayer::restore()
{
	m_bInShow = false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint nowTVPostion = m_pFrame->getPosition();
	CCMoveTo* pMoveUp = CCMoveTo::create(0.4, ccp(size.width / 2, m_pFrame->boundingBox().size.height / 2 + size.height));
	m_pColorLayer->setVisible(false);
	m_pFrame->runAction(pMoveUp);
}


void NavigatorLayer::restartCallback(CCObject* object)
{
	if(!m_bInShow)
	{
		return;
	}

	PlayEffect("Audio_button.mp3");
	if(m_pStageScene)
	{
		restore();
		m_pStageScene->opReStart();
	}
}

void NavigatorLayer::gotoNext(CCObject* object)
{
	if(!m_bInShow)
	{
		return;
	}

	PlayEffect("Audio_button.mp3");
	if(m_pStageScene)
	{
		restore();
		m_pStageScene->gotoNext();
	}
}

void NavigatorLayer::gotoStageSelect( CCObject* object )
{
	if(!m_bInShow)
	{
		return;
	}

	PlayEffect("Audio_button.mp3");
	if(m_pStageScene)
	{
		restore();
		m_pStageScene->opGoBack();
	}
}


void NavigatorLayer::setTime(int nTime)
{
	m_nTime = nTime;
	if(!m_pTimeLabel)
	{		
		setTimeLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 30));		
		m_pTimeLabel->setDimensions(CCSizeMake(220, 25));
		m_pTimeLabel->setPosition(ccp(255, 201));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTimeLabel->setColor(ccMyOrange);
		m_pTimeLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pTimeLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pTimeLabel);
	}

	CCString* pFullTimeString = CCString::createWithFormat("Time:  %d s", m_nTime);
	m_pTimeLabel->setString(pFullTimeString->getCString());
}

void NavigatorLayer::setLostUnit(int nLost)
{
	m_nLostUnit = nLost;
	if(!m_pLostUnitLabel)
	{		
		setLostUnitLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 30));		
		m_pLostUnitLabel->setDimensions(CCSizeMake(220, 25));
		m_pLostUnitLabel->setPosition(ccp(255, 170));
		m_pLostUnitLabel->getTexture()->setAliasTexParameters();
		ccColor3B ccMyOrange={255, 104, 0};
		m_pLostUnitLabel->setColor(ccMyOrange);
		m_pLostUnitLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_pLostUnitLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pFrame->addChild(m_pLostUnitLabel);
	}

	CCString* pFullLostUnitString = CCString::createWithFormat("Unit lost:  %d cat", m_nLostUnit);
	m_pLostUnitLabel->setString(pFullLostUnitString->getCString());
}