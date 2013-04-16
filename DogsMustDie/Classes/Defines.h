//
//  Defines.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-15.
//
//

#ifndef DogsMustDie_Header_h
#define DogsMustDie_Header_h


#include "cocos2d.h"

// CCUserDefault
#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveUserDefault CCUserDefault::sharedUserDefault()->flush
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey

// Audio
#define PreloadEffect(param) AudioManager::getSharedInstance()->preloadEffect(param)
#define PlayEffect(param) AudioManager::getSharedInstance()->playEffect(param)
#define PlayBGM(param)  AudioManager::getSharedInstance()->playBackgroundMusic(param)

// Sprite
// 我要把tag掰成两部分用，高位用来做type,低位用来做tag
#define INT_BIT_LENTH (sizeof(int) * 8)
#define INT_BIT_LENTH_HALF (sizeof(int) * 4)
#define RAW_TAG(p) ((unsigned int)(p->getTag()))
#define GET_TYPE(p) (RAW_TAG(p) >> INT_BIT_LENTH_HALF)
#define GET_TAG(p) ((RAW_TAG(p)  << INT_BIT_LENTH_HALF) >> INT_BIT_LENTH_HALF)


#define SET_TYPE(p, mytype) p->setTag(((RAW_TAG(p)  << INT_BIT_LENTH_HALF) >> INT_BIT_LENTH_HALF) | (mytype <<  INT_BIT_LENTH_HALF) )
#define SET_TAG(p, tag)  p->setTag( ( (RAW_TAG(p) >> INT_BIT_LENTH_HALF) << INT_BIT_LENTH_HALF) | tag )


// other
#define WIN_SIZE (CCDirector::sharedDirector()->getWinSize())


#endif
