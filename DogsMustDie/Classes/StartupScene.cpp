//
//  StartupScene.cpp
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#include "StartupScene.h"
#include "AudioManager.h"
#include "Defines.h"
using namespace cocos2d;

StartupScene::StartupScene(void) :
    _startupLayer(NULL)
{
    
}

StartupScene::~StartupScene(void)
{
}

bool StartupScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		_startupLayer = StartupLayer::create();
		this->addChild(_startupLayer, 0);
		bRet = true;
		PlayBGM("Audio_bgm_home.mp3");
	} while (0);
	return bRet;
}
