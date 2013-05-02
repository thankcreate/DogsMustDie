#include "StageBaseScene.h"
#include "Defines.h"
#include "AudioManager.h"
#include "StageBaseLayer.h"
#include "HelpLayer.h"
#include "RestartLayer.h"
#include "WinLayer.h"
#include "MyUseDefaultDef.h"
#include "StageSelectScene.h"
#include "MiscTool.h"
#include "StageMap.h"
#include "PauseLayer.h"

StageBaseScene::StageBaseScene() :
	m_pStageLayer(NULL),
	m_nBigLevel(0),
	m_nSmallLevel(0),
	m_pHelpLayer(NULL),
	m_pRestartLayer(NULL),
	m_pWinLayer(NULL),
	m_pPauseLayer(NULL)
{

}

StageBaseScene::~StageBaseScene()
{

}

bool StageBaseScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		m_pStageLayer = getMainStageLayer();
		m_pStageLayer->setParentScene(this);		
		this->addChild(m_pStageLayer);
		
		if(m_nBigLevel > 0 && m_nSmallLevel > 0)
		{
			m_pStageLayer->setLevel(m_nBigLevel, m_nSmallLevel);
		}
		
		playBGM();
		bRet = true;
	} while (0);
	return bRet;
}

void StageBaseScene::playBGM()
{
	const char * fileName = getBGMFileName();
	if(fileName != NULL)
		PlayBGM(fileName);
}

const char* StageBaseScene::getBGMFileName()
{	
	return "Audio_bgm_stage_2.mp3";
}



void StageBaseScene::opGoBack()
{
	CCScene* stage1 = StageSelectScene::create();						
	CCDirector::sharedDirector()->replaceScene(stage1);
}

void StageBaseScene::opReStart()
{
	this->removeChild(m_pStageLayer,true);
	// TODO

	// Caution: 此处并不remove掉小电视那一层
	// 因为小电视自己需要一个退出动画，不能在restart时立即销毁	
	init();
}

void StageBaseScene::opSound(bool isOn)
{
	AudioManager::getSharedInstance()->enableSoundAndMusic(isOn);
}


void StageBaseScene::showHelpLayer()
{
	if(m_pHelpLayer == NULL)
	{			
		setHelpLayer(HelpLayer::create());		
		this->addChild(m_pHelpLayer, 10);		
	}
	m_pHelpLayer->setDelegate(m_pStageLayer);
	m_pHelpLayer->show();	
}

void StageBaseScene::showPauseLayer()
{
	if(m_pPauseLayer == NULL)
	{			
		setPauseLayer(PauseLayer::create());		
		this->addChild(m_pPauseLayer, 10);		
		m_pPauseLayer->setStageScene(this);
	}
	m_pPauseLayer->setDelegate(m_pStageLayer);
	m_pPauseLayer->show();
}

// 设置本关的关卡号
// 可以显示在optionlayer 层的 title上
void StageBaseScene::setLevel(int big, int small1)
{
	m_nBigLevel = big;
	m_nSmallLevel = small1;
	m_pStageLayer->setLevel(big, small1);
}

void StageBaseScene::showNavigator(bool isWin, int time, int unitLost)
{
	if(isWin)
	{
		showNavigatorWin(time, unitLost);
	}
	else
	{
		showNavigatorLose(time, unitLost);
	}
}



void StageBaseScene::showNavigatorWin(int time, int unitLost)
{
	int toBig = LoadIntegerFromXML(KEY_PLAYED_TO_BIG, 1);
	int toSmall =  LoadIntegerFromXML(KEY_PLAYED_TO_SMALL, 1);

	int zeroBasedIndex = (m_nBigLevel -  1 ) * SMALL_STAGE_COUNT + m_nSmallLevel - 1;
	int toZeroBasedIndex = zeroBasedIndex + 1;
	int bigIndex = toZeroBasedIndex / SMALL_STAGE_COUNT + 1;
	int smallIndex = toZeroBasedIndex % SMALL_STAGE_COUNT + 1;

	if(bigIndex > toBig )
	{
		SaveIntegerToXML(KEY_PLAYED_TO_BIG, bigIndex);
		SaveIntegerToXML(KEY_PLAYED_TO_SMALL, smallIndex);
		SaveUserDefault();
	}
	else if(bigIndex == toBig &&  smallIndex > toSmall)
	{
		SaveIntegerToXML(KEY_PLAYED_TO_BIG, bigIndex);
		SaveIntegerToXML(KEY_PLAYED_TO_SMALL, smallIndex);
		SaveUserDefault();	
	}

	int scoreStarCount= getScoreStartCount(time, unitLost);
	MiscTool::saveScoreForLevel(m_nBigLevel, m_nSmallLevel, scoreStarCount);

	if(m_pWinLayer == NULL)
	{			
		setWinLayer(WinLayer::create());
		m_pWinLayer->setStageScene(this);
		this->addChild(m_pWinLayer, 10);
	}
	
	
	m_pWinLayer->setTime(time);
	m_pWinLayer->setLostUnit(unitLost);
	m_pWinLayer->setScoreStarCount(scoreStarCount);
	m_pWinLayer->show();	
}


void StageBaseScene::showNavigatorLose(int time, int unitLost)
{
	if(m_pRestartLayer == NULL)
	{
		setRestartLayer(RestartLayer::create());
		m_pRestartLayer->setStageScene(this);		
		this->addChild(m_pRestartLayer, 10);
	}	
	m_pRestartLayer->setTime(time);
	m_pRestartLayer->setLostUnit(unitLost);
	m_pRestartLayer->show();
}

// 1 ~ 3
// 只要赢了至少给个1星吧
int StageBaseScene::getScoreStartCount(int time , int unitLost)
{
	int judgeTime = getJudgeScoreTime();
	if(time > judgeTime  + 26)
		return 1;
	else if(time > judgeTime + 10)
		return 2;
	else 
		return 3;
}




// gotoNext现在统一由BigLevel和SmallLevel来推断
// 一般不由子类重写
void StageBaseScene::gotoNext()
{
	if(m_nBigLevel <=0 || m_nSmallLevel <= 0)
		return;

	// 注意，BigLevel和SmallLevel是从1开始计数
	// 但是此处推演时以0开始计数
	int zeroBasedIndex = (m_nBigLevel -  1 ) * SMALL_STAGE_COUNT + m_nSmallLevel - 1 + 1;	
	int bigIndex = zeroBasedIndex / SMALL_STAGE_COUNT + 1;
	int smallIndex = zeroBasedIndex % SMALL_STAGE_COUNT + 1;

	StageMap::sharedInstance()->gotoStage(bigIndex, smallIndex);

	// TODO 边界情况目前未处理，最后一关，通过画面

}
