//
//  DogsMustDieAppDelegate.cpp
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-15.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "StartupScene.h"
#include "SimpleAudioEngine.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"
#include "StageStartupCGScene.h"
#include "LocalizeManager.h"
#include "StageGameOverScene.h"
#include "IOSWrapper.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
	// Base on 800x480
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800, 480, kResolutionExactFit);
    
    // 国际化init
    // 目前的逻辑为图简单，只在启动时做load
    // 也就是说如果中途切换环境语言，游戏内语言不变
    LocalizeManager::sharedInstance()->initLoad();

	// 第一次时，启动cg页
	bool bFirstLauch = LoadBooleanFromXML(KEY_FIRST_LAUNCH, true);
	CCScene *pScene = NULL;
	if(bFirstLauch)
	{
		SaveBooleanToXML(KEY_FIRST_LAUNCH, false);
		SaveUserDefault();
		pScene = StageStartupCGScene::create();
// 		pScene = StageGameOverScene::create();
	}
	else
	{
		pScene = StartupScene::create(); 
	}

    // run
    pDirector->runWithScene(pScene);
    
    // 增加启动次数
    int nLaunchCount = LoadIntegerFromXML(KEY_LAUNCH_COUNT, 0);
    ++nLaunchCount;
    SaveIntegerToXML(KEY_LAUNCH_COUNT, nLaunchCount);
    SaveUserDefault();
    checkIfNeedShowRateUSDialog();

	// 调试参数开关
	pDirector->setDisplayStats(false);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (IOSWrapper::isProVersion()) {
        // 如果本身就是收费版
        SaveBooleanToXML(KEY_PRO_UPGRADE_PURCHASED, true);
        SaveUserDefault();
    }
#endif
    
    


    return true;
}

void AppDelegate::checkIfNeedShowRateUSDialog()
{
    int nLaunchCount = LoadIntegerFromXML(KEY_LAUNCH_COUNT, 0);
    
    if(nLaunchCount == 3)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        IOSWrapper::sharedInstance()->showRateUSDialog();
#endif
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
