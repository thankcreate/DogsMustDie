#include "StageSelectScene.h"
//#include "AudioManager.h"
#include "Defines.h"
using namespace cocos2d;

StageSelectScene::StageSelectScene(void)
{

}

StageSelectScene::~StageSelectScene(void)
{
}

bool StageSelectScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		_stage1Layer = StageSelectLayer::create();
		this->addChild(_stage1Layer, 0);

		//PlayBGM("Audio_bgm_home.mp3");
		bRet = true;
	} while (0);
	return bRet;
}
