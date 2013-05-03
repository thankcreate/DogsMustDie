#include "TopBannerLayer.h"
#include "Defines.h"
TopBannerLayer::TopBannerLayer() :
	m_pContentLabel(NULL),
	m_pFrame(NULL),
	m_bInShow(false)
{
	
}

bool TopBannerLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// ¿ò¼Ü
		setFrame(CCSprite::create());
		m_pFrame->initWithFile("StageBase_topbanner.png");
		CCSize frameSize = m_pFrame->boundingBox().size;
		m_pFrame->setPosition(ccp(450, size.height + frameSize.height / 2));
		this->addChild(m_pFrame);	

		setContentLabel(CCLabelTTF::create(" ", FONT_8BITOPERATOR_JVE, 30));	
		ccColor3B ccMyOrange={255, 104, 0};
		m_pContentLabel->setPosition(ccp(frameSize.width / 2,  frameSize.height / 2 + 3));
		m_pContentLabel->setDimensions(CCSizeMake(frameSize.width - 50, frameSize.height - 25));
		m_pContentLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
		m_pContentLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_pContentLabel->setColor(ccMyOrange);
		m_pFrame->addChild(m_pContentLabel);
		
		bRet = true;
	} while (0);
	return bRet;
}

void TopBannerLayer::setContent(char* input)
{
	m_pContentLabel->setString(input);
}

void TopBannerLayer::show()
{	
	if(m_bInShow)
		return;

	m_bInShow = true;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMoveTo* pMoveDown = CCMoveTo::create(0.5, ccp(450, size.height - m_pFrame->boundingBox().size.height / 2 + 2));			
	m_pFrame->runAction(pMoveDown);
}

void TopBannerLayer::restore()
{
	if(!m_bInShow)
		return;

	m_bInShow = false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMoveTo* pMoveUp = CCMoveTo::create(0.7, ccp(450, size.height + m_pFrame->boundingBox().size.height / 2 + 4));			
	m_pFrame->runAction(pMoveUp);
}

