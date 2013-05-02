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

    // create a scene. it's an autorelease object
    

	// 第一次时，启动cg页
	bool bFirstLauch = LoadBooleanFromXML(KEY_FIRST_LAUNCH, true);
	CCScene *pScene = NULL;
	if(bFirstLauch)
	{
		SaveBooleanToXML(KEY_FIRST_LAUNCH, false);
		SaveUserDefault();
		pScene = StageStartupCGScene::create();    
	}
	else
	{
		pScene = StartupScene::create(); 
	}

    // run
    pDirector->runWithScene(pScene);

	// 调试参数开关
	pDirector->setDisplayStats(false);

    return true;
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
