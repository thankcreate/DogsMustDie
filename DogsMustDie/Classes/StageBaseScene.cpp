#include "StageBaseScene.h"
#include "Defines.h"
#include "AudioManager.h"
#include "StageBaseLayer.h"
#include "HelpLayer.h"

StageBaseScene::StageBaseScene() :
	m_pStageLayer(NULL),
	m_nBigLevel(0),
	m_nSmallLevel(0),
	m_pHelpLayer(NULL)
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
	return NULL;
	//return "Audio_bgm_1.mp3";
}



void StageBaseScene::opGoBack()
{
	CCScene* stage1 = StageBaseScene::create();						
	CCDirector::sharedDirector()->replaceScene(stage1);
}

void StageBaseScene::opReStart()
{
	this->removeChild(m_pStageLayer,true);
	// TODO

	// Caution: �˴�����remove��С������һ��
	// ��ΪС�����Լ���Ҫһ���˳�������������restartʱ��������	
	init();
}

void StageBaseScene::opSound(bool isOn)
{
	AudioManager::getSharedInstance()->enableSoundAndMusic(isOn);
}


// ���ñ��صĹؿ���
// ������ʾ��optionlayer ��� title��
void StageBaseScene::setLevel(int big, int small1)
{
	m_nBigLevel = big;
	m_nSmallLevel = small1;
}

void StageBaseScene::showHelpLayer()
{
	if(m_pHelpLayer == NULL)
	{			
		setHelpLayer(HelpLayer::create());		
		this->addChild(m_pHelpLayer, 10);
	}
	m_pHelpLayer->show();	
}