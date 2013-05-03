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

		checkIfNeedToAddDailyCoin();
		
		playBGM();
		bRet = true;
	} while (0);
	return bRet;
}

void StageEndlessScene::checkIfNeedToAddDailyCoin()
{
	time_t rawtime;
	struct tm * tmInfo;
	time (&rawtime);

	tmInfo = localtime(&rawtime);
	int year = tmInfo->tm_year + 1900;
	int month = tmInfo->tm_mon + 1;
	int day = tmInfo->tm_mday;

	//CCString* test = CCString::createWithFormat("Month: %d  Day %d", month, day);
	//CCMessageBox(test->getCString(),"");
	int lastYear = LoadIntegerFromXML(KEY_LAST_ENDLESS_DATE_YEAR , -1);
	int lastMonth = LoadIntegerFromXML(KEY_LAST_ENDLESS_DATE_MONTH , -1);
	int lastDay = LoadIntegerFromXML(KEY_LAST_ENDLESS_DATE_DAY , -1);

	if(	lastYear != year
		|| lastMonth != month
		|| lastDay != day )
	{		
		// �ߵ�����˵���ǽ��յ�һ�ε�½���޾�ģʽ
		int coin = LoadIntegerFromXML(KEY_COIN_COUNT, 0);
		++coin;
		SaveIntegerToXML(KEY_COIN_COUNT, coin);
		SaveIntegerToXML(KEY_LAST_ENDLESS_DATE_YEAR, year);
		SaveIntegerToXML(KEY_LAST_ENDLESS_DATE_MONTH, month);
		SaveIntegerToXML(KEY_LAST_ENDLESS_DATE_DAY, day);
		SaveUserDefault();
		showTopBannerLayerWithCustomizedContent(3);		
	}	
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

	// Caution: �˴�����remove��С������һ��
	// ��ΪС�����Լ���Ҫһ���˳�������������restartʱ��������	
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

	CCLabelTTF* pLabel = CCLabelTTF::create("+1.  Daily award. ^_^", "8bitoperator JVE.ttf", 30);	
	ccColor3B ccMyOrange={255, 104, 0};
	pLabel->setPosition(ccp(frameSize.width / 2 + 10,  frameSize.height / 2 + 3));
	pLabel->setDimensions(CCSizeMake(frameSize.width - 50, frameSize.height - 25));
	pLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	pLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	pLabel->setColor(ccMyOrange);
	frame->addChild(pLabel,10);

	CCSprite* pSprite = CCSprite::create("Coin.png");
	pSprite->setPosition(ccp(95,33));
	frame->addChild(pSprite,10);

	
	//m_pTopBannerLayer->addChild(m_pContentLabel);
	
}


