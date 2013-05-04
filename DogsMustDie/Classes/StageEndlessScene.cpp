#include "StageEndlessScene.h"
#include "StageEndlessLayer.h"
#include "StageMap.h"
#include "StartupScene.h"
#include "StageEndlessRestartLayer.h"
#include "StageEndlessWinLayer.h"
#include "StageBaseScene.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"
#include "NoticeLayer.h"
#include "TopBannerLayer.h"
#include "LocalizeManager.h"

#include <time.h>

StageEndlessScene::StageEndlessScene() :
	m_nEndlessRound(0),
	m_pNoticeLayer(NULL)
{
}

StageBaseLayer* StageEndlessScene::getMainStageLayer()
{
	return StageEndlessLayer::create();
}

const char* StageEndlessScene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}

bool StageEndlessScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		setStageBaseLayer(getMainStageLayer());
		getStageBaseLayer()->setParentScene(this);		
		this->addChild(getStageBaseLayer());

		StageEndlessLayer* pLayer = (StageEndlessLayer*) getStageBaseLayer();
		pLayer->initWithRound(m_nEndlessRound);
				
		playBGM();
		bRet = true;
	} while (0);
	return bRet;
}



void StageEndlessScene::opReStart()
{	
	m_nEndlessRound = 0;
	this->removeChild(m_pStageLayer,true);

	init();
}

void StageEndlessScene::continueRestartWithThisRound()
{
	this->removeChild(m_pStageLayer,true);
	init();
}

void StageEndlessScene::gotoNext()
{
	m_nEndlessRound ++;
	this->removeChild(m_pStageLayer,true);

	// Caution: 此处并不remove掉小电视那一层
	// 因为小电视自己需要一个退出动画，不能在restart时立即销毁	
	init();
}

void StageEndlessScene::opGoBack()
{
	CCScene* stage = StartupScene::create();						
	CCDirector::sharedDirector()->replaceScene(stage);
}

void StageEndlessScene::showNoticeLayer()
{
	if(m_pNoticeLayer == NULL)
	{			
		setNoticeLayer(NoticeLayer::create());		
		this->addChild(m_pNoticeLayer, 10);		
		m_pNoticeLayer->setStageScene(this);
	}
	m_pNoticeLayer->setDelegate((StageEndlessLayer*)m_pStageLayer);
	m_pNoticeLayer->show();
	m_pStageLayer->stopUpdate();
}

void StageEndlessScene::showNavigator( bool isWin, int time, int unitLost)
{
	if(isWin)
	{
		showNavigatorWin(0,0);
	}
	else
	{
		showNavigatorLose(0,0);
	}
}


void StageEndlessScene::showNavigatorWin(int time, int unitLost)
{
	int best = LoadIntegerFromXML(KEY_ENDLESS_BEST_ROUND, 0);
	if(m_nEndlessRound > best)
	{
		SaveIntegerToXML(KEY_ENDLESS_BEST_ROUND, m_nEndlessRound );
        SaveUserDefault();
	}


	if(m_pWinLayer == NULL)
	{			
		setWinLayer(StageEndlessWinLayer::create());
		getWinLayer()->setStageScene(this);
		this->addChild(m_pWinLayer, 10);
	}

	getWinLayer()->setRound(m_nEndlessRound);	
	getWinLayer()->show();	
}


void StageEndlessScene::showNavigatorLose(int time, int unitLost)
{
	if(m_pRestartLayer == NULL)
	{
		setRestartLayer(StageEndlessRestartLayer::create());
		getRestartLayer()->setStageScene(this);		
		this->addChild(getRestartLayer(), 10);
	}		
	getRestartLayer()->setRound(m_nEndlessRound);	
	getRestartLayer()->show();
}

void StageEndlessScene::customizeTopBannerLayer()
{
	if(!getTopBannerLayer())
		return;

	CCSprite* frame = getTopBannerLayer()->getFrame();
	if(!frame)
		return;

	CCSize frameSize = frame->boundingBox().size;

	CCLabelTTF* pLabel = CCLabelTTF::create(I18N_STR("Endless_Daily_Award"), FONT_8BITOPERATOR_JVE, 30);
	ccColor3B ccMyOrange={255, 104, 0};
	pLabel->setPosition(ccp(300,  frameSize.height / 2 + 3));
	pLabel->setDimensions(CCSizeMake(frameSize.width - 50, frameSize.height - 25));
	pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	pLabel->setColor(ccMyOrange);
	frame->addChild(pLabel,10);

	CCSprite* pSprite = CCSprite::create("Coin.png");
	pSprite->setPosition(ccp(95,33));
	frame->addChild(pSprite,10);

	
	//m_pTopBannerLayer->addChild(m_pContentLabel);
	
}



