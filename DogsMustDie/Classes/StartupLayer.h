//
//  StartupLayer.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StartupLayer__
#define __DogsMustDie__StartupLayer__

#include "cocos2d.h"

using namespace cocos2d;

class DialogLayer;

class StartupLayer : public CCLayer
{
public:
	StartupLayer(void);
	~StartupLayer(void);
	CREATE_FUNC(StartupLayer);

	CC_SYNTHESIZE(DialogLayer*, m_pDialogLayer, DialogLayer);
    
	bool init();
    
	void startCallback(CCObject* pSender);
	void optionCallback(CCObject* pSender);
	void aboutCallback(CCObject* pSender);
	void endlessCallback(CCObject* pSender);

	void gameCenterCallback(CCObject* pSender);
	void rateUsCallback(CCObject* pSender);
    
    // 目前仅对iOS版有效，评分
    void rateusCallback(CCObject* pSender);
    
	// 目前仅对安卓有效，后退时退出
	void keyBackClicked();

	CC_SYNTHESIZE(CCSprite*, m_pCatPlanet, CatPlanet);
	CC_SYNTHESIZE(CCSprite*, m_pDogPlanet, DogPlanet);

	void shakePlanets();
	void showEndlessNotAllowedDialog();
};


#endif /* defined(__DogsMustDie__StartupLayer__) */

