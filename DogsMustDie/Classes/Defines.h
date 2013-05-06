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

// cocos2d - box2d
#define PTM_RATIO 24.0f

// object type
enum eGameObjectType
{	
	kGameObjectFight,
	kGameObjectStar
};

enum eFightType
{
	kFightPlanet,
	kFightTroops
};

enum eTroopsType
{
	kTroopsComomon,
	kTroopsForStar
};

enum eForceSide
{
	kForceSideCat,
	kForceSideDog,
	kForceSideThird, // Third是第三方,会主动攻击
	kForceSideMiddle,  // Middle是中立，不会主动攻击
};

// CCUserDefault
#define SaveStringToXML cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveUserDefault cocos2d::CCUserDefault::sharedUserDefault()->flush
#define SaveBooleanToXML cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey
#define LoadStringFromXML cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFromXML cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey

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


// Other
#define WIN_SIZE (CCDirector::sharedDirector()->getWinSize())
#define HIT(prob) MiscTool::probabilityHit(prob)
#define STAR_PRELOAD_LOCATION(x, y) m_vecPossibleStarLocations.push_back(ccp(x,y))

// Stage
#define BIG_STAGE_COUNT 3
#define SMALL_STAGE_COUNT 9
#define ENDLESS_COUNT 99999

// i18n
#define CUR_LANG CCApplication::sharedApplication()->getCurrentLanguage()
#define I18N_FILE(name) LocalizeManager::makeResourceFileName(name)
#define I18N_STR(key) LocalizeManager::sharedInstance()->getStringByKey(key)

// Font
// 这是之所以要区分iOS是因为cocos2d 2.0之后
// 貌似iOS上的CCLabelTTF使用font时不能带ttf后缀
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define FONT_8BITOPERATOR_JVE "8bitoperator JVE"
#define FONT_00_STARMAP_TRUETYPE "00 Starmap Truetype"
#else 
#define FONT_8BITOPERATOR_JVE "8bitoperator JVE.ttf"
#define FONT_00_STARMAP_TRUETYPE "00 Starmap Truetype.ttf"
#endif

// IAP
#define AppPurchaseProUpgradeProductId  "com.thankcreate.DogsMustDie.UpgradeToPro"
#define AppPurchaseCoin10_Pro "com.thankcreate.DogsMustDie.10Coins"
#define AppPurchaseCoin10_Lite "com.thankcreate.DogsMustDie.10CoinsLite"
#define AppPurchaseCoin20_Pro "com.thankcreate.DogsMustDie.20Coins"
#define AppPurchaseCoin20_Lite "com.thankcreate.DogsMustDie.20CoinsLite"
#define AppPurchaseCoin50_Pro "com.thankcreate.DogsMustDie.50Coins"
#define AppPurchaseCoin50_Lite "com.thankcreate.DogsMustDie.50CoinsLite"

#define LOCK_BEGIN_INDEX 2

#endif
