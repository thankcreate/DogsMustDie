#include "PauseLayer.h"
#include "MyMenu.h"
#include "StageBaseScene.h"
#include "PauseLayerDelegate.h"

PauseLayer::PauseLayer() :
	m_pStageScene(NULL),
	m_pFrame(NULL),
	m_pColorLayer(NULL),
	m_pTitleLabel(NULL),
	m_pDelegate(NULL),
	m_bInShow(false)
{
}

bool PauseLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// ��ɫ��͸������
		ccColor4B color = ccc4(0, 0, 0, 190);
		setColorLayer(CCLayerColor::create(color));
		m_pColorLayer->setPosition(0, 0);
		m_pColorLayer->setContentSize(size);
		this->addChild(m_pColorLayer);

		// ���
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("Pause_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2 + size.height));
		this->addChild(m_pFrame);

		// ����		
		setTitleLabel(CCLabelTTF::create("Paused", "8bitoperator JVE.ttf", 45));		
		m_pTitleLabel->setPosition(ccp(192, 285));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTitleLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pTitleLabel);

		// ��ť
		MyMenu* pMenu = MyMenu::create();
		pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(pMenu, 1);

		CCMenuItemImage *pResume = new CCMenuItemImage();		
		pResume->initWithNormalImage(
			"Pause_btn_resume_normal.png",
			"Pause_btn_resume_pressed.png",
			"Pause_btn_resume_pressed.png",
			this,
			menu_selector(PauseLayer::resumeCallback));	

		pResume->setPosition(ccp(193, 169));	
		pMenu->addChild(pResume);

		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			"Pause_btn_menu_normal.png",
			"Pause_btn_menu_pressed.png",
			"Pause_btn_menu_pressed.png",
			this,
			menu_selector(PauseLayer::backCallback));	

		pBack->setPosition(ccp(90, 72));	
		pMenu->addChild(pBack);

		CCMenuItemImage *pRestart = new CCMenuItemImage();		
		pRestart->initWithNormalImage(
			"Pause_btn_restart_normal.png",
			"Pause_btn_restart_pressed.png",
			"Pause_btn_restart_pressed.png",
			this,
			menu_selector(PauseLayer::restartCallback));	

		pRestart->setPosition(ccp(288, 72));	
		pMenu->addChild(pRestart);

		// ��ֹ���İ���,��д�Ļ����ֶ�remove from dispatcher,�����಻�ᱻ����
		this->setTouchEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

void PauseLayer::resumeCallback( CCObject* object )
{
	restore();
	if(m_pDelegate)
		m_pDelegate->pauseLayerResumed();
}

void PauseLayer::restartCallback( CCObject* object )
{
	restore();
	if(m_pStageScene)
		m_pStageScene->opReStart();
}

void PauseLayer::backCallback( CCObject* object )
{
	restore();
	if(m_pStageScene)
		m_pStageScene->opGoBack();
}

void PauseLayer::show()
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

void PauseLayer::restore()
{
	m_bInShow = false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint nowTVPostion = m_pFrame->getPosition();
	CCMoveTo* pMoveUp = CCMoveTo::create(0.4, ccp(size.width / 2, m_pFrame->boundingBox().size.height / 2 + size.height));
	m_pColorLayer->setVisible(false);
	m_pFrame->runAction(pMoveUp);
}

bool PauseLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bInShow)
		return true;
	else
		return false;
}

void PauseLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);	
}

PauseLayer::~PauseLayer()
{
	int a  = 1;
	a++;
}