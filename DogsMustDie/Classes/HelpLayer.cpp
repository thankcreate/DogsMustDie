#include "HelpLayer.h"
#include "MyMenu.h"


HelpLayer::HelpLayer() :
	m_bInShow(false),
	m_pFrame(NULL),
	m_pMenu(NULL)
{

}

HelpLayer::~HelpLayer()
{

}

bool HelpLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// 1.ºÚÉ«°ëÍ¸Ã÷±³¾°
		ccColor4B color = ccc4(0, 0, 0, 190);
		setColorLayer(CCLayerColor::create(color));
		m_pColorLayer->setPosition(0, 0);
		m_pColorLayer->setContentSize(size);
		this->addChild(m_pColorLayer, 1);


		// 2.Ö÷¿ò¼Ü
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("StageBase_help_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, m_pFrame->boundingBox().size.height / 2 + size.height));
		this->addChild(m_pFrame, 2);

		// 3.ÍË³ö¼ü
		setMenu(MyMenu::create());
		m_pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(m_pMenu, 1);
				

		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			"StageBase_help_back_normal.png",
			"StageBase_help_back_pressed.png",
			"StageBase_help_back_normal.png",
			this,
			menu_selector(HelpLayer::backCallback));	

		pBack->setPosition(ccp(385, 58));	
		m_pMenu->addChild(pBack);

		// ½ûÖ¹ºó²ãµÄ°´¼ü
		this->setTouchEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

bool HelpLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_bInShow)
		return true;
	else
		return false;
}

void HelpLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);	
}




void HelpLayer::show()
{
	if(m_bInShow)
		return;

	m_bInShow = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMoveTo* pMoveDown = CCMoveTo::create(0.3, ccp(size.width / 2, size.height / 2));
	CCMoveTo* pMoveShakeBack = CCMoveTo::create(0.1, ccp(size.width / 2, size.height / 2 + SHAKE_DISTANCE));
	CCFiniteTimeAction* pSeq = CCSequence::create(pMoveDown, pMoveShakeBack,NULL);
	m_pColorLayer->setVisible(true);
	m_pFrame->runAction(pSeq);
}

void HelpLayer::backCallback( CCObject* pSender )
{
	restore();
}

void HelpLayer::restore()
{
	if(!m_bInShow)
		return;

	m_bInShow = false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();	
	CCMoveTo* pMoveUp = CCMoveTo::create(0.4, ccp(size.width / 2, m_pFrame->boundingBox().size.height / 2 + size.height));
	m_pColorLayer->setVisible(false);
	m_pFrame->runAction(pMoveUp);
}