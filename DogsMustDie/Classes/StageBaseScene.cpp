#include "StageBaseScene.h"
#include "Defines.h"
#include "AudioManager.h"
#include "StageBaseLayer.h"
#include "HelpLayer.h"
#include "RestartLayer.h"
#include "WinLayer.h"
#include "MyUseDefaultDef.h"
#include "StageSelectScene.h"

StageBaseScene::StageBaseScene() :
	m_pStageLayer(NULL),
	m_nBigLevel(0),
	m_nSmallLevel(0),
	m_pHelpLayer(NULL),
	m_pRestartLayer(NULL),
	m_pWinLayer(NULL)
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


// 设置本关的关卡号
// 可以显示在optionlayer 层的 title上
void StageBaseScene::setLevel(int big, int small1)
{
	m_nBigLevel = big;
	m_nSmallLevel = small1;
	//m_pOptionLayer->setLevelLabel(big,small1);
}

void StageBaseScene::showNavigator(bool isWin, int time, int unitLost)
{
	if(isWin)
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


		showNavigatorWin(time, unitLost);
	}
	else
	{
		showNavigatorLose(time, unitLost);
	}
}



void StageBaseScene::showNavigatorWin(int time, int unitLost)
{
	if(m_pWinLayer == NULL)
	{			
		setWinLayer(WinLayer::create());
		m_pWinLayer->setStageScene(this);
		this->addChild(m_pWinLayer, 10);
	}
	
	m_pWinLayer->setTime(time);
	m_pWinLayer->setLostUnit(unitLost);
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