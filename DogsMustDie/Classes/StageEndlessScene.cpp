#include "StageEndlessScene.h"
#include "StageEndlessLayer.h"
#include "StageMap.h"
#include "StartupScene.h"
#include "StageEndlessRestartLayer.h"
#include "StageEndlessWinLayer.h"
#include "StageBaseScene.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"
StageEndlessScene::StageEndlessScene() :
	m_nEndlessRound(0)
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

