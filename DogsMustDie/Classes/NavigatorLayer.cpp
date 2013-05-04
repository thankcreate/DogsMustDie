#include "NavigatorLayer.h"
#include "StageBaseScene.h"
#include "AudioManager.h"
#include "Defines.h"

NavigatorLayer::NavigatorLayer() :
	m_pStageScene(NULL),
	m_bInShow(false),
	m_pFrame(NULL),
	m_nTime(0),
	m_nLostUnit(0),
	m_pTitleLabel(NULL)
{

}

NavigatorLayer::~NavigatorLayer()
{
	int a = 1;
	a++;
}

bool NavigatorLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// 黑色半透明背景
		ccColor4B color = ccc4(0, 0, 0, 190);
		setColorLayer(CCLayerColor::create(color));
		m_pColorLayer->setPosition(0, 0);
		m_pColorLayer->setContentSize(size);
		this->addChild(m_pColorLayer);

		// 框架
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("Navigator_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2 + size.height));
		this->addChild(m_pFrame);

		// 标题
		CCString* pStrTitle = getTitle();
		setTitleLabel(CCLabelTTF::create(pStrTitle->getCString(), FONT_8BITOPERATOR_JVE, 45));		
		m_pTitleLabel->setPosition(ccp(192, 285));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTitleLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pTitleLabel);

	

		// 禁止后层的按键,不写的话得手动remove from dispatcher,否则本类不会被析构
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
	if(m_bInShow)
		return;
	m_bInShow = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMoveTo* pMoveDown = CCMoveTo::create(0.3, ccp(size.width / 2, size.height / 2 + 30));
	CCMoveTo* pMoveShakeBack = CCMoveTo::create(0.1, ccp(size.width / 2, size.height / 2 + 30 + SHAKE_DISTANCE));
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

