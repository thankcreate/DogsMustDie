//
//  StageStartupCGScene.cpp
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#include "StageStartupCGScene.h"
#include "AudioManager.h"
#include "Defines.h"
using namespace cocos2d;

StageStartupCGScene::StageStartupCGScene(void) :
_StageStartupCGLayer(NULL)
{
}

StageStartupCGScene::~StageStartupCGScene(void)
{
}

bool StageStartupCGScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		_StageStartupCGLayer = StageStartupCGLayer::create();
		this->addChild(_StageStartupCGLayer, 0);
		bRet = true;
		PlayBGM("Audio_bgm_startup_cg.mp3");
	} while (0);
	return bRet;
}
