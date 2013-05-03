#include "NoticeLayer.h"
#include "MyMenu.h"
#include "StageBaseScene.h"
#include "NoticeLayerDelegate.h"

#define MAX_INDEX 2

NoticeLayer::NoticeLayer() :
	m_pStageScene(NULL),
	m_pFrame(NULL),
	m_pColorLayer(NULL),
	m_pTitleLabel(NULL),
	m_pDelegate(NULL),
	m_bInShow(false),
	m_pContentLabel(NULL),
	m_nProcessIndex(0)
{
}

bool NoticeLayer::init()
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
		m_pFrame->initWithFile("Pause_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2 + size.height));
		this->addChild(m_pFrame);

		// 标题		
		setTitleLabel(CCLabelTTF::create("Notice", "8bitoperator JVE.ttf", 45));		
		m_pTitleLabel->setPosition(ccp(192, 285));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pTitleLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pTitleLabel);

		setContentLabel(CCLabelTTF::create("^_^\nWelcome to the endless mode.\nIt's a chance to prove you are the bravest cat.", "8bitoperator JVE.ttf", 28));		
		m_pContentLabel->setPosition(ccp(200, 160));
		m_pContentLabel->setDimensions(CCSizeMake(324, 160));
		m_pContentLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
		m_pContentLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pContentLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pContentLabel);

		// 按钮
		MyMenu* pMenu = MyMenu::create();
		pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(pMenu, 1);

		CCMenuItemImage *pNext = new CCMenuItemImage();		
		pNext->initWithNormalImage(
			"Notice_btn_next_normal.png",
			"Notice_btn_next_pressed.png",
			"Notice_btn_next_pressed.png",
			this,
			menu_selector(NoticeLayer::nextCallback));	

		pNext->setPosition(ccp(312, 58));	
		pMenu->addChild(pNext);


		// 禁止后层的按键,不写的话得手动remove from dispatcher,否则本类不会被析构
		this->setTouchEnabled(true);

		bRet = true;
	}while(0);

	return bRet;
}

void NoticeLayer::nextCallback( CCObject* object )
{
	++m_nProcessIndex;
	if(m_nProcessIndex == 1)
	{
		m_pContentLabel->setString("If you fail by accident. You can use 1 coin to continue for a second chance. You'll get 1 free coin every day");
	}
	else if(m_nProcessIndex == 2)
	{
		m_pContentLabel->setString("We highly recommend that you play story mode first.\nGood luck ,sir!\nGod bless cats..meow~");
	}
	else if(m_nProcessIndex > MAX_INDEX)
	{
		restore();
	}	
}


void NoticeLayer::show()
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

void NoticeLayer::restore()
{
	m_bInShow = false;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint nowTVPostion = m_pFrame->getPosition();
	CCMoveTo* pMoveUp = CCMoveTo::create(0.4, ccp(size.width / 2, m_pFrame->boundingBox().size.height / 2 + size.height));
	m_pColorLayer->setVisible(false);
	m_pFrame->runAction(pMoveUp);

	if(m_pDelegate)
		m_pDelegate->noticeLayerFinished();
}

bool NoticeLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bInShow)
		return true;
	else
		return false;
}

void NoticeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);	
}

NoticeLayer::~NoticeLayer()
{
	int a  = 1;
	a++;
}
