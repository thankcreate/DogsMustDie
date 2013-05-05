#include "DialogLayer.h"
#include "MyMenu.h"
#include "AudioManager.h"
#include "Defines.h"
#include "LocalizeManager.h"

DialogLayer::DialogLayer() :
	m_bInShow(false),
	m_pFrame(NULL),
	m_pMenu(NULL),
	m_pContentLabel(NULL)
{
}

DialogLayer::~DialogLayer()
{
	int a  = 1;
	a++;
}

bool DialogLayer::init()
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
		this->addChild(m_pColorLayer, 1);


		// 主框架
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("Dialog_frame.png");
		m_pFrame->setPosition(ccp(size.width / 2, size.height / 2));
		this->addChild(m_pFrame, 2);

		// 退出键
		setMenu(MyMenu::create());
		m_pMenu->setPosition(CCPointZero);	
		m_pFrame->addChild(m_pMenu, 1);


		CCMenuItemImage *pBack = new CCMenuItemImage();		
		pBack->initWithNormalImage(
			"Dialog_ok_normal.png",
			"Dialog_ok_pressed.png",
			"Dialog_ok_pressed.png",
			this,
			menu_selector(DialogLayer::okCallback));	

		pBack->setPosition(ccp(388, 62));	
		m_pMenu->addChild(pBack);

		// 内容
		setContentLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, 35));	
		ccColor3B ccMyOrange={255, 104, 0};
		CCSize frameSize = m_pFrame->boundingBox().size;
		m_pContentLabel->setPosition(ccp(frameSize.width / 2 - 5, 158));
		m_pContentLabel->setDimensions(CCSizeMake(391, 128));
		m_pContentLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
		m_pContentLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pContentLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pContentLabel);

		// 禁止后层的按键,不写的话得手动remove from dispatcher,否则本类不会被析构
		this->setTouchEnabled(true);

		this->setVisible(false);

		bRet = true;
	}while(0);

	return bRet;
}

bool DialogLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_bInShow)
		return true;
	else
		return false;
}

void DialogLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);	
}

void DialogLayer::show()
{
	if(m_bInShow)
		return;

	m_bInShow = true;	

	CCScaleTo* pScaleOut = CCScaleTo::create(0.15, 1.3);
	CCScaleTo* pScaleBack = CCScaleTo::create(0.15, 1);
	
	CCFiniteTimeAction* pSeq = CCSequence::create(pScaleOut, pScaleBack,NULL);
	m_pColorLayer->setVisible(true);
	m_pFrame->runAction(pSeq);
	this->setVisible(true);
}

void DialogLayer::okCallback( CCObject* pSender )
{	
	restore();
}

void DialogLayer::restore()
{
	PlayEffect("Audio_button.mp3");
	if(!m_bInShow)
		return;

	m_bInShow = false;	
	this->setVisible(false);
}


void DialogLayer::setContent(const char* input)
{
	m_pContentLabel->setString(input);
}