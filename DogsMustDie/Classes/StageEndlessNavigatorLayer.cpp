#include "StageEndlessNavigatorLayer.h"
#include "StageBaseScene.h"
#include "AudioManager.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"

StageEndlessNavigatorLayer::StageEndlessNavigatorLayer() :
	m_nRound(0),
	m_pRoundLabel(NULL),
	m_pBestRoundLabel(NULL)
{

}

StageEndlessNavigatorLayer::~StageEndlessNavigatorLayer()
{

}

bool StageEndlessNavigatorLayer::init()
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
		setTitleLabel(CCLabelTTF::create(pStrTitle->getCString(), FONT_8BITOPERATOR_JVE, 45));		
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



