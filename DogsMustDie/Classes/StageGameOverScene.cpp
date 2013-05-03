//
//  StageGameOverScene.cpp
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#include "StageGameOverScene.h"
#include "AudioManager.h"
#include "Defines.h"
using namespace cocos2d;

StageGameOverScene::StageGameOverScene(void) :
_StageGameOverLayer(NULL)
{
}

StageGameOverScene::~StageGameOverScene(void)
{
}

bool StageGameOverScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		_StageGameOverLayer = StageGameOverLayer::create();
		this->addChild(_StageGameOverLayer, 0);
		bRet = true;
		PlayBGM("Audio_bgm_stage_4.mp3");
	} while (0);
	return bRet;
}
